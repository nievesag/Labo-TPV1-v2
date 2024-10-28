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
	destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
	destRect.y = (position.getY() * TILE_SIDE);
	
	//texture->renderFrame(destRect, 0, marioFrame);

	// Usa el flip seg�n la direcci�n
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; //esta estructura es un if-else por si no lo conocias

	texture->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{
	moveMario();

	updateOffset();

	updateAnims();
	cout << (position.getX() * TILE_SIDE) - game->getMapOffset() << endl;

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

void Player::updateAnims()
{
	if (!grounded) {
		//Frame del salto
		marioFrame = 6;
	}
	else if (keyA != keyD) {
		frameTimer++;
		if (frameTimer >= 200) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 4;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (animationFrame == 0 || animationFrame == 3) marioFrame = 2;
			else if (animationFrame == 1) marioFrame = 3;
			else if (animationFrame == 2) marioFrame = 4;
		}
	}
	else {
		//Cuando esta quieto
		marioFrame = 0;
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

	if (screenX > TILE_SIDE * WINDOW_WIDTH / 2) {
		game->addMapOffset(1);
	}
}

bool Player::checkFall()
{
	return (position.getY() * TILE_SIDE - game->getMapOffset()) >= WINDOW_HEIGHT + texture->getFrameHeight();
}

void Player::moveMario()
{
	// Se queda quieto si A y D est�n presionadas simult�neamente
	if (keyA == keyD) {
		direction = Vector2D<int>(0, 0);
	}

	// Movimiento horizontal
	if (keyA != keyD) {

		if (keyA) {
			dir = Vector2D<double>(-1, 0);
			flipSprite = true;  
		}
		else if (keyD) {
			dir = Vector2D<double>(1, 0);
			flipSprite = false; 
		}
	}


	if (keySpace && grounded && !canJump) {
		direction = Vector2D<int>(0, -1); 

		if (keyA) direction = Vector2D<int>(-1, 0);  // Izquierda
		else if (keyD) direction = Vector2D<int>(1, 0); // Derecha
	}

	// Salto
	if (keySpace && grounded && !spacePressed) {
		direction = direction + Vector2D<int>(0, -1); 

		maxHeight = position.getY() - 3; 
		grounded = false;
		isFalling = false;
	}

	// Movimiento en el eje X
	position.setX(position.getX() + (dir.getX() * MARIO_SPEED * 0.09));

	// Saltando
	if (!grounded) {
		if (!isFalling && position.getY() > maxHeight) { // Aun no llega a la altura maxima
			position.setY(position.getY() + (direction.getY() * MARIO_SPEED * 0.1));
		}
		else { //Alcanza la altura maxima y comienza a descender
			isFalling = true;
			position.setY(position.getY() + MARIO_SPEED * 0.1);
		}

		// Chequeo de aterrizaje
		if (position.getY() >= groundedYPos) {
			position.setY(groundedYPos); // Aterriza en el suelo
			grounded = true;
			isFalling = false; 
		}
	}

	// Limita el movimiento a los l�mites del mapa
	if (position.getX() < 0) position.setX(0);

	spacePressed = keySpace;
}
