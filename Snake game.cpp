#include <iostream>
#include <conio.h> // to control the snake
using namespace std;

bool GameOver; // to start or end the game
const int width = 20, height = 20; // field size
int x, y, apple_x, apple_y, score, n_tail; 

int tail_x[100], tail_y[100]; // for the snake`s tail

enum control { STOP = 0, LEFT, RIGHT, UP, DOWN }; // control variables
control dir;

// function to start the game and determine the position of the snake and apples
void Setup() {

    GameOver = false;

    dir = STOP;

    x = width / 2 - 1;
    y = height / 2 - 1;

    apple_x = rand() % width;
    apple_y = rand() % height;

    score = 0;
}

// function to draw all game components
void Draw() {

    // to clear the terminal
    system("cls");

    cout << "Press the 'W'/'A'/'S'/'D' to start the game." << endl;

    // loop that draws the top border of the field
    for (int i = 0; i <= width; i++) {
        cout << "#";
    }
    cout << endl;

    // loop that draws right and left edges of the field, snake`s head, snake`s tail and apples
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            // to draw side edges
            if (j == 0 || j == width - 1) {
                cout << "#";
            }

            // to draw snake`s head
            if (i == y && j == x) {
                cout << "0";
            }

            // to draw apples
            else if (i == apple_y && j == apple_x) {
                cout << "$";
            }

            // to draw snake`s tail
            else {

                // variable for drawing the snake`s tail (always, when the snake has not eaten an apple, does not draw)
                bool print = false;

                // loop to check if the snake ate the apple
                for (int k = 0; k < n_tail; k++) {

                    if (tail_x[k] == j && tail_y[k] == i) {
                        print = true;
                        cout << "o";
                    }
                }

                if (!print) {
                    cout << " ";
                }
            }
        }

        cout << endl;
    }

    // loop that draws the bottom border of the field
    for (int i = 0; i <= width; i++) {
        cout << "#";
    }
    cout << endl;

    cout << "Score: " << score << endl;
}

// key capture function
void Input() {

    if (_kbhit()) {

        switch (_getch()) {

        case 'a':
            dir = LEFT;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 'x':
            GameOver = true;
            break;
        }
    }
}

// the function responsible for the logistics of the game
void Logic() {

    // snake`s tail variables
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev_2x, prev_2y;

    tail_x[0] = x;
    tail_y[0] = y;

    // loop that recalcutates tail length
    for (int i = 1; i < n_tail; i++) {

        prev_2x = tail_x[i];
        prev_2y = tail_y[i];

        tail_x[i] = prev_x;
        tail_y[i] = prev_y;

        prev_x = prev_2x;
        prev_y = prev_2y;
    }

    // snake movement on given keys
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;
    }

    //loops that allow the snake to pass through walls
    if (x >= width - 1) {
        x = 0;
    }

    else if (x < 0) {
        x = width - 2;
    }

    if (y >= height) {
        y = 0;
    }

    else if (y < 0) {
        y = height - 1;
    }

    // loop that ends the game if the snake collided with its tail
    for (int i = 0; i < n_tail; i++) {
        if (tail_x[i] == x && tail_y[i] == y) {
            GameOver = true;
        }
    }

    // creates a new apple when the past is eaten
    if (x == apple_x && y == apple_y) {
        score++;
        apple_x = rand() % width;
        apple_y = rand() % height;
        n_tail++;
    }
}

// the main function of the game
int main()
{
    Setup();

    while (!GameOver) {
        Draw();
        Input();
        Logic();
    }
    
    return 0;
}
