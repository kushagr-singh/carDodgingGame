#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Base Class
class Car {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

public:
    Car(float startSpeed) : speed(startSpeed) {}
    virtual ~Car() = default;

    virtual void update(float deltaTime) = 0;
    
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
    
    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }
};

// Derived Player Class
class PlayerCar : public Car {
public:
    PlayerCar(float startSpeed) : Car(startSpeed) {
        if (!texture.loadFromFile("assets/WhiteCar.png")) {
            std::cerr << "Error loading WhiteCar.png" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f); // Scale down if necessary
        sprite.setPosition(400.f, 600.f); // Starting position
    }

    void update(float deltaTime) override {
        // Keyboard movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move(-speed * deltaTime, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(speed * deltaTime, 0.f);
        }

        // Restrict movement within road boundaries (assuming 800px width window)
        if (sprite.getPosition().x < 150.f) {
            sprite.setPosition(150.f, sprite.getPosition().y);
        }
        if (sprite.getPosition().x > 600.f - sprite.getGlobalBounds().width) {
            sprite.setPosition(600.f - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }
    }
};

// Derived Enemy Class
class EnemyCar : public Car {
public:
    EnemyCar(float startSpeed, float startX, const std::string& texturePath) : Car(startSpeed) {
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Error loading " << texturePath << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f);
        sprite.setPosition(startX, -150.f); // Spawn off-screen at the top
    }

    void update(float deltaTime) override {
        sprite.move(0.f, speed * deltaTime); // Move downward
    }
};

#endif