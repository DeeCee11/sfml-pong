#include <SFML/Graphics.hpp>

int main()
{
	// TODO: move constants into own file?
	// Window resolution - 512x480 like Namco System 11/12!
	const int WINDOW_WIDTH = 512;
	const int WINDOW_HEIGHT = 480;

	// Environment constants
	const float WALL_THICKNESS = 10;
	const float DIVIDER_THICKNESS = 3;

	// Paddle size + positioning
	const float PADDLE_SPEED = 0.1;
	const float PADDLE_THICKNESS = 10;
	const float PADDLE_LENGTH = 40;
	const float PADDLE_OFFSET_L = 20; // Left paddle distance from side of screen - serves as base distance
	const float PADDLE_OFFSET_R = WINDOW_WIDTH - PADDLE_OFFSET_L - PADDLE_THICKNESS;
	const float PADDLE_MAX_Y = WINDOW_HEIGHT - WALL_THICKNESS - PADDLE_LENGTH;


	// Window setup
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
	left_paddle.setPosition({PADDLE_OFFSET_L, WINDOW_WIDTH/2 - PADDLE_LENGTH/2});

	// Right paddle
	sf::RectangleShape right_paddle({PADDLE_THICKNESS, PADDLE_LENGTH});
	right_paddle.setPosition({PADDLE_OFFSET_R, WINDOW_WIDTH/2 - PADDLE_LENGTH/2});

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
			if(left_paddle.getPosition().y <= WALL_THICKNESS){
				left_paddle.setPosition({PADDLE_OFFSET_L, WALL_THICKNESS});
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){ // Left paddle down - A
			left_paddle.move({0.0f, PADDLE_SPEED});
			// Clamp lower y-pos
			if(left_paddle.getPosition().y >= PADDLE_MAX_Y){
				left_paddle.setPosition({PADDLE_OFFSET_L, PADDLE_MAX_Y});
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){ // Right paddle up - P
			right_paddle.move({0.0f, -PADDLE_SPEED});
			// Clamp upper y-pos
			if(right_paddle.getPosition().y <= WALL_THICKNESS){
				right_paddle.setPosition({PADDLE_OFFSET_R, WALL_THICKNESS});
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){ // Right paddle down - L
			right_paddle.move({0.0f, PADDLE_SPEED});
			// Clamp lower y-pos
			if(right_paddle.getPosition().y >= PADDLE_MAX_Y){
				right_paddle.setPosition({PADDLE_OFFSET_R, PADDLE_MAX_Y});
			}
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
