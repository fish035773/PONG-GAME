#include "Player1.h"
#include "Collisioner.h"

Player1::Player1(RenderTarget& target)
{
	body.setFillColor(Color::White);
	body.setSize(Vector2f(50,200));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(body.getSize().x / 2, target.getSize().y / 2);

	multiplyer = 100;
	speed = 10;
}

Player1::~Player1(){

}

void Player1::restart(RenderTarget& target) {
	body.setFillColor(Color::White);
	body.setSize(Vector2f(50, 200));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(body.getSize().x / 2, target.getSize().y / 2);

	multiplyer = 100;
	speed = 10;
}

void Player1::update(RenderTarget& target, float deltatime){
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		body.move(0, -deltatime * speed * multiplyer);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		body.move(0, deltatime * speed * multiplyer);
	}
	collision_window.collision_rectangle(target, body);
}

void Player1::render(RenderTarget& target){
	target.draw(body);
}
