#ifndef COLLISION_H
#define COLLISION_H

struct Collision {
    bool collides = false;      
    bool damages = false;        // indica si la colision implica danio

    SDL_Rect intersection;       // rectangulo de interseccion de la colision
    void* collider = nullptr;    // puntero al objeto con el que se colisiono

    operator bool() const { return collides; }

	// --- message
    // BLOQUES
    bool killBrick = false;
    bool setGrounded = false;

    // SETAS
    bool evolMario = false;
    bool spawnSeta = false;
	// ---

	// TARGET
	// A quien afecta esta colision
	// (usar en lugar de fromPlayer para objetos que atacan a enemigos y a jugador)
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,		// afecta al jugador
		BOTH = 3,		// afecta a ambos
	};
	
	// RESULT
	// Tipo de resultado de la colision
	enum Result {
		NONE,		// no ha habido colision
		DAMAGE,		// la colision hiere
		OBSTACLE,	// la colision impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colision horizontal
	int vertical = 0;     // profundidad de la colision vertical
};

#endif // COLLISION_H