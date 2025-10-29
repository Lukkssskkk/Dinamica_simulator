#include"simulator.hpp"

sf::Clock time_pf;
float ts=0.0f;

Dinamica::Dinamica(float x, float y){
    //Get font:
    if(font.openFromFile("../img/font.ttf")){std::cout << "Font imported\n";}
    //Textures:
    if(info_t.loadFromFile("../img/info.png")){std::cout<<"info texture imported\n";}
    if(menu_t.loadFromFile("../img/menu.png")){std::cout<<"menu texture imported\n";}
    //mouse:
    mouse.setSize({1,1});
    //Button menu:
    button_menu.setSize({25.f,25.f});
    button_menu.setTexture(&menu_t);
    button_menu.setPosition({0,0});
    //Button infos:
    button_info.setSize({25.f,25.f});
    button_info.setTexture(&info_t);
    button_info.setPosition({x-25.f,0.f});
    //Button start:
    startsm.setSize({25.f,25.f});
    startsm.setFillColor(sf::Color::Blue);
    startsm.setPosition({x/2-12.5f,0.f});
    //Button Restart:
    reset_button.setSize({25.f,25.f});
    reset_button.setFillColor(sf::Color::Red);
    reset_button.setPosition({x/2+20.f,0.f});
    //VARS:
    d=false;
    isclicked=false;
    timeperframe=1.f;
    s=0;
    selection=-1;
    text=false;
    g=-1;
    fo=true;
    help_b=false;
    start_b=false;
    restart_b=false;
}

void Dinamica::run(sf::RenderWindow &win){
    Help Mhelp(win);
    while(win.isOpen()){

        isclicked=false;

        processEvents(win);
        Draw(win,Mhelp);
        sf::sleep(sf::milliseconds(10));
    }
}

void Dinamica::processEvents(sf::RenderWindow &win){
    mouse.setPosition({(float)sf::Mouse::getPosition(win).x,(float)sf::Mouse::getPosition(win).y});
    while(const std::optional ev = win.pollEvent()){
        if(ev->is<sf::Event::Closed>()){
            win.close();
        }
        else if(const auto* mousePressed = ev->getIf<sf::Event::MouseButtonReleased>()){
            if(mousePressed->button == sf::Mouse::Button::Left){
                isclicked=true;
            }
        }
        else if(const auto* textEntered = ev->getIf<sf::Event::TextEntered>()) {
            if (text) {
                char c = static_cast<char>(textEntered->unicode);
                if (c == 8 && !input_text.empty()) {
                    input_text.pop_back();
                } else if (std::isprint(c)) {
                    input_text += c;
                }
            }
        }
        else if (const auto* keyPressed = ev->getIf<sf::Event::KeyReleased>()) {
            if(keyPressed->scancode == sf::Keyboard::Scan::Enter){
                if(text){
                    input_text.clear();
                    text=false;
                    if(d){
                    fo = !fo;
                    }
                }
            }
        }
    }
}

void Dinamica::Draw(sf::RenderWindow &win, Help &Mhelp){
    if(!help_b){
        win.clear(sf::Color::White);
        float tr = time_pf.restart().asSeconds();
        ts += ts/timeperframe;
        for(int i=0;i<corps.size();i++){
            if(restart_b){
                start_b=false;
                corps[i].shape.setPosition(corps[i].origin);
            }
            else if(!start_b){
                corps[i].origin=corps[i].shape.getPosition();
            }
            else if (ts >= 1.0f) {
                corps[i].run();
                ts = 0.0f;
            }
            corps[i].draw(win);
        }

        if(button_click(button_menu) && s!=1){
            s=1;
        }
        else if(button_click(button_info) && s!=2){
            s=2;
        }
        else if( (button_click(button_info) && s==2) || (s==1 && button_click(button_menu)) ){
            s=0;
        }
        if(button_click(startsm)){
            start_b= !start_b;
        }
        if(button_click(reset_button)){
            restart_b = !restart_b;
        }

        if(s==2){
            infos(win);
        }
        else if(s==1){
            menu(win);
        }

        win.draw(button_info);
        win.draw(button_menu);
        win.draw(startsm);
        win.draw(reset_button);
        win.display();
    }
    else{
        help_b = Mhelp.draw(win);
    }
}

void Dinamica::colision(sf::RenderWindow &win){
    for(int i=0; i < corps.size();i++){
        for(int j=0; j < corps.size();j++){
            if(corps[i].shape.getGlobalBounds().findIntersection(corps[j].shape.getGlobalBounds())){
                corps[i].vel={0.f,0.f};
                corps[i].force={0.f,0.f};
                corps[i].acel={0.f,0.f};

                corps[j].vel={0.f,0.f};
                corps[j].force={0.f,0.f};
                corps[j].acel={0.f,0.f};
            }
        }
    }
}