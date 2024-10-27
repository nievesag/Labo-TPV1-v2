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
}

void Player::render() const
{

	SDL_Rect destRect;
	// tamanio
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	//posicion
	destRect.x = position.getX() * TILE_SIDE;
	destRect.y = position.getY() * TILE_SIDE;


	texture->renderFrame(destRect, 0, 0);
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
	/*destRect.x = position.getX();
	destRect.y = position.getY();*/
}

void Player::moveMario() {
	const float step = 1.0f;

	// Movimiento horizontal
	if (keyA) {
		position.setX(position.getX() - step);
		keyA = false;
	}
	else if (keyD) {
		position.setX(position.getX() + step);
		keyD = false;
	}

	// Control del salto
	if (keySpace && grounded) {
		direction.setY(-5.0f);  // Velocidad inicial de salto
		grounded = false;  // en el aire
		keySpace = false;  // Resetea el salto hasta la siguiente pulsación
	}

	if (!grounded) {
		direction.setY(direction.getY() + 0.3f);  // Gravedad aplicada

		// Actualizar la posición de Mario
		position.setY(position.getY() + direction.getY());

		// Chequeo de colisión con el suelo
		if (position.getY() >= 13) {  // Detectar el suelo
			position.setY(13);  // Ajustar posición al suelo
			grounded = true;  // Restablecer el estado de aterrizaje
			direction.setY(0);  // Reiniciar la dirección vertical
		}
	}

	// Limitar el movimiento horizontal al área del juego
	if (position.getX() < 0) position.setX(0);  // Límite a la izquierda

	cout << position.getY() << endl;
}
