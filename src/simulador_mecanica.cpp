#include"simulador_dinamica.hpp"

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
    //VARS:
    isclicked=false;
    s=0;
    selection=-1;
    text=false;
    g=-1;
    f=true;
}

void Dinamica::run(sf::RenderWindow &win){
    while(win.isOpen()){

        isclicked=false;

        processEvents(win);
        Draw(win);
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
                    if(d==true){
                        if(f==true){
                            f=false;
                        }else{
                            f=true;
                        }
                    }
                }
            }
        }
    }
}



void Dinamica::Draw(sf::RenderWindow &win){
    win.clear(sf::Color::White);

    if(button_click(button_menu) && s!=1){
        s=1;
    }
    else if(button_click(button_info) && s!=2){
        s=2;
    }
    else if( (button_click(button_info) && s==2) || (s==1 && button_click(button_menu)) ){
        s=0;
    }

    if(s==2){
        infos(win);
    }
    else if(s==1){
        menu(win);
    }

    for(int i=0;i<corps.size();i++){
        corps[i].draw(win);
    }

    win.draw(button_info);
    win.draw(button_menu);
    win.draw(startsm);
        
    win.display();
}