#pragma once

#include "GameObject.h"

#include "GameList.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
    Vector2D<int> position;    // Coordenadas (x, y)
    Vector2D<int> speed;       // Velocidad (vx, vy)
    Vector2D<int> direction;
    int width, height;        // Tama�o del objeto

    int scale;

    Texture* texture;
    SDL_Rect destRect;

    bool _isAlive;

    Collision c;

    // para que no se salga de la pantalla por la izquierda
    bool canMove;

    // Ancla a la lista de objetos del juego
    GameList<SceneObject>::anchor _anchor;

    int frame;
    int frameTimer;
    bool _flipSprite;
    SDL_RendererFlip flip;

public:
    SceneObject(Game* game, Vector2D<int> pos, Texture* texture);

    virtual ~SceneObject() {}

    virtual void render() override;
    virtual void update() override {}

    // Recibe rectangulo que se vera afectado y si viene del jugador
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // igual este metodo aqui no tiene mucho sentido por el tilemap
    //virtual void checkAlive() = 0;
    virtual void updateAnim() = 0;

    // devuelva una copia del objeto sobre el que 
    // se aplica (solo se aplicar� sobre los objetos de objectQueue)
    virtual SceneObject* clone() const = 0;

    // Getters virtuales
    virtual SDL_Rect getCollisionRect() const;

    virtual SDL_Rect getRenderRect() const;

    // Cuando el objeto SceneObject se destruya, siguiendo la secuencia natural de 
    // eliminaci�n de los objetos, se destruir� su atributo anchor y esto implicar� 
    // autom�ticamente su eliminaci�n de la lista
    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

    virtual void manageCollisions(Collision c) = 0;

protected:
    // El m�todo protegido tryToMove concentra el c�digo de la comprobaci�n
    // de las colisiones para todos los objetos del juego. Recibe un vector
    // con el movimiento que se quiere aplicar al objeto, prueba el movimiento
    // en cambos ejes y devuelve la informaci�n de tipo Collision.
    // Target: a qu� hace da�o. 
    // - Si lo usamos en goomba, target sera player.
    // - Si lo usamos en caparazon, target sera both.
    // - Si lo usamos en player, target sera none.
     Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);

    void setScale(int n) { scale = n; }
};


