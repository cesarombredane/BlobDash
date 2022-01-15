#include "../include/input.h"

#include "iostream"

using namespace std;

Input::Input() {
    this->up = this->down = this->left = this->right = false;
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
                        this->up = true;
                        break;
                    case Keyboard::S:
                        this->down = true;
                        break;
                    case Keyboard::Q:
                        this->left = true;
                        break;
                    case Keyboard::D:
                        this->right = true;
                        break;
                    default:
                        break;
                }
                break;
            case Event::KeyReleased:
                switch (event.key.code) {
                    case Keyboard::Z:
                        this->up = false;
                        break;
                    case Keyboard::S:
                        this->down = false;
                        break;
                    case Keyboard::Q:
                        this->left = false;
                        break;
                    case Keyboard::D:
                        this->right = false;
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
    cout << "up = " << this->up << " | down = " << this->down << " | left = " << this->left << " | right = " << this->right << endl;
}

bool Input::get_up() const {
    return this->up;
}

bool Input::get_down() const {
    return this->down;
}

bool Input::get_left() const {
    return this->left;
}

bool Input::get_right() const {
    return this->right;
}
