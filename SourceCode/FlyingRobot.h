#ifndef FLYINGROBOT_H_
#define FLYINGROBOT_H_

#include "Enemy.h"

class FlyingRobot : public Enemy //lol, public enemy
{
private:
	int start_y;
	int dy;
	sf::Uint8 frame;
	sf::Clock timer;
public:
	void init(int,int);
	virtual void update(); //overrides the parent function
};

#endif /* FLYINGROBOT_H_ */