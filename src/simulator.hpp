#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<algorithm>

#define button_click(B) (mouse.getGlobalBounds().findIntersection(B.getGlobalBounds()) && isclicked==true)

class Corp{
    public:
    Corp(int i);
    void run();
    void draw(sf::RenderWindow &win);
    void selected(sf::RenderWindow &win,bool x);

    sf::RectangleShape shape;
    sf::CircleShape shape_p;
    sf::Vector2f pos,vel,acel,force,origin;
    sf::Angle angle;
    float mass,k_el,k_at,work,L,k_ela,k_ata;
    bool p;
    int type;
    int connected[4];

    private:
    
    void F();
    void Fat();
    void Fel();
    void polia(sf::RenderWindow &win);
    void Work_calc();
    void vel_calc();
    void acel_calc();
    void dist_calc();
};

class Help{
    public:
    Help(sf::RenderWindow &win);
    bool draw(sf::RenderWindow &win);
    private:
    sf::Font font;
    std::vector<std::string> text;
    char form_marc,Title_marc;
    bool select;
    sf::RectangleShape roller,quit; //coisa de rolar a tela e botão para fechar o help.
    int rec,extra;
    void print_text(sf::RenderWindow &win);
    void set_position_roller(sf::RenderWindow &win);
    void ReadFile();
    bool button(sf::RenderWindow &win,sf::FloatRect button_obj);
};

class Dinamica{
    public:
        Dinamica(float x,float y);
        void run(sf::RenderWindow &window);
    private:
        int8_t selection,g,s;
        bool isclicked,text,fo,d,help_b,start_b,restart_b,add_line,linedef;
        float timeperframe;

        std::string input_text;
        sf::RectangleShape mouse,startsm,reset_button,button_info,button_menu;
        std::vector<Corp> corps;
        sf::Texture info_t,menu_t,start_t1,start_t2,restart_t1,restart_t2;
        sf::Font font;
        sf::Vector2f p1,p2;

        //GUI:
        float input(sf::RenderWindow &win,sf::Vector2f pos);
        void menu(sf::RenderWindow &win);
        void infos(sf::RenderWindow &win);
        void editpos(int x);
        void line_def(sf::RenderWindow &win);
        //Funções padrões:
        void colision(sf::RenderWindow &win);
        void processEvents(sf::RenderWindow &win);
        void Draw(sf::RenderWindow &win, Help &Mhelp);
};