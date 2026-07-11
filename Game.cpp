#include "Game.h"
#include <cstdlib>
#include <sstream>

void Game::initVariables() {
    this->player = new PlayerCar(400.f);
    this->spawnTimerMax = 1.5f; // Spawn an enemy every 1.5 seconds initially
    this->spawnTimer = this->spawnTimerMax;
    this->score = 0;
    this->globalSpeed = 300.f; // Initial enemy speed
    this->isGameOver = false;
    this->isPaused = false;
}

void Game::initWindow() {
    this->window.create(sf::VideoMode(800, 800), "Car Dodging Game");
    this->window.setFramerateLimit(60);

    // Setup road background
    for(int i = 0; i < 5; i++) {
        sf::RectangleShape line(sf::Vector2f(10.f, 100.f));
        line.setFillColor(sf::Color::White);
        line.setPosition(395.f, i * 200.f);
        this->roadLines.push_back(line);
    }
}

void Game::initFonts() {
    // Make sure to place a standard ttf font in the assets folder or use a system font path
    if (!this->font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(20.f, 20.f);

    this->speedText.setFont(this->font);
    this->speedText.setCharacterSize(24);
    this->speedText.setFillColor(sf::Color::White);
    this->speedText.setPosition(20.f, 50.f);

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(50);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER\nPress R to Restart");
    this->gameOverText.setPosition(200.f, 350.f);
    
    this->pauseText.setFont(this->font);
    this->pauseText.setCharacterSize(50);
    this->pauseText.setFillColor(sf::Color::Yellow);
    this->pauseText.setString("PAUSED\nPress P to Resume");
    this->pauseText.setPosition(220.f, 350.f);
}

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
}

Game::~Game() {
    delete this->player;
    for (auto* enemy : this->enemies) {
        delete enemy;
    }
}

void Game::spawnEnemy() {
    float randomX = static_cast<float>(rand() % 400 + 150); // Random lane between 150 and 550
    std::string textures[] = {"assets/RedCar1.png", "assets/RedCar2.png", "assets/YellowCar1.png", "assets/YellowCar2.png", "assets/YellowCar3.png"};
    int randTex = rand() % 5;
    
    // Vary enemy speed slightly for difficulty
    float enemySpeed = this->globalSpeed + (rand() % 100 - 50); 
    this->enemies.push_back(new EnemyCar(enemySpeed, randomX, textures[randTex]));
}

void Game::updateEnemies(float deltaTime) {
    this->spawnTimer -= deltaTime;
    if (this->spawnTimer <= 0.f) {
        this->spawnEnemy();
        this->spawnTimer = this->spawnTimerMax;
    }

    for (size_t i = 0; i < this->enemies.size(); i++) {
        this->enemies[i]->update(deltaTime);

        // Remove off-screen enemies and increase score
        if (this->enemies[i]->getPosition().y > this->window.getSize().y) {
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            this->score += 10;
            
            // Speed up game gradually
            if(this->score % 50 == 0) {
                this->globalSpeed += 50.f;
                if(this->spawnTimerMax > 0.5f) this->spawnTimerMax -= 0.1f;
            }
        }

        // Collision detection
        if (this->player->getBounds().intersects(this->enemies[i]->getBounds())) {
            this->isGameOver = true;
        }
    }
}

void Game::updateUI() {
    std::stringstream ss;
    ss << "SCORE: " << this->score;
    this->scoreText.setString(ss.str());

    std::stringstream ss2;
    ss2 << "SPEED: " << static_cast<int>(this->globalSpeed / 100);
    this->speedText.setString(ss2.str());
}

void Game::renderUI() {
    this->window.draw(this->scoreText);
    this->window.draw(this->speedText);
    if (this->isGameOver) {
        this->window.draw(this->gameOverText);
    } else if (this->isPaused) {
        this->window.draw(this->pauseText);
    }
}

void Game::resetGame() {
    delete this->player;
    this->player = new PlayerCar(400.f);
    for (auto* enemy : this->enemies) {
        delete enemy;
    }
    this->enemies.clear();
    this->initVariables();
}

void Game::run() {
    sf::Clock clock;
    while (this->window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P && !this->isGameOver) {
                    this->isPaused = !this->isPaused;
                }
                if (event.key.code == sf::Keyboard::R && this->isGameOver) {
                    this->resetGame();
                }
            }
        }

        if (!this->isGameOver && !this->isPaused) {
            this->player->update(deltaTime);
            this->updateEnemies(deltaTime);
            
            // Animate road lines
            for(auto& line : this->roadLines) {
                line.move(0, this->globalSpeed * deltaTime);
                if(line.getPosition().y > 800.f) {
                    line.setPosition(395.f, -100.f);
                }
            }
        }
        
        this->updateUI();

        this->window.clear(sf::Color(50, 50, 50)); // Dark grey road color
        
        // Draw road boundaries
        sf::RectangleShape leftGrass(sf::Vector2f(150.f, 800.f));
        leftGrass.setFillColor(sf::Color(34, 139, 34));
        this->window.draw(leftGrass);
        
        sf::RectangleShape rightGrass(sf::Vector2f(200.f, 800.f));
        rightGrass.setFillColor(sf::Color(34, 139, 34));
        rightGrass.setPosition(600.f, 0.f);
        this->window.draw(rightGrass);

        for(auto& line : this->roadLines) {
            this->window.draw(line);
        }

        this->player->draw(this->window);
        for (auto* enemy : this->enemies) {
            enemy->draw(this->window);
        }
        
        this->renderUI();
        this->window.display();
    }
}