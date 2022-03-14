#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Field.h"

#define CELL_SIZE 50
#define SCREEN_SIZE 200

int main()
{
	sf::VertexArray gridVertical(sf::Lines);
	sf::VertexArray gridHorizontal(sf::Lines);

	for (int i = 0; i <= SCREEN_SIZE / CELL_SIZE; i++) {
		std::cout << i * CELL_SIZE << std::endl;
		gridVertical.append(sf::Vector2f(i * CELL_SIZE, 0));
		gridVertical.append(sf::Vector2f(i * CELL_SIZE, SCREEN_SIZE));
		gridHorizontal.append(sf::Vector2f(0, i * CELL_SIZE));
		gridHorizontal.append(sf::Vector2f(CELL_SIZE, i * SCREEN_SIZE));
	}
	gridVertical.append(sf::Vector2f(0, 0));
	gridVertical.append(sf::Vector2f(150, 150));

	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "serwus");
	//Field field;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (sf::Event::MouseButtonReleased)
				window.isOpen();//field.checkCell(sf::Mouse::getPosition(window).x / CELL_SIZE, sf::Mouse::getPosition(window).y / CELL_SIZE);
		}

		window.draw(gridHorizontal);
		window.draw(gridVertical);
		window.clear();
		window.display();
	}

	return 0;
}