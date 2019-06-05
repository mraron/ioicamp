#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NemJo           0
#define Jo              1
#define Szurke          2
#define Feher           3
#define true 1
#define false 0

typedef int Allas[4];

static int Init = true;
static char kor[4][3];
static int LastMove;
static Allas A;

static void Lep(int *a, int i, int *aa)
{
	int j;
	int kavics;
	for (j = 0; j <= 3; j++)
		aa[j] = a[j];
	aa[i - 1] = 0;
	kavics = a[i - 1] - 1;
	if (kavics == 0)
		return;
	j = 0;
	do {
		aa[kor[i - 1][j]]++;
		kavics--;
		j = (j + 1) % 3;
	} while (kavics != 0);
}  /*Lep*/

static void EndGame(int pont, char* msg)
{
	printf("%s\n", msg);
	exit(0);
}

static void Start(void)
{
	int i, x, z;
	z = 0;

	for (i = 0; i <= 3; i++) {
		scanf("%d", &x);
		A[i] = x;
		z = z + x;
	}

	kor[0][0] = 1; kor[0][1] = 2; kor[0][2] = 3;
	kor[1][0] = 2; kor[1][1] = 3; kor[1][2] = 0;
	kor[2][0] = 3; kor[2][1] = 0; kor[2][2] = 1;
	kor[3][0] = 0; kor[3][1] = 1; kor[3][2] = 2;
	Init = false;
}  /*Start*/

int YourMove()
{
	if (Init)
		Start();
	return LastMove;
}  /*YourMove*/

void MyMove(int i)
{
	Allas AA, A3, A4;
	int L3 = false;
	if (Init)
		Start();

	if (i < 1 || i > 2)
		EndGame(0, "hiba, érvénytelen paraméter MyMove-ban");   /*illegal move*/

	if (A[i - 1] == 0)
		EndGame(0, "hiba, érvénytelen paraméter MyMove-ban");   /*illegal move*/
	Lep(A, i, AA);
	memcpy(A, AA, sizeof(Allas));

	if (A[2] + A[3] == 0)
		EndGame(1, "helyes");
	if (A[2] > 0) {
		Lep(A, 3, A3);
		L3 = true;
	}
	else {
		Lep(A, 4, A4);
	}
	if (L3) {
		memcpy(A, A3, sizeof(Allas));
		LastMove = 3;
		if (A[0] + A[1] == 0)
			EndGame(0, "hiba, vesztettél");
		return;
	}
	memcpy(A, A4, sizeof(Allas));
	LastMove = 4;
	if (A[0] + A[1] == 0)
		EndGame(0, "hiba, vesztettél");
}  /*MyMove*/

int Pit(int i)
{
	int Result;

	if (Init)
		Start();
	if (i < 1 || i > 4) {
		EndGame(0, "hiba, érvénytelen paraméter Pit-ben");
	}
	Result = A[i - 1];
	return Result;
}  /*Pit*/
