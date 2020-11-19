/*
* Author: Molly Jacobsen
* Date: February 11th
*
* functions.cpp
*
* Objective: to provide functions that make it possible to play 3d tic tac toe
*/

#include <iostream>
#include <cstdlib>

using namespace std;

//My internal functions
bool check(int pos[], int max);
int twoInRow(int pos[], int max, char board[]);

void greetAndInstruct(){
	char yn;
	cout << "This is |ULTIMATE TIC-TAC-TOE| - Player vs. Computer" << endl;
	cout << "\nThe 3D board is numbered from 1 to 27 like so:" << endl;
	cout << "\n 1 | 2 | 3 \t 10 | 11 | 12 \t 19 | 20 | 21 " << endl;
	cout << "-----------\t--------------\t--------------" << endl;
	cout << " 4 | 5 | 6 \t 13 | 14 | 15 \t 22 | 23 | 24 " << endl;
	cout << "-----------\t--------------\t--------------" << endl;
	cout << " 7 | 8 | 9 \t 16 | 17 | 18 \t 25 | 26 | 27 " << endl;
	cout << "\nPlayer goes first. simply input the cell you want to occupy. Player's move is marked with X and computer's with O. Get any three in a row to win!" << endl;
	cout << "Are you ready to rumble? (y/n) ";
	cin >> yn;
	if(yn == 'n') exit(0);
}

void displayBoard(char board[]){
	char b[] = " | ";
	cout << "The current board status is: " << endl;
	cout <<board[0]<<b<<board[1]<<b<<board[2]<<'\t';
	cout <<board[9]<<b<<board[10]<<b<<board[11]<<'\t';
	cout <<board[18]<<b<<board[19]<<b<<board[20]<<endl;
	cout <<"---------\t---------\t---------"<<endl;
	cout <<board[3]<<b<<board[4]<<b<<board[5]<<'\t';
	cout <<board[12]<<b<<board[13]<<b<<board[14]<<'\t';
	cout <<board[21]<<b<<board[22]<<b<<board[23]<<endl;
	cout <<"---------\t---------\t---------"<<endl;
	cout <<board[6]<<b<<board[7]<<b<<board[8]<<'\t';
	cout <<board[15]<<b<<board[16]<<b<<board[17]<<'\t';
	cout <<board[24]<<b<<board[25]<<b<<board[26]<<endl;
}

bool checkIfLegal (int cellNbre, char board[]){
	if(cellNbre < 1 || cellNbre > 27){
		cout << "Input out of bounds, please enter a number between 1 and 27." << endl;
		return(false);
	}
	else if(board[cellNbre - 1] != ' '){
		cout << "Cell occupied, please pick another cell." << endl;
		return(false);
	}
	else return(true);
}

bool checkWinner(char board[]){
	int i;			//index for board
	int xs[20], os[20];	//positions of all x's and o's
	int j=0, k=0;		//index for xs, os

	//parse for positions of x's and o's
	for(i=0; i < 27; i++){
		if(board[i] == 'X'){
			xs[j] = i;
			j++;
		}
		else if(board[i] == 'O'){
			os[k] = i;
			k++;
		}
	}
	
	bool xWin= false, oWin= false;
	
	if(j >= 2){	//if there is 3 or more x's
		xWin=(check(xs, j));
	}
	if(k >= 2){
		oWin=(check(os, k));
	}			
	
	return(xWin || oWin);
}

void computerMove(char board[]){
	int i;
	int xs[20], os[20];
	int j=0, k=0;
	
	//parse for x's and o's
	for(i=0; i < 27; i++){	
		if(board[i] == 'X'){
			xs[j] = i;
			j++;
		}
		else if(board[i] == 'O'){
			os[k] = i;
			k++;
		}
	}
	
	int oToWin= twoInRow(os, k, board);	//where o could win
	int xToWin= twoInRow(xs, j, board);	//where x could win
	
	//first priority - to win
	if(oToWin>(-1)) board[oToWin]= 'O';
	
	//second priority - block X
	else if(xToWin>(-1)) board[xToWin]= 'O';
	
	else{
		//take a corner
		if(board[0] == ' ') board[0]= 'O';
		else if(board[2] == ' ') board[2]= 'O';
		else if(board[18] == ' ') board[18]= 'O';
		else if(board[20] == ' ') board[20]= 'O';
		else if(board[6] == ' ') board[6]= 'O';
		else if(board[8] == ' ') board[8]= 'O';
		else if(board[24] == ' ') board[24]= 'O';
		else if(board[26] == ' ') board[26]= 'O';
		else{	//all corners are full
			for(i=1; i<26; i++){
				if(board[i] == ' ') board[i]= 'O';
			}
		}
	}
}

//helper function for computerMove
int twoInRow(int pos[], int max, char board[]){
	int i, j;
	int cur;	//current value
	bool left, secondLeft, right; 
	bool top, secondTop, bottom, front, secondFront, back;
	
	for(i=0; i<max; i++){
		cur=pos[i];
		
		//booleans for table position
		left= ((cur % 3) == 0);
		secondLeft= ((cur % 3) == 1);
		right= !left && !secondLeft;

		top= ((cur<3)||(cur>8&&cur<12)||(cur>17&&cur<21));
		secondTop= ((cur>2&&cur<6)||(cur>11&&cur<15)||(cur>20&&cur<24));
		bottom= !top && !secondTop;
 
		front= (cur < 9);
		secondFront= (cur > 8) && (cur < 18);

		//check for 3D diagonals
		if(cur == 0){
			for(j=i+1; j<=max; j++){
				if(pos[j] == 13 && board[26] == ' ')
					return(26);
				else if(pos[j] == 26 && board[13] == ' ')
					return(13);
			}
		}
		else if(cur == 2){
			for(j=i+1; j<=max; j++){
				if(pos[j] == 13 && board[24] == ' ')
					return(24);
				else if(pos[j] == 24 && board[13] == ' ')
					return(13);
			}
		}
		else if(cur == 6){
			for(j=i+1; j<=max; j++){
				if(pos[j] == 13 && board[20] == ' ')
					return(20);
				else if(pos[j] == 20 && board[13] == ' ')
					return(13);
			}
		}
		else if(cur == 8){
			for(j=i+1; j<=max; j++){
				if(pos[j] == 13 && board[18] == ' ')
					return(18);
				else if(pos[j] == 18 && board[13] == ' ')
					return(13);
			}
		}
		else if(cur == 13){
			for(j=i+1; j<=max; j++){
				if(pos[j] == 26 && board[0] == ' ')
					return(0);
				else if(pos[j] == 24 && board[2] == ' ')
					return(2);
				else if(pos[j] == 20 && board[6] == ' ')
					return(6);
				else if(pos[j] == 18 && board[8] == ' ')
					return(8);
			}
		}

		//Check for 2D diagonals
		if(left && top){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+4 && board[cur+8] == ' ')
					return(cur+8);
				else if(pos[j] == cur+8 && board[cur+4] == ' ')
					return(cur+4);
			}
		}
		else if(right && top){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+2 && board[cur+4] == ' ')
					return(cur+4);
				else if(pos[j] == cur+4 && board[cur+2] == ' ')
					return(cur+2);
			}
		}
		else if(secondLeft && secondTop){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+2 && board[cur-2] == ' ')
					return(cur-2);
				else if(pos[j] == cur+4 && board[cur-4] == ' ')
					return(cur-4);
			}
		}
		
		if(left && front){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+10 && board[cur+20] == ' ')
					return(cur+20);
				else if(pos[j] == cur+20 && board[cur+10] == ' ')
					return(cur+10);
			}
		}
		if(right && front){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+8 && board[cur+16] == ' ')
					return(cur+16);
				else if(pos[j] == cur+16 && board[cur+8] == ' ');
					return(cur+8);
			}
		}
		if(secondLeft && secondFront){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+10 && board[cur-10] == ' ')
					return(cur-10);
				else if(pos[j] == cur+8 && board[cur-8] == ' ')
					return(cur-8);
			}
		}
		
		if(front && top){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+12 && board[cur+24] == ' ')
					return(cur+24);
				else if(pos[j] == cur+24 && board[cur+12] == ' ')
					return(cur+12);
			}
		}
		if(front && bottom){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+6 && board[cur+12] == ' ')
					return(cur+12);
				else if(pos[j] == cur+12 && board[cur+6] == ' ')
					return(cur+6);
			}
		}
		if(secondFront && secondTop){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+12 && board[cur-12] == ' ')
					return(cur-12);
				if(pos[j] == cur+6 && board[cur-6] == ' ')
					return(cur+6);
			}
		}
		
		//check 1D lines
		if(left){
			for(j=i+1; j<=max; j++){

				if(pos[j] == cur+1 && board[cur+2] == ' ')
					return(cur+2);	//return two later
				
				else if(pos[j] == cur+2 && board[cur+1] == ' ')
					return(cur+1);	//return between

			}
		}
		else if(secondLeft){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+1 && board[cur-1] == ' ')
					 return(cur-1);
			}
		}
		
		if(top){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+3 && board[cur+6] == ' ')
					return(cur+6);
			
				if(pos[j] == cur+6 && board[cur+3] == ' ')
					return(cur+3);
				
			}
		}
		else if(secondTop){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+3 && board[cur-3] == ' ') 
					return(cur-3);
			}
		}

		if(front){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+9 && board[cur+18] == ' ')
					return(cur+18);
			
				if(pos[j] == cur+18 && board[cur+9] == ' ');
					return(cur+9);
			}
		}
		else if(secondFront){
			for(j=i+1; j<=max; j++){
				if(pos[j] == cur+9 && board[cur-9] == ' ')
					return(cur-9);
			}
		}
		
	}
	//couldn't find any
	return (-1);
					
}

//helper functions for checkWinner
bool check(int pos[], int max){	//check for three in a row
	bool second = false;
	bool left, right, front, back, top;
	int k;
	
	int cur; 	//current value
	for(int i=0; i<(max-1); i++){	//all positions at least two before end
		
		cur = pos[i];

		left=((pos[i] % 3) == 0);
		right=((pos[i] % 3) == 2);

		front=(pos[i]<9);
		back=(pos[i]>17);

		top=((pos[i]<3)||(pos[i]>8&&pos[i]<12)||(pos[i]>17&&pos[i]<21));
		
		//test the four 3D diagonals
		if(pos[i]==0){		//front/top/left corner
			for(k=i+1; k<=max; k++){
				if(pos[k] == 13) second=true;
				if(pos[k] == 26 && second) return(true);
			}
		}
		if(pos[i]==2){
			for(k=i+1; k<=max; k++){
				if(pos[k] == 13) second=true;
				if(pos[k] == 24 && second) return(true);
			}
		}
		if(pos[i]==6){
			for(k=0; k<=max; k++){
				if(pos[k] == 13) second=true;
				if(pos[k] == 20 && second) return(true);
			}
		}
		if(pos[i]==8){
			for(k=i+1; k<=max; k++){
				if(pos[k] == 13) second=true;
				if(pos[k] == 18 && second) return(true);
			}
		}
		second=false;	//after each block of mutually exlusive ifs
		
		//check the 2D diagonals
		if(left && top){
			for(k=i+1; k<=max; k++){
				if(pos[k] == cur+4) second=true;
				if(pos[k] == cur+8 && second) return(true);
			}
		}
		if(right && top){
			for(k=i+1; k<=max; k++){
				if(pos[k] == cur+2) second=true;
				if(pos[k] == cur+4 && second) return(true);
			}
		}
		second=false;
		if(left && front){
			for(k=i+1; k<=max; k++){
				if(pos[k] == cur+10) second=true;
				if(pos[k] == cur+20 && second) return(true);
			}
		}
		if(right && front){
			for(k=i+1; k<=max; k++){
				if(pos[k] == cur+8) second=true;
				if(pos[k] == cur+16 && second) return(true);
			}
		}
		second=false;
		if(front && top){
			for(k=i+1; k<=max; k++){
				if(pos[k] == cur+12) second=true;
				if(pos[k] == cur+24 && second) return(true);
			}
		}
		if(back && top){
			for(k=0; k<i; k++){
				if(pos[k] == cur-6) second=true;
				if(pos[k] == cur-12 && second) return(true);
			}
		}
		second=false;
		
		//check for 1D lines
		if(left){	//if on left side
			for(k=i+1; k<max; k++){
				if(pos[k] == pos[i]+1){	//directly beside
					second = true;
					break;
				}
			}
			if(second){
				for(k=k+1; k<=max; k++){
					if(pos[k] == pos[i]+2) return(true);
				}
			}
		}
		second=false;
		if(top){
			for(k=i+1; k<max; k++){
				if(pos[k] == cur+3){	//directly below
					second = true;
					break;
				}
			}
			if(second){
				for(k=k+1; k<=max; k++){
					if(pos[k] == cur+3) return(true);
				}
			}
		}
		second=false;
		if(front){
			for(k=i+1; k<max; k++){
				if(pos[k] == pos[i]+9){ //directly behind
					second = true;
					break;
				}
			}
			if(second){
				for(k=k+1; k<=max; k++){
					if(pos[k] == pos[i]+18) return(true);
				}
			}
		}
		second=false;
	}
	return(false);
} 
				
