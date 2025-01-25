#include <iostream>
#include <random>


int randNum(int range) {
    srand(time(0));
    return rand() % range + 1;
}

void guesser(int guesses) {
    int goal = randNum(10);
    bool win = false;
    int guess;

    for (int i = 0; i < guesses; i++) {
        std::cout << "Pick a number: ";
        std::cin >> guess;

        if (guess == goal) {
            win = true;
        } else {
            std::cout << "Wrong! Try again ~" << std::endl;
        }

        if (win) {
            std::cout << std::endl << "YOU WIN :)";
            return;
        }
    }

    std::cout << std::endl << "you lose... :(";
}

int main() {
    guesser(2);

    return 0;
}
