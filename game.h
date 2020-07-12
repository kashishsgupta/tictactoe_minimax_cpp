#include <iostream>
using namespace std;



struct Move
{
        int x;
        int y;
};

class Game
{
    const char human='X';
    const char ai='O';

    enum Player{HUMAN,AI};
    char board[3][3];
    int depth;
    bool isMax;
    int level;
public:
    Game();

    void printBoard();//prints board

    bool gameOver();//returns true if winner has been found or no empty spaces

    bool checkWin(Player player);//checks for win

    void play();//primary game driver, loops turn by turn until a winner

    void getHumanMove();//input in coordinates

    int score();//human 10, ai -10, draw 0

    //Move minimax(char AIboard[3][3]);//returns best ai move

    //int minSearch(char AIboard[3][3]);//minimax helper func, chooses move with least possible score

    //int maxSearch(char AIboard[3][3]);//minimax helper func, choose move with max possible score

    int minimax(char AIboard[3][3], int depth, bool isMax,int alpha,int beta,int level);

    Move findBestMove(char AIboard[3][3],int level);

    bool isMoveLeft();


};

class Human
{
    const char human_1='X';
    const char human_2='O';

    enum Player{HUMAN_1,HUMAN_2};
    char board[3][3];
    int depth;
    bool isMax;

public:
    Human();
    void printBoard();
    bool gameOver();
    bool checkWin(Player player);
    void playGame();
    void getHuman_1Move();
    void getHuman_2Move();
    int score();
    void play();
    int minimax(char HUMANboard[3][3],int depth,bool isMax,int alpha,int beta);
    Move findBestMoveHuman_1(char HUMANboard[3][3]);
    Move findBestMoveHuman_2(char HUMANboard[3][3]);
    bool isMoveLeft();


};
