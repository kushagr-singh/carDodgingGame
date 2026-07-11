#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Car.h"

class Game {
private:
    sf::RenderWindow window;
    PlayerCar* player;
    std::vector<EnemyCar*> enemies;
    
    sf::Font font;
    sf::Text scoreText;
    sf::Text speedText;
    sf::Text gameOverText;
    sf::Text pauseText;

    float spawnTimer;
    float spawnTimerMax;
    int score;
    float globalSpeed;
    bool isGameOver;
    bool isPaused;

    // Road lines for visual effect
    std::vector<sf::RectangleShape> roadLines;

    void initVariables();
    void initWindow();
    void initFonts();
    void spawnEnemy();
    void updateEnemies(float deltaTime);
    void updateUI();
    void renderUI();
    void resetGame();

public:
    Game();
    virtual ~Game();
    void run();
};

#endif