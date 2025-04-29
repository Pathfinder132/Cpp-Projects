#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
int t = 15;
const int width = 20;
const int height = 20;
int fruX, fruY, score;
enum eDir
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
}; // enum declartion to navigate the key switch from left right up down
eDir direction;
struct tailNode
{
    int x;
    int y;
    tailNode *next;
};
tailNode *head = new tailNode;

tailNode *tail = head;
int prevX, prevY;
void setup()
{
    head->next = nullptr;
    gameOver = false;
    direction = STOP; // initial case
    head->x = (width + t) / 2;
    head->y = height / 2;
    head->next = nullptr;
    fruX = rand() % width + t + 1; //% width is to basically range it x-1
    fruY = rand() % height + 1;
    score = 0;
}
tailNode *current = head;
void draw()
{
    system("cls"); // clearscreen
    for (int i = 0; i < width + t + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    current = head->next;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width + t + 2; j++) // 22 sized border is required to get a playfield of 20x20
        {
            current = head->next;
            if (j == 0 || j == width + t + 1)
            {
                cout << "#";
            }
            else if (i == head->y && j == head->x)
            {
                cout << "O";
            }
            else if (i == fruY && j == fruX)
            {
                cout << "F";
            }
            else
            {
                bool printed = false;
                while (current != nullptr)
                {
                    if (i == current->y && j == current->x)
                    {
                        cout << "o";
                        printed = true;
                        break;
                    }
                    else
                    {
                        current = current->next;
                    }
                }
                if (printed != true)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + t + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
}
int cont = 0;
void input()
{
    if (head->x == fruX && head->y == fruY)
    {
        int lastX = tail->x;
        int lastY = tail->y;

        tailNode *newnode = new tailNode;
        newnode->next = nullptr;
        score = score + 10;

        tail->next = newnode;
        tail = newnode;

        newnode->x = lastX;
        newnode->y = lastY;

        if (cont % 2 == 0)
        {
            fruX = rand() % (width + t - 2) + 1;
            fruY = rand() % (height - 2) + 1;
            cont++;
        }
        else if (cont % 2 == 1 && width > 10 && height > 10)
        {
            fruX = rand() % (width + t - 4) + 4;
            fruY = rand() % (height - 4) + 4;
            cont++;
        }
    }
    if (head->x <= 1 || head->x >= width + t || head->y <= 0 || head->y >= height - 1)
        gameOver = true; // this basically covers the boundaries very well so game over can be true
    if (_kbhit())        // for getting the key when user hits the key
    {
        switch (_getch())
        {
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'x':
            gameOver = true; // while loop ends when its true
            break;
        }
    }
}

void logic()
{
    prevX = head->x;
    prevY = head->y;

    switch (direction)
    {
    case LEFT:
        head->x = (head->x) - 1;
        break;
    case RIGHT:
        head->x = (head->x) + 1;
        break;
    case UP:
        head->y = (head->y) - 1; // increasing y will make it go UP in matrix
        break;
    case DOWN:
        head->y = (head->y) + 1; // increasing y will make it go down in matrix
        break;
    }

    current = head->next;
    while (current != nullptr)
    {
        int tempX = current->x;
        int tempY = current->y;

        current->x = prevX;
        current->y = prevY;

        prevX = tempX;
        prevY = tempY;
        current = current->next;
    }
    int delay = max(10, 100 - (score / 2));
    Sleep(delay);
}
int main()
{
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
    }
    cout << "YOUR SCORE: " << score << " !!" << endl;
    return 0;
}