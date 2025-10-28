#include"simulador_dinamica.hpp"

#define text_def(A,B,C,D,E) A.setCharacterSize(20);A.setString(B);A.setFillColor(C);A.setPosition({D,E});
#define df  (font)
bool add_obj_mov=false;

std::string formatar(float valor,int casa=1,bool front=false) {
    std::ostringstream oss;
    if(front){
        oss << std::fixed << '|'<<std::setprecision(casa) << valor;
    }else{
        oss << std::fixed <<std::setprecision(casa) << valor;
    }
    return oss.str();
}

void Dinamica::menu(sf::RenderWindow &win){
    text= true;
    sf::Text o df,c df,p df,pm df,b df,f df,v df,ac df,qm df,an df,k df,kat df,m df;
    sf::RectangleShape space_menu({(float)win.getSize().x/3,(float)win.getSize().y});
    int8_t corptype=-1;

    space_menu.setPosition({0.f,0.f});
    space_menu.setFillColor(sf::Color::Blue);
    text_def(o,"add OBJ",sf::Color::White,0,40);
    text_def(b,"add block",sf::Color::White,0,60);
    text_def(c,"add Line",sf::Color::White,0,100);
    text_def(p,"add Polia",sf::Color::White,0,120);
    text_def(pm,"add Polia movel",sf::Color::White,0,140);
    text_def(f,"force:",sf::Color::Black,0,60);
    text_def(v,"speed:",sf::Color::Black,0,80);
    text_def(ac,"acel: ",sf::Color::Black,0,100);
    text_def(qm,"Qmov: ",sf::Color::Black,0,120);
    text_def(an,"angle:",sf::Color::Black,0,140);
    text_def(m,"mass: ",sf::Color::Black,0,160);
    text_def(kat,"K at: ",sf::Color::Black,0,180);
    text_def(k,"K el: ",sf::Color::Black,0,200);

    if(corps.size()>16){
        std::cout<<"Número máximo de objetos\n";
    }
    if( (add_obj_mov==true ||button_click(o) && selection==-1) &&corps.size()<=16){
        o.setString("QUIT");
        o.setPosition({0,200});
        add_obj_mov=true;
        
        if(button_click(o)){
            add_obj_mov=false;
        }
        else if(button_click(b)){
            Corp corp(0);
            corptype=0;
            corps.push_back(corp);
        }else if(button_click(c)){
            Corp corp(3);
            corptype=3;
            corps.push_back(corp);
        }else if(button_click(p)){
            Corp corp(1);
            corptype=1;
            corps.push_back(corp);
        }else if(button_click(pm)){
            Corp corp(2);
            corptype=2;
            corps.push_back(corp);
        }
        if(corptype!=-1){
            add_obj_mov=false;
            corps.back().shape.setPosition({(float)win.getSize().x/2,(float)win.getSize().y/2});
            corps.back().shape_p.setPosition({(float)win.getSize().x/2,(float)win.getSize().y/2});
            if(corps.back().type == 3){
                //corps.back().defcord(win);
            }
        }
    }

    for(int i=0; i < corps.size();i++){
        if(button_click(corps[i].shape) || button_click(corps[i].shape_p)){
            if(selection!=i){
                selection=i;
            }
        }
        corps[i].selected(win,false);
    }

    win.draw(space_menu);
    if(add_obj_mov==false){
        win.draw(o);
        win.draw(f);
        win.draw(v);
        win.draw(ac);
        win.draw(an);
        win.draw(qm);
        win.draw(m);
        win.draw(k);
        win.draw(kat);
    }else{
        win.draw(p);
        win.draw(pm);
        win.draw(b);
        win.draw(c);
        win.draw(o);
    }

    if(selection!=-1){
        corps[selection].selected(win,true);

        o.setFillColor(sf::Color::Black);
        ac.setFillColor(sf::Color::White);
        qm.setFillColor(sf::Color::White);
        m.setFillColor(sf::Color::White);
        k.setFillColor(sf::Color::White);
        kat.setFillColor(sf::Color::White);
        v.setFillColor(sf::Color::White);
        f.setFillColor(sf::Color::White);
        an.setFillColor(sf::Color::White);
        if(mouse.getGlobalBounds().findIntersection(corps[selection].shape.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            editpos(selection);
        }
        if(mouse.getGlobalBounds().findIntersection(corps[selection].shape_p.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            editpos(selection);
        }

        if(button_click(f) || g==1){
            g=1;
            d=true;
            corps[selection].force=m_input(win,{80,60});
        }
        else if(button_click(v) || g==2){
            g=2;
            d=true;
            corps[selection].vel=m_input(win,{80,80});
        }
        else if(button_click(ac) || g==3){
            g=3;
            d=true;
            corps[selection].acel=m_input(win,{80,100});
        }
        else if(button_click(qm)|| g==4){
            g=4;
            d=false;
            corps[selection].qmov=input(win,{80,120});
        }
        else if(button_click(an) || g==5){
            g=5;
            d=false;
            corps[selection].ang=input(win,{80,140});
        }
        else if(button_click(m) || g==6){
            g=6;
            d=false;
            corps[selection].mass=input(win,{80,180});
        }
        else if(button_click(kat) || g==7){
            g=7;
            d=false;
            corps[selection].k_at=input(win,{80,180});
        }
        else if(button_click(k) || g==8){
            g=8;
            d=false;
            corps[selection].k_el=input(win,{80,200});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            selection=-1;
        }
    }
}

float Dinamica::input(sf::RenderWindow &win,sf::Vector2f pos){
    sf::RectangleShape shape({120,20});
    sf::Text texto_sf df;
    text_def(texto_sf,"",sf::Color::Black,pos.x,pos.y);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::White);

    if(text) {
        texto_sf.setString(input_text);
        win.draw(shape);
        win.draw(texto_sf);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
        g=-1;
    }

    try {
        return std::stof(input_text);
    } catch (...) {
        return 0.f;
    }
    
}

sf::Vector2f Dinamica::m_input(sf::RenderWindow &win,sf::Vector2f pos){
    sf::Vector2f ret;
    sf::RectangleShape shape({120,20});
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::White);
    sf::Text texto_sf df,is_xory df;
    text_def(texto_sf,"",sf::Color::Black,pos.x+20,pos.y);
    text_def(is_xory,"X:",sf::Color::Black,pos.x,pos.y)

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
    
    if(f==false){
        text=true;
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
            g=-1;
        }
    }
    return ret;
}

void Dinamica::editpos(int x){
    if(corps[selection].type==0 || corps[selection].type==3){
        corps[selection].shape.setPosition(mouse.getPosition());
    }else{
        corps[selection].shape_p.setPosition(mouse.getPosition());
    }
}

void Dinamica::infos(sf::RenderWindow &win) {
    std::vector<sf::Text> obj, speed, force, acel, qmov, e, ang, ke, kat;

    sf::RectangleShape space_infos;
    space_infos.setSize({win.getSize().x / 3.f, win.getSize().y / 3.f});
    space_infos.setPosition({win.getSize().x - space_infos.getSize().x, 0.f});
    space_infos.setFillColor(sf::Color::Green);
    win.draw(space_infos);

    // Cabeçalhos
    obj.emplace_back(font);
    speed.emplace_back(font);
    force.emplace_back(font);
    acel.emplace_back(font);
    qmov.emplace_back(font);
    e.emplace_back(font);
    ang.emplace_back(font);
    ke.emplace_back(font);
    kat.emplace_back(font);

    text_def(obj.back(), "Ob:", sf::Color::Black, win.getSize().x * 2 / 3.f, 20.f);
    text_def(speed.back(), "|V:", sf::Color::Black, win.getSize().x * 2 / 3.f + 18, 20.f);
    text_def(force.back(), "|F:", sf::Color::Black, win.getSize().x * 2 / 3.f + 56, 20.f);
    text_def(acel.back(), "|a:", sf::Color::Black, win.getSize().x * 2 / 3.f + 94, 20.f);
    text_def(qmov.back(), "|Qm:", sf::Color::Black, win.getSize().x * 2 / 3.f + 132, 20.f);
    text_def(e.back(), "|Ec:", sf::Color::Black, win.getSize().x * 2 / 3.f + 162, 20.f);
    text_def(ke.back(), "|Ke:", sf::Color::Black, win.getSize().x * 2 / 3.f + 192, 20.f);
    text_def(kat.back(), "|Ka:", sf::Color::Black, win.getSize().x * 2 / 3.f + 222, 20.f);
    text_def(ang.back(), "|An", sf::Color::Black, win.getSize().x * 2 / 3.f + 252, 20.f);

    obj.back().setCharacterSize(9);
    speed.back().setCharacterSize(9);
    force.back().setCharacterSize(9);
    acel.back().setCharacterSize(9);
    qmov.back().setCharacterSize(9);
    e.back().setCharacterSize(9);
    ang.back().setCharacterSize(9);
    ke.back().setCharacterSize(9);
    kat.back().setCharacterSize(9);

    // Desenhar cabeçalhos
    win.draw(obj.back());
    win.draw(speed.back());
    win.draw(force.back());
    win.draw(acel.back());
    win.draw(qmov.back());
    win.draw(e.back());
    win.draw(ang.back());
    win.draw(ke.back());
    win.draw(kat.back());

    // Dados dos corpos
    for (int i = 0; i < corps.size(); i++) {
        obj.emplace_back(font);
        speed.emplace_back(font);
        force.emplace_back(font);
        acel.emplace_back(font);
        qmov.emplace_back(font);
        e.emplace_back(font);
        ang.emplace_back(font);
        ke.emplace_back(font);
        kat.emplace_back(font);

        float y = 30.f+10*i;
        float x = win.getSize().x * 2 / 3.f;

        text_def(obj.back(), std::to_string(i), sf::Color::Black, x, y);
        obj.back().setCharacterSize(6);

        text_def(speed.back(), formatar(corps[i].vel.x,1,1) + ";" + formatar(corps[i].vel.y), sf::Color::Black, x+18, y);
        speed.back().setCharacterSize(6);

        text_def(force.back(), formatar(corps[i].force.x,1,1) + ";" + formatar(corps[i].force.y), sf::Color::Black, x + 56, y);
        force.back().setCharacterSize(6);

        text_def(acel.back(), formatar(corps[i].acel.x,1,1) + ";" + formatar(corps[i].acel.y), sf::Color::Black, x + 94, y);
        acel.back().setCharacterSize(6);

        text_def(qmov.back(), formatar(corps[i].qmov,1,1), sf::Color::Black, x + 132,y);
        qmov.back().setCharacterSize(6);

        text_def(e.back(), formatar(corps[i].work,1,1), sf::Color::Black, x + 162, y);
        e.back().setCharacterSize(6);

        text_def(ke.back(), formatar(corps[i].k_el,1,1), sf::Color::Black, x + 192, y);
        ke.back().setCharacterSize(6);

        text_def(kat.back(), formatar(corps[i].k_at,1,1), sf::Color::Black, x + 222, y);
        kat.back().setCharacterSize(6);

        text_def(ang.back(), formatar(corps[i].ang,0,1), sf::Color::Black, x + 252, y);
        ang.back().setCharacterSize(6);

        // Desenhar linha de dados
        win.draw(obj.back());
        win.draw(speed.back());
        win.draw(force.back());
        win.draw(acel.back());
        win.draw(qmov.back());
        win.draw(e.back());
        win.draw(ang.back());
        win.draw(ke.back());
        win.draw(kat.back());
    }


    // Limpar vetores
    obj.clear();
    speed.clear();
    force.clear();
    acel.clear();
    qmov.clear();
    e.clear();
    ang.clear();
    ke.clear();
    kat.clear();
}