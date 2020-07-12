#include <iostream>
#include "game.h"
using namespace std;

int main()
{
    int choice;
    cout<<"1 player or 2 player.\n";
    cout<<"Enter no 1/2?";
    cin>>choice;
    cout<<endl;
    if(choice==1)
    {Game tictactoe;


    tictactoe.play();}
    else
    {
     Human tictactoe;
     tictactoe.play();
    }

    return 0;
}
