#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <thread>

using namespace std;

int keyPressed(int);
void getColor(int const &, int const &, int const &, bool const &);
string getPath();


int main() {
    int a = 0, b = 0, c = 0;
    bool finish = false;
    thread t1(getColor, ref(a), ref(b), ref(c), ref(finish));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(
            sf::VideoMode(640,480,32),
            "ColorFinder",
            sf::Style::Titlebar | sf::Style::Close, settings
            );

    sf::CircleShape circle(200);
    circle.setRadius(150);
    circle.setPosition(
            window.getSize().x / 2 - circle.getRadius(),
            window.getSize().y / 2 - circle.getRadius() - 40
    );
    circle.setPointCount(100);
    circle.setFillColor(sf::Color::Black);
    circle.setOutlineThickness(10);
    circle.setOutlineColor(sf::Color::Black);

    sf::Font font;
    font.loadFromFile(getPath() + "/PlatNomor-WyVnn.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(23);
    text.setFillColor(sf::Color::Black);


    while(window.isOpen()){

        text.setString("R: ( " + to_string(a) + " ) G: ( " + to_string(b) + " ) B: ( " + to_string(c) + " )");
        circle.setFillColor(sf::Color(a, b, c, 255));
        text.setPosition(
                window.getSize().x / 2 - text.getLocalBounds().width / 2,
                window.getSize().y / 2 + circle.getRadius()
        );

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
                t1.detach();
            }

            window.clear(sf::Color::White);

            window.draw(text);

            window.draw(circle);

            window.display();
        }
        if(finish){
            window.close();
            t1.detach();
        }
    }

    return 0;
}


int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

void getColor(int const &red, int const &green, int const &blue, bool const &finish){
    POINT p;
    bool loop = true;
    while(loop){
        //if(keyPressed(VK_LBUTTON)){
        if(keyPressed((static_cast<int>('F')))){
            cout << '\a';
            GetCursorPos(&p);
            HDC dc = GetDC(NULL);
            COLORREF color = GetPixel(dc, p.x, p.y);
            ReleaseDC(NULL, dc);

            int &_red = const_cast<int &>(red);
            int &_green = const_cast<int &>(green);
            int &_blue = const_cast<int &>(blue);

            _red = GetRValue(color);
            _green = GetGValue(color);
            _blue = GetBValue(color);
        }
        if(keyPressed(VK_ESCAPE)){
            loop = false;

            bool &_finish = const_cast<bool &>(finish);
            _finish = true;
        }
    }
}

string getPath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos1 = string( buffer ).find_last_of( "\\/" );
    string pos1str = string( buffer ).substr( 0, pos1);
    string::size_type pos2 = pos1str.find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos2);
}

