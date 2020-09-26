#include "GameController.hpp"
#include <iostream>

GameController::GameController(Board& board, Player& player, Enemy& enemy) : board_(board), player_(player), enemy_(enemy) {
}

void GameController::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            player_.moveUp();
        }
        if (event.key.code == sf::Keyboard::A) {
            player_.moveLeft();
            std::cout << int(player_.getCurrentDirection()) << '\n';
        }
        if (event.key.code == sf::Keyboard::S) {
            player_.moveDown();
        }
        if (event.key.code == sf::Keyboard::D) {
            player_.moveRight();
        }
        if (event.key.code == sf::Keyboard::Space) {
            player_.placeBomb();
            if (!isClockResetted_) {
                bombClock_ = sf::Clock();
                isClockResetted_ = true;
            }
            
            //after 3 sekundy
            //bum
        }
    }
}

bool GameController::checkBombBlow() {
    if (!player_.isBombPlaced()) {
        return false;
    }
    auto elapsedTime = bombClock_.getElapsedTime();
    player_.updateIsBombPlaced(elapsedTime);
    if (elapsedTime.asSeconds() >= player_.getBomb().getTimeToBlow()) {

        std::cout << "BOOM!\n"; //remove enemy
        isClockResetted_ = false;
        return true;
    }
    return false;

}

void GameController::moveEnemies() {
    enemy_.move(enemyMoveClock_.restart());
}
