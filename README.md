# 🚗 Car Dodging Game

A simple 2D endless car dodging game developed in **C++** using the **SFML (Simple and Fast Multimedia Library)**. The player controls a car, avoids incoming traffic, and tries to survive for as long as possible while the game speed gradually increases.

---

## 🎮 Gameplay

The objective is simple:

- Control your car using the keyboard.
- Dodge the incoming traffic.
- Survive as long as possible.
- The game ends when your car collides with an obstacle.

The game demonstrates the implementation of a basic game loop, collision detection, sprite rendering, object-oriented programming, and event handling using SFML.

---

## ✨ Features

- Endless gameplay
- Smooth keyboard controls
- Randomly spawning enemy vehicles
- Collision detection
- Score tracking
- Increasing game difficulty over time
- Custom car sprites and font assets
- Object-oriented game architecture

---

## 🛠️ Tech Stack

- **Language:** C++
- **Graphics Library:** SFML
- **Paradigm:** Object-Oriented Programming

---

## 📂 Project Structure

```
CarDodgingGame/
│
├── assets/
│   ├── RedCar1.png
│   ├── RedCar2.png
│   ├── WhiteCar.png
│   ├── YellowCar1.png
│   ├── YellowCar2.png
│   └── YellowCar3.png
│
├── fonts/
│   └── KOMIKAP_.ttf
│
├── Car.h
├── Game.h
├── Game.cpp
├── main.cpp
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- C++17 or later
- SFML installed
- GCC / MinGW / MSVC

### Clone the repository

```bash
git clone https://github.com/kushagr-singh/carDodgingGame.git
cd carDodgingGame
```

### Build

Compile the project and link against the required SFML libraries.

Example (MinGW):

```bash
g++ main.cpp Game.cpp -o CarDodgingGame \
-lsfml-graphics \
-lsfml-window \
-lsfml-system
```

> Make sure SFML is properly installed and linked on your system.

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| ← | Move Left |
| → | Move Right |
| Esc | Exit Game |

---

# 📸 Screenshots

### Main Menu

![Main Menu](screenshots/menu.png)

---

### Gameplay

![Gameplay](screenshots/gameplay.png)

---

### Collision / Game Over

![Game Over](screenshots/gameover.png)

---

## 📚 Concepts Demonstrated

- Object-Oriented Programming
- Game Loop
- Event Handling
- Collision Detection
- Sprite Rendering
- Random Object Generation
- Asset Management
- Real-time Input Handling

---

## 🔮 Future Improvements

- Sound effects and background music
- High score persistence
- Multiple difficulty levels
- Animated backgrounds
- Power-ups
- Pause menu
- Better UI and animations

---

## 👨‍💻 Author

**Kushagr Singh**

GitHub: https://github.com/kushagr-singh

---

## 📄 License

This project is intended for educational and learning purposes.
