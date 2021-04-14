/*
 * Jordan Park
 * 2016
 * Bingo Application!
 * 
 * To add windows.h and Play sound:
 * Project -> properties -> general -> update SDK
 * Project -> properties -> linker -> input -> add dependency "Winmm.lib"
 * 
 * Although it should automatically do it, the buffer size of the window 
 * should be set to 80 for intended output
 */

#include <iostream>
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

string bingo1 = "______ _____ _   _ _____ _____ ";
string bingo2 = "| ___ \\_   _| \\ | |  __ \\  _  |";
string bingo3 = "| |_/ / | | |  \\| | |  \\/ | | |";
string bingo4 = "| ___ \\ | | | . ` | | __| | | |";
string bingo5 = "| |_/ /_| |_| |\\  | |_\\ \\ \\_/ /";
string bingo6 = "\\____/ \\___/\\_| \\_/\\____/\\___/ ";
                               
                               


string mpipe = "--------------------------------------------------------------------------------";
string pipe = "|";
string boardtitle = "|       B       |       I       |       N       |       G       |       O      |";
int program = 1;
int rounds = 0;
int a;
int n;

//int c for color 

int c = 13;
int pick;
bool rocky;
bool rocky2;
//
bool one;
bool two;
bool three;
bool four;
bool five;
bool six;
bool seven;
bool eight;
bool nine;
bool ten;
bool eleven;
bool twelve;
bool thirteen;
bool fourteen;
bool fifteen;
bool sixteen;
bool seventeen;
bool eighteen;
bool nineteen;
bool twenty;
bool twenty1;
bool twenty2;
bool twenty3;
bool twenty4;
bool twenty5;


vector<int> vect25(25);
vector<int> vectpara(25);
vector<int> ballpool(100);

void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

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

void writecolor(int thing);

int RNG()
{
	n = (rand() % 75) + 1;
	return n;
}

bool duplicate(vector<int> vect, int b) 
{
	bool run = false;
	for (int i = 0; i < 25; i++)
	{
		if (vect[i] == b)
		{
			run = true;
		}
	}
	return run;
}

void fillpool()
{
	for (int i = 0; i < 100; i++)
	{ 
		ballpool[i] = i + 1;
	}
}

void bingologo()
{
	cout << setw(54) << right << bingo1 << endl;
	cout << setw(54) << right << bingo2 << endl;
	cout << setw(54) << right << bingo3 << endl;
	cout << setw(54) << right << bingo4 << endl;
	cout << setw(54) << right << bingo5 << endl;
	cout << setw(54) << right << bingo6 << endl;

}
                                    

void fillvect()
{
	for (int i = 0; i < 25; i++)
	{
		a = RNG();
		while (duplicate(vect25, a))                      
		{
			a = RNG();
		}
		if (i < 12 || i > 12)
		{
			vect25[i] = a;
		}
		else if (i == 12)
		{
			vect25[i] = 111;
		}

	}

	PlaySound(TEXT("ShootingGallery.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	SetColor(11);
	bingologo();
	SetColor(7);
	Sleep(2000);
	system("cls");
}

void makeboard()
{
	cout << endl;
	cout << mpipe;
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
		cout << setw(7) << pipe;
	cout << mpipe;
	cout << endl; 
	cout << mpipe;

	int z = 0;

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			SetColor(7);

			if (z != 12)
			{
				if (i < 4)
				{
					cout << right << pipe << setw(8);
					SetColor(7);
					writecolor(z);
					cout << vect25[z];
					SetColor(7);
					cout << setw(8);
				}
				if (i == 4)
				{
					cout << right << pipe << setw(8);
					writecolor(z);
					cout << vect25[z];
					SetColor(7);
					cout << setw(7);
				}
				z++;
			}
			else
			{
				cout << right << pipe << setw(13);
				SetColor(c);
				cout << "Free  space";
				SetColor(7);
				cout << setw(3);
				z++;
			}
			
		}
		cout << pipe;
		cout << mpipe;
	}
}

void writecolor(int thing)
{
	switch (thing)
	{

	case 0:
		if (one == true)
	{
		SetColor(c);
	}
		break;
	case 1:
		if (two == true)
		{
			SetColor(c);
		}
		break;
	case 2:
		if (three == true)
		{
			SetColor(c);
		}
		break;
	case 3:
		if (four == true)
		{
			SetColor(c);
		}
		break;
	case 4:
		if (five == true)
		{
			SetColor(c);
		}
		break;
	case 5:
		if (six == true)
		{
			SetColor(c);
		}
		break;
	case 6:
		if (seven == true)
		{
			SetColor(c);
		}
		break;
	case 7:
		if (eight == true)
		{
			SetColor(c);
		}
		break;
	case 8:
		if (nine == true)
		{
			SetColor(c);
		}
		break;
	case 9:
		if (ten == true)
		{
			SetColor(c);
		}
		break;
	case 10:
		if (eleven == true)
		{
			SetColor(c);
		}
		break;
	case 11:
		if (twelve == true)
		{
			SetColor(c);
		}
		break;
	case 12:
		if (thirteen == true)
		{
			SetColor(c);
		}
		break;
	case 13:
		if (fourteen == true)
		{
			SetColor(c);
		}
		break;
	case 14:
		if (fifteen == true)
		{
			SetColor(c);
		}
		break;
	case 15:
		if (sixteen == true)
		{
			SetColor(c);
		}
		break;
	case 16:
		if (seventeen == true)
		{
			SetColor(c);
		}
		break;
	case 17:
		if (eighteen == true)
		{
			SetColor(c);
		}
		break;
	case 18:
		if (nineteen == true)
		{
			SetColor(c);
		}
		break;
	case 19:
		if (twenty == true)
		{
			SetColor(c);
		}
		break;
	case 20:
		if (twenty1 == true)
		{
			SetColor(c);
		}
		break;
	case 21:
		if (twenty2 == true)
		{
			SetColor(c);
		}
		break;
	case 22:
		if (twenty3 == true)
		{
			SetColor(c);
		}
		break;
	case 23:
		if (twenty4 == true)
		{
			SetColor(c);
		}
		break;
	case 24:
		if (twenty5 == true)
		{
			SetColor(c);
		}
		break;
	default: SetColor(7);
		break;


	}
}

//Making every variable start as false
void makegame()
{
	fillvect();
	fillpool();
	one = false;
	two = false;
	three = false;
	four = false;
	five = false;
	six = false;
	seven = false;
	eight = false;
	nine = false;
	ten = false;
	eleven = false;
	twelve = false;
	thirteen = true;
	fourteen = false;
	fifteen = false;
	sixteen = false;
	seventeen = false;
	eighteen = false;
	nineteen = false;
	twenty = false;
	twenty1 = false;
	twenty2 = false;
	twenty3 = false;
	twenty4 = false;
	twenty5 = false;

	for (int i = 0; i < 25; i++)
	{
		vectpara[i] = vect25[i];
	}
}

void evaluatepick(int spot)
{
	if (spot == 0)
	{
		one = true;
	}
	if (spot == 1)
	{
		two = true;
	}
	if (spot == 2)
	{
		three = true;
	}
	if (spot == 3)
	{
		four = true;
	}
	if (spot == 4)
	{
		five = true;
	}
	if (spot == 5)
	{
		six = true;
	}
	if (spot == 6)
	{
		seven = true;
	}
	if (spot == 7)
	{
		eight = true;
	}
	if (spot == 8)
	{
		nine = true;
	}
	if (spot == 9)
	{
		ten = true;
	}
	if (spot == 10)
	{
		eleven = true;
	}
	if (spot == 11)
	{
		twelve = true;
	}
	if (spot == 12)
	{
		thirteen = true;
	}
	if (spot == 13)
	{
		fourteen = true;
	}
	if (spot == 14)
	{
		fifteen = true;
	}
	if (spot == 15)
	{
		sixteen = true;
	}
	if (spot == 16)
	{
		seventeen = true;
	}
	if (spot == 17)
	{
		eighteen = true;
	}
	if (spot == 18)
	{
		nineteen = true;
	}
	if (spot == 19)
	{
		twenty = true;
	}
	if (spot == 20)
	{
		twenty1 = true;
	}
	if (spot == 21)
	{
		twenty2 = true;
	}
	if (spot == 22)
	{
		twenty3 = true;
	}
	if (spot == 23)
	{
		twenty4 = true;
	}
	if (spot == 24)
	{
		twenty5 = true;
	}
}

//check that the spot has not been taken
void checkpick(int pick)
{
	for (int i = 0; i < 25; i++)
	{
		if (vect25[i] == pick)
		{
			evaluatepick(i);
		}
	}
}

//Pick a random spot
bool dopick(vector<int> ballpool, int a)
{
	bool run2 = false;
	{
		if (ballpool[a] == -1)
		{
			run2 = true;
		}
	}
	return run2;
}

//If the check finds you win, play the winning screen and audio
void uWin()
{
	SetColor(10);
	bingologo();
	PlaySound(TEXT("Bingo.wav"), NULL, SND_ASYNC);
	Sleep(2000);
	SetColor(11);
	cout << setw(46) << "BINGO! You win!" << endl;
	cout << setw(39) << "It took " << rounds << " rounds." << endl;
	SetColor(7);
	makeboard();
	Sleep(2000);
}

//First year coding way of checking for every bingo solution.
void didYouWin()
{
	//1
	if (one == true && six == true && eleven == true && sixteen == true && twenty1 == true)
	{
		uWin();
		program = 0;
	}
	//2
	else if (two == true && seven == true && twelve == true && seventeen == true && twenty2 == true)
	{
		uWin();
		program = 0;
	}
	//3
	else if (three == true && eight == true && thirteen == true && eighteen == true && twenty3 == true)
	{
		uWin();
		program = 0;
	}
	//4
	else if (four == true && nine == true && fourteen== true && nineteen == true && twenty4 == true)
	{
		uWin();
		program = 0;
	}
	//5
	else if (five == true && ten == true && fifteen == true && twenty == true && twenty5 == true)
	{
		uWin();
		program = 0;
	}
	//6
	else if (one == true && two == true && three == true && four == true &&five == true)
	{
		uWin();
		program = 0;
	}
	//7
	else if (six == true && seven == true && eight == true && nine == true && ten == true)
	{
		uWin();
		program = 0;
	}
	//8
	else if (eleven == true && twelve == true && thirteen == true && fourteen == true && fifteen == true)
	{
		uWin();
		program = 0;
	}
	//9
	else if (sixteen == true && seventeen == true && eighteen == true && nineteen == true && twenty == true)
	{
		uWin();
		program = 0;
	}
	//10
	else if (twenty1 == true && twenty2 == true && twenty3 == true && twenty4 == true && twenty5 == true)
	{
		uWin();
		program = 0;
	}
	//11
	else if (five == true && nine == true && thirteen == true && seventeen == true && twenty1 == true)
	{
		uWin();
		program = 0;
	}
	//12
	else if (one == true && seven == true && thirteen == true && nineteen == true && twenty5 == true)
	{
		uWin();
		program = 0;
	}
	

}


void menu()
{
	while (program == 1)
	{
		rounds++;
			pick = RNG();
			while (dopick(ballpool, pick))
			{
				pick = RNG();
			}			
			
			cout << "Round: ";
			SetColor(12);
			cout << rounds;
			SetColor(7);
			cout << setw(35) << right << "Pick: ";
			SetColor(14);
			cout << pick << endl;
			SetColor(7);
			checkpick(pick);
			makeboard();
			ballpool[pick] = -1;
			system("pause");
			system("cls");
			didYouWin();

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

int main()
{
	SetWindow(80,20);
	srand(time(NULL));
	makegame();
	menu();
	system("pause");
	return 0;
}
