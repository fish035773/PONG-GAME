#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Collisioner{
public:
	Collisioner();
	~Collisioner();

	void collision_rectangle(RenderTarget& target, RectangleShape& current);
private:
};

