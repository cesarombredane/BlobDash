#include "../include/input.h"

#include "iostream"

using namespace std;

Input::Input() {
    this->left = this->right = false;
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

void Input::show_input() {
    cout << "left = " << this->left << " | right = " << this->right << endl;
}
