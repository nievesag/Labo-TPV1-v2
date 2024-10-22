#include "Player.h"


Player::Player()
{

}

Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> position; // pos de mario
	in >> lives;	// num de vidas
}