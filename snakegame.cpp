#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Direction enum
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// Game variables
bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
int tail;
int tailx[100], taily[100];

// Function declarations
void setup();
void draw();
void input();
void logic();

int main() {
    char start;
    cout << "\t-----------------------------------" << endl;
    cout << "\t\t :Snake King:" << endl;
    cout << "\t-----------------------------------" << endl;
    cout << "Do you want to start the game? Press Y to start: ";
    cin >> start;

    if (start == 'Y' || start == 'y') {
        setup();
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(100); // Adjust speed here
        }

        // Game Over screen
        cout << "\n\t\t--- Game Over! ---" << endl;
        cout << "\t\tFinal Score: " << score << endl;
    }

    return 0;
}

// Setup the game
void setup() {
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tail = 0;
}

// Draw the game board
void draw() {
    system("cls");

    // Top border
    cout << "\t\t";
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    // Main area
    for (int i = 0; i < height; i++) {
        cout << "\t\t";
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";

            if (i == headY && j == headX)
                cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "*"; // Fruit
            else {
                bool print = false;
                for (int k = 0; k < tail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        cout << "o"; // Snake tail
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    // Bottom border
    cout << "\t\t";
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    // Score
    cout << "\t\tScore: " << score << endl;
}

// Handle input
void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        }
    }
}

// Game logic
void logic() {
    // Save previous tail position
    int prevX = tailx[0];
    int prevY = taily[0];
    tailx[0] = headX;
    taily[0] = headY;

    for (int i = 1; i < tail; i++) {
        int tempX = tailx[i];
        int tempY = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    // Move snake head
    switch (dir) {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // Wrap around logic
    if (headX >= width) headX = 0;
    else if (headX < 0) headX = width - 1;
    if (headY >= height) headY = 0;
    else if (headY < 0) headY = height - 1;

    // Snake bites itself
    for (int i = 0; i < tail; i++) {
        if (tailx[i] == headX && taily[i] == headY) {
            gameOver = true;
        }
    }

    // Eat fruit
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail++;
    }
}
