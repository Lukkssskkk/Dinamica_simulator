#include"simulador_dinamica.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Simulador de Dinamica");
    Dinamica simulator(800,600);
    simulator.run(window);
    return 0;
}