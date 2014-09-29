#ifndef ENEMY_H_
#define ENEMY_H_

#include <sfml/Graphics.hpp>

class Enemy
{
protected:
	int x;
	int y;
	int hp;
	sf::Sprite sprite;
	bool m_alive;
public:
	void init(int, int, int, sf::Texture&);	//x, y, HP, image (overload this method for children to not include HP or texture)
	virtual void update(); //possibly overload the method for children, if they need access to the level collision data OR the player's location
	bool is_alive();
	//getters and setters
	void setX(int newX){ x = newX; };
	void setY(int newY){ y = newY; };
	int getX() { return x; };
	int getY() { return y; };
	sf::Sprite* getSprite();
};

#endif /* ENEMY_H_ */