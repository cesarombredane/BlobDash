#include "../include/input.h"

#include "iostream"

using namespace std;

Input::Input() {
    this->x = this->y = 0;
    this->jump = this->dash = false;
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
                    case Keyboard::Space:
                        this->jump = true;
                        break;
                    case Keyboard::LShift:
                        this->dash = true;
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
                    case Keyboard::Space:
                        this->jump = false;
                        break;
                    case Keyboard::LShift:
                        this->dash = false;
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
    cout << "x = " << this->x << " | y = " << this->y << " | jump : " << this->jump << " | dash : " << this->dash << endl;
}

int Input::get_x() const {
    return this->x;
}
int Input::get_y() const {
    return this->y;
}
bool Input::get_jump() const {
    return this->jump;
}
bool Input::get_dash() const {
    return this->dash;
}

void Input::set_jump(bool jump_) {
    this->jump = jump_;
}
void Input::set_dash(bool dash_) {
    this->dash = dash_;
}
