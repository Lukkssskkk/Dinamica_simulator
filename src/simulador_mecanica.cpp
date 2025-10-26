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
    //Space:
    space_sim.setSize({x,y});
    space_sim.setFillColor(sf::Color::White);
    isclicked=false;
    sim_act=true;
    menu_act=false;
    infos_act=false;
    add_obj_mov=false;
    selection=-1;
}

void Dinamica::run(sf::RenderWindow &win){
    while(win.isOpen()){

        isclicked=false;

        while(auto ev = win.pollEvent()){
            const sf::Event e = *ev;
            processEvents(e,win);
        }
        mouse.setPosition({(float)sf::Mouse::getPosition(win).x,(float)sf::Mouse::getPosition(win).y});
        win.clear(sf::Color::Black);
        
        //Draw part:
        if(sim_act){
            Simulator(win);
        }

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

        win.draw(mouse);
        win.draw(button_info);
        win.draw(button_menu);
        
        win.display();
        sf::sleep(sf::milliseconds(10));
    }
}

void Dinamica::processEvents(sf::Event ev,sf::RenderWindow &win){
    if(ev.is<sf::Event::Closed>()){
        win.close();
    }
    if(ev.is<sf::Event::MouseButtonPressed>() && isclicked==false){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            isclicked=true;
        }
    }
}

