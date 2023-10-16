#include "Collisioner.h"

Collisioner::Collisioner(){
}

Collisioner::~Collisioner(){

}

void Collisioner::collision_rectangle(RenderTarget& target, RectangleShape& current){
	if (current.getPosition().y + current.getSize().y / 2 >= target.getSize().y) {
		current.setPosition(current.getPosition().x, target.getSize().y - current.getSize().y / 2);
	}if (current.getPosition().y - current.getSize().y / 2 <= 0) {
		current.setPosition(current.getPosition().x, current.getSize().y / 2);
	}
}

