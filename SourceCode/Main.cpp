#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ImageLibrary.h"
#include "FlyingRobot.h"

#define PLAYER_SPEED 2

struct Camera
{
	int x = 0;
	int y = 0;
	sf::RenderStates state;
};

struct Level
{
	int width;
	int height;
	char* data;
};

int current_level;
char dictionary[255];
Level levels[2];
Level level1;
Camera camera;
Player player;
sf::VertexArray map;
bool can_jump;

//prototype functions
void initialize_levels();
void initialize_map();
void initialize_dictionary();
void interpret_keys();
void update();
bool valid_move();

//used in camera scrolling
int dx;
int dy;
FlyingRobot testRobot; //delete later!
int main()
{
	ImageLibrary::load_textures();
	testRobot.init(100, 256); //delete later!
	can_jump = true;
	sf::Texture tilemap;
	player.init(50,255);
	if (!tilemap.loadFromFile("tilemap.png"))
		std::cout << "Error loading tilemap.png" << std::endl;
	current_level = 1;
	initialize_levels();
	initialize_dictionary();
	map = sf::VertexArray(sf::Quads, levels[current_level].width * levels[current_level].height * 4);
	initialize_map();
	camera.x = 0;
	camera.y = 0;
	camera.state.texture = &tilemap;
	sf::RenderWindow window(sf::VideoMode(320, 320), "Gunned Down");
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		sf::Event event;
		update();	//updates everything
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::W)
						can_jump = true;
					break;
				default:
					break;
			}
			/*if (event.type == sf::Event::Closed)
				window.close();*/
		}

		window.clear();
		window.draw(map, camera.state);
		window.draw(*testRobot.getSprite(), camera.state.transform);
		window.draw(player.getSprite(), camera.state.transform);
		window.display();
	}

	return 0;
}

void initialize_levels()
{
	levels[0].width = 20;
	levels[0].height = 10;
	levels[0].data = "#..................##..................##..................##..................##..................##..................##..................##..................##......#......#....#####################";

	levels[1].width = 60;
	levels[1].height = 30;
	levels[1].data = "#..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##.............#............................................##..........................#................#..............###########..#############################################..##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........................................................##..........#........#................#.................#...##..##########################################################..........................................................##..................................###.....................##......................############........................##.....................#...............................##..###....................#..............................###....##...................#.............................###......##..................#............................###........##.................#...........................###..........##.............#..#.....................#....##.............#############################################################";
}

void initialize_map() //use modulo to handle multiple rows later!
{
	for (int i = 0; i < map.getVertexCount(); i+=4)
	{
		int j = i >> 2;

		map[i].position = sf::Vector2f((j%levels[current_level].width) << 5, (j / levels[current_level].width) << 5);
		map[i+1].position = sf::Vector2f(((j%levels[current_level].width) << 5) + 32, (j / levels[current_level].width) << 5);
		map[i+2].position = sf::Vector2f(((j%levels[current_level].width) << 5) + 32, ((j / levels[current_level].width) << 5) + 32);
		map[i+3].position = sf::Vector2f((j%levels[current_level].width) << 5, ((j / levels[current_level].width) << 5) + 32);

		map[i].texCoords = sf::Vector2f(dictionary[levels[current_level].data[j]]*32, 0);
		map[i + 1].texCoords = sf::Vector2f(dictionary[levels[current_level].data[j]]*32 + 32, 0);
		map[i + 2].texCoords = sf::Vector2f(dictionary[levels[current_level].data[j]]*32 + 32, 32);
		map[i + 3].texCoords = sf::Vector2f(dictionary[levels[current_level].data[j]]*32, 32);
	}
}

void initialize_dictionary() 
{
	//the number values refer to which tile on the tilemap the image should be
	dictionary['#'] = 1;	//black (wall)
	dictionary['.'] = 0;	//white (empty space)
}

void interpret_keys()
{
	//keys pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.setV_X(PLAYER_SPEED);
		player.setDirection(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.setV_X(-PLAYER_SPEED);
		player.setDirection(1);
	}
	else
		player.setV_X(0);

	if (can_jump && player.is_standing() && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.setV_Y(-13);		//maybe make this -10
		player.set_standing(false);
		can_jump = false;	//holding down W won't continuously jump (it looks stupid when that happens)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		std::cout << "camera.x: " << camera.x << "\ncamera.y: " << camera.y << std::endl;
}

bool valid_move(int* corners, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (levels[current_level].data[corners[i]] != '.')
			return false;
	}
	return true;
}

void update()
{
	interpret_keys();
	
	if (!valid_move(player.getCornersDX(levels[current_level].width, levels[current_level].height), 4))
	{
		if (player.getV_X() < 0)//moving left
			player.setX(((player.getX()) >> 5) << 5);
		else //player moving right
			player.setX(((((player.getX()) >> 5) + 1) << 5) - PLAYER_WIDTH);
		player.setV_X(0);
	}

	//collision in the y direction
	if (!player.is_standing() && !valid_move(player.getCornersDXDY(levels[current_level].width, levels[current_level].height), 4))
	{
		if (player.getV_Y() < 0) //moving up
			player.setY((player.getY() >> 5) << 5);
		else //moving down
		{
			player.setY((((player.getY() + PLAYER_HEIGHT + player.getV_Y()) >> 5) << 5) - PLAYER_HEIGHT);
			player.set_standing(true);
		}

		player.setV_Y(0);
	}

	if (player.is_standing() && valid_move(player.getFeet(levels[current_level].width, levels[current_level].height), 2))
		player.set_standing(false); 

	player.update(); 
	testRobot.update(); //delete later

	//camera scrolling
	if (camera.x < levels[current_level].width*32 - 320 && player.getX() > camera.x + 200)
	{
		camera.x += PLAYER_SPEED;
		camera.state.transform.translate(-PLAYER_SPEED, 0);
	}
	else if (camera.x > 0 && player.getX() < camera.x + 120)
	{
		camera.x -= PLAYER_SPEED;
		camera.state.transform.translate(PLAYER_SPEED, 0);
	}

	if (camera.y > 0 && player.getY() < camera.y + 64) //move camera up
	{
		dy = camera.y + 64 - player.getY();
		camera.y -= dy;
		camera.state.transform.translate(0, dy);
	}
	else if (camera.y < levels[current_level].height * 32 - 320 && player.getY() > camera.y + 256) //move camera down
	{
		dy = player.getY() - camera.y - 256;
		camera.y += dy;
		camera.state.transform.translate(0, -dy);
	}
}