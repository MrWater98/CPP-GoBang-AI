#ifndef ZOBRIST_H
#define ZOBRIST_H
#include<unordered_map>
using namespace std;
class Zobrist
{
    public:
        Zobrist();
        virtual ~Zobrist();
        unsigned long long int ZobristTable[15][15][2];
        // Generates a Randome number from 0 to 2^64-1
        unsigned long long int randomInt();
        // This function associates each piece with a number
        int indexOf(char piece);
        // Computes the hash value of a given board
        unsigned long long int computeHash(char board[15][15]);

        unordered_map<string,float> hashTable;
    protected:

    private:
};

#endif // ZOBRIST_H
