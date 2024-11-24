#include "Player.h"
#include "Game.h"

Player::Player(Game* game, Vector2D<int> pos)
	: SceneObject(game, pos, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	setScale(2);

	lives = 3;
	canMove = true;
	marioSpeed = 6;
	onGround = false;
	jumping = false;

	walkFrame = 0;
	_flipSprite = true;
	flip = SDL_FLIP_NONE;

}

void Player::render()
{
	SceneObject::render();
	updateAnim();
}

void Player::update()
{

	if (speed.getY() < SPEED_LIMIT)
		speed = speed + Vector2D<int>(0, GRAVITY);
		//speed += {0, GRAVITY};

	if (canMove)	c = tryToMove(speed, Collision::ENEMIES);
	else if (!canMove && speed.getY() != 0) c = tryToMove({ 0, speed.getY() }, Collision::ENEMIES);

	if (c.vertical)
	{
		if (speed.getY() > 0)
		{
			onGround = true;
			jumping = false;
		}

		speed.setY(0); // importante !!! @ marcos 
	}

	if (speed.getX() > 0)
	{
		flip = SDL_FLIP_NONE;

		// Limites
		if (position.getX() - game->getMapOffset() >= game->getWinWidth() / 2
			&& game->getMapOffset() <= MAP_MAX_OFFSET)
		{
			game->setMapOffset(game->getMapOffset() + speed.getX());
		}
		canMove = true;
	}
	else if (speed.getX() < 0)
	{
		flip = SDL_FLIP_HORIZONTAL;

		if (position.getX() - game->getMapOffset() < TILE_SIDE) canMove = false;
	}
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Player::clone() const
{
	return nullptr;
}




void Player::resetPlayer()
{
}

void Player::updateAnim()
{
	if (speed.getX() != 0 && onGround)
	{
		frameTimer++;
		if (frameTimer >= 1)
		{
			frameTimer = 0;

			int cycleLength = immune ? 4 : 5;
			walkFrame = (walkFrame + 1) % cycleLength;

			// Asigna el frame correspondiente
			if (walkFrame == 0 || walkFrame == (cycleLength - 1)) {
				frame = 2;
			}
			else if (walkFrame == 1) {
				frame = 3;
			}
			else if (walkFrame == 2) {
				frame = 4;
			}
			else if (immune && walkFrame == 3) {
				frame = -1;
			}
		}
	}
	else if (!onGround) {
		frame = 6; // Frame cuando está en el aire
	}
	else {
		frame = 0; // Frame cuando está en reposo
	}
}

void Player::jump()
{
	if (!jumping && onGround)
	{
		onGround = false;
		jumping = true;

		speed.setY(-30);
	}
}

void Player::isSupermario()
{
}

void Player::handleEvent(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			speed.setX(marioSpeed);
			break;

		case SDLK_LEFT:
			speed.setX(-marioSpeed);
			break;

		case SDLK_SPACE:
			jump();
			break;
		case SDLK_r:
			resetPlayer();
			break;
		}
	}
	else if (e.type == SDL_KEYUP) // soltar teclas
	{
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			speed.setX(0);
			break;

		case SDLK_LEFT:
			speed.setX(0);
			break;

		}
	}
}

void Player::manageCollisions(Collision c)
{
}

