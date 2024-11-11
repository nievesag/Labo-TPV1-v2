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

	marioState = MARIO;
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

	// Usa el flip segun la direccion
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; //esta estructura es un if-else por si no lo conocias

	texture->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{
	//game->checkCollisions(destRect, true);

	//collider.h = texture->getFrameHeight() * 2;
	//collider.w = texture->getFrameWidth() * 2;
	//collider.x = position.getX();
	//collider.y = position.getY();

	//cout << collider.h << " " << collider.w << " " << collider.x << " " << collider.y << endl;
	  // Caja de colisión actual
	moveMario();

	updateOffset();

	updateAnims();
}

void Player::handleEvents(const SDL_Event& event)
{
	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	// pulsar
	if (event.type == SDL_KEYDOWN) 
	{
		moving = true;
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
		moving = false;
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

Collision Player::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;

	return c;
}

void Player::updateAnims()
{
	if (!grounded) {
		//Frame del salto
		marioFrame = 6;
	}
	else if (keyA != keyD) {
		frameTimer++;
		if (frameTimer >= 150) {  // Velocidad del ciclo
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

	if (screenX > TILE_SIDE * WINDOW_WIDTH / 2 && game->getMapOffset() < 6100) {
		game->addMapOffset(1);
	}
}

bool Player::checkFall()
{
	// para ver si se ha caido a un agujero
	return (position.getY() * TILE_SIDE - game->getMapOffset()) >= WINDOW_HEIGHT + texture->getFrameHeight();
}

void Player::manageDamage()
{
	if (marioState == 's')
	{
		marioState = 'm';
	}
	else
	{
		if(lives > 0) lives--;

		if (lives <= 0) alive = false;
	}
}

void Player::moveMario()
{

	// Velocidad inicial de salto y gravedad
	const double JUMP_VELOCITY = -10.0;
	const double GRAVITY = 0.5;
	const double MAX_JUMP_HEIGHT = 4.0;

	Vector2D<double> dir(0, 0);

	if (keyA == keyD) {
		dir = Vector2D<double>(0, 0);
	}

	if (keyA != keyD) {
		if (keyA) {
			dir = Vector2D<double>(-1, 0);
			flipSprite = true;  // Activa el flip al mover a la izquierda
		}
		else if (keyD) {
			dir = Vector2D<double>(1, 0);
			flipSprite = false; // Desactiva el flip al mover a la derecha
		}
	}


	// Salto
	if (keySpace && grounded && !canJump) {
		velocityY = JUMP_VELOCITY;
		grounded = false;
		maxHeight = position.getY() - MAX_JUMP_HEIGHT; // Calcula la altura máxima en Y
	}

	// Aplicar gravedad si no está en el suelo
	if (!grounded) {
		// Incrementar la velocidad en Y por la gravedad
		velocityY += GRAVITY;

		// Calcular la nueva posición tentativa de Mario en Y
		double newY = position.getY() + velocityY;

		// Comprobar si Mario ha alcanzado o superado la altura máxima
		if (newY <= maxHeight) {
			newY = maxHeight; // Fija la posición en la altura máxima
			velocityY = 0;    // Anula la velocidad hacia arriba
		}

		// Crear un rectángulo de colisión para la nueva posición vertical
		SDL_Rect new_rect;
		new_rect.h = texture->getFrameHeight();
		new_rect.w = texture->getFrameWidth();
		new_rect.x = position.getX() * TILE_SIDE;
		new_rect.y = newY * TILE_SIDE;

		// Comprobación de colisión en la nueva posición vertical
		if (!(game->checkCollisions(new_rect, true).collides)) {
			position.setY(newY); // Actualiza la posición si no hay colisión
		}
		else {
			// Si hay colisión, Mario toca el suelo
			position.setY(groundedYPos);
			velocityY = 0;
			grounded = true;
		}
	}

	//if (keySpace && grounded && !canJump) {
	//	direction = Vector2D<int>(0, -1);
	//	maxHeight = position.getY() - 4;
	//	grounded = false;
	//	isFalling = false;
	//}

	////MOV VER
	//if (!grounded) {
	//	if (!isFalling && position.getY() > maxHeight) 
	//	{
	//		new_position.setY(position.getY() - MARIO_SPEED);

	//		new_rect.h = new_position.getY() * 2;
	//		new_rect.w = new_position.getX() * 2;
	//		new_rect.x = position.getX() * TILE_SIDE;
	//		new_rect.y = position.getY() * TILE_SIDE;

	//		// si no hay colision -> actualiza la posicion
	//		if (!(game->checkCollisions(new_rect, true).collides)) 
	//		{
	//			position.setY(new_position.getY());

	//			destRect.h = texture->getFrameHeight() * 2;
	//			destRect.w = texture->getFrameWidth() * 2;
	//			destRect.x = position.getX() * TILE_SIDE;
	//			destRect.y = position.getY() * TILE_SIDE;
	//		}
	//		// en caso de haberla cae
	//		else 
	//		{
	//			isFalling = true;

	//			new_position.setY(position.getY() + MARIO_SPEED);

	//			new_rect.h = new_position.getY() * 2;
	//			new_rect.w = new_position.getX() * 2;
	//			new_rect.x = position.getX() * TILE_SIDE;
	//			new_rect.y = position.getY() * TILE_SIDE;

	//			// si no hay colision -> actualiza la posicion
	//			if (!(game->checkCollisions(new_rect, true).collides))
	//			{
	//				position.setY(new_position.getY());

	//				destRect.h = texture->getFrameHeight() * 2;
	//				destRect.w = texture->getFrameWidth() * 2;
	//				destRect.x = position.getX() * TILE_SIDE;
	//				destRect.y = position.getY() * TILE_SIDE;
	//			}
	//			// en caso de haberla mantiene la posicion inicial
	//		}
	//	}
	//	else 
	//	{
	//		isFalling = true;

	//		new_position.setY(position.getY() + MARIO_SPEED);

	//		new_rect.h = new_position.getY() * 2;
	//		new_rect.w = new_position.getX() * 2;
	//		new_rect.x = position.getX() * TILE_SIDE;
	//		new_rect.y = position.getY() * TILE_SIDE;

	//		// si no hay colision -> actualiza la posicion
	//		if (!(game->checkCollisions(new_rect, true).collides))
	//		{
	//			position.setY(new_position.getY());

	//			destRect.h = texture->getFrameHeight() * 2;
	//			destRect.w = texture->getFrameWidth() * 2;
	//			destRect.x = position.getX() * TILE_SIDE;
	//			destRect.y = position.getY() * TILE_SIDE;
	//		}
	//		// en caso de haberla mantiene la posicion inicial
	//	}



	//	if (position.getY() >= groundedYPos) 
	//	{
	//		new_position.setY(groundedYPos);

	//		new_rect.h = new_position.getY() * 2;
	//		new_rect.w = new_position.getX() * 2;
	//		new_rect.x = position.getX() * TILE_SIDE;
	//		new_rect.y = position.getY() * TILE_SIDE;

	//		// si no hay colision -> actualiza la posicion
	//		if (!(game->checkCollisions(new_rect, true).collides))
	//		{
	//			position.setY(groundedYPos);

	//			grounded = true;
	//			isFalling = false;
	//			dir.setY(0);
	//		}
	//	}
	//}

	// MOV HOR
	// condicion para que no se salga por la izquierda
	if ((((position.getX() * TILE_SIDE) - game->getMapOffset()) + (dir.getX())) >= 0) 
	{
		if (dir.getX() != 0)
		{
			new_position.setX(position.getX() + (dir.getX() * MARIO_SPEED));
			//new_position.setY(position.getY());

			new_rect.h = new_position.getY() * 2;
			new_rect.w = new_position.getX() * 2;
			new_rect.x = position.getX() * TILE_SIDE;
			new_rect.y = position.getY() * TILE_SIDE;

			// si no hay colision -> actualiza la posicion
			if(!(game->checkCollisions(new_rect, true).collides))
			{
				position.setX(new_position.getX());

				destRect.h = texture->getFrameHeight() * 2;
				destRect.w = texture->getFrameWidth() * 2;
				destRect.x = position.getX() * TILE_SIDE;
				destRect.y = position.getY() * TILE_SIDE;
			}
			// en caso de haberla mantiene la posicion inicial
		}
	}

	canJump = keySpace;
}