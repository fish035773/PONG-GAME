#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "collisioner.h"
#include "Player1.h"
#include "Player2.h"
using namespace sf;
using namespace std;

class Ball{
public:
	Ball(RenderTarget& target);
	~Ball();
	
	CircleShape body;

	bool gameover;
	bool gamestart;
	bool win_p1, win_p2;
	bool call_timer;
	bool call_restarter;

	void update(RenderTarget& target, float deltatime, RectangleShape& player1, RectangleShape& player2);
	void render(RenderTarget& target);
	void render_start_message(RenderTarget& target);
	void winner(RenderTarget& target);
	void count_down(RenderTarget& target, float deltatime);

	void restart(RenderTarget& target);
	void render_restart_message(RenderTarget& target);
private:
	Collisioner collision_with_window;

	Vector2f velocity;
	Vector2f max_velocity;
	Vector2f min_velocity;

	Font font;
	Text text_p1,text_p2;
	Text win_message;
	Text start_message;
	Text timer;
	Text restart_message;

	SoundBuffer soundbuffer;
	Sound sound;

	Clock clock;

	int points_p1;
	int points_p2;
	float multiplyer;
	float time_limit;

	void gameover_detector(RenderTarget& target);
	void ball_start_dir();

	bool check_collision(RectangleShape& player1, RectangleShape& player2);
	void collision_circle(RenderTarget& target);

	void randomizer(float& velocity, int add_chance);

	void set_text(RenderTarget& target);
	void update_text();
};

