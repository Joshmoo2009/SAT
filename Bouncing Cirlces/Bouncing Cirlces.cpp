
//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <iostream>
#include "SFML\System\Time.hpp"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Pentagon.h"
#include "CollisionDetection.h"


using namespace std;
 
 
  
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
 
int main() 
{ 
	srand(NULL);
	sf::Time CollisionClock = sf::Time();
	int timer = 0;
	bool d_cir = false, d_tri = false, d_rect = false, d_pent = false;
    // Create the main window 
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Bouncing Balls"); 

	const int num = 2;
	const int ballNum = 2;
	const int triNum = num;
	const int rectNum = num;
	const int pentNum = num;

	CollisionDectection collision;
	Triangle triangleArray[triNum];
	Circle circleArray[ballNum];
	MyRectangle rectangleArray[rectNum];
	Pentagon pentagonArray[pentNum];

	vector<BouncingObject> collidingShapes;
	for (int i = 0; i != num; i++)
		collidingShapes.push_back(triangleArray[i]);

	for (int i = 0; i != num; i++)
		collidingShapes.push_back(rectangleArray[i]);

	for (int i = 0; i != num; i++)
		collidingShapes.push_back(pentagonArray[i]);
	#pragma region Font and text
	// Declare and load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.ttf");

	// Create a text
	sf::Text text0("0- None", font);
	text0.setCharacterSize(20);
	text0.setStyle(sf::Text::Bold);
	text0.setColor(sf::Color::Yellow);
	text0.setPosition(10,20);

	sf::Text text1("1- Circles", font);
	text1.setCharacterSize(20);
	text1.setStyle(sf::Text::Bold);
	text1.setColor(sf::Color::Yellow);
	text1.setPosition(10,50);

	sf::Text text2("2- Triangles", font);
	text2.setCharacterSize(20);
	text2.setStyle(sf::Text::Bold);
	text2.setColor(sf::Color::Yellow);
	text2.setPosition(10,80);

	sf::Text text3("3- Rectangle", font);
	text3.setCharacterSize(20);
	text3.setStyle(sf::Text::Bold);
	text3.setColor(sf::Color::Yellow);
	text3.setPosition(10,110);

	sf::Text text4("4- Pentagon", font);
	text4.setCharacterSize(20);
	text4.setStyle(sf::Text::Bold);
	text4.setColor(sf::Color::Yellow);
	text4.setPosition(10,140);

	sf::Text text5("5- All", font);
	text5.setCharacterSize(20);
	text5.setStyle(sf::Text::Bold);
	text5.setColor(sf::Color::Yellow);
	text5.setPosition(10,170);

	#pragma endregion

    // Start game loop 
    while (window.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (window.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                window.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                window.close(); 
			#pragma region Keypresses
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { d_cir = false;	d_tri = false;		d_rect = false;		d_pent = false;}//None active
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { d_cir = true;		d_tri = false;		d_rect = false;		d_pent = false;}//Circle active
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { d_cir = false;	d_tri = true;		d_rect = false;		d_pent = false;}//Triangle active
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { d_cir = false;	d_tri = false;		d_rect = true;		d_pent = false;}//Rectangle active
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { d_cir = false;	d_tri = false;		d_rect = false;		d_pent = true;}//Pentagon active
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { d_cir = true;		d_tri = true;		d_rect = true;		d_pent = true;}//All active
			#pragma endregion

			//if (Event.key.code == sf::Keyboard::A)
			//	triangleArray[0].setPosition(sf::Vector2f(sf::Mouse().getPosition(window)));
			//if (Event.key.code == sf::Keyboard::S)
			//	triangleArray[1].setPosition(sf::Vector2f(sf::Mouse().getPosition(window)));
        } 
         
		//prepare frame
        window.clear();
		window.setFramerateLimit(500);
		//window.draw(text);
		
		bool SAT = collision.CheckCollision(triangleArray[0], triangleArray[1]);
		cout << SAT << endl;
		
		//bool SAT = collision.CheckForCollisionSAT(rectangleArray[0], rectangleArray[1]);
		//cout << SAT << endl;

		#pragma region Draw Circles
		if(d_cir)
		{
			for (int index = 0; index != ballNum; index++)
			{
				circleArray[index].Update();
				circleArray[index].Draw(window);
			}
		}
		#pragma endregion
		#pragma region Draw Triangles
		if(d_tri)
		{
			for(int index = 0; index != triNum; index++)
			{
				//if (collision.SimpleCollision())
				//	collision.CheckForCollisionSAT();
				triangleArray[index].Update();
				triangleArray[index].Draw(window);
				for (int j = 1; j != triNum; j++)
				{
					if (index != j)
					{
						if (collision.CheckCollision(triangleArray[index], triangleArray[j]))
						{
							triangleArray[index].BounceObject(triangleArray[j].getPosition());
							triangleArray[j].BounceObject(triangleArray[index].getPosition());
						}
					}
				}
			}
		}
		#pragma endregion
		#pragma region Draw Rectangle
		if(d_rect)
		{
			for (int index = 0; index != rectNum; index++)
			{
				rectangleArray[index].Update();
				rectangleArray[index].Draw(window);
			}
		}
		#pragma endregion
		#pragma region Draw Pentagon
		if(d_pent)
		{
			for (int index = 0; index != pentNum; index++)
			{
				pentagonArray[index].Update();
				pentagonArray[index].Draw(window);
			}
		}
		#pragma endregion
		
		/*for (int i = 0; i != collidingShapes.size() - 1; i++)
		{
			for (int j = 0; j != collidingShapes.size() - 1; j++)
			{
				if (i != j)
				{
					//bool SAT = collision.CheckCollision(collidingShapes[i], collidingShapes[j]);
					//cout << SAT << endl;
					if (collision.CheckCollision(collidingShapes[i], collidingShapes[j]))
					{
						collidingShapes[i].BounceObject(collidingShapes[j].getPosition());
						collidingShapes[j].BounceObject(collidingShapes[i].getPosition());
					}
				}
			}
		}*/

		#pragma region Draw Text
		window.draw(text0);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		#pragma endregion
		
        // Finally, display rendered frame on screen 
        window.display(); 
    } //loop back for next frame
   
    return EXIT_SUCCESS; 
}
