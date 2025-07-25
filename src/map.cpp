#include "map.h"

using namespace std;
using namespace sf;

// constructeur
Map::Map()
{
	if (!backgroundTexture.loadFromFile("assets/graphics/background.png")) // chargement du background
	{
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
		background.setTexture(backgroundTexture);

	if (!tileSetTexture.loadFromFile("assets/graphics/tileset.png")) // chargement de la tileset
	{
		cout << "Erreur durant le chargement de l'image du tileset." << endl;
	}
	else
		tileSet.setTexture(tileSetTexture);

	startX = startY = 0; // initialisation des variables
}

// accesseur
int Map::getBeginX(void) const { return beginx; }
int Map::getBeginY(void) const { return beginy; }
int Map::getStartX(void) const { return startX; }
int Map::getStartY(void) const { return startY; }
int Map::getMaxX(void) const { return maxX; }
int Map::getMaxY(void) const { return maxY; }

// pour player
int Map::getTile(int x, int y) const { return tile[y][x]; }

// mutateur
void Map::setStartX(int valeur) { startX = valeur; }
void Map::setStartY(int valeur) { startY = valeur; }

// fonctions

void Map::drawBackground(RenderWindow &window) // on dessine le background
{
	window.draw(background);
}

void Map::loadMap()
{
	fstream fin; // creation du flux pour lire le fichier
	int x = 0;	 // initialisation de 2 variable pour la suite
	int y = 0;

	maxX = 0; // reinialiation de maxX et maxY
	maxY = 0; //(limite de la map)

	vector<vector<int>> lignes; // creation d'un vecteur en 2 dimentions

	vector<int> myVectData; // creation d'un vecteur temporaire pour lire une ligne

	string strligne, strcara; // creation d'une chaine de caractere temporaire

	stringstream iostr; // costructeuration d'un stringstream pour gerer les chaines

	fin.open("assets/map/map.txt"); // on ouvre le fichier map

	if (!fin.is_open()) // en cas d'erreur on leve une exeption
	{
		cerr << "Erreur de chargement du fichier.";
	}

	while (!fin.eof()) // lecture du fichier jusqu'a la fin
	{
		getline(fin, strligne); // recuperation de la ligne dans la chaine 'strligne'

		if (!strligne.size()) // si la ligne est vide on continue
			continue;

		iostr.clear(); // sinon on continue et on clear stringteam

		iostr.str(strligne); // on y envoi le contenue de strligne

		myVectData.clear(); // on clear le vecteur ligne

		while (true) // boucle pour lire tout les numero de tiles
		{
			getline(iostr, strcara, ' '); // on recupere tout les numero de tiles en les separant grace au espaces

			myVectData.push_back(atoi(strcara.c_str())); // on recupere les numeros dans le vecteur ligne

			if (!iostr.good())
				break; // si c'est finit on quite la boucle
		}

		if (myVectData.size()) // si le vecteur ligne est plein, on l'envoi dans le vecteur a 2 dimention
			lignes.push_back(myVectData);
	}

	fin.close(); // fermeture du fichier

	beginx = lignes[0][0]; // on recupere beginX et beginY dans les 2 premiers valeur du tableau
	beginy = lignes[0][1];

	for (x = 2; x < MAX_MAP_X + 2; x++) // on charge la 1er ligne independament car elle contien plus d'information
	{																		//(beginX et beginY)
		tile[y][x - 2] = lignes[y][x];
	}

	for (y = 1; y < MAX_MAP_Y; y++) // on charge le reste du tableau
	{																// et on boucle jusqu'a MAP_MAX qui sont les valeur max de la map (50x19)
		for (x = 0; x < MAX_MAP_X; x++)
		{
			tile[y][x] = lignes[y][x]; // on copie le vecteur temporaire dans le tableau a 2 dimentions

			if (tile[y][x] > 0) // on detecte si la tile n'est pas vide
			{
				if (x > maxX) // on augmente les valeur de maxX et maxY car la map n'est pas finit
				{
					maxX = x;
				}

				if (y > maxY)
				{
					maxY = y;
				}
			}
		}
	}
	maxX = (maxX + 1) * TILE_SIZE; // on converti les coordonnees en pixel
	maxY = (maxY + 1) * TILE_SIZE; //(+1 car on commence a la ligne/colone 0) puis on multipllie par la taille d'une tile
}

void Map::draw(RenderWindow &window)
{
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a; // initialisation de varables pour la suite

	mapX = startX / TILE_SIZE; // initialisation de mapX a la 1er colode que l'on doit decouper
	x1 = (startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	mapY = startY / TILE_SIZE; // pareil pour mapY
	y1 = (startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	// on dessine la carte en commancant par startX et startY on commance par y1 jusqu'a y2 (de 0 a 600 pixels) et on se decale de TILE_SIZE (32 pixels) a chaque fois
	for (y = y1; y < y2; y += TILE_SIZE)
	{
		mapX = startX / TILE_SIZE; // a chaque debut de ligne on reinitialise mapX qui contien la colone

		for (x = x1; x < x2; x += TILE_SIZE) // a chaque colone on dessine la bonne tileen allant de 0 a 600 pixels
		{
			a = tile[mapY][mapX]; // suivant le numero de la tile

			ysource = a / 10 * TILE_SIZE; // calcul pour obtenir les coordonnees de la tile e decouper
			xsource = a % 10 * TILE_SIZE; // ici il y a 10 tiles par ligne

			tileSet.setPosition(Vector2f(x, y)); // decoupage de la tile
			tileSet.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
			window.draw(tileSet); // on dessine la tile

			mapX++; // incrementation de mapX
		}
		mapY++; // incrementation de mapY
	}
}

void Map::testDefilement(void) // fonction temporaire de defilement
{
	if (startX < maxX - SCREEN_WIDTH - 10)

		startX += 10;
}
