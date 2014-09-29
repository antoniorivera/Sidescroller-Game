#include <iostream>
#include "ImageLibrary.h"

using namespace std;

sf::Texture ImageLibrary::flying_robot_tex;

//load
void ImageLibrary::load_textures()
{
	if (!flying_robot_tex.loadFromFile("enemy_robot_animation.png"))
		cout << "Error loading enemy_robot_animation.png" << endl;
}