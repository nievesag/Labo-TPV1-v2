#pragma once

#include "GameObject.h"

#include "GameList.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
    // movimiento
    Vector2D<int> position;    // Coordenadas (x, y)
    Vector2D<int> speed;       // Velocidad (vx, vy)
    Vector2D<int> direction;

    // representacion
    int width, height;        // Tamaño del objeto
	Texture* texture;
	SDL_RendererFlip flip;
	bool flipSprite;
	double scale;
    SDL_Rect destRect;

    // animacion
	int frame;
	int frameTimer;

    // logica
    bool isAlive;
    Collision c;
    bool canMove; // para que no se salga de la pantalla por la izquierda
    GameList<SceneObject>::anchor _anchor; // Ancla a la lista de objetos del juego

public:
    SceneObject(Game* game, Vector2D<int> pos, Texture* texture, Vector2D<int> s);

    SceneObject(Game* game, Vector2D<int> pos, Texture* texture);

    virtual ~SceneObject() {}

	SceneObject(const SceneObject& s); // constructor copia
	SceneObject& operator=(const SceneObject& s); // asignacion por copia

	// ---- hit ----
	// colisiones
	virtual void manageCollisions(Collision collision) = 0;
	virtual void render() override;

    virtual void update() override {}

    // Recibe rectangulo que se vera afectado y si viene del jugador
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // igual este metodo aqui no tiene mucho sentido por el tilemap
    //virtual void checkAlive() = 0;
    virtual void updateAnim() = 0;

	Point2D<int> getPosition() { return position; }
	
	// Para gestion de cola de objetos ->
	//	Se usa para poder clonar los objetos polimorficamente e insertar copias en la lista de objetos del juego
	//	Para evitar tener que recargar el mapa desde el archivo al reiniciar el nivel (muere mario)
	//	Hay que tener en cuenta que cuando se reinicia el nivel todos los objetos del juego (salvo el jugador y
	//	el tilemap) han de ser destruidos y reemplazados por objetos nuevos
	//	Lo mismo ha de ocurrir si el reinicio se produce en un punto de control y no al principio del mapa

	// devuelve una copia del objeto sobre el que se aplica (solo se aplicara sobre los objetos de objectQueue)
	virtual SceneObject* clone() const = 0;

    // Getters virtuales
    virtual SDL_Rect getCollisionRect() const;

    virtual SDL_Rect getRenderRect() const;

    // Cuando el objeto SceneObject se destruya, siguiendo la secuencia natural de 
    // eliminacion de los objetos, se destruira su atributo anchor y esto implicara
    // automaticamente su eliminacion de la lista
    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

protected:
    // El metodo protegido tryToMove concentra el codigo de la comprobacion
    // de las colisiones para todos los objetos del juego. Recibe un vector
    // con el movimiento que se quiere aplicar al objeto, prueba el movimiento
    // en cambos ejes y devuelve la informacion de tipo Collision
    // Target: a que hiere 
    // - Si lo usamos en goomba, target sera player.
    // - Si lo usamos en caparazon, target sera both.
    // - Si lo usamos en player, target sera none.
     Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);

    void setScale(double n) { scale = n; }

    void setAlive(bool a) { isAlive = a;  }
};