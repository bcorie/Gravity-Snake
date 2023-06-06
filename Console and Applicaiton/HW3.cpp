// Starter code by Andrew Wheeland
// Logic and implementation by Corie Beale
// IGME 209 : RIT

#define SFML_STATIC
#include <iostream>
#include <GravitySnake.h>
#include <iomanip>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Functions.h"
using namespace std;

/* GravitySnake.h is the header file for a dynamically linked library (dll) called
* GravitySnake.dll. The GravitySnake library is a set of functions that satisfy the
* requirements of HW2 - Gravity Snake. In order to allow you to complete HW3 without
* the need for a done version of HW2, this DLL has been created. Using it's functions,
* you can implement HW3 without the HW2 code. A full breakdown of it's functions
* can be found in the homework document.
*/

int main()
{
	// window setup
	float const WINDOW_WIDTH  = 800;
	float const WINDOW_HEIGHT = 800;

	// Improves formatting of console output.
	cout << fixed << showpoint << setprecision(2);

	// bound delcaration
	float floorMod = -WINDOW_HEIGHT / 2 + 50.0f; // buffer for snake body
	float ceilMod  = WINDOW_HEIGHT / 2 - 50.0f; // buffer for UI and text
	float leftMod  = 0.0f;
	float rightMod = WINDOW_WIDTH - 50.0f;
	// -350, 350, 0, 750

	//Sets the possible bounds of where the target can spawn here.
	//This function is from the DLL.
	setTargetBounds(leftMod, rightMod, floorMod, ceilMod);

	//Create the physics world, and all the objects. Return a pointer to the snake body.
	//These functions are from the DLL.
	initVariables(b2Vec2(0.0f, -98.0f));
	createFloor(b2Vec2(rightMod / 2, floorMod), 400.0f, 1.0f);
	createCeiling(b2Vec2(rightMod / 2, ceilMod), 400.0f, 1.0f);
	createLeftWall(b2Vec2(leftMod, 0.0f), 1.0f, 400.0f);
	createRightWall(b2Vec2(rightMod, 0.0f), 1.0f, 400.0f);
	b2Body* snake = createSnake(b2Vec2(0.0f, 5.0f), 0.5f, 0.5f);

	// ui and game border
	sf::RectangleShape inGameCeilingBorder(sf::Vector2f(WINDOW_WIDTH, 1.0f));
	inGameCeilingBorder.setFillColor(sf::Color(150, 150, 150));
	inGameCeilingBorder.setPosition(0.0f, 50.0f);

	/* The following block of code is from the SFML drawing tutorial. To accomplish
	* the requirements of HW3, you will need to take the code above and modify it
	* to work within the code provided below. Rather than using the display() method
	* like above, you will need to render shapes to represent the walls, snake, and
	* target.
	* 
	* Note, you should be creating your SFML shapes BEFORE the while (window.isOpen())
	* loop, then render them WITHIN the loop. Additionally, the while(targetsCollected < 2)
	* loop from up above will need to be turned into an if statement so that it doesn't
	* block SFML from rendering new frames to the window.
	*/

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity Snake");

	// Shape creation
	sf::RectangleShape snakeShape(sf::Vector2f(50, 50));
	snakeShape.setFillColor(sf::Color::Yellow);
	float snakeX, snakeY;

	sf::CircleShape targetShape(10.0f);
	targetShape.setFillColor(sf::Color::Red);
	float targetX, targetY;

	// input and scoring variables
	int targetsCollected = 0;
	int score = 0;
	int totalKeypresses = 0;
	// Array for if a key is pressed. Handles two keys being held at the same time.
	bool keyHolds[3] = { false, false, false }; // W, A, D


	// Font: Tw Cen MT Regular
	sf::Font font;
	font.loadFromFile("TCM_____.TTF");

	// Text setup
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setPosition(WINDOW_WIDTH / 2.5f, 7.5);

	// startup menu vars
	sf::Text gameNameText;
	gameNameText.setString("GRAVITY SNAKE");
	gameNameText.setFont(font);
	gameNameText.setCharacterSize(72);	
	gameNameText.setPosition(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 5.0f);
	gameNameText.setFillColor(sf::Color::Yellow);

	sf::Text controlsText;
	controlsText.setString("Use WAD to move.\nCollect 5 floating targets with\nthe highest score you can!\n\nPress enter to start...");
	controlsText.setFont(font);
	controlsText.setCharacterSize(48);
	controlsText.setPosition(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 3.0f);
	controlsText.setFillColor(sf::Color(200, 150, 0));

	// results menu vars
	sf::Text resultsText;
	resultsText.setFont(font);
	resultsText.setCharacterSize(56);
	resultsText.setPosition(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 5.0f);
	resultsText.setFillColor(sf::Color(100, 255, 100));

	sf::Text scoreFinalText;
	scoreFinalText.setFont(font);
	scoreFinalText.setCharacterSize(48);
	scoreFinalText.setPosition(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 2.5f);
	scoreFinalText.setFillColor(sf::Color(0, 255, 100));

	sf::Text replayText;
	replayText.setFont(font);
	replayText.setCharacterSize(36);
	replayText.setPosition(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.5f);
	replayText.setFillColor(sf::Color(255, 255, 0));

	bool play = false, newHighScore = false;
	int highScore = 0;
	int const TARGETS = 5;


	// run the program as long as the window is open
	while (window.isOpen())
	{
		//cout << score << " " << highScore << endl;

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		window.pollEvent(event);

		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();

		// clear the window with black color
		window.clear(sf::Color::Black);
		
		// start menu
		if (play == false)
		{
			window.draw(gameNameText);
			window.draw(controlsText);
			
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				play = true;
			}

		}

		else
		{
			if (targetsCollected < TARGETS)
			{
				// update shape positions
				snakeX = b2dToSFMLX(snake->GetPosition().x, WINDOW_WIDTH);
				snakeY = b2dToSFMLY(snake->GetPosition().y, WINDOW_HEIGHT);
				snakeShape.setOrigin(snakeX, snakeY);

				targetX = b2dToSFMLX(getTargetPosition().x, WINDOW_WIDTH);
				targetY = b2dToSFMLY(getTargetPosition().y, WINDOW_HEIGHT);
				targetShape.setOrigin(targetX, targetY);

				// draw everything
				window.draw(snakeShape);
				window.draw(targetShape);
				window.draw(inGameCeilingBorder);
				window.draw(scoreText);

				// end the current frame
				window.display();


				//This function advances the physics world by deltaTime, and returns the deltaTime in seconds.
				//This function is from the DLL.
				float deltaTime = updateWorldAndReturnDeltaTime();

				//Process input and apply forces to the snake.
				//Removed from Functions.h for more versatility and score measuring
				#pragma region input handling
// direct key presses
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					// only valid keypress if on ground
					// prevents flying and multi-jump
					if (snakeY <= -740.0f || keyHolds[0] == true)
					{
						if (keyHolds[0] == false) // new press
						{
							keyHolds[0] = true;
							totalKeypresses++;
						}

						applyForceToSnake(b2Vec2(0.0f, 100000.0f));
					}
				}
				else
				{
					keyHolds[0] = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (keyHolds[1] == false) // new press
					{
						keyHolds[1] = true;
						totalKeypresses++;
					}

					applyForceToSnake(b2Vec2(-10000.0f, 0.0f));
				}
				else
				{
					keyHolds[1] = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if (keyHolds[2] == false) // new press
					{
						keyHolds[2] = true;
						totalKeypresses++;
					}

					applyForceToSnake(b2Vec2(10000.0f, 0.0f));
				}
				else
				{
					keyHolds[2] = false;
				}

#pragma endregion

				//This function checks if the snake is close to the target. It takes in a maximum collision distance.
				//This function is from the DLL.
				// offsets for collision check calculation
				if ((((snakeX < targetX) || (snakeY > targetY)) && checkCollisionAndMoveTarget(55.0f)) || // snake left or top of target: 55.0f
					(((snakeX - 25.0f > targetX) || (snakeY < targetY)) && checkCollisionAndMoveTarget(5.0f)))	 // snake right or bottom of target: 5.0f
				{
					targetsCollected++;
					if (totalKeypresses == 0) score += 1000;
					else score += (1.0f / totalKeypresses) * 1000;
					totalKeypresses = 0;
					scoreText.setString("Score " + to_string(score));
				}
			}
			else
			{
				// results
				window.clear(sf::Color::Black);
				
				int tempHighScore = highScore;
				if (score >= highScore)
				{
					resultsText.setString("You finished with a\nscore of " + to_string(score) + "!");
					scoreFinalText.setString("NEW HIGHSCORE!\nOld highscore: " + to_string(tempHighScore));
					replayText.setString("Play again for a new highscore?\nPress enter to start...");
					newHighScore = true;
				}
				else
				{
					resultsText.setString("You finished with a\nscore of " + to_string(score) + ".");
					scoreFinalText.setString("You were off by your old\nhighscore by " + to_string(tempHighScore - score) + ".");
					replayText.setString("Play again for a highscore?\nPress enter to start...");
					newHighScore = false;
				}
				
				window.draw(resultsText);
				window.draw(scoreFinalText);
				window.draw(replayText);

				window.display();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					play = true;
					targetsCollected = 0;
					if (newHighScore) highScore = score;
					score = 0;
					scoreText.setString("Score: 0");
				}
			}
		}
	}
	
	// memory cleanup
	//delete[] keyHolds;
	//delete& snake;
	//snake = nullptr;

	releaseVariables();
}