#include "Player.h"

using namespace std;
using namespace sf;

Player::Player()
{
	// Chargement de la spritesheet de Player
	if (!texturePlayer.loadFromFile("assets/graphics/spritesheet.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement du spritesheet du Player." << endl;
	}
	else
		spritePlayer.setTexture(texturePlayer);

	playerPosX = 0;
	playerPosY = 0;
	saveX = 0;
	saveY = 0;
	direction = 0;
	etat = 0;
	frameMax = frameTimer = frameNumber = 0;
	w = 0;
	h = 0;
	xSprite = 0;
	ySprite = 0;
	isGround = false;
	isCeiling = false;
	isJumping = false;
	jumpTimer = MAX_JUMP;
};

void Player::initialize(Map &map)
{
	// etat + direction
	etat = IDLE;
	direction = RIGHT;
	timeBetween2Frames = IDLE_SPEED;

	// animation :
	frameNumber = 0;								 // On initialise le numéro de la frame ou commencer
	frameTimer = timeBetween2Frames; // On dit en cb de tps on change de frameMax
	// Ici timeBetween2Frames/60 sec.
	frameMax = 4;
	// hauteur et largeur du personnage pour spritesheet.
	h = PLAYER_HEIGHT;
	w = PLAYER_WIDTH;

	// initialisation des positions de départs et de respawn.
	playerPosX = map.getBeginX();
	playerPosY = map.getBeginY();

	spritePlayer.setPosition(50, 300);
};

void Player::deplacement(Input &input)
{
	if (!isGround)
	{
		etat = FALL;
		frameMax = 4;
		timeBetween2Frames = FALL_SPEED;
		spritePlayer.move(Vector2f(0, GRAVITE));
		if (input.getButton().left)
		{
			direction = LEFT;
			spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
		}

		if (input.getButton().right)
		{
			direction = RIGHT;
			spritePlayer.move(Vector2f(PLAYER_SPEED, 0));
		}
	}

	else if (input.getButton().left)
	{
		etat = WALK;
		frameMax = 10;
		timeBetween2Frames = WALK_SPEED;
		direction = LEFT;
		spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
		if (input.getButton().right)
		{
			spritePlayer.move(Vector2f(PLAYER_SPEED, 0));
			direction = RIGHT;
		}
	}

	else if (input.getButton().right)
	{
		etat = WALK;
		frameMax = 10;
		timeBetween2Frames = WALK_SPEED;
		direction = RIGHT;
		spritePlayer.move(Vector2f(PLAYER_SPEED, 0));

		if (input.getButton().left)
		{
			spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
			direction = LEFT;
		}
	}

	else
	{
		etat = IDLE;
		frameMax = 4;
		timeBetween2Frames = IDLE_SPEED;
	}

	if (isCeiling)
	{
		isJumping = false;
		jumpTimer = 0;
	}
	if (isWallR)
		spritePlayer.move(Vector2f(-PLAYER_SPEED - 2, 0));
	if (isWallL)
		spritePlayer.move(Vector2f(PLAYER_SPEED + 2, 0));
	if (isJumping)
	{
		spritePlayer.move(Vector2f(0, -JUMP_HEIGHT));
		etat = JUMP;
		frameMax = 6;
		timeBetween2Frames = JUMP_SPEED;

		if (input.getButton().left)
		{
			direction = LEFT;
			spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
		}

		if (input.getButton().right)
		{
			direction = RIGHT;
			spritePlayer.move(Vector2f(PLAYER_SPEED, 0));
		}
	}

	if (input.getButton().jump)
	{
		if (jumpTimer <= 0)
		{
			isJumping = false;
			if (isGround)
			{
				jumpTimer = MAX_JUMP;
			}
		}
		else
		{
			jumpTimer--;
			isJumping = true;
		}
	}
	else if (!input.getButton().jump)
	{
		isJumping = false;
		jumpTimer = 0;
		if (isGround)
		{
			jumpTimer = MAX_JUMP;
		}
	}

	else if (input.getButton().left)
	{
		etat = WALK;
		frameMax = 10;
		timeBetween2Frames = WALK_SPEED;
		direction = LEFT;
		spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
		if (input.getButton().right)
		{
			spritePlayer.move(Vector2f(PLAYER_SPEED, 0));
			direction = RIGHT;
		}
	}

	else if (input.getButton().right)
	{
		etat = WALK;
		frameMax = 10;
		timeBetween2Frames = WALK_SPEED;
		direction = RIGHT;
		spritePlayer.move(Vector2f(PLAYER_SPEED, 0));

		if (input.getButton().left)
		{
			spritePlayer.move(Vector2f(-PLAYER_SPEED, 0));
			direction = LEFT;
		}
	}
};

int Player::getPosX(void) const { return spritePlayer.getPosition().x; };
int Player::getPosY(void) const { return spritePlayer.getPosition().y; };

void Player::draw(RenderWindow &window)
{
	/* Gestion du timer */
	// Si notre timer (un compte à rebours en fait) arrive à zéro
	if (frameTimer <= 0)
	{
		// On le réinitialise
		frameTimer = timeBetween2Frames;

		// Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
		frameNumber++;

		// Mais si on dépasse la frame max, il faut revenir à la première :
		if (frameNumber >= frameMax)
			frameNumber = 0;
	}
	// Sinon, on décrémente notre timer
	else
		frameTimer--;

	ySprite = etat * h;
	xSprite = frameNumber * w;

	if (direction == LEFT)
	{
		spritePlayer.setTextureRect(IntRect(xSprite + 32, ySprite, -w, h));
		window.draw(spritePlayer);
	}

	else if (direction == RIGHT)
	{
		spritePlayer.setTextureRect(IntRect(xSprite, ySprite, w, h));
		window.draw(spritePlayer);
	}
};

void Player::mapColision(Map &map)
{
	spriteX = spritePlayer.getPosition().x;
	spriteY = spritePlayer.getPosition().y;

	for (i = 0; i <= 32; i++)
	{
		// Test collision sol
		if (map.getTile((spriteX + 37 - i) / 32, (spriteY + 33) / 32) > 1)
			isGround = true;
		else if (map.getTile((spriteX - 12 + i) / 32, (spriteY + 33) / 32) > 1)
			isGround = true;
		else
			isGround = false;
		// Test collision plafond
		if (map.getTile((spriteX + 37 - i) / 32, (spriteY + 12) / 32) > 1)
			isCeiling = true;
		else if (map.getTile((spriteX - 10 + i) / 32, (spriteY + 12) / 32) > 1)
			isCeiling = true;
		else
			isCeiling = false;

		// Test collision droite
		if (map.getTile((spriteX + 25) / 32, (spriteY + i - 1) / 32) > 1)
			isWallR = true;
		else
			isWallR = false;

		// Test collision droite
		if (map.getTile((spriteX + 2.5) / 32, (spriteY + i - 1) / 32) > 1)
			isWallL = true;
		else
			isWallL = false;
	}
}
