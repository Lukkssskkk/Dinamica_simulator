#include"simulador_dinamica.hpp"

void Dinamica::Simulator(sf::RenderWindow &win){
    space_sim.setSize({win.getSize().x,win.getSize().y});
    space_sim.setFillColor(sf::Color::White);
    win.draw(space_sim);
    if(selection!=-1){
        win.draw(selection_shape);
    }
    for(int i=0;i<corps.size();i++){
        win.draw(corps[i].shape);
    }
}
float F(int sel){
    //
}