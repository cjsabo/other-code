#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// This program is written by Ankur Gupta.
// This program is a template for the Connect Four game.
// Compile and run this program so that you can see what
// will be printed out.

// This function draws the board.
void drawboard(ostream &, char [][7], int, int);
void drawcolorboard(ostream &, char [][7], int, int);
int humanmove(int, char[][7], int);
int  compmove(int, char[][7], int);
int verticalwin(char [][7], int, int, int);
int horizontalwin(char [][7], int, int, int);
int diagonalwin(char [][7], int, int, int);

int main () {
	
	ofstream outfile;
	outfile.open("gamelog01.txt");
	
	char board [6][7] = {0};
	srand(time(0));
	
	
	
	// Uncomment these lines to try out the
	// code for the first time.
	// Remove lines 19-25 (this block of code)
	// when you finally write your program.
	/*for (int x = 0; x < 6; x++)
		for (int y = 0; y < 7; y++)
			board[x][y] = 'X';*/
	//board[0][0] = 'O';
	//board[2][4] = 'X';
	
	
	// WRITE YOUR MENU PART HERE!!!
	int players;
	cout << "How many players are playing today? ";
	cin >> players;
	if(players == 1){
		int ref = 0;
		int first;
		cout << "Would you like to go first or second? " ;
		cin >> first;
		if(first == 1){
			while(ref == 0){
			drawcolorboard(cout, board, 6, 7);
			drawboard(outfile, board, 6, 7);
			ref = humanmove(1, board, 6);
			if(board[0][0] == 'Q') {
				cout << "See you again soon!!" << endl;
				break;
			}
			if(ref == 1) {
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				cout << "Player 1 has won!!" << endl;
				outfile<< "Player 1 has won!!" << endl;
				break;
			}
			drawcolorboard(cout, board, 6, 7);
			drawboard(outfile, board, 6, 7);
			ref = compmove(2, board, 6);
			if(ref == 1){
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				cout << "The computer has won!!" << endl;
				break;
			}
		}			
	}
		if(first == 2){
			while(ref == 0){
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				ref = compmove(1, board, 6);
				if(ref == 1){
					drawcolorboard(cout, board, 6, 7);
					drawboard(outfile, board, 6, 7);
					cout << "The computer has won!!" << endl;
					break;
				}
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				ref = humanmove(2, board, 6);
				if(board[0][0] == 'Q') {
					cout << "See you again soon!!" << endl;
					break;
				}
				if(ref == 1) {
					drawcolorboard(cout, board, 6, 7);
					drawboard(outfile, board, 6, 7);
					cout << "Player 2 has won!!" << endl;
					outfile << "Player 2 has won!!" << endl;
					break;
				}
			}
		}
	}		
	if(players == 2) {
		int ref = 0;
		while (ref == 0){
			drawcolorboard(cout, board, 6, 7);
			drawboard(outfile, board, 6, 7);
			ref = humanmove(1, board, 6);
			if(board[0][0] == 'Q') {
				cout << "See you again soon!!" << endl;
				break;
			}
			if(ref == 1) {
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				cout << "Player 1 has won!!" << endl;
				outfile<< "Player 1 has won!!" << endl;
				break;
			}
			drawcolorboard(cout, board, 6, 7);
			drawboard(outfile, board, 6, 7);
			ref = humanmove(2, board, 6);
			if(board[0][0] == 'Q') {
				cout << "See you again soon!!" << endl;
				break;
			}
			if(ref == 1) {
				drawcolorboard(cout, board, 6, 7);
				drawboard(outfile, board, 6, 7);
				cout << "Player 2 has won!!" << endl;
				outfile << "Player 2 has won!!" << endl;
				break;
			}
			
		}
	
	}
	
			
	// This is a sample use of the drawboard function.
	// It prints out the board to the screen.
   // The second drawboard command prints the game board
   // to the output file called gamelog01.txt
	//drawcolorboard(cout, board, 6, 7);
	//drawboard(outfile, board, 6, 7);
	
	outfile.close();
	return 0;
} // end main

// Ankur Gupta

// This function prints the board to the indicated ostream object.
// This function is intended to print to a file or it prints without color.
// The values in the board are 'X' for player 1, 'O' (the letter) for
// player 2, and the ASCII value of 0 (zero) for an empty space.
void drawboard(ostream & out, char b[][7], int r, int c) {
	out << endl;
	for (int x = r-1; x >= 0; x--) {
		out << "|";
		for (int y = 0; y < c-1; y++)
			out << "----";
		out << "---|" << endl << "|";
		for (int y = 0; y < c-1; y++)
			if (b[x][y] == 0)
				out << "   |";
			else
				out << " " << b[x][y] << " |";
		if (b[x][c-1] == 0)
			out << "   | " << x << endl;
		else
			out << " " << b[x][c-1] << " | " << x << endl;
	}
	
	out << "|";
	for (int y = 0; y < c-1; y++)
		out << "----";
	out << "---|" << endl;
	
	out << " ";
	for (int y = 0; y < c; y++)
		out << " " << y << "  ";
	out << endl << endl;

} // end drawboard function

// This function prints the board to the indicated ostream object.
// This function is intended to look pretty on a terminal with colors.
// The values in the board are 'X' for player 1, 'O' (the letter) for
// player 2, and the ASCII value of 0 (zero) for an empty space.
void drawcolorboard(ostream & out, char b[][7], int r, int c) {
	// Use this to bold the whole board
	out << "\033[1;37m"; 
	out << endl;
	for (int x = r-1; x >= 0; x--) {
		out << "|";
		for (int y = 0; y < c-1; y++)
			out << "----";
		out << "---|" << endl << "|";
		for (int y = 0; y < c-1; y++)
			if (b[x][y] == 0)
				out << "   |";
			else if (b[x][y] == 'X')
				out << " \033[1;31m" << b[x][y] << "\033[1;37m |";
			else
				out << " \033[1;34m" << b[x][y] << "\033[1;37m |";				
		if (b[x][c-1] == 0)
			out << "   | " << x << endl;
		else if (b[x][c-1] == 'X')
			out << " \033[1;31m" << b[x][c-1] << "\033[1;37m |" << x << endl;
		else
			out << " \033[1;34m" << b[x][c-1] << "\033[1;37m |" << x << endl;
	}
	
	out << "|";
	for (int y = 0; y < c-1; y++)
		out << "----";
	out << "---|" << endl;
	
	out << " ";
	for (int y = 0; y < c; y++)
		out << " " << y << "  ";
	// Use this to bold the whole board
	out << "\033[0m";
	out << endl << endl;

} // end drawboard function

int humanmove(int player, char board [][7], int rows){
	int col;
	cout << "What column would Player " << player << " like to play in? ";
	cin >> col;	
	while(col < -1 || col > 6) {
		cout << "No no no. You can't do that. Try again. What column? ";
		cin >> col;
	}	 
	while(board[5][col] == 'X' || board[5][col] == 'O'){
		cout << "No no no, you can't do that. Try again. What column? ";
		cin >> col;
	}
	if(col == -1) {
		board[0][0] = 'Q';
	}
	if (col >= 0 && col <= 6) {
	if(player == 1){
		for(int r = 0; r < rows; r++){
			if(board[r][col] == 0){
				board[r][col] = 'X';
				break;
				}
				if(board[r][col] == 'X' || board[r][col] == 'O'){
					continue;
				}
			}
		}
	if(player == 2) {
		for(int r = 0; r < rows; r++){
			if(board[r][col] == 0){
				board[r][col] = 'O';
				break;
				}
				if(board[r][col] == 'X' || board[r][col] == 'O'){
					continue;
				}
			}
		}
	}
	return verticalwin(board, 6, 0, 0);
}
//start of new function
int verticalwin(char board[][7], int rows, int moverow, int movecolumn) {
	int con = 0; 
	for(movecolumn = 0; movecolumn < 7; movecolumn++){
		for(moverow = 0; moverow < rows; moverow++){
			if(board[moverow][movecolumn] == 'X') {
				con += 1;
			}
			if(board[moverow][movecolumn] != 'X'){
				con = 0;
			}
			if(con == 4){
				return 1;
			}
		}
		con = 0;
	}
	con = 0;
	for(movecolumn = 0; movecolumn < 7; movecolumn++){
		for(moverow = 0; moverow < rows; moverow++){
			if(board[moverow][movecolumn] == 'O') {
				con += 1;
			}
			if(board[moverow][movecolumn] != 'O'){
				con = 0;
			}
			if(con == 4){
				return 1;
			}
		}
		con = 0;
	}
	return horizontalwin(board, 6, 0, 0);
}
//start of new function
int horizontalwin(char board[][7], int rows, int moverow, int movecolumn){
	int con = 0;
	for(moverow = 0; moverow < rows; moverow++){
		for(movecolumn = 0; movecolumn < 7; movecolumn++){
			if(board[moverow][movecolumn] == 'X') {
				con += 1;
			}
			if(board[moverow][movecolumn] != 'X'){
				con = 0;
			}
			if(con == 4){
				return 1;
			}
		}
		con = 0;
	}
	con = 0;
	for(moverow = 0; moverow < rows; moverow++){
		for(movecolumn = 0; movecolumn < 7; movecolumn++){
			if(board[moverow][movecolumn] == 'O') {
				con += 1;
			}
			if(board[moverow][movecolumn] != 'O'){
				con = 0;
			}
			if(con == 4){
				return 1;
			}
		}
		con = 0;
	}
	return diagonalwin(board, 6, 0, 0);
}
//start of new function
int diagonalwin(char board[][7], int rows, int moverow, int movecolumn){
	int con = 0;
	for(movecolumn = 0; movecolumn < 7; movecolumn++){
		for(moverow = 0; moverow < rows; moverow++){
			int r = moverow;
			int c = movecolumn;
			while(board[r++][c++] == 'X'){
				con +=1;
			}
			if(con == 4){
				return 1;
			}	
			if(board[r][c] != 'X'){
				con = 0;
			}	
		}
		con = 0;	
	}
	for(movecolumn = 0; movecolumn < 7; movecolumn++){
		for(moverow = 0; moverow < rows; moverow++){
			int r = moverow;
			int c = movecolumn;
			while(board[r++][c++] == 'O'){
				con +=1;
			}
			if(con == 4){
				return 1;
			}	
			if(board[r][c] != 'O'){
				con = 0;
			}	
		}
		con = 0;	
	}
	for(movecolumn = 6; movecolumn >= 0; movecolumn--){
		for(moverow = 0; moverow < rows; moverow++){
			int r = moverow;
			int c = movecolumn;
			while(board[r++][c--] == 'X'){
				con += 1;
			}
			if(con == 4){
				return 1;
			}
			if(board[r][c] != 'X'){
				con = 0;
			}
		}
		con = 0;
	}
	for(movecolumn = 6; movecolumn >= 0; movecolumn--){
		for(moverow = 0; moverow < rows; moverow++){
			int r = moverow;
			int c = movecolumn;
			while(board[r++][c--] == 'O'){
				con += 1;
			}
			if(con == 4){
				return 1;
			}
			if(board[r][c] != 'O'){
				con = 0;
			}
		}
		con = 0;
	}
	return 0;
}

int compmove(int player, char board[][7], int rows){
	int col = rand() % 7;
	while(board[5][col] == 'X' || board[5][col] == 'O'){
		col = rand() % 7;
	}
	if(player == 1){
		for(int r = 0; r < rows; r++){
			if(board[r][col] == 0){
				board[r][col] = 'X';
				break;
				}
				if(board[r][col] == 'X' || board[r][col] == 'O'){
					continue;
				}
			}
		}

	if(player == 2){
		for(int r = 0; r < rows; r++){
			if(board[r][col] == 0){
				board[r][col] = 'O';
				break;
				}
				if(board[r][col] == 'X' || board[r][col] == 'O'){
					continue;
				}
			}
		}
	return verticalwin(board, 6, 0, 0);
	}
	