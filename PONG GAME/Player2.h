#pragma once
#include <SFML/Graphics.hpp>
#include "Collisioner.h"
using namespace sf;

class Player2 {
public:
	Player2(RenderTarget& target);
	~Player2();

	RectangleShape body;
	
	void update(RenderTarget& target, float deltatime);
	void render(RenderTarget& target);

	void restart(RenderTarget& target);
private:
	float speed;
	float multiplyer;
	Collisioner collision_window;
};

