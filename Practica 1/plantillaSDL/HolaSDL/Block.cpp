#include "Block.h"
#include "Game.h"

Block::Block(Game* g, std::istream& in)
	: game(g)
{
	in >> position;
	position = position - Point2D<double>(0, 1); 

	in >> tipoL;
	in >> accionL;

	// Asignamos el tipo de bloque basado en el carácter leído
	switch (tipoL) {
	case 'B':
		tipo = LADRILLO;
		blockFrame = 5;
		break;
	case '?':
		tipo = SORPRESA;
		blockFrame = 0;  // Comienza la animación del bloque sorpresa desde el primer frame
		break;
	case 'H':
		tipo = OCULTO;
		blockFrame = 4;
		break;
	}

	// Asignamos la acción del bloque basado en el carácter leído
	switch (accionL) {
	case 'P':
		accion = POTENCIADOR;
		break;
	case 'C':
		accion = MONEDA;
		break;
	}

	texture = game->getTexture(Game::BLOCK); // textura inicial del bloque

	//blockFrame = 0;
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
		if (frameTimer >= 1050) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 3;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (animationFrame == 0 ) blockFrame = 1;
			else if (animationFrame == 1) blockFrame = 2;
			else if (animationFrame == 2) blockFrame = 0;
		}
	}
}

void Block::hit(const SDL_Rect& rect, bool fromPlayer)
{

}