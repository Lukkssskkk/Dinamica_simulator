#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>

#define button_click(B) (mouse.getGlobalBounds().findIntersection(B.getGlobalBounds()) && isclicked==true)

class Corp{
    public:
    Corp(int i);
    void run(sf::RenderWindow &win);

    sf::RectangleShape shape;
    sf::CircleShape shape_p;
    sf::Vector2f pos,vel,acel,force;
    sf::Angle angle;
    float mass,k_el,k_at,qmov,work,power,k_col;
    int type;

    private:

    //Calculo:
    float F();
    float Fat();
    float Fel();
    float polia_fixa();
    float polia_movel();
    float Qmovimento();
    float Work_calc();
    float Power_Calc();
    float vel_calc();
    float acel_calc();
    float dist_calc();
    float colisao_calc();
    float colision();
    float corda();
};


class Dinamica{
    public:
        Dinamica(float x,float y);
        void run(sf::RenderWindow &window);
    private:
        unsigned int selection;
        bool isclicked,infos_act,menu_act,sim_act,add_obj_mov,start;
        float timeperframe;

        sf::RectangleShape mouse,selection_shape,startsm,form_info;
        std::vector<Corp> corps;
        sf::RectangleShape button_info,button_menu;
        std::vector<sf::RectangleShape> inputs;
        sf::RectangleShape space_sim,space_menu,space_infos;
        std::vector<sf::Text> texts;
        sf::Texture info_t,menu_t;
        sf::Font font;
        sf::Clock time;

        //GUI:
        float input();
        sf::Vector2f m_input();
        void menu(sf::RenderWindow &win);
        void infos(sf::RenderWindow &win);

        //Funções padrões:
        void processEvents(sf::Event ev, sf::RenderWindow &win);

        //Nucleo do simulador:
        void Simulator(sf::RenderWindow &win);
};