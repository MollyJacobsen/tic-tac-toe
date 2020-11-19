/*	
* Author: Molly Jacobsen
* Date: February 11th
*
* main.cpp
*
* Objective: to run a game of tic tac toe by calling functions from functions.cpp
*/

#include <iostream>

using namespace std;


/*
* Functions included in "functions.cpp"
*
* void greetAndInstruct(){;}
* void displayBoard(char board[]){;}
* bool checkIfLegal(int cellNbre, char board[]){return(true);}
* bool checkWinner(char board[]){return(true);}
* void computerMove(char board[]){;}
*/

#include "functions.cpp"

char myBoard[27];

int main (){
	
	// Set blank board 
	for(int i=0;i<27;i++) myBoard[i]=' ';

	greetAndInstruct();
	displayBoard(myBoard);

	// Set up variables
	bool userTurn= true;
	int symbols= 0;
	int cell;

	char winner;
	bool tie= true;

	while(symbols<27){
		if(userTurn){
			cout<<"Where would you like to place your X?"<<endl;
			cin>>cell;
			if(checkIfLegal(cell, myBoard)){
				myBoard[cell-1]= 'X';
				symbols++;
				userTurn= false;
				displayBoard(myBoard);
				if(checkWinner(myBoard)){
					winner= 'X';
					tie= false;
					break;
				}
			}
		}
		else{
			computerMove(myBoard);
			symbols++;
			userTurn= true;
			displayBoard(myBoard);
			if(checkWinner(myBoard)){
				winner= 'O';
				tie= false;
				break;
			}
		}
		
			
	}
	
	cout<<"GAME OVER"<<endl;
	
	if(tie) cout<<"It was a tie!"<<endl;
	else{
		cout<<"The winner was "<<winner<<'!'<<endl;
		if(winner == 'X') cout<<"Congratulations!"<<endl;
		else cout<<"Too Bad :("<<endl;
	}
	return 1;
}

