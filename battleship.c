#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define boardSize 10

void displayPlayground(int gameArray[boardSize][boardSize]) {
	for (int mn = 0; mn < boardSize; mn++) {
		for (int mni = 0; mni < boardSize; mni++) {
			printf(" %d  ", gameArray[mni][mn]);
		}
		printf("\n");
	}

	int y_sign = 65;
	printf_s("\n--------------------------------------------------------------------");
	printf_s("\n|     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |");
	printf_s("\n--------------------------------------------------------------------");

	for (int j = 0; j < 10; j++)
	{
		printf_s("\n|  %c  |", y_sign++);
		for (int i = 0; i < 10; i++)
		{
			if (gameArray[i][j] == 93)
			{
				printf_s("     |");
			}
			/*else if (gameArray[i][j] > 10 && gameArray[i][j] < 50) //wyswietla polozenie statkow na planszy uzytkownika
			{
				printf_s("  f  |");

			}*/
			else if (gameArray[i][j] > 100 && gameArray[i][j] < 150)
			{
				printf_s("  X  |");

			}
			/*else if (gameArray[i][j] == 5)
			{
				printf_s("  X  |");

			}*/
			else if (gameArray[i][j] == 6)
			{
				printf_s("  S  |");

			}
			else if (gameArray[i][j] == 99)
			{
				printf_s("  *  |");

			}
			else if (gameArray[i][j] == 98)
			{
				printf_s("  c  |");

			}
			else
			{
				printf_s("     |");
			}
		}
		printf_s("\n--------------------------------------------------------------------");
	}
}

int shipGenerator(int lengthOfShip, int gameArray[boardSize][boardSize], int counter) {
	int temporaryShipCells[4][2];
	int startingCell[2] = { ((double)rand() / RAND_MAX) * (boardSize), ((double)rand() / RAND_MAX) * (boardSize)}; // x- and y-coordinate of start point of ship
	//int directionOfShips = (int)(((double)rand() / RAND_MAX) * (boardSize)) % 2; // 0 - downward, 1 - rightward from startingCell
	int shipIsSet = 0;
	int shipCollision = 0;
	int directionOfShip;
	int imageOfSurrouding = 93;

	for (directionOfShip = 0; directionOfShip < 4; directionOfShip++) {
		directionOfShip = (int)(((double)rand() / RAND_MAX) * (boardSize)) % 4;
		if (directionOfShip == 0 && shipIsSet == 0) { //dol
			if (!(startingCell[1] >= boardSize - lengthOfShip)) {
				for (int i = 0; i < lengthOfShip; i++) {
					temporaryShipCells[i][0] = startingCell[0];
					temporaryShipCells[i][1] = startingCell[1] + i;
				}
				shipIsSet = 1;
				break;
			}
		}
		if (directionOfShip == 1 && shipIsSet == 0) { //prawo
			if (!(startingCell[0] >= boardSize - lengthOfShip)) {
				for (int i = 0; i < lengthOfShip; i++) {
					temporaryShipCells[i][0] = startingCell[0] + i;
					temporaryShipCells[i][1] = startingCell[1];
				}
				shipIsSet = 1;
				break;
			}
		}
		if (directionOfShip == 2 && shipIsSet == 0) { //gora
			if (!(startingCell[1] <= lengthOfShip)) {
				for (int i = 0; i < lengthOfShip; i++) {
					temporaryShipCells[i][0] = startingCell[0];
					temporaryShipCells[i][1] = startingCell[1] - i;
				}
				shipIsSet = 1;
				break;
			}
		}
		if (directionOfShip == 3 && shipIsSet == 0) { //lewo
			if (!(startingCell[0] <= lengthOfShip)) {
				for (int i = 0; i < lengthOfShip; i++) {
					temporaryShipCells[i][0] = startingCell[0] - i;
					temporaryShipCells[i][1] = startingCell[1];
				}
				shipIsSet = 1;
				break;
			}
		}
	}

	if (shipIsSet) {
		for (int k = 0; k < lengthOfShip; k++) {
			int x = temporaryShipCells[k][0];
			int y = temporaryShipCells[k][1];
			int gameArrayCell = gameArray[x][y];
			if ((gameArrayCell >= 11 && gameArrayCell <= 50) || gameArrayCell == imageOfSurrouding) {
				shipCollision = 1;
			}
		}
	}

	if (!shipCollision && shipIsSet) {
		for (int k = 0; k < lengthOfShip; k++) {
			int X = temporaryShipCells[k][0];
			int Y = temporaryShipCells[k][1];
			if (directionOfShip == 1 || directionOfShip == 3) {
				if (Y < boardSize - 1) {
					gameArray[X][Y + 1] = imageOfSurrouding;
				}
				if (Y > 0) {
					gameArray[X][Y - 1] = imageOfSurrouding;
				}
			}
			else {
				if (X < boardSize - 1) {
					gameArray[X + 1][Y] = imageOfSurrouding;
				}
				if (X > 0) {
					gameArray[X - 1][Y] = imageOfSurrouding;
				}
			}

			if (directionOfShip == 0) {
				if (temporaryShipCells[0][1] > 0) {
					gameArray[temporaryShipCells[0][0]][temporaryShipCells[0][1] - 1] = imageOfSurrouding;
				}
				if (temporaryShipCells[lengthOfShip - 1][1] < boardSize - 1) {
					gameArray[temporaryShipCells[lengthOfShip - 1][0]][temporaryShipCells[lengthOfShip - 1][1] + 1] = imageOfSurrouding;
				}
			}
			else if (directionOfShip == 2) {
				if (temporaryShipCells[0][1] < boardSize - 1) {
					gameArray[temporaryShipCells[0][0]][temporaryShipCells[0][1] + 1] = imageOfSurrouding;
				}
				if (temporaryShipCells[lengthOfShip - 1][1] > 0) {
					gameArray[temporaryShipCells[lengthOfShip - 1][0]][temporaryShipCells[lengthOfShip - 1][1] - 1] = imageOfSurrouding;
				}				
			}
			else if (directionOfShip == 1) {
				if (temporaryShipCells[0][0] > 0) {
					gameArray[temporaryShipCells[0][0] - 1][temporaryShipCells[0][1]] = imageOfSurrouding;
				}
				if (temporaryShipCells[lengthOfShip - 1][0] < boardSize - 1) {
					gameArray[temporaryShipCells[lengthOfShip - 1][0] + 1][temporaryShipCells[0][1]] = imageOfSurrouding;
				}
			}
			else
			{
				if (temporaryShipCells[0][0] < boardSize - 1) {
					gameArray[temporaryShipCells[0][0] + 1][temporaryShipCells[0][1]] = imageOfSurrouding;
				}
				if (temporaryShipCells[lengthOfShip - 1][0] > 0) {
					gameArray[temporaryShipCells[lengthOfShip - 1][0] - 1][temporaryShipCells[0][1]] = imageOfSurrouding;
				}
			}

			switch (lengthOfShip)
			{
			case 1:
				gameArray[X][Y] = 10+counter;
				break;
			case 2:
				gameArray[X][Y] = 20+counter+k;
				break;
			case 3:
				gameArray[X][Y] = 30+counter+k;
				break;
			case 4:
				gameArray[X][Y] = 40+counter+k;
				break;
			default:
				break;
			}

		}
	}
	else {
		return 0;
	}
	return 1;
	
}

void shipsGenerator(int gameArray[boardSize][boardSize]) {
	int typeAndNumberOfShips[4] = { 4,3,2,1 }; //jedno-, dwu-, trzy-, czteromasztowe
	srand(time(NULL));

	for (int mn = 0; mn < boardSize; mn++) {
		for (int mni = 0; mni < boardSize; mni++) {
			gameArray[mn][mni] = 94;
		}
	}

	for (int j = 3; j >= 0; j--) {
		for (int i = 1; i <= typeAndNumberOfShips[j]; i++) {
			while (!shipGenerator(j + 1, gameArray,i)) {}
		}
	}
}

void sunkenShip(int X, int Y, int lengthOfShip, int arrayOfShips[boardSize][boardSize]) {
	int howMany = 0;
	for (int i = X - lengthOfShip + 1; i <= X + lengthOfShip - 1; i++)
	{
		for (int j = Y - lengthOfShip + 1; j <= Y + lengthOfShip - 1; j++)
		{
			if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
			{
				if (arrayOfShips[i][j]/10 == (lengthOfShip*10+100)/10 && arrayOfShips[X][Y] / 10 == (lengthOfShip * 10 + 100) / 10)
				{
					//arrayOfShips[i][j] = 6;
					howMany++;
				}
			}
		}
	}
	if (howMany == lengthOfShip) {
		for (int i = X - lengthOfShip + 1; i <= X + lengthOfShip - 1; i++)
		{
			for (int j = Y - lengthOfShip + 1; j <= Y + lengthOfShip - 1; j++)
			{
				if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
				{
					//if (arrayOfShips[i][j] == 5 && ((arrayOfShips[i][j]/10) == lengthOfShip))
					if (arrayOfShips[i][j] / 10 == (lengthOfShip * 10 + 100) / 10) //&& arrayOfShips[X][Y] / 10 == (lengthOfShip * 10 + 100) / 10)
					{
						arrayOfShips[i][j] = 6;
					}
				}
			}
		}
	}
}

int userInputCheck(int X, char Y) {
	
	if ((X > 0 && X < 11) && (((int)Y >= 65 && (int(Y) <=74)) || ((int)Y >= 97 && ((int)Y <= 106)))) {
		return 1;
	}
	return 0;
}

int userShot(int X,int Y,int arrayOfShips[boardSize][boardSize],int hintOfShipPlace) {
	if (Y >= 97) {
		Y -= 97;
	}
	else {
		Y -= 65;
	}
	int shot = arrayOfShips[X-1][Y];
	if (shot >= 10 && shot <= 50) {
		arrayOfShips[X - 1][Y] = shot+100;
		sunkenShip(X - 1, Y, shot / 10, arrayOfShips);
		printf("Trafiles statek\n");
		return 1;
	} else if (shot == 93) {
		if (hintOfShipPlace == 1) {
			arrayOfShips[X - 1][Y] = 98;
			printf("Jestes blisko\n");
		}
		else {
			arrayOfShips[X - 1][Y] = 99;
		}
	}
	else if (shot == 94) {
		arrayOfShips[X - 1][Y] = 99;
		printf("Pudlo\n");
	}
	return 0;
}

void clearScreen()
{
	system("@cls||clear");
}

void startGame() {
	int arrayOfGeneratedShips[boardSize][boardSize];
	printf("\tGra w statki\t\n");
	char inputChar;
	int hints = 0;
	printf("Wcisinij s zeby zaczac: ");
	while (scanf_s(" %c", &inputChar, 1) == 1 && (int)inputChar != 115) {
		printf("\nWprowadzono zly znak");
		printf("\nWcisinij s zeby zaczac: ");
	}
	printf("Chcesz podpowiedzi? (1 - tak, 0 - nie): ");
	scanf_s("%d", &hints);
	shipsGenerator(arrayOfGeneratedShips);

	int inputCoordinateX;
	char inputCoordinateY;
	int counterOfShots = 0;
	int counterOfHits = 0;
	
	while (1) {

		displayPlayground(arrayOfGeneratedShips);
		printf("\nX - strzal\nS - caly statek utonal\n* - pudlo");

		if (hints) {
			printf("\nc - jestes blisko");
		}

		printf("\nLiczba strzalow: %d", counterOfShots);
		printf("\nLiczba trafien: %d", counterOfHits);
		printf("\nPodaj wspolrzedne strzalu: ");
		scanf_s(" %c", &inputCoordinateY, 1);
		scanf_s("%d", &inputCoordinateX);
		clearScreen();

		if (userInputCheck(inputCoordinateX, inputCoordinateY)) {
			printf("\nWprowadzono dobre wspolrzedne \n");
			counterOfHits += userShot(inputCoordinateX, inputCoordinateY, arrayOfGeneratedShips, hints);
		}
		else {
			printf("\nWprowadzono zle wspolrzedne \n");
		}

		inputCoordinateX = 0;
		inputCoordinateY = 0;
		counterOfShots++;

		if (counterOfShots > 100 || counterOfHits == 20) {
			break;
		}
	}
	clearScreen();
	displayPlayground(arrayOfGeneratedShips);
	printf("\nKoniec\n");
	system("pause");
}

int main() {
	startGame();
	return 0;
}