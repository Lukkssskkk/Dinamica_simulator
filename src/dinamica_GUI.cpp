#include"simulador_dinamica.hpp"

void Dinamica::menu(sf::RenderWindow &win){
    sf::Text obj_t(font),cord_s(font),polia_s(font),poliam_s(font),cordas_t(font),force_t(font),vel_t(font),acel_t(font),qmov_t(font),ang_t(font),kel_t(font),kat_t(font),mass_t(font);
    
    obj_t.setCharacterSize(20);
    obj_t.setString("\n\n+OBJ");
    obj_t.setFillColor(sf::Color::White);

    selection_shape.setFillColor(sf::Color::Black);
    selection_shape.setSize({60.f,60.f});
    selection_shape.setOrigin({30.f,30.f});

    force_t.setCharacterSize(20);
    force_t.setString("\n\n\nF:");
    force_t.setFillColor(sf::Color::Black);

    vel_t.setCharacterSize(20);
    vel_t.setString("\n\n\n\nV:");
    vel_t.setFillColor(sf::Color::Black);

    acel_t.setCharacterSize(20);
    acel_t.setString("\n\n\n\n\na:");
    acel_t.setFillColor(sf::Color::Black);

    qmov_t.setCharacterSize(20);
    qmov_t.setString("\n\n\n\n\n\nQm:");
    qmov_t.setFillColor(sf::Color::Black);

    ang_t.setCharacterSize(20);
    ang_t.setString("\n\n\n\n\n\n\ngraus:");
    ang_t.setFillColor(sf::Color::Black);

    mass_t.setCharacterSize(20);
    mass_t.setString("\n\n\n\n\n\n\n\nm:");
    mass_t.setFillColor(sf::Color::Black);

    kat_t.setCharacterSize(20);
    kat_t.setString("\n\n\n\n\n\n\n\n\nk_at:");
    kat_t.setFillColor(sf::Color::Black);

    kel_t.setCharacterSize(20);
    kel_t.setString("\n\n\n\n\n\n\n\n\n\nk_el:");
    kel_t.setFillColor(sf::Color::Black);

    if(button_click(obj_t) && selection==-1){
        Corp corp(0);
        corps.push_back(corp);
        add_obj_mov=true;
    }
    else if(add_obj_mov==true){
        corps.back().shape.setPosition(mouse.getPosition());
        if(button_click(corps.back().shape)){
            add_obj_mov=false;
            if(corps.back().shape.getPosition().x < space_sim.getSize().x/3){
                corps.back().shape.setPosition({space_sim.getSize().x/2, space_sim.getSize().y/2});
            }
        }
    }

    for(int i=0; i < corps.size();i++){
        if(button_click(corps[i].shape)){
            if(selection!=i){
                selection=i;
                selection_shape.setPosition(corps[i].shape.getPosition());
            }else{
                selection=-1;
            }
        }
    }

    space_menu.setPosition({0.f,0.f});
    space_menu.setFillColor(sf::Color::Blue);
    space_menu.setSize({win.getSize().x/3,win.getSize().y});
    if(selection!=-1){
        obj_t.setFillColor(sf::Color::Black);
        acel_t.setFillColor(sf::Color::White);
        qmov_t.setFillColor(sf::Color::White);
        mass_t.setFillColor(sf::Color::White);
        kel_t.setFillColor(sf::Color::White);
        kat_t.setFillColor(sf::Color::White);
        vel_t.setFillColor(sf::Color::White);
        force_t.setFillColor(sf::Color::White);
        ang_t.setFillColor(sf::Color::White);
        
        if(button_click(acel_t)){
            //corps[selection].acel=m_input();
        }else if(button_click(qmov_t)){
            //corps[selection].qmov=input();
        }else if(button_click(mass_t)){
            //corps[selection].mass=input();
        }else if(button_click(kel_t)){
            //corps[selection].mass=input();
        }else if(button_click(kat_t)){
            //corps[selection].mass=input();
        }else if(button_click(vel_t)){
            //corps[selection].mass=input();
        }else if(button_click(force_t)){
            //corps[selection].mass=input();
        }else if(button_click(ang_t)){
            //corps[selection].mass=input();
        }else if(button_click(acel_t)){
            //corps[selection].mass=input();
        }

    }
    win.draw(space_menu);
    win.draw(obj_t);
    win.draw(force_t);
    win.draw(vel_t);
    win.draw(acel_t);
    win.draw(ang_t);
    win.draw(qmov_t);
    win.draw(mass_t);
    win.draw(kel_t);
    win.draw(kat_t);

}

void Dinamica::infos(sf::RenderWindow &win){
    sf::Text obj(font),obj_speed(font),obj_force(font),obj_acel(font),obj_qmov(font),obj_e(font),obj_angulation(font);
    
    space_infos.setSize({win.getSize().x / 4.f, win.getSize().y / 2.f});
    space_infos.setPosition({win.getSize().x - space_infos.getSize().x, 0.f});
    space_infos.setFillColor(sf::Color::Green);
    win.draw(space_infos);
}

float Dinamica::input(){
    //
}

sf::Vector2f Dinamica::m_input(){
    //
}