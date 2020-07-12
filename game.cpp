#include <iostream>
#include <sstream>//string stream
#include <iomanip>//parametric manipulators
#include "game.h"
#include <bits/stdc++.h>
using namespace std;

Game::Game()
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

void Game::printBoard()
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

bool Game::gameOver()
{
    if(checkWin(HUMAN)) return true;
	else if(checkWin(AI)) return true;

    /*bool emptySpace = false;
    for(int i = 0; i < 3; i++) {
		if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;*/
	bool emptySpace=isMoveLeft();
	return !emptySpace;
}

bool Game::isMoveLeft()
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


bool Game::checkWin(Player player)
{
    char playerChar;
    if(player==HUMAN) playerChar=human;
    else playerChar=ai;

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

int Game::score()
{
    if(checkWin(HUMAN)) { return 10; }
	else if(checkWin(AI)) { return -10; }
	return 0; // draw

}

/*Move Game::minimax(char AIboard[3][3])
{
    cout<<"in minimax\n";
    int bestMoveScore=100;//-100 is arbitrary
    Move bestMove;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(AIboard[i][j]=='-')
            {
                AIboard[i][j]=ai;
                int tempMoveScore=maxSearch(AIboard);
                if(tempMoveScore<=bestMoveScore)
                {
                    bestMoveScore=tempMoveScore;
                    bestMove.x=i;
                    bestMove.y=j;
                }
                AIboard[i][j]='-';

            }

        }
    }
    return bestMove;



}

int Game::maxSearch(char AIboard[3][3])
{
    cout<<"in maxsearch\n";
    if(gameOver()) return score();
    Move bestMove;

    int bestmoveScore=-1000;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(AIboard[i][j]=='-')
            {
                AIboard[i][j]=human;
                int tempMoveScore=minSearch(AIboard);
                if(tempMoveScore>=bestmoveScore)
                {
                    bestmoveScore=tempMoveScore;
                    bestMove.x=i;
                    bestMove.y=j;
                }
                AIboard[i][j]='-';
            }
        }
    }
    return bestmoveScore;
}

int Game::minSearch(char AIboard[3][3])
{
    cout<<"in minsearch\n";
    if(gameOver()) return score();
    Move bestMove;

    int bestMoveScore=1000;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(AIboard[i][j]=='-')
            {
                AIboard[i][j]=ai;
                int tempMoveScore=maxSearch(AIboard);
                if(tempMoveScore<=bestMoveScore)
                {
                    bestMoveScore=tempMoveScore;
                    bestMove.x=i;
                    bestMove.y=j;
                }
                AIboard[i][j]='-';
            }
        }
    }
    return bestMoveScore;
}*/

int Game::minimax(char AIboard[3][3], int depth,bool isMax,int alpha,int beta,int level)
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
    if(level==1)
    {
        if(depth==3)
        {
            int x=score();
            return x;
        }
    }


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
                if(AIboard[i][j]=='-')
                {
                    //make the move
                    AIboard[i][j]=human;
                    //printBoard();

                    //call minimax recursively
                    //choose max value
                    best=max(best, minimax(board,depth+1,!isMax,alpha,beta,level));
                    alpha=max(alpha,best);
                    //cout<<"in isMax=true depth="<<depth<<"  best="<<best<<" alpha="<<alpha<<" beta="<<beta<<"\n";

                    if(beta<=alpha)
                        {
                            //cout<<"beta<=alpha\n";

                            flag=1;
                             AIboard[i][j]='-';
                            break;
                        }

                    //undo the move
                       AIboard[i][j]='-';
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
                if(AIboard[i][j]=='-')
                {
                    //make the move
                    AIboard[i][j]=ai;

                    //call minimax recursively
                    //choose min value
                    best=min(best,minimax(board,depth+1,!isMax,alpha,beta,level));
                    beta=min(beta,best);
                    //cout<<"in isMax=false depth="<<depth<<" best="<<best<<" beta="<<beta<<" alpha="<<alpha<<"\n";

                    if(beta<=alpha)
                    {
                        //cout<<"beta<=alpha\n";

                        flag=1;
                         AIboard[i][j]='-';
                        break;
                    }
                    //undo the move
                      AIboard[i][j]='-';
                }
            }

            if(flag==1) break;
        }
         //cout<<"in isMax=true  best returned="<<best<<"\n";
         //printBoard();
        return best;
    }

}

Move Game::findBestMove(char AIboard[3][3],int level)
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
            if(AIboard[i][j]=='-')
            {
                //make the move
                AIboard[i][j]=ai;
                //printBoard();
                //compute evaluation func for this move
                int moveVal=minimax(AIboard,0,true,alpha,beta,level);
                //undo the move
                AIboard[i][j]='-';
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

void Game::getHumanMove()
{
    int x;
    int y;
		cout << "Enter your move in coordinate form, ex: (1,3)." << endl;
		cout << "Your Move: ";
		cin>>x>>y;
		x=x-1;
		y=y-1;
        if(x<0 || x>2 || y<0 || y>2)
        {
            cout<<"invalid move\n";
            getHumanMove();
        }
        if(board[x][y]==human || board[x][y]==ai)
        {
            cout<<"invalid move\n";
            getHumanMove();
        }
	board[x][y] = human;
}



void Game::play()
{
    int turn=0;
    printBoard();
    cout<<"Enter difficulty level";
    cin>>level;
    while(!checkWin(HUMAN) && !checkWin(AI) && !gameOver())
    {
        cout<<"TURN= "<<turn<<"\n";
        //human move
        if(turn%2==0)
        {
            getHumanMove();
            if(checkWin(HUMAN))
                cout<<"Human Player Wins"<<endl;
            turn++;
            printBoard();
        }
        else
        {
            cout<<endl<<"Computer Player Move"<<endl;
            Move AImove=findBestMove(board,level);
            //Move AImove=minimax(board);
            board[AImove.x][AImove.y]=ai;
            if(checkWin(AI))
                cout<<"Computer Player Wins"<<endl;
            turn++;
            printBoard();
        }
    }
}

