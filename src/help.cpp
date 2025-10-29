#include"simulator.hpp"

Help::Help(sf::RenderWindow &win){
    if(font.openFromFile("../img/font.ttf")){std::cout<<"Font para help importada com sucesso\n";}

    std::fstream file("../resume.res", std::ios::in);
    if(!file.is_open()){
        std::cout<<"Can't find the file,creating a new\n";
        std::ofstream novoArquivo("../resume.res");
        if (novoArquivo.is_open()) {
            novoArquivo << "^Título de Exemplo\n";
            novoArquivo <<"~Formula de exemplo\n";
            novoArquivo << "texto de exemplo.\n";
            novoArquivo.close();
            ReadFile();
        } else {
            std::cout << "Erro ao criar o arquivo.\n";
            return;
        }
    }else{
        std::cout<<"File opened in correct place\n";
        ReadFile();
    }
    file.close();

    form_marc = '~';
    Title_marc = '^';
    roller.setSize({20.f,40.f});
    roller.setPosition({(float)win.getSize().x-20.f,0.0f});
    roller.setFillColor(sf::Color::Black);
    quit.setSize({60.f,20.f});
    quit.setFillColor(sf::Color::Red);
    quit.setPosition({(float)win.getSize().x-60.f,(float)win.getSize().y-20.f});
    rec=0;
    extra=0;
    select=false;
}

bool Help::draw(sf::RenderWindow &win){
    win.clear(sf::Color::White);
    print_text(win);
    set_position_roller(win);
    win.draw(roller);
    win.draw(quit);
    win.display();
    return button(win,quit.getGlobalBounds());
}

void Help::print_text(sf::RenderWindow &win){
    int tot = text.size();
    int li = 0;
    sf::Text resume_text(font);
    float tam_conteudo=0.f;
    for(int i=rec; i < text.size() && tam_conteudo<win.getSize().y*12-20.f;i++){
        li++;
        if (text[i].empty()) continue;
        if(text[i][0] == form_marc){    //se é uma formula
            resume_text.setStyle(sf::Text::Italic);
            std::string linha = text[i];
            linha.erase(linha.begin());
            resume_text.setString(linha);
            resume_text.setCharacterSize(14);
            resume_text.setFillColor(sf::Color::Green);
            resume_text.setPosition({0.0f, 22.f*(i-rec)});
            tam_conteudo += 27.f*(i-rec);
        }else if(text[i][0] == Title_marc){  //se é um título
            std::string linha = text[i];
            linha.erase(linha.begin());
            resume_text.setString(linha);
            resume_text.setStyle(sf::Text::Bold);
            resume_text.setCharacterSize(14);
            resume_text.setFillColor(sf::Color::Blue);
            resume_text.setPosition({0.0f,22.f*(i-rec)});
            tam_conteudo += 32.f*(i-rec);
        }else{                        //É um texto padrão
            resume_text.setStyle(sf::Text::Regular);
            resume_text.setString(text[i]);
            resume_text.setCharacterSize(14);
            resume_text.setFillColor(sf::Color::Black);
            resume_text.setPosition({0.0f,22.f*(i-rec)});
            tam_conteudo += 22.f*(i-rec);
        }
        win.draw(resume_text);
    }
    extra=tot-li;
}
void Help::ReadFile(){

    std::ifstream file("../resume.res");
    std::string line;
    while (std::getline(file, line)){
        text.push_back(line);
    }
    file.close();
}

void Help::set_position_roller(sf::RenderWindow &win){
    sf::Vector2u tamanhoJanela = win.getSize(); 
    sf::FloatRect boundsJanela({0.f, 0.f}, {(float)tamanhoJanela.x, (float)tamanhoJanela.y - 20.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && rec < extra) {
        rec++;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && rec-1 >= 0) {
        rec--;
    }
    roller.setSize({roller.getSize().x, win.getSize().y - (extra * 5) - 20.f});
    if (!button(win, roller.getGlobalBounds()) || select) {
        
        sf::Vector2i mousepos = sf::Mouse::getPosition(win);
        sf::sleep(sf::milliseconds(10));
        if (mousepos.y<sf::Mouse::getPosition(win).y && rec< extra) {
            rec++;
        }
        if (mousepos.y > sf::Mouse::getPosition(win).y && rec - 1 >= 0) {
            rec--;
        }

        if (button(win, roller.getGlobalBounds())) {
            select = false;
        }
    }
    roller.setOrigin({0,0});
    roller.setPosition({roller.getPosition().x,(float)rec*5});
}


bool Help::button(sf::RenderWindow &win, sf::FloatRect button_obj){
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    sf::Vector2f mouseWorldPos = win.mapPixelToCoords(mousePos);
    sf::FloatRect mouseRect({mouseWorldPos.x, mouseWorldPos.y},{ 1.f, 1.f});
    if (button_obj.findIntersection(mouseRect) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return false;
    }
    return true;
}