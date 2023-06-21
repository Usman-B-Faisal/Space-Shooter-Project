#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void start();
void welcome();
void levelUP();
void frame();
void Pause();
void in_rec();
void corelogic();
void gameover();

bool fire0, fire1, fire2, restart, lost, existf0, S_enemy3;
bool S_enemy, S_enemy0, S_enemy1, S_enemy2, existf1, pause;
const int width = 40;
const int height = 15;
int x = 0, y = 0, eX = 0, eY = 0,e0X = 0, e0Y = 0, f0X = 0, f0Y = 0, f1X = 0, f1Y = 0, f2X = 0, f2Y = 0, level = 1;
int e1X = 0, e1Y = 0, e2X = 0, e2Y = 0, e3X = 0, e3Y = 0, score = 0, lives = 0, speed0 = 20, speed1 = 10;
char enemy0 = char(234), enemy1 = char(232);
long clo;


int main()
{
	srand(time(0));
	ofstream record;
start:
	welcome();
	start();
	SetConsoleTextAttribute(hStdOut, 8); //color: BG: black | Text: Grey.
	while (!lost)
	{
		levelUP();
		frame();
		in_rec();
		Pause();
		corelogic();

		if (restart)
		{
		restart:
			system("cls");
			for (int i = 0; i < 9; i++)
				cout << "\n";
			system("color 0E");  //color: BG: black | text: light_Yellow
			cout << "\t\t\t\t\t\t  :) Restarting...\n";
			Sleep(1500);
			system("cls");
			goto start;
		}
		Sleep(15); //control frames speed.
		clo++; 
	}

	system("cls");
	Sleep(200);
	record.open("record.txt",ios::app);
	gameover();
	cout << "\n\t\t Press 'r' to play again. \n\t\t Press 'e' to save record and exit. ";
	if (_getch() == 'r')
		goto restart;
	else if (_getch() == 'e')
	{ 
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t        Saveing... \n";
		Sleep(1500);
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t  Saved successfully  ;) \n\n\n\n\n\n\n";
		record << endl <<"\t\t\t\t\t\t  " << level << "   |   " << score;

	}
}

void start()
{
	pause = false;
	restart = false;
	lost = false;
	existf0 = false;
	existf1 = false;
	score = 0;
	lives = 3;
	x = width / 2;
	y = height - 1;
	eX = rand() % width;
	e0X = rand() % width;
	e1X = rand() % width;
	e2X = rand() % width;
	e3X = rand() % width;
	eY = 0;
	e0Y = 0;
	e1Y = 0;
	e2Y = 0;
	e3Y = 0;
}

void welcome()
{             
	 system("color 0E");   //color: BG: black | text: light_Yellow
	 cout << "\n\n\n\n";
	 cout << "      - - - - - - - - - - - - - - - - - - - - -| S P A C E  S H O O T E R |- - - - - - - - - - - - - - - - - - - - -";
	 cout << "\n\n\n\n";
	 cout << "       ----------------->>INSTRUCTIONS<<----------------- \t ------------------->>CONTROLS<<------------------- \n";
	 cout << "      |                                                  |\t|                                                  |\n";
	 cout << "      |-> Kill the enemies before they pass you.         |\t|-> Use 'a' to move left and 'd' to move right.    |\n";
	 cout << "      |-> Be careful some of them have more health.       |\t|-> Press space to fire, one at a time.            |\n";
	 cout << "      |-> Killing this one '" << char(234) << "' gives 2 points.           |\t|-> Press 'r' to restart the game.                 |\n";
	 cout << "      |-> Killing this one '" << char(232) << "' gives 5 points.           |\t|-> Press 'p' to pause the game.                   |\n";
	 cout << "      |-> This one '" << char(232) << "' is faster so, kill him FAST.      |\t|-> Press 'e' to end the game.                     |\n";
	 cout << "      |-> You have only one chance, be careful.          |\t|-> Press enter to start the game.                 |\n";
	 cout << "      |                                                  |\t|                                                  |\n";
	 cout << "       -------------------------------------------------- \t -------------------------------------------------- \n";

	_getch();
}

void levelUP()
{
	if (score >= 80 && level < 5)
	{
		level++;
		score = 0;

		if (level == 1)
			speed0 = 20;

		else if (level == 2) 
		{
			speed0 = 20;
			speed1 = 15;
		}

		else if (level == 3)
		{
			speed0 = 15;
			speed1 = 10;
		}

		else if (level == 4)
		{
			speed0 = 10;
			speed1 = 5;
		}

		else if (level == 5)
		{
			system("cls");
			for (int i = 0; i < 7; i++)
				cout << "\n";
			system("color 0E");  //color: BG: black | text: light_Yellow
			cout << "\t\t\t\t\t ------------------------ \n";
			cout << "\t\t\t\t\t|     You Are Winner     |\n";
			cout << "\t\t\t\t\t ------------------------ \n";
			Sleep(500);
			cout << "\n\n\t\t Press 'e' to end. \n\t\t Press 'c' to continue to Endless mode.";
			if (_getch() == 'e')
				lost = true;

			else if (_getch() == 'c')
				system("color 08");  //color: BG: black | text: Grey
		}
	}
}

void frame()
{
	system("cls");
	for (int i = 0; i < width; i++)
	{
		cout << char(219); //upper main wall.
	}
	cout << '\n';

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width + 3; j++)
		{
			if (j == 0)
				cout << char(219); //left side main wall.

			if (j > 0 && j < width - 1)//width - 1, so don't print on the boundary. 
			{
				if (i == y && j == x)
					cout << char(202);
				else if ((i == e0Y && j == e0X && S_enemy0 == true) || (i == eY && j == eX && S_enemy == true))
					cout << enemy0;
				else if (i == e1Y && j == e1X && S_enemy1 == true)
					cout << enemy0;
				else if ((i == e2Y && j == e2X && S_enemy2 == true) || (i == e3Y && j == e3X && S_enemy3 == true))
					cout << enemy1;
				else if ((i == f0Y && j == f0X) || (i == f1Y && j == f1X) || (i == f2Y && j == f2X))
					cout << "*";
				else
					cout << " ";
			}

			if (j == width + 2)
				cout << char(219); //right side main wall.
		}
		cout << "\n";
	}
	for (int i = 0; i < width; i++)
	{
		cout << char(219); //bottom main wall
	}
	
	               //bottom score wall.
	if (score < 10 && level < 5)
	{
	cout << "\n" << char(219);
	cout << "  Score: " << score << "  " << char(219);
	cout << "  Lives: " << lives << "  " << char(219);
	cout << "  Level: " << level << "  " << char(219);
	}
	else if (score >= 10 && level < 5) 
	{
		cout << "\n" << char(219);
		cout << " Score: " << score << "  " << char(219);
		cout << "  Lives: " << lives << "  " << char(219);
		cout << "  Level: " << level << "  " << char(219);
	}
	else if (score < 10 && level == 5)
	{
		cout << "\n" << char(219);
		cout << "  Score: " << score << "  " << char(219);
		cout << "  Lives: " << lives << "  " << char(219);
		cout << "   Endless  " << char(219);
	}
	else if (score >= 10 && level ==5)
	{
		cout << "\n" << char(219);
		cout << " Score: " << score << "  " << char(219);
		cout << "  Lives: " << lives << "  " << char(219);
		cout << "  Endless   " << char(219);
	}

	cout << "\n";
	for (int i = 0; i < width; i++)
	{
		cout << char(219);
	}
	cout << "\n";
}
	

void Pause()
{
	if (pause)
	{
		system("cls");
		Sleep(100);

		for (int i = 0; i < 9; i++)
			cout << "\n";
		system("color 0E");  //color: BG: black | text: light_Yellow
		cout << "\t\t\t\t\t\t  Game Paused " << char(222) << char(222);

		_getch();
		pause = false;
		system("color 08");  //color: BG: black | text: Grey
	}
}

void in_rec()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (x > 1)     //left movement
			{
				x -= 1;
			}
			break;

		case 'd':          //right movement
			if (x < width - 2)
			{
				x += 1;
			}
			break;

		case ' ':
		{
			if (fire0 == false)
			{
				fire0 = true;
				existf0 = true;
			}
			else if (fire1 == false)
			{
				fire1 = true;
				existf1 = true;
			}
			else
				fire2 = true;
		}
			break;

		case 'e':

			lost = true;
			break;

		case 'r':

			restart = true;
			break;

		case 'p':

			pause = true;
			break; 

		}
	}

}


void corelogic()
{
	// missile logic
	if (fire0 == true && existf0 == true)
	{
		f0X = x;
		f0Y = height - 2;
		existf0 = false;
	}

	if (f0Y == 0)
	{
		existf0 = false;
		fire0 = false;
	}
	if (fire1 == true && existf1 == true)
	{
		f1X = x;
		f1Y = height - 2;
		existf1 = false;
	}
	
	if (f1Y == 0)
	{
		existf1 = false;
		fire1 = false;
	}
	
	if(fire2 == true)
	{
		f2X = x;
		f2Y = height - 2;
		fire2 = false;
	}
	f0Y -= 1;        //for movement of missles
	f1Y -= 1;
	f2Y -= 1;
	                                      //for enemy
	if (f0Y == eY && f0X == eX || f1Y == eY && f1X == eX || f2Y == eY && f2X == eX) //death logic of enemy.
	{
		score += 2;
		S_enemy = false;
		enemy0 = char(234);
		eX = 0;
		eY = 0;
	}
	if (clo % speed0 == 0) //slowes speed of enemy movement.
		eY++;
	if (clo % 50 == 0 && S_enemy == false)//enemy spawn logic.
	{
		S_enemy = true;
		eX = rand() % (width - 3);
		eY = 0;
	}

	                                      //for enemy0
	if (f0Y == e0Y && f0X == e0X || f1Y == e0Y && f1X == e0X || f2Y == e0Y && f2X == e0X) //death logic of enemy.
	{
		score += 2;
		S_enemy0 = false;
		enemy0 = char(234);
		e0X = 0;
		e0Y = 0;
	}
	if (clo % speed0 == 0) //slowes speed of enemy movement.
		e0Y++;
	if (clo % 50 == 0 && S_enemy0 == false)//enemy spawn logic.
	{
		S_enemy0 = true;
		e0X = rand() % (width - 3);
		e0Y = 0;
	}
	                                      //for enemy1 
	if (f0Y == e1Y && f0X == e1X || f1Y == e1Y && f1X == e1X || f2Y == e1Y && f2X == e1X)//death logic of enemy.
	{
		score += 2;
		S_enemy1 = false;
		enemy0 = char(234);
		e1X = 0;
		e1Y = 0;
	}
	if (clo % speed0 == 0) //slowes speed of enemy movement.
		e1Y++;
	if (clo % 30 == 0 && S_enemy1 == false)//enemy spawn logic.
	{
		S_enemy1 = true;
		e1X = rand() % (width - 3);
		e1Y = 0;
	} 
	                                      //for enemy2
	if (f0Y == e2Y && f0X == e2X || f1Y == e2Y && f1X == e2X || f2Y == e2Y && f2X == e2X)//death logic of enemy.
	{
		score += 5;
		S_enemy2 = false;
		enemy1 = char(232);
		e2X = 0;
		e2Y = 0;
	}
	if (clo % speed1 == 0) //slowes speed of enemy movement.
		e2Y++;
	if (clo % 100 == 0 && S_enemy2 == false && level > 1)//enemy spawn logic.
	{
		S_enemy2 = true;
		e2X = rand() % (width - 3);
		e2Y = 0;
	}                                      //for enemy3
	if (f0Y == e3Y && f0X == e3X || f1Y == e3Y && f1X == e3X || f2Y == e3Y && f2X == e3X)//death logic of enemy.
	{
		score += 5;
		S_enemy3 = false;
		enemy1 = char(232);
		e3X = 0;
		e3Y = 0;
	}
	if (clo % speed1 == 0) //slowes speed of enemy movement.
		e3Y++;
	if (clo % 75 == 0 && S_enemy3 == false && level > 3)//enemy spawn logic.
	{
		S_enemy3 = true;
		e3X = rand() % (width - 3);
		e3Y = 0;
	}

	if ((S_enemy1 == true && e1Y == height) || (S_enemy2 == true && e2Y == height) || (S_enemy0 == true && e0Y == height) || (S_enemy == true && eY == height))
	{
		lives -= 1;
	}
	
	if(lives == 0)
	{
			lost = true;
	}
}

void gameover()
{
	system("color 04"); //color: BG: black | text: Red
	for (int i = 0; i < 9; i++)
		cout << "\n";

	cout << "\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout << "\t\t\t\t\t\tx       Game Over       x\n";
	cout << "\t\t\t\t\t\txxxxxxxxxxxxxxxxxxxxxxxxx\n";
	Sleep(1000);
	system("cls");
	for (int i = 0; i < 7; i++)
		cout << "\n";
	system("color 0E"); //color: BG: black | text: light_Yellow
	cout << "\t\t\t\t\t\t ------->>RECORD<<------- \n";
	cout << "\t\t\t\t\t\t|   You reached level " << level << "  |\n";
	cout << "\t\t\t\t\t\t|------------------------|\n";
	if (score < 10)
		cout << "\t\t\t\t\t\t|    Your score was: " << score << "   |\n";
	else
		cout << "\t\t\t\t\t\t|   Your score was: " << score << "   |\n";
	cout << "\t\t\t\t\t\t ------------------------ \n";

	for (int i = 0; i < 7; i++)
		cout << "\n";
}