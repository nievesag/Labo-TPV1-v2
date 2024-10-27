#include "Player.h"
#include "Game.h"


Player::Player(Game* g, std::istream& in)
	: game(g)
{
	in >> position; // pos de mario
	//position = position - Point2D<double>(0, 1);
	in >> lives;	// num de vidas
	direction = Vector2D<int>(0,0);

	texture = game->getTexture(Game::MARIO); // textura inicial de mario

	marioFrame = 0;

	marioState = 'm';
	grounded = true;
}

void Player::render() const
{
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
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Player::moveMario()
{
	// PARAR
	if (keyA == keyD) // si se pulsan 2 teclas a la vez
	{
		direction = Vector2D<int>(0, 0);
	}
	// MOVER
	else if (keyA != keyD) // si NO se pulsan 2 teclas a la vez
	{
		// -- IZQ
		// direction X = -1
		if (keyA) direction = Vector2D<int>(-1, 0);
		// -- DER
		// direction X = +1
		else if (keyD) direction = Vector2D<int>(1, 0);
		// -- SALTO
		else if (keySpace && grounded)
		{
			grounded = false;
			direction = direction + Vector2D<int>(0, 1);
		}
	}
	// -- AGACHARSE
	// solo si es supermario
	// if (keyS && (marioState == 's')) ;

	// SALIR
	if (keyE) game->EndGame();

	// se mueve a mario
	position.setX(position.getX() + (direction.getX() * MARIO_SPEED));

	if(!grounded)
	{
		position.setY(position.getY() + (direction.getY() * MARIO_SPEED));
	}

	// para que no se salga por la izq, lo que ya se ha movido
	if (position.getX() < 0) position.setX(0);
}