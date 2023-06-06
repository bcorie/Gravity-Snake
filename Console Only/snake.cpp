// Author: Corie Beale

#include "Snake.h"
#include <iostream>
#include <time.h>
using namespace std;


/// <summary>
/// Checks if the snake is colliding
/// with the target using AABB collision type
/// </summary>
/// <param name="snake">head of snake</param>
/// <param name="target">target to hit</param>
/// <returns>true if colliding</returns>
bool Snake::isCollided(b2Body* snake, b2Vec2* target)
{
	if ((target->x - 0.2f <= snake->GetPosition().x) && // min x T < max x S
		(target->x + 0.2f >= snake->GetPosition().x) && // max x T > min x S
		(target->y + 0.2f >= snake->GetPosition().y) && // max y T > min y S
		(target->y - 0.2f <= snake->GetPosition().y))	 // min y T < max y S
	{
		return true;
	}

	return false;
}

/// <summary>
/// Applies a force onto the snake based
/// on player input
/// </summary>
/// <param name="snake_">snake head</param>
/// <param name="input">character key press</param>
void Snake::applyForces(b2Body* snake, char input)
{
    if (input == 'w' || input == 'W')
    {
        snake->ApplyForceToCenter(b2Vec2(0, 8000), true);
    }

    if (input == 'a' || input == 'A')
    {
        snake->ApplyForceToCenter(b2Vec2(-1000, 0), true);
    }

    if (input == 's' || input == 'S')
    {
        snake->ApplyForceToCenter(b2Vec2(0, -1000), true);
    }

    if (input == 'd' || input == 'D')
    {
        snake->ApplyForceToCenter(b2Vec2(1000, 0), true);
    }
}

/// <summary>
/// Moves the location of the target.
/// </summary>
/// <param name="target">target to move</param>
void Snake::moveTarget(b2Vec2* target)
{
    srand(time(NULL));
    rand();
    float randVal1 = -4.0f + (((float)rand() / (float)RAND_MAX) * 8); // between -5.0 and 5.0 as float
    float randVal2 = -4.0f + (((float)rand() / (float)RAND_MAX) * 8);
    (*target).Set(randVal1, randVal2);
}
