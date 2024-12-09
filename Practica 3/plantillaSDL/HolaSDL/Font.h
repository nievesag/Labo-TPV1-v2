//﻿#pragma once
//#include <SDL_ttf.h>
//#include <string>
//#include "texture.h"
//
//
//class Font
//{
//	TTF_Font* font = nullptr;
//
//public:
//	Font() = default;
//	Font(const std::string& filename, int size);
//	Font(const Font& font) = delete;
//	~Font();
//	void load(const std::string& filename, int size);
//	void freeMemory();
//	SDL_Surface* generateSurface(const std::string& text, SDL_Color color) const;
//	Texture* generateTexture(SDL_Renderer* renderer, const std::string& text,
//		SDL_Color color) const;
//};