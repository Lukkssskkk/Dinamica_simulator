#include"simulador_dinamica.hpp"

Dinamica::Dinamica(float x, float y){
    //Get font:
    font.openFromFile("../img/font.ttf");
    //Textures:
    info_t.loadFromFile("../img/info.png");
    menu_t.loadFromFile("../img/menu.png");
    //mouse:
    mouse.setSize({2,2});
    mouse.setFillColor(sf::Color::Green);
    mouse.setOrigin({1,1});
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
    //Space:
    space_sim.setSize({x,y});
    space_sim.setFillColor(sf::Color::White);
    //VARS:
    isclicked=false;
    sim_act=true;
    menu_act=false;
    infos_act=false;
    add_obj_mov=false;
    selection=-1;
    corp_type=-1;
    start=false;
    text=false;
    ga=false;
    gm=false;
    gv=false;
    gf=false;
    gan=false;
    gkel=false;
    gkat=false;
    gqmov=false;
    gwork=false;
    gkat=false;
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
        if(ev->is<sf::Event::MouseButtonPressed>() && isclicked==false){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                isclicked=true;
            }
        }
        if (const auto* textEntered = ev->getIf<sf::Event::TextEntered>()) {
            if (text) {
                char c = static_cast<char>(textEntered->unicode);
                if (c == 8 && !input_text.empty()) {
                    input_text.pop_back();
                } else if (std::isprint(c)) {
                    input_text += c;
                }
            }
        }
        if (const auto* keyPressed = ev->getIf<sf::Event::KeyReleased>()) {
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

void Dinamica::Simulator(sf::RenderWindow &win){
    for(int i=0;i<corps.size();i++){
        corps[i].draw(win);
    }
}

void Dinamica::Draw(sf::RenderWindow &win){
    win.clear(sf::Color::Black);
        
        //Draw part:
        win.draw(space_sim);
        if(button_click(button_menu)){
            if(menu_act == false){
                menu_act=true;
            }else{
                menu_act=false;
            }
        }if(menu_act){
            menu(win);
        }

        if(button_click(button_info)){
            if(infos_act == false){
                infos_act=true;
            }else{
                infos_act=false;
            }
        }if(infos_act){
            infos(win);
        }

    Simulator(win);

    //win.draw(mouse);
    win.draw(button_info);
    win.draw(button_menu);
    win.draw(startsm);
        
    win.display();
}