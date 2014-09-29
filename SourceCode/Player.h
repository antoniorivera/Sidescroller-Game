#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_WIDTH 13
#define PLAYER_HEIGHT 32
#include <SFML/Graphics.hpp>

class Player
{
private:
	unsigned char current_frame;
	unsigned char new_frame;
	unsigned char direction;	//0 or 1
	int x;
	int y;
	int v_x;
	int v_y;
	int hp;
	int corners[4];
	int feet[2];
	bool standing;
	bool can_shoot;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock timer;

public:
	int getX();
	int getY();
	int getV_X();
	int getV_Y();
	int* getCornersDX(int, int);
	int* getCornersDXDY(int, int);
	int* getFeet(int, int);
	bool is_standing();
	void update();
	void setX(int);
	void setY(int);
	void setV_X(int);
	void setV_Y(int);
	void setDirection(int);
	void set_standing(bool);
	void init(int, int);
	sf::Sprite getSprite();
	sf::Rect<int> getRect();
};

#endif /* PLAYER_H_ */