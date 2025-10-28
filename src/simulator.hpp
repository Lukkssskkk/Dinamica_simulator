#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include <iomanip>
#include <sstream>
#include <fstream>

#define button_click(B) (mouse.getGlobalBounds().findIntersection(B.getGlobalBounds()) && isclicked==true)

class Corp{
    public:
    Corp(int i);
    void run();
    void draw(sf::RenderWindow &win);
    void selected(sf::RenderWindow &win,bool x);
    void defcord(sf::RenderWindow &win);

    sf::RectangleShape shape;
    sf::CircleShape shape_p;
    sf::Vector2f pos,vel,acel,force,origin;
    sf::Angle angle;
    float mass,k_el,k_at,qmov,work,power,k_col,ang,L,k_ela,k_ata;
    int type;

    private:

    float F();          //De certo emplementado de forma básica na função run.
    float Fat();        //De certo emplementado de forma básica na função run.
    float Fel();        //De certo emplementado de forma básica na função run.
    float polia();
    float Qmovimento(); //De certo emplementado de forma básica na função run.
    float Work_calc();  //De certo emplementado de forma básica na função run.
    float Power_Calc();
    float vel_calc();   //De certo emplementado de forma básica na função run.
    float acel_calc();  //De certo emplementado de forma básica na função run.
    float dist_calc();  //De certo emplementado de forma básica na função run.
};

class Help{
    public:
    Help(sf::RenderWindow &win);
    bool draw(sf::RenderWindow &win);
    private:
    std::fstream file;  //arquivo que contem o resumo.
    sf::Font font;
    std::vector<sf::Text> resume_text;
    char form_marc,Title_marc;
    sf::RectangleShape roller,quit; //coisa de rolar a tela e botão para fechar o help.
    void print_text(sf::RenderWindow &win);
    void set_position_roller(sf::RenderWindow &win);
    void ReadFile();
    bool quit_func(sf::RenderWindow &win);
};

class Dinamica{
    public:
        Dinamica(float x,float y);
        void run(sf::RenderWindow &window);
    private:
        int8_t selection,g,s;
        bool isclicked,text,f,d,help_b,start_b,restart_b;
        float timeperframe;

        std::string input_text;
        sf::RectangleShape mouse,startsm,reset_button,button_info,button_menu;
        std::vector<Corp> corps;
        sf::Texture info_t,menu_t;
        sf::Font font;

        //GUI:
        float input(sf::RenderWindow &win,sf::Vector2f pos);
        sf::Vector2f m_input(sf::RenderWindow &win,sf::Vector2f pos);
        void menu(sf::RenderWindow &win);
        void infos(sf::RenderWindow &win);
        void editpos(int x);
        //Funções padrões:
        void colision();
        void processEvents(sf::RenderWindow &win);
        void Draw(sf::RenderWindow &win, Help &Mhelp);
};