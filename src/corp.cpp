#include"simulator.hpp"

Corp::Corp(int i){
    if(i==0){
        shape.setSize({50.f,50.f});
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({25.f,25.f});
        type=0;
        p=false;
    }
    else if(i==1){
        shape_p.setRadius(25.f);
        shape_p.setFillColor(sf::Color::Cyan);
        shape_p.setOrigin({25.f,25.f});
        type=1;
        p=false;
    }
    else if(i==2){
        shape_p.setRadius(25.f);
        shape_p.setFillColor(sf::Color::Blue);
        shape_p.setOrigin({25.f,25.f});
        type=2;
        p=false;
    }
    else if(i==3){
        shape.setSize({5.f,5.f});
        shape.setFillColor(sf::Color::Black);
        shape.setOrigin({2.5f,2.5f});
        type=3;
        p=true;
    }

    vel.x= 0.0;
    vel.y=0.0;
    acel.x=0.0;
    acel.y=0.0;
    force.x=0.0;
    force.y=0.0;
    angle=sf::degrees(0.f);
    mass=1.0;
    k_el=0.0;
    k_at=0.0;
    k_ata=0.0;
    k_ela=0.0;
    work=0.0;
}


void Corp::run(){
    if(type ==0 || type ==3){
        shape.setRotation(angle);
    }
    Work_calc();
    Fat();
    Fel();
    F();
    acel_calc();
    vel_calc();
    dist_calc();
    
}


void Corp::draw(sf::RenderWindow &win){
    if(type==0 || type==3){
        shape.setRotation(angle);
        win.draw(shape);
    }else if(type==1 || type==2){
        win.draw(shape_p);
    }
}

void Corp::selected(sf::RenderWindow &win,bool x){
    if(x == true){
        sf::Font font;
        sf::RectangleShape f_dem,v_dem,a_dem;
        font.openFromFile("../img/font.ttf");
        sf::Text values(font);
        values.setString("M:"+ std::to_string((int)mass) + '\n' 
        +"F:"+ std::to_string((int)force.x) + ';' + std::to_string((int)force.y) +'\n'
        +"V:"+ std::to_string((int)vel.x) + ';' + std::to_string((int)vel.y) + '\n'
        +"a:"+  std::to_string((int)acel.x) + ';' + std::to_string((int)acel.y) + '\n'
        +"W:"+  std::to_string((int)work) + '\n'
        );
        values.setCharacterSize(10);

        if(type ==0 || type==3){
            values.setPosition({shape.getPosition().x-25.f,shape.getPosition().y-25.f});
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(6.f);
            win.draw(values);
        }
        else if(type==1 || type==2){
            shape_p.setOutlineColor(sf::Color::Black);
            shape_p.setOutlineThickness(5.f);
        }
    }else{
        if(type ==0 || type==3){
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(0.f);
        }
        else if(type==1 || type==2){
            shape_p.setOutlineColor(sf::Color::Black);
            shape_p.setOutlineThickness(0.f);
        }
    }
}

void Corp::Work_calc(){
    if(force.x != 0.0 || force.y != 0.0){
        work = sqrt(
        (force.x*(shape.getPosition().x - origin.x))*(force.x*(shape.getPosition().x - origin.x)) 
        +
        (force.y*(shape.getPosition().y - origin.y))*(force.y*(shape.getPosition().y - origin.y))
        );  //W = F.d;
    }
}
void Corp::F(){
    force.x=acel.x*mass;
    force.y=acel.x*mass;
}
void Corp::Fat(){
    if(force.x!=0 && force.y!=0){
        force.x -=force.y*k_ata;
    }
}
void Corp::Fel(){
    if(vel.x != 0){
        L = force.x*k_ela;   //Fel = k.x -> x = Fel/k
        //vel.x=sqrt(2*k_ela*L*L/m);                   //mv²/2=kx² -> v= sqrt(2kx²/m)
    }
}
void Corp::acel_calc(){
    if(mass!=0){
        acel.x = force.x/mass;  // a=F/m ou F=ma;
        acel.y = force.y/mass;
    }
}
void Corp::vel_calc(){
    if(acel.x!=0.0 || acel.y!=0.0){
        vel=vel+acel;   //V = v+ at(segundo)
    }
    
}
void Corp::dist_calc(){
    shape.setPosition({shape.getPosition().x+vel.x/10,shape.getPosition().y+vel.y/10});
}
//float Corp::polia(){}

void Corp::polia(sf::RenderWindow &win){
    //TODO
}