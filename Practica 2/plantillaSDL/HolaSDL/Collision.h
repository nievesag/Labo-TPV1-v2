#ifndef COLLISION_H
#define COLLISION_H

struct Collision {

	// TARGET
	// A quien afecta esta colision
	// (usar en lugar de fromPlayer para objetos que atacan a enemigos y a jugador)
	enum Target {
		EMPTY = 1,		// para colision vacia
		ENEMIES = 2,	// afecta a enemigos
		PLAYER = 3,		// afecta al jugador
		BOTH = 4,		// afecta a ambos
	};
	
	// RESULT
	// Tipo de resultado de la colision
	enum Result {
		NONE,		// no ha habido colision
		DAMAGE,		// la colision hiere (a mario)
		OBSTACLE,	// la colision impide el movimiento
		ACTION
	};

	Target target = EMPTY;
	Result result = NONE;
	int horizontal = 0;   // profundidad de la colision horizontal
	int vertical = 0;     // profundidad de la colision vertical

	operator bool() const {
		bool c = false;
		if (result != NONE) {
			return true;
		}
	};

	SDL_Rect intersectionRect;

};

#endif // COLLISION_H