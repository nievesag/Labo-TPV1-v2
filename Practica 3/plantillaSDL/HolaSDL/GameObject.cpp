#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Game* g) : game(g)
{
}

GameObject::GameObject(GameState* s) : state(s)
{
}

GameObject::GameObject(Game* g, GameState* s) : game(g), state(s)
{
}

GameObject::~GameObject()
{
}