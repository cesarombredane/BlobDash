#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Map
{
public:
	Map();

	// Accesseurs
	int getBeginX(void) const; // coordonnees de depart du hero
	int getBeginY(void) const;
	int getStartX(void) const; // point de depart pour dessiner la map
	int getStartY(void) const;
	int getMaxX(void) const; // coordonnees de fin de map
	int getMaxY(void) const;
	int getTile(int x, int y) const;

	// mutateurs
	void setStartX(int valeur);
	void setStartY(int valeur);

	// fonctions
	void drawBackground(sf::RenderWindow &window); // dessine le background
	void loadMap();																 // charge la map depuis map.txt
	void draw(sf::RenderWindow &window);					 // dessine la map charge precedement
	void testDefilement(void);										 // fonction deffilement (temporraire)

private:
	/* Coordonnees de depart du heros, lorsqu'il commence le niveau */
	int beginx, beginy;

	/* Coordonnees de debut, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonnees max de fin de la map */
	int maxX, maxY;

	/* Tableau a double dimension representant la map de tiles */
	int tile[19][50];

	// background
	sf::Texture backgroundTexture;
	sf::Sprite background;

	// Tilesets
	sf::Texture tileSetTexture;
	sf::Sprite tileSet;

	// Taille de la fenetre : 800x600 pixels
	const int SCREEN_WIDTH = 1066;
	const int SCREEN_HEIGHT = 600;

	/* Taille maxi de la map : 50 x 19 tiles */
	const int MAX_MAP_X = 50;
	const int MAX_MAP_Y = 19;

	const int TILE_SIZE = 32;
};
#endif
