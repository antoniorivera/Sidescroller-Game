#include "FlyingRobot.h"
#include "ImageLibrary.h"

void FlyingRobot::init(int x, int y)
{
	Enemy::init(x, y, 10, ImageLibrary::flying_robot_tex);
	start_y = y;
	dy = -1;
	sprite.setTextureRect(sf::Rect<int>(0,0,16,32));
	frame = 0;
	timer.restart();
}

void FlyingRobot::update()
{
	Enemy::update();

	if (dy > 0) //moving down
	{
		if (y == start_y)
			dy = -1; //change direction
	}
	else //moving up
	{
		if (start_y - y > 64)
			dy = 1; //change direction
	}

	y += dy;
	sprite.setPosition(x, y);

	if (timer.getElapsedTime().asMilliseconds() > 300)
	{
		frame++;
		sprite.setTextureRect(sf::Rect<int>((frame % 2)*16, 0, 16, 32));
		timer.restart();
	}
}