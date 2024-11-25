#include "Player.h"
#include "Game.h"

Player::Player(Game* game, Vector2D<int> pos)
	: SceneObject(game, pos, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	setScale(2);

	lives = 3;
	canMove = true;
	velX = 6;
	grounded = false;
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

	if (canMove)
		c = tryToMove(speed, Collision::ENEMIES);
	else if(!canMove && speed.getY() != 0) 
		c = tryToMove({ 0, speed.getY() }, Collision::ENEMIES);

	if (c.vertical)
	{
		if (speed.getY() > 0)
		{
			grounded = true;
			jumping = false;
		}

		speed.setY(0); 
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
	if (speed.getX() != 0 && grounded)
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
	else if (!grounded) {
		frame = 6; // Frame cuando est� en el aire
	}
	else {
		frame = 0; // Frame cuando est� en reposo
	}
}

void Player::jump()
{
	if (!jumping && grounded)
	{
		grounded = false;
		jumping = true;

		speed.setY(-30);
	}
}

void Player::isSupermario()
{
}

void Player::handleEvent(SDL_Event event)
{
	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	// pulsar
	if (event.type == SDL_KEYDOWN)
	{
		// IZQ
		if (key == SDL_SCANCODE_A)
		{
			speed.setX(-velX);
			keyA = true;
		}
		// DER
		else if (key == SDL_SCANCODE_D)
		{
			speed.setX(velX);
			keyD = true;
		}
		// ABJ
		else if (key == SDL_SCANCODE_S) keyS = true;

		// SALTAR
		else if (key == SDL_SCANCODE_SPACE)
		{

			keySpace = true;
			if (!jumping && grounded)
			{
				grounded = false;
				jumping = true;

				speed.setY(-30);
			}
		}
		// SALIR
		else if (key == SDL_SCANCODE_E) keyE = true;

		// OFFSET
		else if (key == SDL_SCANCODE_RIGHT) keyDer = true;
	}

	// despulsar
	else if (event.type == SDL_KEYUP)
	{
		// IZQ
		if (key == SDL_SCANCODE_A)
		{
			speed.setX(0);
			keyA = false;
		}
		// DER
		else if (key == SDL_SCANCODE_D)
		{
			speed.setX(0);
			keyD = false;
		}
		// ABJ
		else if (key == SDL_SCANCODE_S) keyS = false;

		// SALTAR
		else if (key == SDL_SCANCODE_SPACE) keySpace = false;

		// SALIR
		else if (key == SDL_SCANCODE_E) keyE = false;

		// OFFSET
		else if (key == SDL_SCANCODE_RIGHT) keyDer = false;
	}
}

void Player::manageCollisions(Collision c)
{
}


void Player::manageCollisions(Collision collision)
{
	// si el target soy yo...
	if(collision.target == Collision::PLAYER)
	{
		if(collision.result == Collision::DAMAGE)
		{
			manageDamage();
		}
	}
}

SceneObject* Player::clone() const
{
	return new Player(*this);
}

void Player::updateAnim()
{
	if (!grounded) 
	{
		// Frame del salto
		frame = 6;
	}
	else if (keyA != keyD) 
	{
		frameTimer++;
		if (frameTimer >= 120) // Velocidad del ciclo
		{  
			frameTimer = 0;
			marioFrame = (marioFrame + 1) % 4;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (marioFrame == 0 || frame == 3) frame = 2;
			else if (marioFrame == 1) frame = 3;
			else if (marioFrame == 2) frame = 4;
		}
	}
	else 
	{
		// Cuando esta quieto
		frame = 0;
	}
}

void Player::updateOffset()
{
	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset

	// CONVERSION DE COOR:
	// COOR TOTALES => la pos de mario sin convertir
	// COOR DE LA VISTA => COOR TOTALES - MAPOFFSET

	int screenX = position.getX() * TILE_SIDE - game->getMapOffset();

	if (screenX > TILE_SIDE * WINDOW_WIDTH / 2 && game->getMapOffset() < MAP_MAX_OFFSET) 
	{
		game->addMapOffset(1);
	}
}

void Player::checkFall()
{
	// para ver si se ha caido a un agujero
	if (position.getY() > deadH) 
	{
		position.setY(10 * TILE_SIDE);
		game->setMapOffset(0);
		position.setX(1);
		marioState = MARIO;
		lives--;
	}
}

void Player::manageDamage()
{
	if (!invencible) 
	{
		if (marioState == SUPERMARIO)
		{
			marioState = MARIO;
			position.setY(position.getY() + 0.5);
		}
		else
		{
			if (lives > 0) 
			{
				invencible = true;
				lives--;
			}

			if (lives <= 0) alive = false;
		}
	}

	invencible = true;
}

void Player::manageInvencible()
{
	if ((invCounter < maxInvCounter) && invencible)
	{
		invCounter++;
	}
	else 
	{
		invCounter = 0;
		invencible = false;
	}
}





