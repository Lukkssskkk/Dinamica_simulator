#include"simulador_dinamica.hpp"

Corp::Corp(int i){
    if(i==0){
        shape.setSize({50.f,50.f});
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({25.f,25.f});
        type=0;
    }
    else if(i==1){
        shape_p.setRadius(25.f);
        shape_p.setFillColor(sf::Color::Cyan);
        shape_p.setOrigin({25.f,25.f});
        type=1;
    }
    else if(i==2){
        shape_p.setRadius(25.f);
        shape_p.setFillColor(sf::Color::Blue);
        shape_p.setOrigin({25.f,25.f});
        type=2;
    }
    else if(i==3){
        shape.setSize({5.f,5.f});
        shape.setFillColor(sf::Color::Black);
        shape.setOrigin({2.5f,2.5f});
        type=3;
    }

    vel.x= 0.0;
    vel.y=0.0;
    acel.x=0.0;
    acel.y=0.0;
    force.x=0.0;
    force.y=0.0;
    //angle.asDegrees(sf::Angle::asDegrees(0.0));
    mass=0.0;
    k_el=0.0;
    k_at=0.0;
    qmov=0.0;
    work=0.0;
    power=0.0;
    k_col=0.0;
}

/*
void Corp::run(sf::RenderWindow &win){
    if(type==0){            //square
    F();
    Fat();
    Fel();
    Qmovimento();
    Work_calc();
    Power_Calc();
    vel_calc();
    acel_calc();
    dist_calc();
    colisao_calc();
    colision();
    }
    else if(type==1){       //polia_fixa
    polia_fixa();
    }else if(type==2){      //polia_movel
    polia_movel();
    }
    else if(type==3){
        corda();            //corda
    }
}
*/

void Corp::draw(sf::RenderWindow &win){
    if(type==0 || type==3){
        win.draw(shape);
    }else if(type==1 || type==2){
        win.draw(shape_p);
    }
}

void Corp::selected(sf::RenderWindow &win,bool x){
    if(x == true){
        if(type ==0 || type==3){
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(5.f);
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