#include"simulator.hpp"

Help::Help(sf::RenderWindow &win){
    if(font.openFromFile("../img/font.ttf")){std::cout<<"Font para help importada com sucesso\n";}
    file.open("resume.res", std::ios::out);
    form_marc = (char)253;
    Title_marc = (char)252;
    roller.setSize({40.f,20.f});
    roller.setPosition({(float)win.getSize().x,(float)win.getSize().y});
    roller.setOrigin({20.f,10.f});
    roller.setFillColor(sf::Color::Black);
    quit.setSize({60.f,20.f});
    quit.setFillColor(sf::Color::Red);
    quit.setPosition({(float)win.getSize().x-60.f,(float)win.getSize().y-20.f});
}

bool Help::draw(sf::RenderWindow &win){
    win.clear(sf::Color::White);
    win.draw(roller);
    for(int i=0;i<resume_text.size();i++){
        win.draw(resume_text[i]);
    }
    win.draw(quit);
    win.display();
    return quit_func(win);
}

bool Help::quit_func(sf::RenderWindow &win){
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    sf::Vector2f mouseWorldPos = win.mapPixelToCoords(mousePos);

    sf::FloatRect mouseRect({mouseWorldPos.x, mouseWorldPos.y},{ 1.f, 1.f});

    if (quit.getGlobalBounds().findIntersection(mouseRect) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return false;
    }
    return true;
}

//void Help::print_text(sf::RenderWindow &win){}
//void Help::set_position_roller(sf::RenderWindow &win){}
//void Help::ReadFile(){}