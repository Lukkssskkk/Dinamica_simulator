#include"simulador_dinamica.hpp"

void Dinamica::menu(sf::RenderWindow &win){
    sf::Text obj_t(font),cord_s(font),polia_s(font),poliam_s(font),block(font),force_t(font),vel_t(font),acel_t(font),qmov_t(font),ang_t(font),kel_t(font),kat_t(font),mass_t(font);
    sf::RectangleShape selection_s,space_menu;
    //Select object:
    selection_s.setSize({60.f,60.f});
    selection_s.setFillColor(sf::Color::Black);
    selection_s.setOrigin({30.f,30.f});
    //MENU BOX:
    space_menu.setPosition({0.f,0.f});
    space_menu.setFillColor(sf::Color::Blue);
    space_menu.setSize({win.getSize().x/3,win.getSize().y});
    //add OBJ button:
    obj_t.setCharacterSize(20);
    obj_t.setString("\n\n+OBJ");
    obj_t.setFillColor(sf::Color::White);
    //add block sub button de OBJ:
    block.setCharacterSize(20);
    block.setString("\n\n\n+Block");
    block.setFillColor(sf::Color::White);
    //add cord sub button de OBJ:
    cord_s.setCharacterSize(20);
    cord_s.setString("\n\n\n\n+Cord");
    cord_s.setFillColor(sf::Color::White);
    //add polia fixa sub button de OBJ:
    polia_s.setCharacterSize(20);
    polia_s.setString("\n\n\n\n\n+Polia_fixa");
    polia_s.setFillColor(sf::Color::White);
    //add polia movel sub button de OBJ:
    poliam_s.setCharacterSize(20);
    poliam_s.setString("\n\n\n\n\n\n+Polia_movel");
    poliam_s.setFillColor(sf::Color::White);
    //defina força de um bloco de acordo com x e y:
    force_t.setCharacterSize(20);
    force_t.setString("\n\n\nF:");
    force_t.setFillColor(sf::Color::Black);
    //defina velocidade de um bloco de acordo com x e y:
    vel_t.setCharacterSize(20);
    vel_t.setString("\n\n\n\nV:");
    vel_t.setFillColor(sf::Color::Black);
    //defina aceleração de um bloco de acordo com x e y:
    acel_t.setCharacterSize(20);
    acel_t.setString("\n\n\n\n\na:");
    acel_t.setFillColor(sf::Color::Black);
    //defina quantidade de movimento:
    qmov_t.setCharacterSize(20);
    qmov_t.setString("\n\n\n\n\n\nQm:");
    qmov_t.setFillColor(sf::Color::Black);
    //defina angulo
    ang_t.setCharacterSize(20);
    ang_t.setString("\n\n\n\n\n\n\ngraus:");
    ang_t.setFillColor(sf::Color::Black);
    //defina massa
    mass_t.setCharacterSize(20);
    mass_t.setString("\n\n\n\n\n\n\n\nm:");
    mass_t.setFillColor(sf::Color::Black);
    //defina atrito
    kat_t.setCharacterSize(20);
    kat_t.setString("\n\n\n\n\n\n\n\n\nk_at:");
    kat_t.setFillColor(sf::Color::Black);
    //defina elasticidade
    kel_t.setCharacterSize(20);
    kel_t.setString("\n\n\n\n\n\n\n\n\n\nk_el:");
    kel_t.setFillColor(sf::Color::Black);

    if(add_obj_mov==true){
            obj_t.setString("\n\nQUIT");
        
        if(button_click(obj_t)){
            add_obj_mov=false;
        }
        else{
            if(button_click(block)){
                Corp corp(0);
                corps.push_back(corp);
                corp_type=0;
            }else if(button_click(cord_s)){
                std::cout << "add cord\n";
                Corp corp(3);
                corps.push_back(corp);
                corp_type=3;
            }else if(button_click(polia_s)){
                Corp corp(1);
                std::cout << "add polia fixa\n";
                corps.push_back(corp);
                corp_type=1;
            }else if(button_click(poliam_s)){
                std::cout << "add polia movel\n";
                Corp corp(2);
                corps.push_back(corp);
                corp_type=2;
            }
        }
        if(corp_type!=-1){
            add_obj_mov=false;
            if(corp_type==0){
                corps.back().shape.setPosition({space_sim.getSize().x/2, space_sim.getSize().y/2});
            }else if(corp_type==1 || corp_type==2){
                corps.back().shape_p.setPosition({space_sim.getSize().x/2, space_sim.getSize().y/2});
            }else{
                //
            }
        }
    }
    else if(button_click(obj_t)){
        add_obj_mov=true;
        corp_type=-1;
    }

    for(int i=0; i < corps.size();i++){
        if(button_click(corps[i].shape)){
            if(selection!=i){
                selection=i;
                selection_s.setPosition(corps[i].shape.getPosition());
            }
        }
        else if(button_click(corps[i].shape_p)){
            if(selection!=i){
                selection=i;
                selection_s.setPosition(corps[i].shape.getPosition());
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                selection=-1;
    }

    win.draw(space_menu);
    if(add_obj_mov==false){
    win.draw(obj_t);
    win.draw(force_t);
    win.draw(vel_t);
    win.draw(acel_t);
    win.draw(ang_t);
    win.draw(qmov_t);
    win.draw(mass_t);
    win.draw(kel_t);
    win.draw(kat_t);
    }else{
        win.draw(polia_s);
        win.draw(poliam_s);
        win.draw(block);
        win.draw(cord_s);
        win.draw(obj_t);
    }
    if(selection!=-1){
        win.draw(selection_s);
        obj_t.setFillColor(sf::Color::Black);
        acel_t.setFillColor(sf::Color::White);
        qmov_t.setFillColor(sf::Color::White);
        mass_t.setFillColor(sf::Color::White);
        kel_t.setFillColor(sf::Color::White);
        kat_t.setFillColor(sf::Color::White);
        vel_t.setFillColor(sf::Color::White);
        force_t.setFillColor(sf::Color::White);
        ang_t.setFillColor(sf::Color::White);
        if(mouse.getGlobalBounds().findIntersection(corps[selection].shape.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            editpos(selection);
        }
        if(mouse.getGlobalBounds().findIntersection(corps[selection].shape_p.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            editpos(selection);
        }

        if(button_click(force_t) || gf==true){
            text=true;
            gf=true;
            d=true;
            corps[selection].force=m_input(win,{60,60},&gf);
        }
        else if(button_click(vel_t) || gv==true){
            text=true;
            gv=true;
            d=true;
            corps[selection].vel=m_input(win,{60,80},&gv);
        }
        else if(button_click(acel_t) || ga==true){
            text=true;
            ga=true;
            d=true;
            corps[selection].acel=m_input(win,{60,100},&ga);
        }
        else if(button_click(qmov_t)|| gqmov==true){
            text=true;
            gqmov=true;
            d=false;
            corps[selection].qmov=input(win,{60,120},&gqmov);
        }
        else if(button_click(ang_t) || gan==true){
            text=true;
            gan=true;
            d=false;
            corps[selection].ang=input(win,{60,140},&gan);
        }
        else if(button_click(mass_t) || gm==true){
            gm=true;
            text=true;
            d=false;
            corps[selection].mass=input(win,{60,160},&gm);
        }
        else if(button_click(kat_t) || gkat==true){
            text=true;
            gkat=true;
            d=false;
            corps[selection].k_at=input(win,{60,180},&gkat);
        }
        else if(button_click(kel_t) || gkel==true){
            text=true;
            gkel=true;
            d=false;
            corps[selection].k_el=input(win,{60,200},&gkel);
        }
    }
}

float Dinamica::input(sf::RenderWindow &win,sf::Vector2f pos,bool *x){
    std::string texto;
    sf::RectangleShape shape({80,20});
    sf::Text texto_sf(font);
    texto_sf.setCharacterSize(20);
    texto_sf.setPosition({pos.x,pos.y});
    shape.setPosition(pos);
    texto_sf.setFillColor(sf::Color::Black);
    shape.setFillColor(sf::Color::White);

    if(text) {
        texto_sf.setString(input_text);
        win.draw(shape);
        win.draw(texto_sf);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
        *x=false;
    }

    try {
        return std::stof(input_text);
    } catch (...) {
        return 0.f;
    }
    
}

sf::Vector2f Dinamica::m_input(sf::RenderWindow &win,sf::Vector2f pos,bool *x){
    sf::Vector2f ret;
    sf::RectangleShape shape({80,20});
    sf::Text texto_sf(font),is_xory(font);
    texto_sf.setCharacterSize(20);
    texto_sf.setPosition({pos.x+20,pos.y});
    is_xory.setCharacterSize(20);
    is_xory.setPosition(pos);
    is_xory.setString("X:");
    is_xory.setFillColor(sf::Color::Black);
    shape.setPosition(pos);
    texto_sf.setFillColor(sf::Color::Black);
    shape.setFillColor(sf::Color::White);

    if(text) {
        texto_sf.setString(input_text);
        win.draw(shape);
        win.draw(texto_sf);
        win.draw(is_xory);
    }

    try {
         ret.x = std::stof(input_text);
    } catch (...) {
        ret.x = 0.f;
    }

    text=true;
    
    if(f==false){
        is_xory.setString("Y:");
        if(text) {
            texto_sf.setString(input_text);
            win.draw(shape);
            win.draw(texto_sf);
            win.draw(is_xory);
        }
        try {
            ret.y = std::stof(input_text);
        } catch (...) {
            ret.y = 0.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
            *x=false;
        }
    }
    return ret;
}

void Dinamica::editpos(int x){
    if(corps[selection].type==0){
        corps[selection].shape.setPosition(mouse.getPosition());
        if(button_click(corps[selection].shape)){
        }
    }else if(corps[selection].type!=3){
        corps[selection].shape_p.setPosition(mouse.getPosition());
        if(button_click(corps[selection].shape_p)){
        }
    }
}

void Dinamica::infos(sf::RenderWindow &win){
    sf::Text obj(font),obj_speed(font),obj_force(font),obj_acel(font),obj_qmov(font),obj_e(font),obj_angulation(font);
    
    space_infos.setSize({win.getSize().x / 4.f, win.getSize().y / 2.f});
    space_infos.setPosition({win.getSize().x - space_infos.getSize().x, 0.f});
    space_infos.setFillColor(sf::Color::Green);
    win.draw(space_infos);
}