#include <iostream>
#include <sstream>//string stream
#include <iomanip>//parametric manipulators
#include "game.h"
#include <bits/stdc++.h>
using namespace std;

Human::Human()
{
   /*board[3][3]={
       {'O','X','O'},
        {'X','X','O'},
        {'-','-','-'}
                };*/
    board[0][0]='-';
    board[0][1]='-';
    board[0][2]='-';
    board[1][0]='-';
    board[1][1]='-';
    board[1][2]='-';
    board[2][0]='-';
    board[2][1]='-';
    board[2][2]='-';

}

void Human::printBoard()
{
    cout<<"---------------------";
    for(int i=0;i<3;i++)
    {
        cout<<'\n'<<"|";
        for(int j=0;j<3;j++)
        {
            cout<<setw(3)<<board[i][j]<<setw(3)<<"|";
        }
    }
    cout<<'\n'<<"---------------------"<<'\n';
}

bool Human::gameOver()
{
    if(checkWin(HUMAN_1)) return true;
	else if(checkWin(HUMAN_2)) return true;

    /*bool emptySpace = false;
    for(int i = 0; i < 3; i++) {
		if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;*/
	bool emptySpace=isMoveLeft();
	return !emptySpace;
}

bool Human::isMoveLeft()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]=='-')
                return true;

        }
    }
    return false;
}

bool Human::checkWin(Player player)
{
    char playerChar;
    if(player==HUMAN_1) playerChar=human_1;
    else playerChar=human_2;

    for(int i = 0; i < 3; i++) {
		// Check horizontals
		if(board[i][0] == playerChar && board[i][1] == playerChar
			&& board[i][2] == playerChar)
			return true;

		// Check verticals
		if(board[0][i] == playerChar && board[1][i] == playerChar
			&& board[2][i] == playerChar)
			return true;
	}

	// Check diagonals
	if (board[0][0] == playerChar && board[1][1] == playerChar
		&& board[2][2] == playerChar) {
		return true;
	} else if (board[0][2] == playerChar && board[1][1] == playerChar
		&& board[2][0] == playerChar) {
		return true;
	}
	return false;


}

int Human::score()
{
    if(checkWin(HUMAN_1)) { return 10; }
	else if(checkWin(HUMAN_2)) { return -10; }
	return 0; // draw

}


int Human::minimax(char HUMANboard[3][3], int depth,bool isMax,int alpha,int beta)
{
    //cout<<"into minimax depth-"<<depth<<" isMax="<<isMax<<"\n";
    int flag=0;

    //maximizer won
    if(score()==10)
        return 10-depth;
    //minimizer won
    if(score()==-10)
        return -10+depth;
    //tie
    if(isMoveLeft()==false)
        return 0;

    //maximizer move
    if(isMax)
    {
        int best=-1000;
        //traverse all cells
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                //cout<<"in isMax=true  i="<<i<<" j="<<j<<"\n";
                //check if cell is empty
                if(HUMANboard[i][j]=='-')
                {
                    //make the move
                    HUMANboard[i][j]=human_1;
                    //printBoard();

                    //call minimax recursively
                    //choose max value
                    best=max(best, minimax(board,depth+1,!isMax,alpha,beta));
                    alpha=max(alpha,best);
                    //cout<<"in isMax=true depth="<<depth<<"  best="<<best<<" alpha="<<alpha<<" beta="<<beta<<"\n";

                    if(beta<=alpha)
                        {
                            //cout<<"beta<=alpha\n";

                            flag=1;
                            HUMANboard[i][j]='-';
                            break;
                        }

                    //undo the move
                       HUMANboard[i][j]='-';
                }

            }

            if(flag==1) break;
        }
        //cout<<"in isMax=true best returned="<<best<<"\n";
        //printBoard();
        return best;

    }

    //minimizer move
    else
    {
        int best=1000;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                 //cout<<"in isMax=false  i="<<i<<" j="<<j<<"\n";
                //check if cell is empty
                if(HUMANboard[i][j]=='-')
                {
                    //make the move
                    HUMANboard[i][j]=human_2;

                    //call minimax recursively
                    //choose min value
                    best=min(best,minimax(board,depth+1,!isMax,alpha,beta));
                    beta=min(beta,best);
                    //cout<<"in isMax=false depth="<<depth<<" best="<<best<<" beta="<<beta<<" alpha="<<alpha<<"\n";

                    if(beta<=alpha)
                    {
                        //cout<<"beta<=alpha\n";

                        flag=1;
                        HUMANboard[i][j]='-';
                        break;
                    }
                    //undo the move
                      HUMANboard[i][j]='-';
                }
            }

            if(flag==1) break;
        }
         //cout<<"in isMax=true  best returned="<<best<<"\n";
         //printBoard();
        return best;
    }

}


Move Human::findBestMoveHuman_1(char HUMANboard[3][3])
{
    //cout<<"findBestMove\n";
    int bestVal=1000;
    Move bestMove;

    //traverse all cells
    //evaluate minimax for all empty cell
    //return cell with optimal value

    for(int i=0;i<3;i++)
    {
        //cout<<"findBestMove i="<<i<<"\n";
        for(int j=0;j<3;j++)
        {
             int alpha=-1000;
             int beta=1000;
            //cout<<"findBestMove j="<<j<<"\n";
            //check if cell is empty
            if(HUMANboard[i][j]=='-')
            {
                //make the move
                HUMANboard[i][j]=human_1;
                //printBoard();
                //compute evaluation func for this move
                int moveVal=minimax(HUMANboard,0,false,alpha,beta);
                //undo the move
                HUMANboard[i][j]='-';
                //printBoard();
                //if value of current move is
                //more than best value
                //update best move
                if(moveVal<bestVal)
                {
                    bestMove.x=i;
                    bestMove.y=j;
                    bestVal=moveVal;
                }
            }

        }
    }

    cout<<"the value of the best move is "<<bestVal<<endl;

    return bestMove;

}


Move Human::findBestMoveHuman_2(char HUMANboard[3][3])
{
    //cout<<"findBestMove\n";
    int bestVal=1000;
    Move bestMove;

    //traverse all cells
    //evaluate minimax for all empty cell
    //return cell with optimal value

    for(int i=0;i<3;i++)
    {
        //cout<<"findBestMove i="<<i<<"\n";
        for(int j=0;j<3;j++)
        {
             int alpha=-1000;
             int beta=1000;
            //cout<<"findBestMove j="<<j<<"\n";
            //check if cell is empty
            if(HUMANboard[i][j]=='-')
            {
                //make the move
                HUMANboard[i][j]=human_2;
                //printBoard();
                //compute evaluation func for this move
                int moveVal=minimax(HUMANboard,0,true,alpha,beta);
                //undo the move
                HUMANboard[i][j]='-';
                //printBoard();
                //if value of current move is
                //more than best value
                //update best move
                if(moveVal<bestVal)
                {
                    bestMove.x=i;
                    bestMove.y=j;
                    bestVal=moveVal;
                }
            }

        }
    }

    cout<<"the value of the best move is "<<bestVal<<endl;

    return bestMove;

}

void Human::getHuman_1Move()
{
    int x;
    int y;
		cout << "Human1 enter your move in coordinate form, ex: (1,3)." << endl;
		cout << "Your Move: ";
		cin>>x>>y;
		x=x-1;
		y=y-1;
        if(x<0 || x>2 || y<0 || y>2)
        {
            cout<<"invalid move\n";
            getHuman_1Move();
        }
        if(board[x][y]==human_1 || board[x][y]==human_2)
        {
            cout<<"invalid move\n";
            getHuman_1Move();
        }
	board[x][y] = human_1;
}
void Human::getHuman_2Move()
{
    int x;
    int y;
		cout << "Human2 enter your move in coordinate form, ex: (1,3)." << endl;
		cout << "Your Move: ";
		cin>>x>>y;
		x=x-1;
		y=y-1;
        if(x<0 || x>2 || y<0 || y>2)
        {
            cout<<"invalid move\n";
            getHuman_2Move();
        }
        if(board[x][y]==human_1 || board[x][y]==human_2)
        {
            cout<<"invalid move\n";
            getHuman_2Move();
        }
	board[x][y] = human_2;
}



void Human::play()
{
    int turn=0;
    printBoard();
    while(!checkWin(HUMAN_1) && !checkWin(HUMAN_2) && !gameOver())
    {
        //cout<<"TURN= "<<turn<<"\n";
        //human move
        if(turn==0)
        {
            cout<<"Human1 Player Move"<<endl;
            getHuman_1Move();
            if(checkWin(HUMAN_1))
                cout<<"Human1 Player Wins"<<endl;
            turn++;
            printBoard();
        }
        else if(turn%2==0 && turn!=0)
        {
            cout<<"Human1 Player Move"<<endl;
            Move HUMAN_1move=findBestMoveHuman_1(board);
            cout<<"best human1 move is"<<HUMAN_1move.x+1<<" "<<HUMAN_1move.y+1<<endl;
            getHuman_1Move();
            if(checkWin(HUMAN_1))
                cout<<"Human1 Player Wins"<<endl;
            turn++;
            printBoard();
        }
        else if(turn%2!=0)
        {
            cout<<endl<<"Human2 Player Move"<<endl;
            Move HUMAN_2move=findBestMoveHuman_2(board);
            //Move AImove=minimax(board);
            cout<<"best human2 move is"<<HUMAN_2move.x+1<<" "<<HUMAN_2move.y+1<<endl;
            getHuman_2Move();
            if(checkWin(HUMAN_2))
                cout<<"Human2 Player Wins"<<endl;
            turn++;
            printBoard();
        }
    }
}




