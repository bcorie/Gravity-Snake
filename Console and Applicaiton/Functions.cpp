#include "Functions.h"
#include <iostream>
#include <GravitySnake.h>
#include <conio.h>
using namespace std;

void display(b2Body* snake)
{
	cout << "Target: (" << getTargetPosition().x << ", " << getTargetPosition().y << ")  ";
	cout << "Snake: (" << snake->GetPosition().x << ", " << snake->GetPosition().y << ")  " << endl;
}


float b2dToSFMLX(float xVal, float windowWidth)
{
	float winHalf = windowWidth / 2.0f;
	return -xVal;
}

float b2dToSFMLY(float yVal, float windowHeight)
{
	float winHalf = windowHeight / 2.0f;
	if (yVal < winHalf) return yVal - winHalf;
	if (yVal > winHalf) return yVal + winHalf;
	return yVal;
}
