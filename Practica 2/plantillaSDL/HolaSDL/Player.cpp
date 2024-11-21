#include "Player.h"
#include "Game.h"


Player::Player(Game* g, Point2D<double> pos, Texture* texture, int lives)
	: SceneObject(g, pos, g->getTexture(Game::MARIO))
{
	game = g;
	direction = Vector2D<int>(0,0);

	lives = maxLives;

	textureM = g->getTexture(Game::MARIO);		// textura inicial de mario
	textureS = g->getTexture(Game::SUPERMARIO); // textura supermario

	marioFrame = 0;

	marioState = MARIO;
	grounded = true;
	position = pos;
	groundedYPos = pos.getY();
}

void Player::render() const
{
	SDL_Rect destRect;

	if (marioState == SUPERMARIO) {
		destRect.w = textureS->getFrameWidth() * 1.7;
		destRect.h = textureS->getFrameHeight() * 1.7;
		destRect.y = (position.getY() * TILE_SIDE) - (destRect.h - textureM->getFrameHeight());
	}
	else {
		destRect.w = textureM->getFrameWidth();
		destRect.h = textureM->getFrameHeight();
		destRect.y = position.getY() * TILE_SIDE;
	}

	// posicion
	destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
	
	// Usa el flip segun la direccion
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; //esta estructura es un if-else por si no lo conocias

	if (marioState != SUPERMARIO) 
		textureM->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
	else
		textureS->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{

	manageInvencible();
	//updateRect();

	moveMario();

	updateTexture();

	updateOffset();

	updateAnims();

}

void Player::updateTexture()
{
	if (marioState != SUPERMARIO) texture = textureM;
	else texture = textureS;
}


void Player::updateRect() {
	destRect.h = texture->getFrameHeight() * 2;
	destRect.w = texture->getFrameWidth() * 2;
	destRect.x = position.getX() * TILE_SIDE;
	destRect.y = position.getY() * TILE_SIDE;
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

Collision Player::hit(const SDL_Rect& rect, Collision::Target t)
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
		if (frameTimer >= 45) {  // Velocidad del ciclo
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

	if (screenX > TILE_SIDE * WINDOW_WIDTH / 2 && game->getMapOffset() < 6000) {
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
	if (!invencible) 
	{
		if (marioState == SUPERMARIO)
		{
			marioState = MARIO;
			position.setY(position.getY() + 0.5);
		}
		else
		{
			if (lives > 0) {
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

Collision Player::tryToMove(Vector2D<double> v, Collision::Target t)
{
	return Collision();
}

void Player::moveMario()
{
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

	if (keySpace && grounded && !canJump) {
		direction = Vector2D<int>(0, -1);
		maxHeight = position.getY() - 5;
		grounded = false;
		isFalling = false;
	}

	//MOV VER
	if (!grounded) {
		if (!isFalling && position.getY() > maxHeight) 
		{
			new_position.setY(position.getY() - 0.003 + 0.001);  //GRAVEDAD

			new_rect.h = new_position.getY() * 2;
			new_rect.w = new_position.getX() * 2;
			new_rect.x = position.getX() * TILE_SIDE;
			new_rect.y = position.getY() * TILE_SIDE;

			// si no hay colision -> actualiza la posicion
			if (!(game->checkCollisions(new_rect, Collision::Target::PLAYER).collides)) 
			{
				position.setY(new_position.getY());

				destRect.h = texture->getFrameHeight() * 2;
				destRect.w = texture->getFrameWidth() * 2;
				destRect.x = position.getX() * TILE_SIDE;
				destRect.y = position.getY() * TILE_SIDE;
			}
			// en caso de haberla cae
			else 
			{
				isFalling = true;

				new_position.setY(position.getY() + 0.0002);

				new_rect.h = new_position.getY() * 2;
				new_rect.w = new_position.getX() * 2;
				new_rect.x = position.getX() * TILE_SIDE;
				new_rect.y = position.getY() * TILE_SIDE;

				// si no hay colision -> actualiza la posicion
				if (!(game->checkCollisions(new_rect, Collision::Target::PLAYER).collides))
				{
					position.setY(new_position.getY());

					destRect.h = texture->getFrameHeight() * 2;
					destRect.w = texture->getFrameWidth() * 2;
					destRect.x = position.getX() * TILE_SIDE;
					destRect.y = position.getY() * TILE_SIDE;
				}
				// en caso de haberla mantiene la posicion inicial
			}
		}
		else 
		{
			isFalling = true;

			new_position.setY(position.getY() + 0.0002);

			new_rect.h = new_position.getY() * 2;
			new_rect.w = new_position.getX() * 2;
			new_rect.x = position.getX() * TILE_SIDE;
			new_rect.y = position.getY() * TILE_SIDE;

			// si no hay colision -> actualiza la posicion
			if (!(game->checkCollisions(new_rect, Collision::Target::PLAYER).collides))
			{
				position.setY(new_position.getY());

				destRect.h = texture->getFrameHeight() * 2;
				destRect.w = texture->getFrameWidth() * 2;
				destRect.x = position.getX() * TILE_SIDE;
				destRect.y = position.getY() * TILE_SIDE;
			}
			// en caso de haberla mantiene la posicion inicial
		}

		if (position.getY() >= groundedYPos) 
		{
			position.setY(groundedYPos);
			grounded = true;
			isFalling = false;
		}
	}

	//cout << position.getX() << endl;

	// MOV HOR
	// condicion para que no se salga por la izquierda
	if ((((position.getX() * TILE_SIDE) - game->getMapOffset()) + (dir.getX())) >= 0)
	{
		if (dir.getX() != 0)
		{
			new_position.setX(position.getX() + (dir.getX() * MARIO_SPEED));
			new_position.setY(position.getY());

			new_rect.h = new_position.getY() * 2;
			new_rect.w = new_position.getX() * 2;
			new_rect.x = position.getX() * TILE_SIDE;
			new_rect.y = position.getY() * TILE_SIDE;

			// si no hay colision -> actualiza la posicion
			if(!(game->checkCollisions(new_rect, Collision::Target::PLAYER).collides))
			{
				position.setX(new_position.getX());
				position.setY(new_position.getY());

				destRect.h = texture->getFrameHeight() * 2;
				destRect.w = texture->getFrameWidth() * 2;
				destRect.x = position.getX() * TILE_SIDE;
				destRect.y = position.getY() * TILE_SIDE;
			}
			// en caso de haberla mantiene la posicion inicial
			else
			{
				if (dir.getX() == 1) {
					dir.setX(-1);
					position.setY(position.getY());
					position.setX(new_position.getX());
				}	
				else if (dir.getX() == -1) {
					dir.setX(1);
					position.setY(position.getY());
					position.setX(new_position.getX());
				}
			}
		}

		if (!grounded)
			position.setY(position.getY() + 0.001);

		if (position.getY() >= groundedYPos)
		{
			position.setY(groundedYPos);
			grounded = true;
			isFalling = false;
		}
	}

	canJump = keySpace;
}