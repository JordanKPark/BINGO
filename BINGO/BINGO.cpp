/* UPDATED-2021
 * Jordan Park
 * 2016
 * Bingo Application!
 *
 * To add windows.h and Play sound:
 * Project -> properties -> general -> update SDK
 * Project -> properties -> linker -> input -> add dependency "Winmm.lib"
 *
 * NOTE ON STARTUP! :
 * Although it should automatically do it,
 * In console properties,
 *  * The buffer size of the window should be SET TO 80 for intended output
 *  * UNCHECK wrap text on output
 */

 /* TO DO list
 *
 *  * Bingo display in a text file
 *  * Users Login opening screen or continue as guest
 *  * Users are associated with currency
 *  * Menu
 *     * Play
 *        * encase so when you win you go back
 *        * highlight the current pick if it's picked in a different color
 *        * make winning rows highlighted in a different color with a pause before the win
 *        * make betting (under 40, 30, 20, etc) with different betting multipliers
 *     * Leaderboards
 *        * for best rounds
 *        * for highest moneys
 *     * Quit
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <MMSystem.h>

 //play once
 //PlaySound(TEXT("DearGod.wav"), NULL, SND_ASYNC);
 //play and loop
 //PlaySound(TEXT("TakeOut.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

using namespace std;

string mpipe = "--------------------------------------------------------------------------------";
string pipe = "|";
string boardtitle = "|       B       |       I       |       N       |       G       |       O      |";

//quit flag for program 
bool program = true;

//quit flag for game
bool game = true;

//global round tracker
int rounds = 0;

//2d array of our bingo card
int boardArrayNums[5][5] = { 0 };

//parallel 2d array of bools for if a number on our board has been picked
bool boardArrayFlags[5][5] = { {false} };

//a vector of picked balls so we don't pick the same ball twice
vector<bool> ballpool(75, false);

/*
1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white
*/
void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

//Returns Random number 1-75
int RNG()
{
	int n = (rand() % 75) + 1;
	return n;
}

//Check for duplicate random number on our Board
bool duplicateCheck(int x)
{
	bool run = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (boardArrayNums[i][j] == x)
			{
				run = true;
			}
		}
	}
	return run;
}

//displays ascii bingo
void bingologo()
{
	fstream logoFile;
	logoFile.open("bingoAscii.txt", ios::in);

	if (logoFile.is_open())
	{
		string logoLine;
		while (getline(logoFile, logoLine))
		{
			cout << setw(73) << right << logoLine << endl;
		}
	}
}

//fills our users' board with random numbers except our free space
//#no duplicates
void fillBoard()
{
	int boardNum;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!(i == 2 && j == 2))
			{
				boardNum = RNG();
				while (duplicateCheck(boardNum))
				{
					boardNum = RNG();
				}
				boardArrayNums[i][j] = boardNum;
			}
		}
	}
}

//creates and displays our bingo card
void makeBoard()
{
	cout << endl;
	cout << mpipe;
	//BINGO top line
	cout << pipe << setw(8) << right;
	SetColor(10);
	cout << "B";
	SetColor(7);
	cout << setw(8) << pipe << setw(8);
	SetColor(10);
	cout << "I";
	SetColor(7);
	cout << setw(8) << pipe << setw(8);
	SetColor(10);
	cout << "N";
	SetColor(7);
	cout << setw(8) << pipe << setw(8);
	SetColor(10);
	cout << "G";
	SetColor(7);
	cout << setw(8) << pipe << setw(8);
	SetColor(10);
	cout << "O";
	SetColor(7);
	cout << setw(7) << pipe;//
	cout << mpipe;
	cout << endl;
	cout << mpipe;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SetColor(7);

			if (!(i == 2 && j == 2))
			{
				SetColor(7);
				cout << right << pipe << setw(8);

				//if this number has been picked, 
				//then make it purple to  the user
				if (boardArrayFlags[i][j])
				{
					SetColor(13);
				}

				cout << boardArrayNums[i][j];
				SetColor(7);

				cout << ((j < 4) ? setw(8) : setw(7));
			}
			else
			{
				cout << right << pipe << setw(13);
				SetColor(13);
				cout << "Free  space";
				SetColor(7);
				cout << setw(3);
			}
		}
		cout << pipe;
		cout << mpipe;
	}
}

//Making every variable start as false
//filling board and starting music. setting free space to true
void makeGame()
{
	PlaySound(TEXT("ShootingGallery.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	SetColor(14);
	bingologo();
	SetColor(7);
	Sleep(3000);
	system("cls");

	//set free space to true.
	boardArrayFlags[2][2] = true;

	//fill board with numbers
	fillBoard();
}

//check the picked ball (int pick) with the scorecard numbers (boardArrayNums)
void checkpick(int pick)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//if pick is on your scoreboard, set flag
			if (boardArrayNums[i][j] == pick)
			{
				boardArrayFlags[i][j] = true;
			}
		}
	}
}

//If the check finds you've won, play the winning screen and audio
void winScreen()
{
	SetColor(10);
	bingologo();
	PlaySound(TEXT("Bingo.wav"), NULL, SND_ASYNC);
	Sleep(2000);
	SetColor(11);
	cout << setw(46) << "BINGO! You win!" << endl;
	cout << setw(39) << "It took " << rounds << " rounds." << endl;
	SetColor(7);
	makeBoard();
	Sleep(2000);
}

//function to check your scorecards' rows or columns for wins
bool checkRowsOrColumns(string orientation)
{
	for (int i = 0; i < 5; i++)
	{
		bool consecutive = true;
		for (int j = 0; j < 5; j++)
		{
			if (!boardArrayFlags[i][j] && orientation == "rows")
			{
				consecutive = false;
			}
			else if (!boardArrayFlags[j][i] && orientation == "columns")
			{
				consecutive = false;
			}
		}
		if (consecutive)
		{
			return true;
		}
	}
	return false;
}

//function to check your scorecards' diagonals for wins
bool checkDiagonals()
{
	bool consecutive = true;
	//top left -> bottom right
	for (int i = 0; i < 5; i++)
	{
		if (!boardArrayFlags[i][i])
		{
			consecutive = false;
		}
	}

	//check for top left -> bottom right
	if (consecutive)
	{
		return true;
	}

	//bottom left -> top right
	consecutive = true;
	for (int i = 4, j = 0; i >= 0 && j <= 4; i--, j++)
	{
		if (!boardArrayFlags[i][j])
		{
			consecutive = false;
		}
	}
	//check for bottom left -> top right
	if (consecutive)
	{
		return true;
	}
}

//win check for if the rows or columns or diagonals have a win.
//if so, end program and display the win screen
void winCheck()
{
	if (checkRowsOrColumns("rows") || checkRowsOrColumns("columns") || checkDiagonals())
	{
		winScreen();
		game = false;
	}
}

//play game loop, keeps track of rounds and picks, then displays
//calls makeBoard after each pick and then checks for win
void play()
{
	while (game)
	{
		//increment rounds
		rounds++;

		//take a pick
		int pick = RNG();
		while (ballpool[(pick - 1)])
		{
			pick = RNG();
		}
		//set flag in ballpool to true/picked
		ballpool[(pick - 1)] = true;

		//display rounds and the ball pick
		cout << "Round: ";
		SetColor(12);
		cout << rounds;
		SetColor(7);
		cout << setw(35) << right << "Pick: ";
		SetColor(14);
		cout << pick << endl;
		SetColor(7);

		checkpick(pick);

		makeBoard();
		system("pause");
		system("cls");
		winCheck();
	}
}

//Set the window size buffer to 80 for correct format.
void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

void menu()
{
	/*
	while (program)
	{

	}
	*/
}

int main()
{
	SetWindow(80, 20);
	srand(time(NULL));
	menu();
	makeGame();
	play();
	system("pause");
	return 0;
}