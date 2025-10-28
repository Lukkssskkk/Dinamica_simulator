#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include <iomanip>
#include <sstream>

#define button_click(B) (mouse.getGlobalBounds().findIntersection(B.getGlobalBounds()) && isclicked==true)

class Corp{
    public:
    Corp(int i);
    void run(sf::RenderWindow &win);
    void draw(sf::RenderWindow &win);
    void selected(sf::RenderWindow &win,bool x);
    void defcord(sf::RenderWindow &win);

    sf::RectangleShape shape;
    sf::CircleShape shape_p;
    sf::Vector2f pos,vel,acel,force;
    sf::Angle angle;
    float mass,k_el,k_at,qmov,work,power,k_col,ang;
    int type;

    private:

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
        int8_t selection,g,s;
        bool isclicked,text,f,d;
        float timeperframe;

        std::string input_text;
        sf::RectangleShape mouse,startsm,reset_button,button_info,button_menu;
        std::vector<Corp> corps;
        sf::Texture info_t,menu_t;
        sf::Font font;
        sf::Clock time;

        //GUI:
        float input(sf::RenderWindow &win,sf::Vector2f pos);
        sf::Vector2f m_input(sf::RenderWindow &win,sf::Vector2f pos);
        void menu(sf::RenderWindow &win);
        void infos(sf::RenderWindow &win);
        void editpos(int x);
        //Funções padrões:
        void processEvents(sf::RenderWindow &win);
        void Draw(sf::RenderWindow &win);
};