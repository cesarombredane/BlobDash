#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input // creer objet Input
{
    struct Button
    {
        bool left, right, escape, down, jump, dash;
    }; // ajout des variables dans l'objet Input

public:
    Input(); // constructeur

    Button getButton(void) const; // accesseur

    void setButton(int bouton, bool etat); // mutateur

    void gestionInputs(sf::RenderWindow &window); // transformer ces touches en varaiables booléennes
    void getInput(sf::RenderWindow &window);      // recuperer les touches du clavier

private:
    sf::Event event;
    Button button;

    enum
    {
        down,
        right,
        left,
        dash,
        jump,
        escape
    }; // énumeration des boutons
};
#endif