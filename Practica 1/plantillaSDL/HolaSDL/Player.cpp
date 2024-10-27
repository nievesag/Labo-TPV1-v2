#include "Player.h"
#include "Game.h"


Player::Player(Game* g, std::istream& in)
	: game(g)
{
	in >> position; // pos de mario
	position = position - Point2D<double>(0, 1);
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
	// tamanio
	int w = destRect.w;
	w = texture->getFrameWidth();
	int h = destRect.h;
	h = texture->getFrameHeight();

	// posicion
	int x = destRect.x;
	x = position.getX() * TILE_SIDE;
	int y = destRect.y;
	y = position.getY() * TILE_SIDE;

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
	else if ((keyA != keyD) && grounded) // si NO se pulsan 2 teclas a la vez y esta en el suelo
	{
		// -- IZQ
		// direction X = -1
		if (keyA) direction = Vector2D<int>(-1, 0);
		// -- DER
		// direction X = +1
		else if (keyD) direction = Vector2D<int>(1, 0);
		// -- SALTO
		else if (keySpace)
		{
			direction = direction + Vector2D<int>(0, 1);
			maxHeight = position.getY() + 4 * TILE_SIDE;
			grounded = false;
		}
	}
	// -- AGACHARSE
	// solo si es supermario
	// if (keyS && (marioState == 's')) ;

	// SALIR
	if (keyE) game->EndGame();

	// se mueve a mario
	position.setX(position.getX() + (direction.getX() * MARIO_SPEED));

	// 
	if(!grounded && position.getY() < maxHeight)
	{
		position.setY(position.getY() + (direction.getY() * MARIO_SPEED));
	}
	// llega a altura max
	if(!grounded && position.getY() >= maxHeight)
	{
		position.setY(position.getY() - (direction.getY() * MARIO_SPEED));
	}

	// comprobar si se esta en el suelo
	if(position.getY() == groundedYPos) grounded = true;

	// para que no se salga por la izq, lo que ya se ha movido
	if (position.getX() < 0) position.setX(0);
}