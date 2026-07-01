#include <SFML/Graphics.hpp>

int main()
{
	const int WINDOW_WIDTH = 512;
	const int WINDOW_HEIGHT = 480;
	const float WALL_THICKNESS = 10;
	const float DIVIDER_THICKNESS = 3;

	sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Pong" );

	// Walls
	sf::RectangleShape top_wall({WINDOW_WIDTH, WALL_THICKNESS});
	sf::RectangleShape bottom_wall({WINDOW_WIDTH, WALL_THICKNESS});
	bottom_wall.setPosition({0, WINDOW_HEIGHT-WALL_THICKNESS});

	// Divider
	sf::RectangleShape divider({DIVIDER_THICKNESS, WINDOW_HEIGHT});
	divider.setPosition({WINDOW_WIDTH/2 - (DIVIDER_THICKNESS/2), 0});

	while ( window.isOpen() )
	{
		// Handle window close
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();

		window.draw(top_wall);
		window.draw(bottom_wall);
		window.draw(divider);

		window.display();
	}
}
