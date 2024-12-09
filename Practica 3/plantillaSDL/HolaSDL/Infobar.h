#ifndef INFOBAR_H
#define INFOBAR_H

#include "GameObject.h"
#include "Texture.h"
class Game;
class PlayState;

class InfoBar : public GameObject
{
protected:
	Texture* texturaNumeros;
	Texture* nombreMario;
	int score;
	int time;
	int lives;
	uint32_t lastTimeUpdate;

	PlayState* playState;

public:

	InfoBar(Game* game, PlayState* ps);

	~InfoBar() override;

	void render() const override;

	void update() override;

	
};
#endif

