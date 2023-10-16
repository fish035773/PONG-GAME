#pragma once
#include <SFML/Graphics.hpp>
#include "Collisioner.h"
using namespace sf;

class Player1 {
public:
	Player1(RenderTarget& target);
	~Player1();

	RectangleShape body;

	void update(RenderTarget& target, float deltatime);
	void render(RenderTarget& target);
	void restart(RenderTarget& target);
private:
	Collisioner collision_window;
	float speed;
	float multiplyer;
};

