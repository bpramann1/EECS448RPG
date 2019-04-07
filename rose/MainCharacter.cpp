#include<iostream>
#include<vector>
#include "MainCharacter.h"
#include "Math.h"
#include "ChaseUser.h"

#pragma region Constructors
MainCharacter::MainCharacter() 
	: animationPicNumber(1)			//This should be added 
	, dying(false)					//in the order they're 
	, mainCharacter()				//declared in the .h file
{
	separateImageToArrayOfTextures("warrior spritesheet calciumtrice.png");
}
#pragma endregion


void MainCharacter::separateImageToArrayOfTextures(std::string fileName) {
	sf::Texture texture;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j <10; j++)
		{
			if (!texture.loadFromFile(fileName, sf::IntRect(j * 32, i * 32, 32, 32)))
			{
				printf("Could not load main character image!");
			}
			textures[(10 * i) + j] = texture;
		}
	}

	
}

float MainCharacter::getXLocation() {
	return mainCharacter.getXPosition();
}

float MainCharacter::getYLocation() {
	return mainCharacter.getYPosition();
}

void MainCharacter::drawCharacter(sf::RenderWindow& window) {

	if (!dying)
	{
		if (nextCharacterState != death)
		{
			if (nextCharacterState != attacking) {
				if (nextCharacterState != walking)
				{
					nextCharacterState = mainCharacter.getCharacterState();
				}
				else {
					if ((mainCharacter.getCharacterState() == attacking) || (mainCharacter.getCharacterState() == death))
					{
						nextCharacterState = mainCharacter.getCharacterState();
					}
				}
			}
			else {
				if (mainCharacter.getCharacterState() == death)
				{
					nextCharacterState = death;
				}
			}
		}
	}
	else {
		currentCharacterState = death;
	}
	if (currentCharacterState == death)
	{
		dying = true;
	}
	sf::Sprite sprite;
	sprite.setTexture(textures[((int(currentCharacterState) + 1)*10) + (((animationPicNumber - (animationPicNumber % 5)) / 5) - 1)]);
	sprite.setOrigin(16.f, 16.f);
	if (!mainCharacter.getCharacterDirectionalOrientation()) {
		sprite.scale(-1.f, 2.f);
	}
	else
	{
		sprite.scale(1.f, 2.f);
	}
	sprite.setPosition(mainCharacter.getXPosition() + 32, mainCharacter.getYPosition() + 16);
	window.draw(sprite);
	animationPicNumber += 5;
	if (animationPicNumber > 59)
	{
		if (dying)
		{
			exit(0);
		}
		else {
			animationPicNumber = 1;
			currentCharacterState = nextCharacterState;
			mainCharacter.setCharacterState(idle);
			nextCharacterState = idle;
		}
	}

}

void MainCharacter::walkRight(float amount)
{
	if (amount>=1)
	{
		mainCharacter.setCharacterState(walking);
	}
	mainCharacter.increaseXPosition(amount);
	mainCharacter.setCharacterDirectionalOrientation(true);
}

void MainCharacter::walkLeft(float amount)
{
	if (amount >= 1)
	{
		mainCharacter.setCharacterState(walking);
	}
	mainCharacter.increaseXPosition(-1*amount);
	mainCharacter.setCharacterDirectionalOrientation(false);
}

void MainCharacter::walkUp(float amount)
{
	if (amount >= 1)
	{
		mainCharacter.setCharacterState(walking);
	}
	mainCharacter.increaseYPosition(-1*amount);
}

void MainCharacter::walkDown(float amount)
{
	if (amount>=1)
	{
		mainCharacter.setCharacterState(walking);
	}
	mainCharacter.increaseYPosition(amount);
}

void MainCharacter::setState(StateOfCharacter state)
{
	mainCharacter.setCharacterState(state);
}


void MainCharacter::chaseUser(float UserXPosition, float UserYPosition) {
	std::vector<float> coordinates = getChaseUserMovementAmount(UserXPosition, UserYPosition, getXLocation(), getYLocation());
	if (coordinates[0]>0)
	{
		walkRight(coordinates[0]);
	}
	else if (coordinates[0] < 0) {
		walkLeft(-1 * coordinates[0]);
	}
	if (coordinates[1] >0)
	{
		walkDown(coordinates[1]);
	}
	else if (coordinates[1] < 0) {
		walkUp(-1 * coordinates[1]);
	}
	if (coordinates[4] <17)
	{
		mainCharacter.setCharacterState(attacking);
	}







}