#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "player1.h";
#include "player2.h";
#include "Ball.h"
#include "Collisioner.h"

using namespace sf;
using namespace std;

int main() {
	cout << "WELCOME TO PONG" << endl;
	cout << "@MADE BY 吳是悅" << endl << endl;
	cout << "LOADING..." << endl;

	RenderWindow window(VideoMode(1280, 800), "PONG", Style::Titlebar | Style::Close);
	Event event;
	RectangleShape line;
	RectangleShape background;
	Texture background_texture;
	Player1 player1(window);
	Player2 player2(window);
	Ball ball(window);
	Collisioner collision;
	
	srand(time(0));
	window.setFramerateLimit(60);
	 
	Clock clock;
	float deltatime;

	//SET LINE
	line.setSize(Vector2f(0.5, window.getSize().y));
	line.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	line.setOrigin(0.5, window.getSize().y / 2);

	//SET RANDOM BACKGROUND
	int random_load = rand() % 39 + 1;
	string path = "Background/" + to_string(random_load) + ".jpeg";
	background_texture.loadFromFile(path);
	background.setTexture(&background_texture);
	background.setSize(Vector2f(window.getSize()));

	//GAME LOOP
	while (window.isOpen()) {
		window.clear();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}else if (event.type == Event::KeyPressed && !ball.gameover){
				if (Keyboard::isKeyPressed(Keyboard::E)) {
					ball.call_timer = true;
				}
			}else if (event.type == Event::KeyPressed && ball.gameover) {
				if (Keyboard::isKeyPressed(Keyboard::X)) {
					ball.call_restarter = true;
				}
			}
		}

		//RESTART AFTER GAMEOVER
		if (ball.gameover && ball.call_restarter) {
			ball.restart(window);
			player1.restart(window);
			player2.restart(window);

			int random_load = rand() % 18 + 1;
			string path = "Background/" + to_string(random_load) + ".jpeg";
			background_texture.loadFromFile(path);
			background.setTexture(&background_texture);
		}

		//UPDATE
		deltatime = clock.restart().asSeconds(); //取得時間變化量

		window.draw(background);
		window.draw(line);

		//遊戲未結束且遊戲已開始時會更新物件
		if (!ball.gameover && ball.gamestart) { 
			player1.update(window, deltatime);
			player2.update(window, deltatime);
			ball.update(window, deltatime, player1.body, player2.body);
		}
		//若遊戲開始後遊戲結束則顯示贏方、提示按"X"重置
		else if(ball.gameover && ball.gamestart) {
			ball.winner(window);
			ball.render_restart_message(window);
		}

		//RENDER
		player1.render(window);
		player2.render(window);
		ball.render(window);

		//COUNT DOWN
		if(!ball.gamestart && !ball.call_timer) ball.render_start_message(window);
		if (ball.call_timer && !ball.gamestart) {
			ball.count_down(window, deltatime);
		}

		//DISPLAY OBJECTS
		window.display();	
	}
}