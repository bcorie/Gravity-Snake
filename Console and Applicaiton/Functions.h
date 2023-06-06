#pragma once
#include <Box2D/Box2D.h>

void display(b2Body* snake);
float b2dToSFMLX(float xVal, float windowWidth);
float b2dToSFMLY(float xVal, float windowHeight);
	