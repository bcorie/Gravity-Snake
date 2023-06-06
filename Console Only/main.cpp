// Author: Corie Beale

#define SFML_STATIC

#include <iostream>
#include <conio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <time.h>
#include "Snake.h"

using namespace sf;
using namespace std;


int main()
{
    // world setup
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    #pragma region wall and body creation

    #pragma region ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f); // pos
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 5.0f); // box
    groundBody->CreateFixture(&groundBox, 0.0f);
    #pragma endregion

    #pragma region left wall
    b2BodyDef leftWallDef;
    leftWallDef.position.Set(-10.0f, 0.0f);
    b2Body* leftWallBody = world.CreateBody(&leftWallDef);

    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(5.0f, 6.0f);
    leftWallBody->CreateFixture(&leftWallBox, 0.0f);
    #pragma endregion

    #pragma region right wall
    b2BodyDef rightWallDef;
    rightWallDef.position.Set(10.0f, 0.0f);
    b2Body* rightWallBody = world.CreateBody(&rightWallDef);

    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(5.0f, 11.0f);
    rightWallBody->CreateFixture(&rightWallBox, 0.0f);
    #pragma endregion

    #pragma region ceiling
    b2BodyDef ceilingDef;
    ceilingDef.position.Set(0.0f, 10.0f);
    b2Body* ceilingBody = world.CreateBody(&ceilingDef);

    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox(6.0f, 5.0f);
    ceilingBody->CreateFixture(&ceilingBox, 0.0f);
    #pragma endregion

    #pragma endregion

    // snake creation
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    body->CreateFixture(&fixtureDef);

    

    // make snake object
    Snake snake;
    
    // target creation
    b2Vec2 target;
    snake.moveTarget(&target);

    #pragma region gameplay loop
    bool running = true;
    b2Vec2 position;
    Clock deltaClock;
    Time deltaTime;

    char input;
    char lastInput = '.';
    int keyPresses = 0, score = 0, targetsTotal = 1, targetsCollected = 0;
    while (running)
    {
        deltaTime = deltaClock.getElapsedTime();
        deltaClock.restart();
        world.Step(deltaTime.asSeconds(), 6, 2);

        position = body->GetPosition();


        // input handler
        if (_kbhit())
        {
            input = _getch();
            
            if (input == 27 || targetsCollected >= 5) // ESC key pressed
            {
                running = false;
            }

            if (input != lastInput) keyPresses++;
            lastInput = input;

            snake.applyForces(body, input);
        }


        // collision check
        if (snake.isCollided(body, &target))
        {
            // make new target
            snake.moveTarget(&target);
            targetsTotal++;
            targetsCollected++; 

            // score calculation
            if (keyPresses > 0)
            {
                score += (targetsCollected / (double)keyPresses) * 1000;
            }
        }

        // display
        cout << "Snake: (" << position.x << ", " << position.y << ")" <<
                "\tTarget: (" << target.x << ", " << target.y << ")";

        cout << "\tScore: " << score << " " << endl;

                
    }

    // final display
    cout << endl << endl <<
        "You have finished with a score of " << score << "!" << endl <<
        "You collected " << targetsCollected << " out of " << targetsTotal - 1 << " targets!" << endl;
    
    if (targetsCollected >= 5)
    {
        cout << "You have collected all 5 targets. Well done!" << endl;
    }

    cout << "Thank you for playing! Press ENTER to exit...";
    
    cin.ignore();

    #pragma endregion
    
}
