#include "MyGraphicLib4.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define _H 768
#define _W 1024

//bool type for handling conditions
#define bool char
#define true 1
#define false 0

#define FilenameLength 100

// save & load operation types
#define SAVE 2
#define LOAD 3

// define colors according to arrays
#define BLUE 0
#define GREEN 1
#define RED 2

//define copy modes
#define INPUT_TO_OUTPUT 1
#define OUTPUT_TO_INPUT 2

unsigned __int8 pixelBeffer1[_H][_W][3] ;
unsigned __int8 pixelBeffer2[_H][_W][3] = { 0 };

char Table();
bool SaveLoadFile(char);
void Copy(unsigned __int8,unsigned __int8,char,bool);
void AskForCopy();
void Mirror(unsigned __int8, unsigned __int8);
void MakeBlackAndWhite(unsigned __int8, unsigned __int8);
void MakeOld(unsigned __int8, unsigned __int8);
void MakeTransparent(unsigned __int8, unsigned __int8);
void Enhance(unsigned __int8, unsigned __int8);

int main()
{
	while (1)
	{
		system("cls"); //clear the screen
		switch (Table())
		{
		case 'l':
		case 'L':
		{
			if (SaveLoadFile(LOAD) == false)
				continue;
			break;
		}
		case 's':
		case 'S':
		{
			if (SaveLoadFile(SAVE) == false)
				continue;
			break;
		}
		case '1':
		{
			Copy(pixelBeffer1, pixelBeffer2, INPUT_TO_OUTPUT,true);
			break; 
		}
		case '2':
		{
			Copy(pixelBeffer1, pixelBeffer2, OUTPUT_TO_INPUT,true);
			break;
		}
		case 'a':
		case 'A':
		{
			Mirror(pixelBeffer1, pixelBeffer2);
			break;
		}
		case 'b':
		case 'B':
		{
			MakeBlackAndWhite(pixelBeffer1, pixelBeffer2);
			break;
		}
		case 'c':
		case 'C':
		{
			MakeOld(pixelBeffer1, pixelBeffer2);
			break;
		}
		case 'd':
		case 'D':
		{
			MakeTransparent(pixelBeffer1, pixelBeffer2);
			break;
		}
		case 'e':
		case 'E':
		{
			Enhance(pixelBeffer1, pixelBeffer2);
			break;
		}
		case 'x':
		case 'X':
			return 0;
		}
	}
	return 0;
}

char Table()
{
	char choice = '\0';
	printf("\tEnter one of the following options :\n_________________________________________\n\n L. Load bmp file in photo1\n");
	printf(" S. Save photo2 to a bmp file\n\n");
	printf(" 1. Copy photo 1 to photo 2\n");
	printf(" 2. Copy photo 2 to photo 1\n\n");
	printf(" A. Aks photo 1 Raa be surate AAyine tabdil kon va dar photo 2 begzar\n");
	printf(" B. Aks photo 1 Raa be surate siaho sefid tabdil kon va dar photo 2 begzar\n");
	printf(" C. Aks e photo 1 Raa be aks e ghadimi tabdil kon va dar photo 2 begzar\n");
	printf(" D. Aks photo1 raa vazeh kon va dar photo2 begzar\n");
	printf(" E. Keifiate noure aks photo1 raa behtar kon va dar photo2 begzar\n");
	printf("\n X. Az barname kharej sho ...");
	while (choice != 'l' && choice != 'L' && choice != 'S' && choice != 's' && choice != '1' && choice != '2' && choice != 'a' && choice != 'A' && choice != 'B' &&
			choice != 'b' && choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D' && choice != 'E' && choice != 'e' && choice != 'X' && choice != 'x')
		choice = _getch(); // ->choice = getch();
	system("cls"); //clear the screen
	return choice;
}

bool SaveLoadFile(char operationType) //operationType detemines the function must save or load the file
{
	char fn[FilenameLength] = { '\0' };//initial the array elements with '\0'
	int endOfString = 0;
	printf("Enter the path : ");
	gets_s(fn, FilenameLength); // -> scanf("%s",fn);
	if (fn[0] == '\0')
	{
		printf("Incorrect file name ...\n\tAny key for returning to table...");
		_getch();//getch();
		return false;
	}
	for (; fn[endOfString] != '\0'; endOfString++);
	endOfString--; //finds the last letter of the path
	if (endOfString <= 3 || fn[endOfString] != 'p' || fn[endOfString - 1] != 'm' || fn[endOfString - 2] != 'b' || fn[endOfString - 3] != '.')
	{
		fn[endOfString + 1] = '.';
		fn[endOfString + 2] = 'b';
		fn[endOfString + 3] = 'm';
		fn[endOfString + 4] = 'p'; //add .bmp to the end of the file name if the user has not entered it
		for (endOfString += 5; endOfString < FilenameLength; endOfString++)
			fn[endOfString] = '\0';//initial other chars of string with '\0'(null) char
	}
	bool result = operationType == SAVE ? SaveBitmap(fn,pixelBeffer2) : LoadBitmap(fn, pixelBeffer1);
	if (result == false)
		printf("\n\nAn error occured while %s ...\nAny key for returning to the table ...",operationType == SAVE ? "Saving" : "Loading");
	else
		printf("\n\n%s was successful ... Any key to continue ...", operationType == SAVE ? "Saving" : "Loading");
	_getch(); // ->getch();
	return result;
}

void Copy(unsigned __int8 input[_H][_W][3],unsigned __int8 output[_H][_W][3],char copyMode,bool clearScreen) 
//the clearScreen argument just determines that the function must clear the screen before typing or not  
{
	int i = 0;
	for (; i < _H; i++)
	{
		int j = 0;
		for (; j < _W; j++)
		{
			int k = 0;
			for (; k < 3; k++)
			{
				if (copyMode == INPUT_TO_OUTPUT)
					output[i][j][k] = input[i][j][k];
				else
					input[i][j][k] = output[i][j][k];
			}
		}
	}
	if (clearScreen == true)
		system("cls");
	printf("The operation was successful ...\nthe %s array copied to %s array\n\tAny key for returning to the table ...",
		copyMode == INPUT_TO_OUTPUT ? "input" : "output" ,copyMode == INPUT_TO_OUTPUT ? "output" : "input");
	_getch();//->getch();
	return;

}

void AskForCopy()
{
	printf("\n\nDo you want to perform the new actions on the new bitmap ?\n1)Yes, copy the photo2 to photo1\n2)No , dont't change photo1 ...");
	char choice = '\0';
	while (choice != '1' && choice != '2')
		choice = _getch(); //-> choice = getch();
	if (choice == '1')
	{
		printf("\n");
		Copy(pixelBeffer1, pixelBeffer2, OUTPUT_TO_INPUT,false);
	}
	else
	{
		printf("\n\tOK ... Any key for returning to the table ...");
		_getch(); //->getch();
	}
	return;
}

void Mirror(unsigned __int8 input[_H][_W][3], unsigned __int8 output[_H][_W][3])
{
	int h = 0;
	for (; h < _H; h++)
	{
		int w1 = 0, w2 = _W;
		for (; w1 < _W; w1++, w2--)
		{
			int i = 0;
			for(; i < 3; i++)
				output[h][w2][i] = input[h][w1][i];
		}
	}
	printf("\nThe Bitmap was successfully mirrored ...");
	AskForCopy();
	return;
}

void MakeBlackAndWhite(unsigned __int8 input[_H][_W][3], unsigned __int8 output[_H][_W][3])
{
	int h = 0;
	for (; h < _H; h++)
	{
		int w = 0;
		for (; w < _W; w++)
		{
			int i = 0;
			for (; i < 3; i++)
				output[h][w][i] = (input[h][w][0] + input[h][w][1] + input[h][w][2]) / 3;
		}
	}
	printf("\nThe Bitmap is now Black and White ...");
	AskForCopy();
	return;
}

void MakeOld(unsigned __int8 input[_H][_W][3], unsigned __int8 output[_H][_W][3])
{
	int h = 0;
	for (; h < _H; h++)
	{
		int w = 0;
		for (; w < _W; w++)
		{
				output[h][w][RED] = (input[h][w][0] + input[h][w][1] + input[h][w][2]) / 3;
				output[h][w][GREEN] = output[h][w][RED] * 0.9;
				output[h][w][BLUE] = output[h][w][GREEN];
		}
	}
	printf("\nThe Bitmap is now Old Black and White ...");
	AskForCopy();
	return;
}

void MakeTransparent(unsigned __int8 input[_H][_W][3], unsigned __int8 output[_H][_W][3])
{
	int h = 0;
	for (; h < _H; h++)
	{
		int w = 0;
		for (; w < _W; w += _W-1) //initial the pixels of first and last culomns in output array with the input array pixels
		{
			int i = 0;
			for (; i < 3; i++)
				output[h][w][i] = input[h][w][i];
		}
		for (w = 1; w < _W-1; w++)
		{
			int i = 0;
			for (; i < 3; i++)
			{
				if (h == 0 || h == _H - 1)
					output[h][w][i] = input[h][w][i];//initial the pixels of 1st and last rows in output array with the input array pixels
				else
				{
					const int M = -4 * input[h][w][i] + input[h - 1][w][i] + input[h + 1][w][i] + input[h][w - 1][i] + input[h][w + 1][i];
					output[h][w][i] = 255 * (input[h][w][i] - M + 57) / (314 + 57);
				}
			}
		}
	}
	printf("\nThe tranceparency of the bitmap increased...");
	AskForCopy();
	return;
}

void Enhance(unsigned __int8 input[_H][_W][3], unsigned __int8 output[_H][_W][3])
{
	unsigned __int8 min1, max1;
	min1 = max1 = input[0][0][0];
	{//here we find the min and max of informations
		int i = 0;
		for (; i < _H; i++)
		{
			int j = 0;
			for (; j < _W; j++)
			{
				int k = 0;
				for (; k < 3; k++)
				{
					if (min1 > input[i][j][k])
						min1 = input[i][j][k];
					if (max1 < input[i][j][k])
						max1 = input[i][j][k];

				}
			}
		}
	}
	int h = 0;
	const unsigned __int8 R = max1 - min1;
	for (; h < _H; h++)
	{
		int w = 0;
		for (; w < _W; w++)
		{
			int i = 0;
			for (; i < 3; i++)
				output[h][w][i] = 255 * (input[h][w][i] - min1) / R;
		}
	}
	printf("\nThe Bitmap enhanced ...");
	AskForCopy();
	return;
}