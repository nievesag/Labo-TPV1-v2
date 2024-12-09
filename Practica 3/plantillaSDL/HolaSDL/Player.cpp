#include "Player.h"

#include "AnimationState.h"
#include "Game.h"
#include "PlayState.h"

Player::Player(Game* g, Point2D<int> p, Texture* t, int l, Vector2D<int> s, PlayState* play)
	: SceneObject(g, p, t, s, play), lives(l)
{
	lives = 3;
	canMove = true;
	velX = 6;
	grounded = false;
	jumping = false;

	walkFrame = 0;
	flipSprite = true;
	flip = SDL_FLIP_NONE;

	marioState = MARIO;
	textureM = game->getTexture(Game::MARIO);		// textura inicial de mario
	textureS = game->getTexture(Game::SUPERMARIO); // textura supermario

	invencible = false;
	play->addEventListener(this);
	
}

void Player::render() const
{

	SceneObject::render();
}

void Player::update()
{
	updateRect();
	updateAnim();

	if (speed.getY() < SPEED_LIMIT)
		speed = speed + Vector2D<int>(0, GRAVITY);

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
		if (position.getX() - playState->getMapOffset() >= game->getWinWidth() / 2
			&& playState->getMapOffset() <= MAP_MAX_OFFSET)
		{
			playState->setMapOffset(playState->getMapOffset() + speed.getX());
		}
		canMove = true;
	}
	else if (speed.getX() < 0)
	{
		flip = SDL_FLIP_HORIZONTAL;

		if (position.getX() - playState->getMapOffset() < TILE_SIDE) canMove = false;
	}

	updateTexture();

	checkFall();

	finishLevel();

	marioState = game->getMarioState();

	//cout << speed.getX() << endl;
}

void Player::updateTexture()
{
	if (marioState != SUPERMARIO) 
	{
		setScale(2);
		texture = textureM;
	}
	else
	{
		setScale(1.5);
		texture = textureS;
	}
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colision
	SDL_Rect ownRect = getCollisionRect();

	// si la colision es con los enemies
	if (target == Collision::PLAYER && SDL_HasIntersection(&ownRect, &region) )
	{
		manageDamage();

		const std::function<bool()> animation = [this]()->bool { return manageAnimation(); };
		GameState* ps = new AnimationState(game, playState, animation );

		// lo pasa al gsMachine que ya luego hace sus cosas
		//game->getgsMachine()->pushState(ps);
	}

	return NO_COLLISION; // constante Collision{}
}

bool Player::manageAnimation()
{
	// mientras la altura en y sea menor (aun no se cae) -> lo hace caer
	if (position.getY() < deadH)
	{
		position.setY(position.getY()-10);
		return true;
	}
	return false; // se ha caido
}

void Player::manageDamage()
{
	if (!invencible)
	{
		if (marioState == SUPERMARIO)
		{
			marioState = MARIO;
		}
		else
		{
			if (lives > 0)
			{
				invencible = true;
				lives--;
			}

			if (lives <= 0) isAlive = false;
		}
	}

	invencible = true;
}

void Player::resetPosition(Vector2D<int> pos)
{
	position = pos;
}

void Player::finishLevel()
{
	cout << position.getX() << endl;
	if (position.getX() >= flagPosition && game->getCurrentLevel() == 1)
	{
		velX = 0;
		cout << "FINAL" << endl;
		game->setCurrentLevel(game->getCurrentLevel()+1);
		playState->setVictory(true);
		int k = game->getCurrentLevel();
		string level = std::to_string(k);
		
		

		if(game->getCurrentLevel() > game->getMaxWorlds())
		{
			game->setExit(true);
			
		}
		else
		{
			playState->reloadWorld(level, "../assets/maps/world");
		}
	}
	else if (position.getX() >= flag2Position && game->getCurrentLevel() == 2)
	{
		playState->setEndVictory(true);
	}
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
		frame = 6;
	}
	else {
		frame = 0;
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

void Player::handleEvent(const SDL_Event& event)
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

void Player::updateOffset()
{
	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset

	// CONVERSION DE COOR:
	// COOR TOTALES => la pos de mario sin convertir
	// COOR DE LA VISTA => COOR TOTALES - MAPOFFSET

	int screenX = position.getX() * TILE_SIDE - playState->getMapOffset();

	if (screenX > TILE_SIDE * WINDOW_WIDTH / 2 && playState->getMapOffset() < MAP_MAX_OFFSET)
	{
		playState->addMapOffset(1);
	}
}

void Player::checkFall()
{
	// para ver si se ha caido a un agujero
	if (position.getY() > deadH)
	{
		position.setY(10 * TILE_SIDE);
		playState->setFalled(true);
		
		playState->reloadWorld(to_string(game->getCurrentLevel()), "../assets/maps/world");
		playState->setFalled(false);
		position.setX(40);
		marioState = MARIO;
		lives--;
	}
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