#include "Player2.h"
#include "Collisioner.h"

Player2::Player2(RenderTarget& target)
{
	body.setFillColor(Color::White);
	body.setSize(Vector2f(50, 200));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(target.getSize().x - body.getSize().x / 2, target.getSize().y / 2);

	multiplyer = 100;
	speed = 10;
}

Player2::~Player2() {

}

void Player2::restart(RenderTarget& target){
	body.setFillColor(Color::White);
	body.setSize(Vector2f(50, 200));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(target.getSize().x - body.getSize().x / 2, target.getSize().y / 2);

	multiplyer = 100;
	speed = 10;
}

void Player2::update(RenderTarget& target, float deltatime) {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		body.move(0, -deltatime * speed * multiplyer);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		body.move(0, deltatime * speed * multiplyer);
	}
	collision_window.collision_rectangle(target, body);
}

void Player2::render(RenderTarget& target) {
	target.draw(body);
}

