//TODO: Move this all to an executive class 

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainCharacter.h"
#include "Cowboy.h"
#include "Skeleton.h"
#include "tile.h"
#include <vector>
#include "link.h"
#include "map.h"

using size = std::vector<MainCharacter>::size_type;

Link cowboy;
std::vector<MainCharacter> mainCharacters;
Skeleton skeleton;
bool enabled = false;
std::vector<sf::Texture> textures;
void separateImageToArrayOfTextures(const std::string& filename);



void runContinuousPartOfGame() {
	int counter = 0;
	separateImageToArrayOfTextures("warrior spritesheet calciumtrice.png");
	while (true)
	{
		system("CLS");
		if (enabled) {
			if (counter % 100 == 0)
			{
				mainCharacters.push_back(MainCharacter(textures));
			}
			for (size i = 0; i < mainCharacters.size(); i++)
			{
				mainCharacters[i].chaseUser(cowboy.xPos(), cowboy.yPos());
			}
			sf::sleep(sf::milliseconds(100));
			counter++;
			skeleton.chasePlayer(cowboy.xPos(), cowboy.yPos());
		}
	}

}

int main()
{
	sf::Thread thread(&runContinuousPartOfGame);
	thread.launch();
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works");
	GrassyTile tile({ 0.0f, 0.0f });
	GrassyTile tile2({500.f, 300.f});
	GrassyMap grassyMap(1000, 600);

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			enabled = true;
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				cowboy.moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				cowboy.moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				cowboy.moveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cowboy.moveLeft();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				cowboy.attack();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		tile.drawTo(window);
		tile2.drawTo(window);
		grassyMap.drawTo(window);
		cowboy.drawTo(window);
		for (size i = 0; i < mainCharacters.size(); i++)
		{
			mainCharacters[i].drawCharacter(window);
		}
		skeleton.drawTo(window);
		window.display();

	}

	thread.terminate();
}




void separateImageToArrayOfTextures(const std::string& filename) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sf::Texture texture;
			texture.loadFromFile(filename, sf::IntRect(j * 32, i * 32, 32, 32));
			textures.push_back(texture); // error thrown here, does not seems to effect anything
			system("CLS");
		}
	}
}
