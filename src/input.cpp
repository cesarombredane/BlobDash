#include "../include/input.h"

#include "iostream"
#include "cmath"

using namespace std;

Input::Input() {
    this->x = this->y = 0;
}

void Input::input(RenderWindow &window, Event &event) {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                switch (event.key.code) {
                    case Keyboard::Escape:
                        window.close();
                        break;
                    case Keyboard::Z:
                        this->y = -1;
                        break;
                    case Keyboard::S:
                        this->y = 1;
                        break;
                    case Keyboard::Q:
                        this->x = -1;
                        break;
                    case Keyboard::D:
                        this->x = 1;
                        break;
                    default:
                        break;
                }
                break;
            case Event::KeyReleased:
                switch (event.key.code) {
                    case Keyboard::Z:
                        this->y = Keyboard::isKeyPressed(Keyboard::S) ? 1 : 0;
                        break;
                    case Keyboard::S:
                        this->y = Keyboard::isKeyPressed(Keyboard::Z) ? -1 : 0;
                        break;
                    case Keyboard::Q:
                        this->x = Keyboard::isKeyPressed(Keyboard::D) ? 1 : 0;
                        break;
                    case Keyboard::D:
                        this->x = Keyboard::isKeyPressed(Keyboard::Q) ? -1 : 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Input::show_input() const {
    cout << "x = " << this->x << " | y = " << this->y << endl;
}

int Input::get_x() const {
    return this->x;
}

int Input::get_y() const {
    return this->y;
}