// Author: Corie Beale

#pragma once
#include <Box2D/Box2D.h>

class Snake
{
public:
	bool isCollided(b2Body* snake, b2Vec2* target);
	void applyForces(b2Body* snake, char input);
	void moveTarget(b2Vec2* target);
};

