#include "Ball.h"

Ball::Ball(RenderTarget& target)
{
	font.loadFromFile("Fonts/manaspc.ttf");
	soundbuffer.loadFromFile("Sound/ping-pong-ball-hit.wav");
	sound.setBuffer(soundbuffer);

	body.setRadius(15);
	body.setFillColor(Color::White);
	body.setPosition(target.getSize().x / 2, target.getSize().y / 2);
	body.setOrigin(body.getRadius(), body.getRadius());

	gameover = false;
	gamestart = false;
	call_timer = false;
	call_restarter = false;
	time_limit = 3;

	win_p1 = false;
	win_p2 = false;
	points_p1 = 0;
	points_p2 = 0;

	multiplyer = 300;
	velocity.x = 2;
	velocity.y = 2;

	ball_start_dir();

	max_velocity = Vector2f(3.8,3.8);
	min_velocity = Vector2f(2, 2);

	update_text();
	set_text(target);
}

Ball::~Ball(){

}

void Ball::restart(RenderTarget& target){
	body.setRadius(15);
	body.setFillColor(Color::White);
	body.setPosition(target.getSize().x / 2, target.getSize().y / 2);
	body.setOrigin(body.getRadius(), body.getRadius());

	gameover = false;
	gamestart = false;
	call_restarter = 0;
	call_timer = false;
	time_limit = 3;

	win_p1 = false;
	win_p2 = false;
	points_p1 = 0;
	points_p2 = 0;

	multiplyer = 300;
	velocity.x = 2;
	velocity.y = 2;

	ball_start_dir();

	max_velocity = Vector2f(3.8, 3.8);
	min_velocity = Vector2f(2, 2);

	update_text();
	set_text(target);
}

void Ball::render_restart_message(RenderTarget& target) {
	target.draw(restart_message);
}

void Ball::gameover_detector(RenderTarget& target) {
	if (body.getPosition().x + body.getRadius() >= target.getSize().x - body.getRadius()) {
		points_p1 += 1;
		win_p1 = true;
		update_text();
		gameover = true;
	}else if (body.getPosition().x - body.getRadius() <= 0) {
		points_p2 += 1;
		win_p2 = true;
		update_text();
		gameover = true;
	}
}

void Ball::set_text(RenderTarget& target) {
	text_p1.setCharacterSize(40);
	text_p1.setFillColor(Color::White);
	text_p1.setFont(font);
	text_p1.setOrigin((text_p1.getLocalBounds().width + text_p1.getLocalBounds().left) / 2, (text_p1.getLocalBounds().top + text_p1.getLocalBounds().height) / 2);
	text_p1.setPosition((text_p1.getLocalBounds().width + text_p1.getLocalBounds().left) / 2 + target.getSize().x / 5 , (text_p1.getLocalBounds().top + text_p1.getLocalBounds().height) / 2 + 10);

	text_p2.setCharacterSize(40);
	text_p2.setFillColor(Color::White);
	text_p2.setFont(font);
	text_p2.setOrigin((text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2, (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2);
	text_p2.setPosition(target.getSize().x - (text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2 - target.getSize().x / 5 , (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2 + 10);

	win_message.setCharacterSize(100);
	win_message.setFillColor(Color::White);
	win_message.setFont(font);
	win_message.setOrigin((text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2, (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2);
	win_message.setPosition(target.getSize().x / 2 - 50, target.getSize().y / 2 + 20);
	win_message.setString("NONE");

	start_message.setCharacterSize(70);
	start_message.setFillColor(Color::White);
	start_message.setFont(font);
	start_message.setOrigin((text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2, (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2);
	start_message.setString("PRESS E TO START");
	start_message.setPosition(target.getSize().x / 2 - 275,target.getSize().y / 2);

	timer.setCharacterSize(100);
	timer.setFillColor(Color::White);
	timer.setFont(font);
	timer.setOrigin((text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2, (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2);
	timer.setString("NONE");
	timer.setPosition(target.getSize().x / 2 + 45, target.getSize().y / 2 + 50);

	restart_message.setCharacterSize(70);
	restart_message.setFillColor(Color::White);
	restart_message.setFont(font);
	restart_message.setOrigin((text_p2.getLocalBounds().width + text_p2.getLocalBounds().left) / 2, (text_p2.getLocalBounds().top + text_p2.getLocalBounds().height) / 2);
	restart_message.setString("PRESS X TO RESTART");
	restart_message.setPosition(target.getSize().x / 2 - 300, target.getSize().y / 2 + 70);
}

void Ball::ball_start_dir() {
	int random = rand() % 4;
	switch (random) {
		case 0:
			velocity.x = 2;
			velocity.y = 2;
			break;
		case 1:
			velocity.x = -2;
			velocity.y = -2;
			break;
		case 2:
			velocity.x = 2;
			velocity.y = -2;
			break;
		case 3:
			velocity.x = -2;
			velocity.y = 2;
			break;
	}
}

void Ball::update_text() {
	stringstream ss_p1, ss_p2;
	ss_p1 << "P1 : " << points_p1 << endl;
	ss_p2 << "P2 : " << points_p2 << endl;
	text_p1.setString(ss_p1.str());
	text_p2.setString(ss_p2.str());
}

bool Ball::check_collision(RectangleShape& player1, RectangleShape& player2){
	if(body.getGlobalBounds().intersects(player1.getGlobalBounds())){
		if (body.getPosition().x - body.getRadius() > player1.getPosition().x){
		}
		return true;
	}
	else if (body.getGlobalBounds().intersects(player2.getGlobalBounds())) {
		return true;
	}
	return false;

}

void Ball::collision_circle(RenderTarget& target) {
	if (body.getPosition().y + body.getRadius() >= target.getSize().y) {
		body.setPosition(body.getPosition().x, target.getSize().y - body.getRadius());
		velocity.y *= -1;
	}
	if (body.getPosition().y - body.getRadius() <= 0) {
		body.setPosition(body.getPosition().x, body.getRadius());
		velocity.y *= -1;
	}
}

void Ball::randomizer(float& velocity, int add_chance) {
	int random = rand() % 100 + add_chance;
	random = min(max(random, 0), 100);

	if (random <= 10) {
		velocity *= -0.85;
	}else if (random <= 25) {
		velocity *= -0.95;
	}else if(random <= 35) {
		velocity *= -1.4;
	}else if (random <= 55) {
		velocity *= -1.55;
	}else if (random <= 65) {
		velocity *= -1.65;
	}else if (random <= 75) {
		velocity *= -1.85;
	}else if (random <= 85) {
		velocity *= -1.95;
	}else if (random <= 100) {
		velocity *= -1;
	}else velocity *= -1;
}
void Ball::update(RenderTarget& target, float deltatime, RectangleShape& player1, RectangleShape& player2){
	gameover_detector(target);

	if (body.getPosition().x < player1.getPosition().x + player1.getSize().x / 2 && body.getPosition().x > target.getSize().x / 2) {
		points_p1 += 1;
		win_p1 = true;
		update_text();
		gameover = true;
	}
	else if (body.getPosition().x > player2.getPosition().x - player2.getSize().x / 2 && body.getPosition().x < target.getSize().x / 2) {
		points_p2 += 1;
		win_p2 = true;
		update_text();
		gameover = true;
	}
	if (!gameover) {
		if (check_collision(player1, player2)) {
			if (velocity.x > 0) points_p2 += 1;
			else if (velocity.x < 0) points_p1 += 1;

			sound.play();

			if (body.getPosition().y + body.getRadius() <= player1.getPosition().y - player1.getSize().y * 0.4) {
				randomizer(velocity.x, 0);
				randomizer(velocity.y, 0);
			}
			else if (body.getPosition().y + body.getRadius() <= player1.getPosition().y - player1.getSize().y * 0.3) {
				randomizer(velocity.x, 20);
				randomizer(velocity.y, 30);
			}
			else if (body.getPosition().y + body.getRadius() <= player1.getPosition().y - player1.getSize().y * 0.2) {
				randomizer(velocity.x, 30);
				randomizer(velocity.y, 10);
			}
			else if (body.getPosition().y + body.getRadius() <= player1.getPosition().y - player1.getSize().y * 0.1) {
				randomizer(velocity.x, 40);
				randomizer(velocity.y, 20);
			}
			else if (body.getPosition().y + body.getRadius() >= player1.getPosition().y + player1.getSize().y * 0.4) {
				randomizer(velocity.x, 0);
				randomizer(velocity.y, 0);
			}
			else if (body.getPosition().y + body.getRadius() >= player1.getPosition().y + player1.getSize().y * 0.3) {
				randomizer(velocity.x, 20);
				randomizer(velocity.y, 25);
			}
			else if (body.getPosition().y + body.getRadius() >= player1.getPosition().y + player1.getSize().y * 0.2) {
				randomizer(velocity.x, 30);
				randomizer(velocity.y, 10);
			}
			else if (body.getPosition().y + body.getRadius() >= player1.getPosition().y + player1.getSize().y * 0.1) {
				randomizer(velocity.x, 40);
				randomizer(velocity.y, 20);
			}
			else {
				randomizer(velocity.x, 25);
				randomizer(velocity.y, 25);
			}
			if (abs(velocity.x) > max_velocity.x) velocity.x = velocity.x / abs(velocity.x) * max_velocity.x;
			if (abs(velocity.y) > max_velocity.y) velocity.y = velocity.x / abs(velocity.x) * max_velocity.y;
			if (abs(velocity.x) < min_velocity.x) velocity.x = velocity.x / abs(velocity.x) * min_velocity.x;
			if (abs(velocity.y) < min_velocity.y) velocity.y = velocity.x / abs(velocity.x) * min_velocity.y;
		}
		collision_circle(target);
		body.move(velocity * deltatime * multiplyer);

		update_text();
	}
}

void Ball::render(RenderTarget& target){
	target.draw(body);
	target.draw(text_p1);
	target.draw(text_p2);
	if(gameover) target.draw(win_message);
}

void Ball::render_start_message(RenderTarget& target){
	target.draw(start_message);
}

void Ball::winner(RenderTarget& target){
	if (win_p1) win_message.setString("P1 WINS !");
	else if (win_p2) win_message.setString("P2 WINS !");
	win_message.setPosition(target.getSize().x / 2 - 150, target.getSize().y / 2 - 100);
}

void Ball::count_down(RenderTarget& target, float deltatime){
	time_limit -= deltatime;
	if (time_limit <= 0) {
		gamestart = true;
	}
	else if (time_limit <= 1) {
		timer.setString("1");
	}
	else if (time_limit <= 2) {
		timer.setString("2");
	}
	else if (time_limit <= 3) {
		timer.setString("3");
	}

	target.draw(timer);
}


