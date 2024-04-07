#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 60;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int ScoreX = 1;

bool obstacles[height][width];

//Levels
void Levels() {
    gameOver = false;

    // Initialize Obstacles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            obstacles[i][j] = false;
        }
    }

    // Obstacles Level
    int choice;
    cout << "Choose Level:" << endl;
    cout << "1. Endless" << endl;
    cout << "2. Heaven-Hell" << endl;
    cout << "3. Cross" << endl;
    cout << "4. Compartments" << endl;
    cout << "5. Center Hall" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        break;
    case 2:
        for (int j = 0; j < width / 3; j++) {
            obstacles[height / 2][j] = true;
        }
        for (int j = 2*width/3; j < width; j++) {
            obstacles[height / 2][j] = true;
        }
        break;
    case 3:
        for (int i = 0; i < height/4; i++) {
            obstacles[i][width / 2] = true;
        }
        for (int i = 3*height / 4; i < height; i++) {
            obstacles[i][width / 2] = true;
        }
        for (int j = 0; j < width/4; j++) {
            obstacles[height / 2][j] = true;
        }
        for (int j = 3*width / 4; j < width; j++) {
            obstacles[height / 2][j] = true;
        }
        break;
    case 4:
        for (int i = 0; i < height/2; i++) {
            obstacles[i][width / 4] = true;
        }
        for (int i = height/2; i < height; i++) {
            obstacles[i][2*width /3 ] = true;
        }
        for (int j = 0; j < width/2; j++) {
            obstacles[2*height / 3][j] = true;
        }
        for (int j = width/2; j < width; j++) {
            obstacles[height / 4][j] = true;
        }
        break;
    case 5:
        for (int i = height/4; i < 3*height/5; i++) {
            obstacles[i][width / 4] = true;
        }
        for (int i = 2*height/5; i < 3*height/4; i++) {
            obstacles[i][3*width / 4] = true;
        }
        for (int j = width/4; j < 3*width/4; j++) {
            obstacles[height / 4][j] = true;
        }
        for (int j = width/4; j < 3*width/4; j++) {
            obstacles[3*height / 4][j] = true;
        }
        break;
    default:
        break;
    }
}

//GAmePlay Area
void Draw() {
    system("cls");
    for (int i = 0; i < width/2 +1; i++)
        cout << "X ";
        cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) //border
                cout << "x";
            if (i == y && j == x) // snake
                cout << "O";
            else if (i == fruitY && j == fruitX) //fruit
                cout << "#";
            else if (obstacles[i][j]) // Draw obstacle if present
                cout << "*";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; //snake body
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1) //border
                cout << "x";
        }
        cout << endl;
    }

    for (int i = 0; i < width/2 +1; i++) //border
        cout << "X ";
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Score LevelUp:" << ScoreX << endl;
}

//Score LevelUp
void LevelUp() {
    if (score >= ScoreX * 50) {
        ScoreX++;
        if (ScoreX <= 3) {
            Levels();
            Draw();
        } else {
            gameOver = true;
        }
    }
}

int main() {
    while (true) {
        Levels();
        while (!gameOver) {
            Draw();
            LevelUp();
            Sleep(100);
        }

        // Game over
        Draw();
        cout << "Game Over!" << endl;
        cout << "Press R to restart or Q to quit." << endl;

        //restart or quit input
        char choice;
        cin >> choice;
        if (choice == 'r' || choice == 'R') {
            gameOver = false;
        } else if (choice == 'q' || choice == 'Q') {
            break;
        }
    }
    return 0;
}
