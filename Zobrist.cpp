#include "Zobrist.h"
#include <bits/stdc++.h>
using namespace std;
Zobrist::Zobrist()
{
    // Initializes the table
    for (int i = 0; i<15; i++)
	for (int j = 0; j<15; j++)
		for (int k = 0; k<2; k++)
		ZobristTable[i][j][k] = randomInt();
    //ctor
}

Zobrist::~Zobrist()
{
    //dtor
}
mt19937 mt(01234567);
unsigned long long int Zobrist::randomInt()
{
    uniform_int_distribution<unsigned long long int>
								dist(0, UINT64_MAX);
	return dist(mt);
}
int Zobrist::indexOf(char piece)
{
    if (piece=='x')
		return 0;
	if (piece=='o')
		return 1;
	else
		return -1;
}
unsigned long long int Zobrist::computeHash(char board[15][15])
{
    unsigned long long int h = 0;
	for (int i = 0; i<15; i++)
	{
		for (int j = 0; j<15; j++)
		{
			if (board[i][j]!='.')
			{
				int piece = indexOf(board[i][j]);
				h ^= ZobristTable[i][j][piece];
			}
		}
	}
	return h;
}
