#include "Player.h"
#include "Game.h"


Player::Player(Game* g, std::istream& in)
	: game(g)
{
	in >> position; // pos de mario
	position = position - Point2D<double>(0, 1); // coloca bien a mario
	in >> lives;	// num de vidas
	direction = Vector2D<int>(0,0);

	texture = game->getTexture(Game::MARIO); // textura inicial de mario

	marioFrame = 0;

	marioState = 'm';
	grounded = true;

	groundedYPos = position.getY();
}

void Player::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX() * TILE_SIDE;
	destRect.y = position.getY() * TILE_SIDE;
	
	texture->renderFrame(destRect, 0, marioFrame);
}

void Player::update()
{
	moveMario();

	updateOffset();

	updateRect();
}

void Player::handleEvents(const SDL_Event& event)
{
	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	// pulsar
	if (event.type == SDL_KEYDOWN) 
	{
		// IZQ
		if (key == SDL_SCANCODE_A) keyA = true;

		// DER
		else if (key == SDL_SCANCODE_D) keyD = true;

		// ABJ
		else if (key == SDL_SCANCODE_S) keyS = true;

		// SALTAR
		else if (key == SDL_SCANCODE_SPACE) keySpace = true;

		// SALIR
		else if (key == SDL_SCANCODE_E) keyE = true;

		// OFFSET
		else if (key == SDL_SCANCODE_RIGHT) keyDer = true;
	}

	// despulsar
	else if (event.type == SDL_KEYUP) 
	{
		// IZQ
		if (key == SDL_SCANCODE_A) keyA = false;

		// DER
		else if (key == SDL_SCANCODE_D) keyD = false;

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

void Player::hit(SDL_Rect* rect)
{
	if (lives > 0) lives--;
	else isAlive = false;
}

void Player::updateRect()
{
	// posicion
	/*destRect.x = position.getX();
	destRect.y = position.getY();*/
}

void Player::updateOffset()
{
	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset
	if (position.getX() > game->getWinWidth() / 2) // lo de la movida de conversion entre coor de mundo y pantalla
	{
		game->addMapOffset(10);
	}
}

void Player::moveMario()
{
	Vector2D<double> dir(0, 0);

	// se queda quieto
	if(keyA == keyD) // si se pulsan 2 teclas a la vez
	{
		dir = Vector2D<double>(0, 0);
	}

	// MOVER
	if ((keyA != keyD) && grounded) // si NO se pulsan 2 teclas a la vez y esta en el suelo
	{
		// -- IZQ
		// direction X = -1
		if (keyA) {
			dir = Vector2D<double>(-1, 0);
			
		}
		// -- DER
		// direction X = +1
		else if (keyD) {
			dir = Vector2D<double>(1, 0);
		}
	}
	// -- SALTO
	else if (keySpace)
	{
		direction = direction + Vector2D<int>(0, -1);
		cout << position.getY() << endl;
		//maxHeight = position.getY() - 1; // por algun motivo si pongo a capon 12 si va????
		maxHeight = 12;
		grounded = false;
	}
	else if(keyDer)
	{
		if (game->getMapOffset() < 6100)  
		{
			game->addMapOffset(10);
		}
	}

	// se mueve a mario
	position.setX(position.getX() + (dir.getX() * MARIO_SPEED));

	// esta saltando
	if(!grounded)
	{
		// no ha llegado a la altura max
		if(position.getY() > maxHeight)
		{
			position.setY(position.getY() + (direction.getY() * MARIO_SPEED));
		}
		// llega a altura max
		if(position.getY() < maxHeight-1)
		{
			position.setY(0); // debug
			//position.setY(position.getY() - (direction.getY() * MARIO_SPEED));
		}

		cout << position.getY() << endl;
	}

	// comprobar si se esta en el suelo
	if(position.getY() == groundedYPos) grounded = true;

	// para que no se salga por la izq, lo que ya se ha movido
	if (position.getX() < 0) position.setX(0);
}