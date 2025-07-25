#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "map.h"

class Player
{
public:
	Player();
	void initialize(Map &map);
	void draw(sf::RenderWindow &window);
	void deplacement(Input &input);
	void mapColision(Map &map);

	int getPosX(void) const;
	int getPosY(void) const;

private:
	// position du Player
	int playerPosX;
	int playerPosY;
	int saveX, saveY;
	// Etat
	int direction;
	int etat;
	bool isGround, isWallR, isWallL, isCeiling, isJumping;
	// Variable pour animation
	int frameMax;
	int frameNumber;
	int frameTimer;
	int h, w;
	int xSprite, ySprite;
	int timeBetween2Frames;
	// variable colision et saut
	int i;
	int spriteX;
	int spriteY;
	int jumpTimer;
	// création objets texture et sprite
	sf::Texture texturePlayer;
	sf::Sprite spritePlayer;

	// constante
	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGHT = 32;
	// vitesse player
	const float PLAYER_SPEED = 1.5;
	// etats
	const int IDLE = 0;
	const int IDLE_SPEED = 15;
	const int WALK = 1;
	const int WALK_SPEED = 3;
	const int RUN = 2;
	const int RUN_SPEED = 6;
	const int JUMP = 3;
	const int JUMP_SPEED = 6;
	const int D_JUMP = 4;
	const int D_JUMP_SPEED = 0;
	const int DASH = 5;
	const int DASH_SPEED = 0;
	const int WALL = 6;
	const int WALL_SPEED = 0;
	const int DEAD = 7;
	const int DEAD_SPEED = 0;
	const int FALL = 8;
	const int FALL_SPEED = 20;
	// Gravité
	const int GRAVITE = 2;
	const int JUMP_HEIGHT = 5;
	const int MAX_JUMP = 30;
	// direction
	const int RIGHT = 1;
	const int LEFT = 2;
};
#endif
