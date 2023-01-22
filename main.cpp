
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>


using namespace std;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pin-Pong");
sf::Vector2u currentWindowSize = window.getSize();
sf::Vector2f sizeNow;
sf::RectangleShape rec;
sf::RectangleShape recEnemy;
sf::CircleShape circle;
sf::Vector2f circleSpeed;
int recScore = 0;
int recEnemyScore = 0;
int colorIndex = 0;


bool intersects(sf::CircleShape, sf::RectangleShape, int);

void setCircleColor ();

void gameRound (int);

int main(){
	sizeNow.x = 200;
	sizeNow.y = 20;
	window.setFramerateLimit(144);
	rec.setSize(sizeNow);
	rec.setPosition((currentWindowSize.x / 2.f) - rec.getSize().x / 2.f,
		(currentWindowSize.y / 100.f) * 2);
	rec.setFillColor(sf::Color::White);
	recEnemy.setSize(sizeNow);
	recEnemy.setPosition((currentWindowSize.x / 2.f) - recEnemy.getSize().x / 2.f,
		(currentWindowSize.y / 100.f) * 96);
	recEnemy.setFillColor(sf::Color::White);
	circle.setRadius(20);
	circle.setPosition((currentWindowSize.x / 2.f) - circle.getRadius(),
    	(currentWindowSize.y / 100.f) * 45);
	circle.setFillColor(sf::Color::White);
	circleSpeed.x = 0.5f;
	circleSpeed.y = 1.5f;
	circle.move(circleSpeed.x, circleSpeed.y);

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
      	}
	  	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A )
			&& rec.getPosition().x >= 0) {
			rec.move(-1.5f, 0.f);
		}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
			&&  rec.getPosition().x + rec.getSize().x < currentWindowSize.x ) {
            rec.move(1.5f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& recEnemy.getPosition().x >= 0) {
            recEnemy.move(-1.5f, 0.f);
        }
	  	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			&&  recEnemy.getPosition().x + recEnemy.getSize().x < currentWindowSize.x ) {
            recEnemy.move(1.5f, 0.f);
        }
        if (circle.getPosition().x + (circle.getRadius() * 2) >= currentWindowSize.x) {
          		circleSpeed.x *= -1.f;
		} 
		if (circle.getPosition().x <= 0){
				circleSpeed.x *= -1.f;
		} 
		if (intersects(circle, rec, 0)){
				setCircleColor();
				circleSpeed.y *= -1.05f;
				circleSpeed.x *= 1.05f;
		} 
		if (intersects(circle, recEnemy, 1)){
				setCircleColor();
				circleSpeed.y *= -1.05f;
				circleSpeed.x *= 1.05f;
		}
        if (circle.getPosition().y > currentWindowSize.y) {
            gameRound(0);
        }
        if (circle.getPosition().y < 0) {
            gameRound(1);
        }
    	circle.move(circleSpeed.x, circleSpeed.y);
        window.clear();
        window.draw(rec);
        window.draw(recEnemy);
        window.draw(circle);
        window.display();
    }
    return 0;
}

static sf::Color colors[] = {sf::Color::Red,     sf::Color::Green,
                             sf::Color::Blue,    sf::Color::Cyan,
                             sf::Color::Magenta, sf::Color::Yellow};
void setCircleColor (){
	circle.setFillColor(colors[colorIndex]);
	colorIndex = (colorIndex + 1) % 6;
}

void gameRound (int i) {
    if (i) {
    	recEnemyScore++;
    }
	if (!i){
		recScore++;
	}
  	cout << recScore << "\t" << recEnemyScore << endl;
  	circle.setPosition(currentWindowSize.x / 2.f,(currentWindowSize.y / 100.f) * 45);
  	circleSpeed.y = 1.5f;
  	circleSpeed.x = 0.5f;
}


bool intersects(sf::CircleShape circle, sf::RectangleShape rec , int i) {
	if (circle.getPosition().y >= rec.getPosition().y - (rec.getSize().y * 2) 
		&& circle.getPosition().x + (circle.getRadius() * 2) > rec.getPosition().x 
		&& circle.getPosition().x - circle.getRadius() < (rec.getPosition().x + rec.getSize().x)
		&& i ){
		return true;
	}
	else if (circle.getPosition().y <= rec.getPosition().y + (rec.getSize().y) 
		&& circle.getPosition().x + (circle.getRadius() * 2) > rec.getPosition().x 
		&& circle.getPosition().x - circle.getRadius() < (rec.getPosition().x + rec.getSize().x)
		&& !i ){
		return true;
	}
	else if (circle.getPosition().y > rec.getPosition().y - rec.getSize().y * 2 && i){
		gameRound(0);
		return false;
	}
	else if (circle.getPosition().y < rec.getPosition().y + rec.getSize().y && !i){
		gameRound(1);
		return false;
	}
	else {
		return false;
	}
}