#include "Player.h"
#include "Game.h"


Player::Player(Game* g, std::istream& in)
	: game(g)
{
	in >> position; // pos de mario
	in >> lives;	// num de vidas
}

void Player::render() const
{
	texture->render(destRect);
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
		direction = Vector2D<double>(0, 0);
	}
	// MOVER
	else if (keyA != keyD) // si NO se pulsan 2 teclas a la vez
	{
		// -- IZQ
		// direction X = -1
		if (keyA) direction = Vector2D<double>(-1, 0);
		// -- DER
		// direction X = +1
		else if (keyD) direction = Vector2D<double>(1, 0);
	}
	// SALIR
	if (keyE) game->EndGame();

	// se mueve la mario
	position.setX(position.getX() + (direction.getX() * MARIO_SPEED));

	// para que no se salga por la izq, lo que ya se ha movido
	if (position.getX() < 0) position.setX(0);
}