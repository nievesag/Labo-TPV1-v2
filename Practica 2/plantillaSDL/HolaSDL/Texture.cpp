#include <string>

#include <SDL_image.h>

#include "Texture.h"

using namespace std;

SDL_Texture*
Texture::loadTexture(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);

	if (surface == nullptr)
		throw "load surface \""s + filename + '"';

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (texture == nullptr)
		throw "create texture"s;

	return texture;
}

Texture::Texture(SDL_Renderer* renderer, SDL_Texture* texture, int rows, int columns)
  : renderer(renderer)
  , texture(texture)
  , nrows(rows)
  , ncolumns(columns)
{
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	frameWidth = width / ncolumns;
	frameHeight = height / nrows;
}

Texture::Texture(SDL_Renderer* renderer, const char* filename, int rows, int columns)
  : Texture(renderer, loadTexture(renderer, filename), rows, columns)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void
Texture::render() const
{
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void
Texture::render(const SDL_Rect& rect) const
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void
Texture::renderRect(const SDL_Rect& source) const
{
	SDL_RenderCopy(renderer, texture, &source, nullptr);
}

void
Texture::render(const SDL_Rect& rect, double angle, const SDL_Point* center, SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, center, flip);
}

void
Texture::renderFrame(const SDL_Rect& rect, int row, int col) const
{
	SDL_Rect origin{col * frameWidth, row * frameHeight, frameWidth, frameHeight};
	SDL_RenderCopy(renderer, texture, &origin, &rect);
}

void
Texture::renderFrame(const SDL_Rect& rect, int row, int col, SDL_RendererFlip flip) const
{
	SDL_Rect origin{col * frameWidth, row * frameHeight, frameWidth, frameHeight};
	SDL_RenderCopyEx(renderer, texture, &origin, &rect, 0, nullptr, flip);
}

void
Texture::renderFrame(const SDL_Rect& rect,
                     int row,
                     int col,
                     double angle,
                     const SDL_Point* center,
                     SDL_RendererFlip flip) const
{
	SDL_Rect origin{col * frameWidth, row * frameHeight, frameWidth, frameHeight};
	SDL_RenderCopyEx(renderer, texture, &origin, &rect, angle, center, flip);
}

void
Texture::render(const SDL_Rect& rect, SDL_Color color) const
{
	// Save the original color to recover it later
	SDL_Color original;
	SDL_GetTextureColorMod(texture, &original.r, &original.g, &original.b);

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	render(rect);
	SDL_SetTextureColorMod(texture, original.r, original.g, original.b);
}
