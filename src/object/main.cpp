#include "../include/main.h"

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "BlobDash"); // création de l'objet fenêtre

	// on affiche l'icon
	Image icon;
	if (!icon.loadFromFile("src/assets/graphics/icon.png"))
		exit(EXIT_FAILURE);

	window.setIcon(16, 16, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true); // activation de la syncronisation vertical

	// création des objet Input et Map.
	Input input;
	Player player;
	Map map;
	Music music;
	sf::View cam;

	player.initialize(map);

	if (!music.openFromFile("src/assets/sound/music.wav"))
		return -1;

	music.setVolume(0);
	music.setLoop(true);
	music.play();

	map.loadMap(); // appelle la fonction loadmap

	while (window.isOpen()) // permet de fermer le programme en cas de fermeture de la fenêtre
	{
		input.gestionInputs(window); // appelle la fonction gestion input

		window.clear(); // efface le contenue de la fenetre

		map.drawBackground(window); // appelle la fonction drawBackground

		map.draw(window); // appelle la fonction draw

		player.draw(window);

		player.mapColision(map);

		player.deplacement(input);

		cam.setCenter(player.getPosX(), 300);

		window.display(); // affiche la fenetre
	}

	return 0;
}
