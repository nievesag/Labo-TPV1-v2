#include "Player.h"
#include "Game.h"

Player::Player(Game* g, Point2D<int> p, Texture* t, int l)
	: SceneObject(g, p, t), lives(l)
{
	maxLives = lives;

	textureM = game->getTexture(Game::MARIO);		// textura inicial de mario
	textureS = game->getTexture(Game::SUPERMARIO); // textura supermario

	marioFrame = 0;

	marioState = MARIO;
	grounded = true;
	flip = SDL_FLIP_NONE;
	velX = 6;
	flipSprite = true;
	setScale(2);
}

void Player::render()
{
	// Usa el flip segun la direccion
	/*SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if (marioState != SUPERMARIO)
	{
		textureM->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
	}
	else  textureS->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);*/

	SceneObject::render();
	updateAnim();
}

void Player::update()
{
	if (speed.getY() < SPEED_LIMIT) 
		speed = speed + Vector2D<int>(0, GRAVITY);

	if (canMove)
		c = tryToMove(speed, Collision::ENEMIES);


	else if (!canMove && speed.getY() != 0)
	{
		Vector2D<int> vec = Vector2D<int>(0, speed.getY());
		c = tryToMove(vec, Collision::ENEMIES);
	}

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

	//moveMario(limitX, limitY);

	//manageCollisions(tryToMove(getNextMoveVector(), Collision::ENEMIES));

	//manageInvencible();

	
	//updateRect();
	//updateOffset();


	//checkFall();

	cout << position.getX() << endl;
}

void Player::updateTexture()
{
	if (marioState != SUPERMARIO) texture = textureM;
	else texture = textureS;
}

void Player::updateRect()
{
	if (marioState == SUPERMARIO)
	{
		destRect.w = textureS->getFrameWidth() * 4.7;
		destRect.h = textureS->getFrameHeight() * 4.7;
		destRect.y = (position.getY() * TILE_SIDE) - (destRect.h - textureM->getFrameHeight());
	}
	else
	{
		destRect.w = textureM->getFrameWidth() * 2;
		destRect.h = textureM->getFrameHeight() * 2;
		destRect.y = position.getY();
	}

	// posicion
	destRect.x = position.getX() - game->getMapOffset();
}

void Player::handleEvents(const SDL_Event& event)
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

Collision Player::hit(const SDL_Rect& rect, Collision::Target t)
{
	Collision c;

	return c;
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
	return nullptr;
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

Vector2D<double> Player::getNextMoveVector()
{
	return Vector2D<double>(position.getX() + (direction.getX() * speed.getX()), position.getY() - speed.getY());
}

void Player::moveMario(bool moveX, bool moveY)
{
	/*#pragma region DIRECCIONES
	if (keyA == keyD) 
	{
		direction = Vector2D<int>(0, 0);
	}

	else if (keyA != keyD) 
	{
		if (keyA) 
		{
			direction = Vector2D<int>(-1, 0);
			flipSprite = true;
		}
		else if (keyD) 
		{
			direction = Vector2D<int>(1, 0);
			flipSprite = false;
		}
	}

	if (keySpace && grounded && !isFalling)
	{
		direction.setY(-1);
		maxHeight = position.getY() - 5;
		grounded = false;
	}
	else  direction.setY(0);
	#pragma endregion

	 Movimiento horizontal
	if (moveX && direction.getX() != 0 && (keyA || keyD))
	{
		
		cout << "siisi" << endl;
		speed.setX(velX);
		double auxVelX = speed.getX();
		position.setX(position.getX() + (direction.getX() * auxVelX));
		
	}

	if (position.getX() * TILE_SIDE - game->getMapOffset() <= 0 && direction.getX() == -1)
		position.setX(game->getMapOffset() / TILE_SIDE);

	if (position.getX() * TILE_SIDE + (TILE_SIDE * WINDOW_WIDTH) >= mapTiles * TILE_SIDE && direction.getX() == 1)
		position.setX(margen + (mapTiles * TILE_SIDE - (TILE_SIDE * WINDOW_WIDTH)) / TILE_SIDE);

	 Movimiento vertical
	if (position.getY() > maxHeight && keySpace && !isFalling && (moveY || direction.getY() == -1))
	{
		speed.setY(velY);
		double auxVelY = speed.getY();
		position.setY(position.getY() - auxVelY);
	}
	else if (moveY && (position.getY() <= maxHeight || direction.getY() == 0))
	{
		isFalling = true;
		position.setY(position.getY() + gravity);
	}*/

}