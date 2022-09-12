#include <iostream>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include <time.h>

#define Screen_width 90
#define Screen_height 26
#define Win_width 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','+','+',' ',
					'+','+','+','+',
					' ','+','+',' ',
					'+','+','+','+' };

int carPos = Win_width / 2;
int score = 0;

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
	if (size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
void DrawBorder()
{
	for (int i = 0; i < Screen_height; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			gotoXY(0 + j, i);	cout << "±";
			gotoXY(Win_width - j, i);	cout << "±";
		}
	}
	for (int i = 0; i < Screen_height; i++)
	{
		gotoXY(Screen_width, i);	cout << "±";
	}
}
void GenEnemy(int ind)
{
	enemyX[ind] = 17 + rand() % 33;
}
void DrawEnemy(int ind)
{
	if (enemyFlag[ind] == true)
	{
		gotoXY(enemyX[ind], enemyY[ind]);	cout << "****";
		gotoXY(enemyX[ind], enemyY[ind]+1);	cout << " ** ";
		gotoXY(enemyX[ind], enemyY[ind]+2);	cout << "****";
		gotoXY(enemyX[ind], enemyY[ind]+3);	cout << " ** ";
	}
}
void EreaseEnemy(int ind)
{
	if (enemyFlag[ind] == true)
	{
		gotoXY(enemyX[ind], enemyY[ind]);	cout << "    ";
		gotoXY(enemyX[ind], enemyY[ind] + 1);	cout << "    ";
		gotoXY(enemyX[ind], enemyY[ind] + 2);	cout << "    ";
		gotoXY(enemyX[ind], enemyY[ind] + 3);	cout << "    ";
	}
}
void ResetEnemy(int ind)
{
	EreaseEnemy(ind);
	enemyY[ind] = 1;
	GenEnemy(ind);
}
void DrawCar()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoXY(j + carPos, i + 22);	cout << car[i][j];
		}
	}
}
void eraseCar()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoXY(j + carPos, i + 22);	cout << " ";
		}
	}
}
int collision()
{
	if (enemyY[0] + 4 >= 23)
	{
		if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
		{
			return 1;
		}
	}
	return 0;
}
void GameOver()
{
	system("cls");
	cout << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t---------- Game Over -----------\n";
	cout << "\t\t--------------------------------\n\n";
	cout << "\t\t\tScore: " << score<<endl;
	cout << "\t\tPress any key to go back to menu";
	_getch();
}
void updateScore()
{
	gotoXY(Win_width + 7, 5); cout << "Score: " << score << endl;
}
void instructions()
{
	system("cls");
	cout << "Instructions";
	cout << "\n--------------------------";
	cout << "\nAvoid cars by moving left or right";
	cout << "\n\nPress 'a' to move left";
	cout << "\nPress 'd' to move left";
	cout << "\nPress 'escape' to exit";
	cout << "\n\nPress any key to go back to menu";
	_getch();
}
void play()
{
	carPos = -1 + Win_width / 2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	system("cls");
	DrawBorder();
	updateScore();
	GenEnemy(0);
	GenEnemy(1);
	gotoXY(Win_width + 7, 2);	cout << "Car Game";
	gotoXY(Win_width + 6, 4);	cout << "-----------";
	gotoXY(Win_width + 6, 6);	cout << "-----------";
	gotoXY(Win_width + 7, 12);	cout << "Control";
	gotoXY(Win_width + 7, 13);	cout << "--------- ";
	gotoXY(Win_width + 2, 14);	cout << " A Key - Left";
	gotoXY(Win_width + 2, 15);	cout << " D Key - Right";
	gotoXY(18,5);	cout << "Press any Key to start";
	_getch();
	gotoXY(18,5);	cout << "                      ";
	while (1)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a' || ch == 'A')
			{
				if (carPos > 18)
				{
					carPos -= 4;
				}
			}
			if (ch == 'd' || ch == 'D')
			{
				if (carPos < 50)
				{
					carPos += 4;
				}
			}
			if (ch == 27)
			{
				break;
			}
		}
		DrawCar();
		DrawEnemy(0);
		DrawEnemy(1);
		if (collision() == 1)
		{
			GameOver();
			return;
		}
		Sleep(50);
		eraseCar();
		EreaseEnemy(0);
		EreaseEnemy(1);
		if (enemyY[0] == 10)
		{
			if (enemyFlag[1] == 0)
			{
				enemyFlag[1] = 1;
			}
		}
		if (enemyFlag[0] == 1)
		{
			enemyY[0] += 1;
		}
		if (enemyFlag[1] == 1)
		{
			enemyY[1] += 1;
		}
		if (enemyY[0] > Screen_height - 4)
		{
			ResetEnemy(0);
			score++;
			updateScore();
		}
		if (enemyY[1] < Screen_height - 4)
		{
			ResetEnemy(1);
			score++;
			updateScore();
		}
	}
}
int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	do
	{
		system("cls");
		gotoXY(10, 5);	cout << "----------------------";
		gotoXY(10, 6);	cout << "|      Car Game      |";
		gotoXY(10, 7);	cout << "----------------------";
		gotoXY(10, 9);	cout << "1. Start game";
		gotoXY(10, 10);	cout << "2. Instructions";
		gotoXY(10, 11);	cout << "3. Quit";
		gotoXY(10, 13);	cout << "Select Option:";
		char op = _getche();
		if (op == '1')
		{
			play();
		}
		else if (op == '2')
		{
			instructions();
		}
		else if (op == '3')
		{
			exit(0);
		}
	}
	while (1);
	return 0;
}