#include "input.h"

using namespace std;
using namespace sf;

// constructeur
Input::Input()
{
    // cree une variable bool pour chaque touche du clavier necessaire
    button.left = button.right = button.down = button.jump = button.dash = false;
}

// accesseur
Input::Button Input::getButton(void) const
{
    return button;
}

// mutateur
void Input::setButton(int bouton, bool etat)
{
    switch (bouton)
    {
    case down:
        button.down = etat; // la touche qui associe l'action
        break;

    case right:
        button.right = etat;
        break;

    case left:
        button.left = etat;
        break;

    case dash:
        button.dash = etat;
        break;

    case jump:
        button.jump = etat;
        break;

    case escape:
        button.escape = etat;
        break;
    }
}

void Input::gestionInputs(RenderWindow &window) // Fonctions
{
    getInput(window);
}

void Input::getInput(RenderWindow &window)
{
    while (window.pollEvent(event)) // tant qu'il y a des evenement a traiter
    {
        switch (event.type) // on regarde le type de l'evenement
        {
        case Event::Closed: // on ferme la fenetre
            window.close();
            break;

        case Event::KeyPressed:     // touche pressée
            switch (event.key.code) // quelle touche a été pressée
            {
            case Keyboard::Escape: // la touche sur le clavier
                window.close();
                break;

            case Keyboard::Space:
                button.jump = true;
                break;

            case Keyboard::M:
                button.dash = true;
                break;

            case Keyboard::Q:
                button.left = true;
                break;

            case Keyboard::D:
                button.right = true;
                break;

            case Keyboard::S:
                button.down = true;
                break;

            default:
                break;
            }
            break;

        case Event::KeyReleased:    // touche relachée
            switch (event.key.code) // quelle touche est relachée
            {
            case Keyboard::Space:
                button.jump = false;
                break;

            case Keyboard::Q:
                button.left = false;
                break;

            case Keyboard::D:
                button.right = false;
                break;

            case Keyboard::S:
                button.down = false;
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