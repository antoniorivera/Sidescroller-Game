#include "Player.h"
#include <iostream>

using namespace std;

void Player::init(int x, int y)
{
	hp = 100;
	standing = false;
	current_frame = 0;
	direction = 0;
	this->x = x;
	this->y = y;
	if (!texture.loadFromFile("protagonist_sprite_sheet.png"))
		cout << "Error loading protagonist_sprite_sheet.png" << endl;
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::Rect<int>(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
}

int Player::getX()
{ 
	return x; 
}

void Player::setX(int x)
{
	this->x = x;
}

int Player::getY()
{ 
	return y; 
}

void Player::setY(int y)
{
	this->y = y;
}

int Player::getV_X()
{ 
	return v_x; 
}

void Player::setV_X(int v_x)
{
	this->v_x = v_x;
}

int Player::getV_Y()
{ 
	return v_y; 
}

void Player::setV_Y(int v_y)
{
	this->v_y = v_y;
}

void Player::update()
{
	x += v_x;
	y += v_y;
	if (!standing && v_y <= 5)
		v_y++;
	sprite.setPosition(x, y);

	if (v_x != 0)
	{
		if (timer.getElapsedTime().asMilliseconds() > 200 && current_frame != 1)
		{
			new_frame = 1;
			timer.restart();
		}
		else if (timer.getElapsedTime().asMilliseconds() > 200)
		{
			new_frame = 2;
			timer.restart();
		}
	}	
	else
	{
		new_frame = 0;
	}

	//if (new_frame != current_frame)
	sprite.setTextureRect(sf::Rect<int>(new_frame*PLAYER_WIDTH, direction*PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
	current_frame = new_frame;
}

//returns the int values for the map locations the player intersects (only considering v_x)
int* Player::getCornersDX(int map_width, int map_height)
{
	x += v_x;
	corners[0] = (x >> 5) + map_width*(y >> 5);												//top left
	corners[1] = ((x + PLAYER_WIDTH - 1) >> 5) + map_width*(y >> 5);						//top right
	corners[2] = ((x + PLAYER_WIDTH - 1) >> 5) + map_width*((y + PLAYER_HEIGHT - 1) >> 5);	//bottom right
	corners[3] = (x >> 5) + map_width*((y + PLAYER_HEIGHT - 1) >> 5);						//bottom left
	x -= v_x;
	//cout << corners[0] << "," << corners[1] << "," << corners[2] << "," << corners[3] << endl;
	return corners;
}

//returns the int values for the map locations the player intersects (considering v_x and v_y)
int* Player::getCornersDXDY(int map_width, int map_height)
{
	x += v_x;
	y += v_y;
	corners[0] = (x >> 5) + map_width*(y >> 5);											//top left
	corners[1] = ((x + PLAYER_WIDTH-1) >> 5) + map_width*(y >> 5);						//top right
	corners[2] = ((x + PLAYER_WIDTH-1) >> 5) + map_width*((y + PLAYER_HEIGHT-1) >> 5);	//bottom right
	corners[3] = (x >> 5) + map_width*((y + PLAYER_HEIGHT-1) >> 5);						//bottom left
	x -= v_x;
	y -= v_y;
	return corners;
}

int* Player::getFeet(int map_width, int map_height)
{
	x += v_x;
	y += v_y;
	feet[0] = ((x + PLAYER_WIDTH - 1) >> 5) + map_width*((y + PLAYER_HEIGHT) >> 5);	//bottom right
	feet[1] = (x >> 5) + map_width*((y + PLAYER_HEIGHT) >> 5);						//bottom left
	x -= v_x;
	y -= v_y;
	return feet;
}

//returns bounding box
sf::Rect<int> Player::getRect()
{
	return sf::Rect<int>(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}

bool Player::is_standing()
{
	return standing;
}

void Player::set_standing(bool b)
{
	standing = b;
}

sf::Sprite Player::getSprite()
{
	return sprite;
}

void Player::setDirection(int dir)
{
	direction = dir;
}