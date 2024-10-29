#include "Block.h"
#include "Game.h"

Block::Block(Game* g, std::istream& in)
	: game(g)
{
	in >> position;
	position = position - Point2D<double>(0, 1); // coloca bien al goomba
	in >> tipo;
	in >> accion;

	switch (tipo) {
	case 'B':
		tipo = LADRILLO;
		blockFrame = 5;
		break;
	case '?':
		tipo = SORPRESA;
		blockFrame = 0;
		break;
	case 'H':
		tipo = OCULTO;
		blockFrame = 4;
		break;
	}

	switch (accion) {
	case 'P':
		accion = POTENCIADOR;
		break;
	case 'C':
		accion = MONEDA;
		break;
	}

	texture = game->getTexture(Game::BLOCK); // textura inicial del bloque

	blockFrame = 0;
}

void Block::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
	destRect.y = (position.getY() * TILE_SIDE);

	texture->renderFrame(destRect, 0, blockFrame);
}

void Block::update()
{
	if (tipo == SORPRESA) {
		frameTimer++;
		if (frameTimer >= 150) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 4;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (animationFrame == 0 || animationFrame == 3) blockFrame = 2;
			else if (animationFrame == 1) blockFrame = 3;
			else if (animationFrame == 2) blockFrame = 4;
		}
	}
}

void Block::hit(SDL_Rect* rect)
{

}