/* UPDATED-2021
 * Jordan Park
 * 2016/2017
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
 *     * acoustic brawl training music in menu?
 *     * Play
 *        * encase so when you win you go back
 *        * make betting (under 40, 30, 20, etc) with different betting multipliers
 *        * highlight the current pick if it's picked in a different color
 *        * make winning rows highlighted in a different color with a pause before the win   
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
#include <windows.h> //colors
#include <MMSystem.h> //sounds
#include <conio.h> //cursor position

 //play once
 //PlaySound(TEXT("DearGod.wav"), NULL, SND_ASYNC);
 //play and loop
 //PlaySound(TEXT("TakeOut.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

using namespace std;

string mpipe = "--------------------------------------------------------------------------------";
string pipe = "|";
string boardtitle = "|       B       |       I       |       N       |       G       |       O      |";

CONST int MENU_SIZE = 4;
string menu_choices[MENU_SIZE] = {"PLAY", "LEADERBOARDS", "ACCOUNT", "QUIT"};

//menu_item = element in menu_choices
//x 
int menu_item = 0, gotoY = 9;

//quit flag for program 
bool program = true;

//quit flag for game
bool game = true;

//winning numbers for showing 
vector<int> winningNums;

//global round tracker
int rounds = 0;

//2d array of our bingo card
int boardArrayNums[5][5] = { 0 };

//parallel 2d array of bools for if a number on our board has been picked
bool boardArrayFlags[5][5] = { {false} };

//a vector of picked balls so we don't pick the same ball twice
vector<bool> ballpool(75, false);

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto and SetColor()
COORD CursorPosition; // used for goto

/*
1: Blue 2: Green 3: Cyan 4: Red 5: Purple
6: Yellow (Dark) 7: Default white 8: Gray/Grey
9: Bright blue 10: Brigth green 11: Bright cyan
12: Bright red 13: Pink/Magenta 14: Yellow
15: Bright white
*/
void SetColor(string color)
{
	int value = 7;

	if (color == "Default" || color == "White")
	{
		value = 7;
	}
	else if (color == "Green")
	{
		value = 10;
	}
	else if (color == "Cyan" || color == "Blue")
	{
		value = 11;
	}
	else if (color == "Red")
	{
		value = 12;
	}
	else if (color == "Pink" || color == "Purple")
	{
		value = 13;
	}
	else if (color == "Yellow")
	{
		value = 14;
	}

	SetConsoleTextAttribute(console, value);
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

void bingologoMenu()
{
	fstream logoFile;
	logoFile.open("bingoAscii2.txt", ios::in);

	if (logoFile.is_open())
	{
		string logoLine;
		int rainbow = 10;
		while (getline(logoFile, logoLine))
		{
			SetConsoleTextAttribute(console, rainbow);
			rainbow++;
			cout << setw(53) << right << logoLine << endl;
		}
	}
	SetColor("Default");
}

//fills our users' board with random numbers 1-75 except our free space (0)
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

bool compareWinningNumbers(int x)
{
	for (int i = 0; i < winningNums.size(); i++)
	{
		if (winningNums[i] == x)
		{
			return true;
		}
	}
	return false;
}

//creates and displays our bingo card
void makeBoard(int foundPick)
{
	cout << endl;
	cout << mpipe;
	//BINGO top line
	string bingoString = "BINGO";
	cout << pipe << setw(8) << right;

	for (int i = 0; i < bingoString.size(); i++)
	{
		SetColor("Green");
		cout << bingoString[i];

		if (i < bingoString.size() - 1)
		{
			SetColor("Default");
			cout << setw(8) << pipe << setw(8);
		}
	}

	SetColor("Default");
	cout << setw(7) << pipe;//
	cout << mpipe;
	cout << endl;
	cout << mpipe;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SetColor("Default");

			if (!(i == 2 && j == 2)) //if not the free space
			{
				SetColor("Default");
				cout << right << pipe << setw(8);
				//if this number has been picked and is the most recent pick, make it yellow
				//or 
				//if the game has been won and this is one of the winning numbers
				if ((boardArrayFlags[i][j] && boardArrayNums[i][j] == foundPick) 
					|| (foundPick == -1 && compareWinningNumbers(boardArrayNums[i][j])))
				{
					SetColor("Yellow");
				}
				//if this number has been picked, 
				//then make it pink/purple to  the user
				else if (boardArrayFlags[i][j])
				{
					SetColor("Pink");
				}
				else
				{
					SetColor("Cyan");
				}
				cout << boardArrayNums[i][j];

				SetColor("Default");
				cout << ((j < 4) ? setw(8) : setw(7));
			}
			//free space
			else
			{
				cout << right << pipe << setw(13);
				//if game has been won and free space is included, yellow.. if not.. pink
				if (foundPick == -1 && compareWinningNumbers(0))
				{
					SetColor("Yellow");
				}
				else
				{
					SetColor("Pink");
				}
				cout << "Free  space";
				SetColor("Default");
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
	PlaySound(TEXT("ShootingGallery.wav"), NULL, SND_ASYNC | SND_LOOP);
	SetColor("Yellow");
	bingologo();
	SetColor("Default");
	Sleep(3000);
	system("cls");

	//set free space to true.
	boardArrayFlags[2][2] = true;

	//fill board with numbers
	fillBoard();
}

//check the picked ball (int pick) with the scorecard numbers (boardArrayNums)
bool checkpick(int pick)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//if pick is on your scoreboard, set flag
			if (boardArrayNums[i][j] == pick)
			{
				boardArrayFlags[i][j] = true;
				return true;
			}
		}
	}
	return false;
}

//If the check finds you've won, play the winning screen and audio
void winScreen()
{
	SetColor("Green");
	bingologo();
	cout << endl;
	PlaySound(TEXT("Bingo.wav"), NULL, SND_ASYNC);
	Sleep(2000);
	SetColor("Cyan");
	cout << setw(46) << "BINGO! You win!" << endl;
	cout << setw(39) << "It took " << rounds << " rounds." << endl;
	SetColor("Default");
	//-1 is code for winning here, set the winning numbers to yellow
	makeBoard(-1);
	Sleep(2000);
	system("pause");
	system("cls");
}

//function to check your scorecards' rows or columns for wins
//winningNums keeps track of last checked row or column for 
//if it is a win, we can reference it for highlighting it later
bool checkRowsOrColumns(string orientation)
{
	for (int i = 0; i < 5; i++)
	{
		bool consecutive = true;
		for (int j = 0; j < 5; j++)
		{
			if (!boardArrayFlags[i][j] && orientation == "rows")
			{
				winningNums.clear();
				consecutive = false;
			}
			else if (!boardArrayFlags[j][i] && orientation == "columns")
			{
				winningNums.clear();
				consecutive = false;
			}

			if (orientation == "rows" && consecutive == true)
			{
				winningNums.push_back(boardArrayNums[i][j]);
			}
			else if (orientation == "columns" && consecutive == true)
			{
				winningNums.push_back(boardArrayNums[j][i]);
			}
		}
		if (consecutive)
		{
			return true;
		}
	}
	winningNums.clear();
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
		winningNums.push_back(boardArrayNums[i][i]);
	}

	//check for top left -> bottom right
	if (consecutive)
	{
		return true;
	}

	winningNums.clear();
	
	//bottom left -> top right
	consecutive = true;
	for (int i = 4, j = 0; i >= 0 && j <= 4; i--, j++)
	{
		if (!boardArrayFlags[i][j])
		{
			consecutive = false;
		}
		winningNums.push_back(boardArrayNums[i][j]);
	}
	//check for bottom left -> top right
	if (consecutive)
	{
		return true;
	}
	
	winningNums.clear();
	return false;

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

		bool foundPick = checkpick(pick);

		//highlight pick in yellow if foundPick is true on the board
		cout << endl;
		if (foundPick)
		{
			makeBoard(pick);
		}
		else
		{
			makeBoard(0);
		}

		//display rounds and the ball pick
		cout << endl << endl;
		cout << setw(32) << " ---------------";
		cout << setw(33) << "---------------\n";
		cout << setw(17) << pipe << "  ROUND: ";
		SetColor("Red");
		cout << setw(2) << rounds;
		SetColor("Default");
		cout << setw(4) << pipe;

		SetColor("Default");
		cout << setw(18) << right << pipe << "  PICK: ";
		SetColor("Yellow");
		cout << setw(2) << pick;
		SetColor("Default");
		cout << setw(4) << pipe << endl;
		cout << setw(32) << " ---------------";
		cout << setw(33) << "---------------\n";

		cout << endl << endl << endl << endl;
		Sleep(600);
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

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void displayMenuOptions(int selected)
{
	for (int i = 0, j = 9; i < MENU_SIZE; i++, j+=2)
	{
		gotoXY(32, j);

		if (i == selected)
		{
			SetColor("Purple");
		}

		cout << menu_choices[i];

		SetColor("Default");
	}
}

void menu()
{
	cout << endl;
	bingologoMenu();
	SetColor("Yellow");
	gotoXY(29, 9); cout << "->";
	SetColor("Default");
	

	while (program)
	{
		displayMenuOptions(menu_item);

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN)) //down button pressed
		{
			//reset old arrow
			gotoXY(29, gotoY); cout << "  ";

			//if going down and you reach the end of list, reset to top
			if (gotoY == 15)
			{
				gotoY = 9;
				menu_item = 0;
			}
			else
			{
				gotoY+=2;
				menu_item++;
			}

			SetColor("Yellow");
			gotoXY(29, gotoY); cout << "->";
			SetColor("Default");
			continue;

		}

		if (GetAsyncKeyState(VK_UP)) //up button pressed
		{
			//reset old arrow
			gotoXY(29, gotoY); cout << "  ";

			//if going up and you reach the top of the list, reset to bottom
			if (gotoY == 9)
			{
				gotoY = 15;
				menu_item = MENU_SIZE - 1;
			}
			else
			{
				gotoY-=2;
				menu_item--;
			}

			SetColor("Yellow");
			gotoXY(29, gotoY); cout << "->";
			SetColor("Default");
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {

				gotoXY(20, 16);
				system("cls");
				makeGame();
				play();
				cout << endl;
				bingologoMenu();
				SetColor("Yellow");
				gotoXY(29, 9); cout << "->";
				SetColor("Default");
				break;
			}


			case 1: {
				gotoXY(20, 16);
				cout << "You chose Leaderboards...     ";
				break;
			}

			case 2: {
				gotoXY(20, 16);
				cout << "You chose Account...     ";
				break;
			}

			case 3: {
				gotoXY(20, 16);
				program = false;
			}

			}
		}
	}

	gotoXY(20, 21);
}

int main()
{
	SetWindow(80, 30);
	srand(time(NULL));
	menu();
	system("pause");
	return 0;
}