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
	vel = Vector2D<double>(velX, velY);
	groundedYPos = pos.getY();
}

void Player::render() const
{
	SDL_Rect destRect;

	if (marioState == SUPERMARIO) {
		destRect.w = textureS->getFrameWidth() * 4.7;
		destRect.h = textureS->getFrameHeight() * 4.7;
		destRect.y = (position.getY() * TILE_SIDE) - (destRect.h - textureM->getFrameHeight());
	}
	else {
		destRect.w = textureM->getFrameWidth() * 2;
		destRect.h = textureM->getFrameHeight() * 2;
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
	if (marioState == 0)
		texture = textureM;
	else if (marioState == 1)
		texture = textureS;

	moveMario();

	manageCollisions(tryToMove(getNextMoveVector(), Collision::ENEMIES));

	manageInvencible();
	//updateRect();


	updateTexture();

	updateOffset();

	updateAnims();

	checkFall();

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

void Player::updateAnims()
{
	if (!grounded) {
		//Frame del salto
		marioFrame = 6;
	}
	else if (keyA != keyD) {
		frameTimer++;
		if (frameTimer >= 120) {  // Velocidad del ciclo
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

void Player::checkFall()
{
	// para ver si se ha caido a un agujero
	if (position.getY() > deadH) {
		position.setY(10);
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



Vector2D<double> Player::getNextMoveVector()
{
	return Vector2D<double>(direction.getX() * vel.getX(), direction.getY() - vel.getY());
}

void Player::moveMario()
{
	if (keyA == keyD) {
		direction = Vector2D<int>(0, 0);
	}

	else if (keyA != keyD) {
		if (keyA) {
			direction = Vector2D<int>(-1, 0);
			flipSprite = true;
		}
		else if (keyD) {
			direction = Vector2D<int>(1, 0);
			flipSprite = false;
		}
	}

	if (keySpace)
	{
		direction.setY(-1);
	}
	else
		direction.setY(0);
}