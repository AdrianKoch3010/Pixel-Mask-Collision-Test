
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>

#include "PixelMask.h"

using namespace std;
using namespace sf;


int main()
{
	RenderWindow window(VideoMode(600, 800, 32), "Pixel Mask Test", Style::Default);
	Event eve;
	Texture texture;
	Sprite sprite;

	texture.loadFromFile("Resources/animation.png");
	sprite.setTexture(texture);

	// For testing the inverse transform
	sprite.move(30, 105);
	sprite.rotate(20);
	sprite.setOrigin(20, 10);
	sprite.scale(Vector2f(2.0f, 0.5f));

	PixelMask pixelMask(sprite);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Add views
	View defaultView = window.getDefaultView();
	View gameView = defaultView;

	// Limit the framerate for easier movement
	window.setVerticalSyncEnabled(true);
	////////////////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		Vector2f clickPosition(0.0f, 0.0f);
		bool clicked = false;

		while (window.pollEvent(eve))
		{
			if (eve.type == Event::KeyReleased)
			{
				if (eve.key.code == Keyboard::Key::Escape)
					window.close();
			}
			else if (eve.type == Event::Closed)
			{
				window.close();
			}
			else if (eve.type == Event::MouseButtonReleased)
			{
				if (eve.mouseButton.button == Mouse::Button::Left)
				{
					clicked = true;
					clickPosition.x = eve.mouseButton.x;
					clickPosition.y = eve.mouseButton.y;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////////////
		// Update the view
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
			gameView.move(0, 1);
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			gameView.move(0, -1);
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			gameView.move(1, 0);
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			gameView.move(-1, 0);
		if (Keyboard::isKeyPressed(Keyboard::Key::R))
			gameView = defaultView;
		//////////////////////////////////////////////////////////////////////////////////

		// Call the update function
		if (clicked)
		{
			cout << endl << endl << "Mouse clicked at: " << clickPosition.x << ", " << clickPosition.y;

			// reverse the view transforms
			clickPosition = window.mapPixelToCoords(static_cast<Vector2i>(clickPosition));
			// reverse the sprite (transformable) transforms
			clickPosition = sprite.getInverseTransform().transformPoint(clickPosition);
			if (pixelMask.contains(clickPosition))
			{
				cout << endl << "The sprite has been clciked";
			}
		}

		window.clear(Color::Magenta);
		window.setView(gameView);
		window.draw(sprite);
		window.display();
	}

	cout << endl << endl << "Press any key to end the program...";
	_getch();
	return EXIT_SUCCESS;
}