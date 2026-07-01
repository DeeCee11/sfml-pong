#include <SFML/Graphics.hpp>

int main()
{
	const int WINDOW_WIDTH = 512;
	const int WINDOW_HEIGHT = 480;
	const float WALL_THICKNESS = 10;
	const float DIVIDER_THICKNESS = 3;
	const float PADDLE_THICKNESS = 10;
	const float PADDLE_LENGTH = 40;
	const float PADDLE_OFFSET = 20; // Paddle distance from side of screen
	const float PADDLE_SPEED = 0.1;

	sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Pong" );

	// Walls
	sf::RectangleShape top_wall({WINDOW_WIDTH, WALL_THICKNESS});
	sf::RectangleShape bottom_wall({WINDOW_WIDTH, WALL_THICKNESS});
	bottom_wall.setPosition({0, WINDOW_HEIGHT-WALL_THICKNESS});

	// Divider
	sf::RectangleShape divider({DIVIDER_THICKNESS, WINDOW_HEIGHT});
	divider.setPosition({WINDOW_WIDTH/2 - (DIVIDER_THICKNESS/2), 0});

	// Left paddle
	sf::RectangleShape left_paddle({PADDLE_THICKNESS, PADDLE_LENGTH});
	left_paddle.setPosition({PADDLE_OFFSET, WINDOW_WIDTH/2 - PADDLE_LENGTH/2});

	// Right paddle
	sf::RectangleShape right_paddle({PADDLE_THICKNESS, PADDLE_LENGTH});
	right_paddle.setPosition({WINDOW_WIDTH - PADDLE_OFFSET - PADDLE_THICKNESS, WINDOW_WIDTH/2 - PADDLE_LENGTH/2});

	while ( window.isOpen() )
	{
		// Handle window close
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) ) // TODO: switch Escape key exit to an event?
				window.close();
		}

		// Handle movement TODO - shorten clamping, move into function(s)?
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)){ // Left paddle up - Q
			left_paddle.move({0.0f, -PADDLE_SPEED});
			// Clamp upper y-pos
			if(left_paddle.getPosition().y <= WALL_THICKNESS) left_paddle.setPosition({PADDLE_OFFSET, WALL_THICKNESS}); 
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){ // Left paddle down - A
			left_paddle.move({0.0f, PADDLE_SPEED});
			// Clamp lower y-pos
			if(left_paddle.getPosition().y >= WINDOW_HEIGHT-PADDLE_LENGTH-WALL_THICKNESS) left_paddle.setPosition({PADDLE_OFFSET, WINDOW_HEIGHT-PADDLE_LENGTH-WALL_THICKNESS}); // TODO: shorten this oml
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){ // Right paddle up - P
			right_paddle.move({0.0f, -PADDLE_SPEED});
			// Clamp upper y-pos
			if(right_paddle.getPosition().y <= WALL_THICKNESS) right_paddle.setPosition({WINDOW_WIDTH - PADDLE_OFFSET - PADDLE_THICKNESS, WALL_THICKNESS}); 
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){ // Right paddle down - L
			right_paddle.move({0.0f, PADDLE_SPEED});
			// Clamp lower y-pos
			if(right_paddle.getPosition().y >= WINDOW_HEIGHT-PADDLE_LENGTH-WALL_THICKNESS) right_paddle.setPosition({WINDOW_WIDTH - PADDLE_OFFSET - PADDLE_THICKNESS, WINDOW_HEIGHT-PADDLE_LENGTH-WALL_THICKNESS}); // TODO: shorten this oml
		}

		window.clear();

		// Draw to screen TODO - move into function?
		window.draw(top_wall);
		window.draw(bottom_wall);
		window.draw(divider);
		window.draw(left_paddle);
		window.draw(right_paddle);

		window.display();
	}
}
