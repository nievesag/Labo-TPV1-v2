#include "Infobar.h"
#include "Game.h"



InfoBar::InfoBar(Game* game, PlayState* ps): GameObject(game), playState(ps)
{
    texturaNumeros = game->getTexture(Game::NUMBERS);
    nombreMario = game->getTexture(Game::NOMBREMARIO);
    time = 400;
    score = 0;
    lastTimeUpdate = SDL_GetTicks();
    
}

InfoBar::~InfoBar()
{

}


void InfoBar::render() const
{
   
    SDL_Rect rectDestino;

    //Contador tiempo
    int auxTime = time; 
    int posX = game->getWinWidth() - 90; 
    int posY = 40; 
    int digitWidth = texturaNumeros->getFrameWidth() * 0.75; 
    int digitHeight = texturaNumeros->getFrameHeight() * 0.75; 

    for (int i = 0; i < 3; i++) 
    {
        int digit = auxTime % 10; //Pillas el ultimo digito, ultimo cero de 400
        auxTime /= 10; //Y lo quitas, ahora es 40

        rectDestino = { posX + ((2 - i) * digitWidth), posY, digitWidth, digitHeight };
        //Hace 0 0 4 -> 400 al reves
        texturaNumeros->renderFrame(rectDestino, 0, digit);
    }

    //Letras mario
    int letterWidth = nombreMario->getFrameWidth(); 
    int letterHeight = nombreMario->getFrameHeight(); 
    posX = 10; 
    posY = 10;

    const int nameFrames[] = { 0, 1, 2, 3, 4 }; 
    for (int i = 0; i < 5; i++)
    {
        rectDestino = { posX + (i * letterWidth), posY, letterWidth, letterHeight };
        nombreMario->renderFrame(rectDestino, 0, nameFrames[i]);
    }

    // Puntuación
    int auxScore = score;
    posX = 10; 
    posY = 10 + letterHeight + 5; 
    digitWidth = texturaNumeros->getFrameWidth() * 0.75;
    digitHeight = texturaNumeros->getFrameHeight() * 0.75;

    for (int i = 0; i < 6; i++)
    {
        int digit = auxScore % 10; 
        auxScore /= 10; 

        rectDestino = { posX + ((5 - i) * digitWidth), posY, digitWidth, digitHeight };
        texturaNumeros->renderFrame(rectDestino, 0, digit);
    }

    // Vidas
    int auxLives = lives;
    posX = game->getWinWidth() - 40; 
    posY = 10; 

    rectDestino = { posX, posY, digitWidth, digitHeight };
    texturaNumeros->renderFrame(rectDestino, 0, auxLives);

}

void InfoBar::update()
{
    uint32_t currentTime = SDL_GetTicks(); 
    if (time > 0 && currentTime - lastTimeUpdate >= 1000)
    {
        time--;                   
        lastTimeUpdate = currentTime; 
    }

    score = game->getPoints();
    lives = playState->getPlayer()->getLives();
}

