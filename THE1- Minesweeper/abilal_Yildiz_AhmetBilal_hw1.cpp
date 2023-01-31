// Ahmet Bilal Yildiz
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "randgen.h"
using namespace std;

void operation1( const vector<vector<char>> & display, const vector<vector<char>> & imatrix, int &row, int &col);
void operation2(bool &check2, vector<vector<char>> &display ,const vector<vector<char>> & matrix, int &row, int &col, int &c_num);
void print(const vector<vector<char>> &matrix, const int & row, const int &col);
int main(){
	int row, col; // getting number of rows and colons;

	cout << "Give the dimensions of the matrix: ";
	cin >> row >> col;

	vector<vector<char>> matrix (row, vector<char>(col,'X')); // matrix is the actual matrix which represents the arranged minefield(B's and numbers of neighboring mines);
	vector<vector<char>> imatrix (row, vector<char>(col,'X')); // imatrix is the matrix which consists of only ints showing the number neighboring mines even a cell has a mine;
	vector<vector<char>> display(row, (vector<char>(col, 'X'))); // display is the matrix to display opened cells;
	int nrMines;
	cout << "How many bombs: "; // asking for number of bombs;
	cin >> nrMines;
	while((nrMines <= 0) || (nrMines >= row*col)){
		if (nrMines <= 0){
		cout << "The number of bombs could not be less than one. ";

		}
		else if(nrMines >= row*col){
			cout << "The number of bombs can not be greater than the whole number of cells minus one. "; 
		
		}
		cout << "Please give the number of bombs again: ";
		cin >> nrMines;
	}

	print(matrix, row, col);

	// distributing the bombs randomly;
	int i = 0;
	int posx = 0;
	int posy = 0;
	RandGen random;
	while (i < nrMines){
		posx = random.RandInt(row);
		posy = random.RandInt(col);
		if (matrix[posx][posy] != 'B'){
			matrix[posx][posy] = 'B';
			i++;
		}

	}
	// since ASCII number of 0 is 48, use char(int+48) to convert a decimal to a char;
	// calculating the neighboring bombs;

	for (int j= 0; j < row; j++){
		for (int k=0; k< col; k++){
			int num = 0;
			if(row == 1){ // calculating the neighbor mines in  1 row matrix;
				if(k == 0){
					if(matrix[j][k+1] == 'B'){
						num++;
					}
				}
				else if(k == col-1){
					if(matrix[j][k-1] == 'B'){
						num++;
					}
				} 
				else {
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k-1] == 'B'){
						num++;
					}
				
				}
				imatrix[j][k] = char(num+ 48);
				if(matrix[j][k] != 'B'){
					matrix[j][k] = char(num + 48);

				}

			} 
			else if(col == 1){// calculating the neighbor mines in  1 col matrix;
				if(j == 0){
					if(matrix[j+1][k] == 'B'){
						num++;
					}
				}
				else if(j == row-1){
					if(matrix[j-1][k] == 'B'){
						num++;
					}
				}
				else{
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
				
				}
				imatrix[j][k] = char(num+ 48);
				if(matrix[j][k] != 'B'){
					matrix[j][k] = char(num + 48);

				}
			
			}
			// calculating the neighbor mines in normal matrix(neither 1 row nor 1 col);
			else if(j == 0){
				if (k == 0){ // top left corner;

					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k+1] == 'B'){
						num++;
					}
					

				}
				else if (k == col-1) { // top right corner;

					
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k-1] == 'B'){
						num++;
					}
					
				}
				else { // top middles;

					

					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j+1][k-1] == 'B'){
						num++;
					}
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k+1] == 'B'){
						num++;
					}
					
				}

				imatrix[j][k] = char(num+ 48);
				if(matrix[j][k] != 'B'){
					matrix[j][k] = char(num + 48);

				}
			}
			else if (j == row-1 ){
				if (k == 0){ // down left corner;
				
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					if(matrix[j-1][k+1] == 'B'){
						num++;
					}
					
				}
				else if (k == col-1) { // down right corner;
						
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					if(matrix[j-1][k-1] == 'B'){
						num++;
					}


				}
				else { // down middle corners;
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					if(matrix[j-1][k+1] == 'B'){
						num++;
					}
				
				}
				imatrix[j][k] = char(num+ 48);
				if(matrix[j][k] != 'B'){
					matrix[j][k] = char(num + 48);

				}
			}
			else{ // middle cells(neither top nor down);
				if (k == 0){// left middle;
					
					
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j-1][k+1] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					
				} 
				else if (k== col-1){ //right middle;
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k-1] == 'B'){
						num++;
					}
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k-1] == 'B'){
						num++;
					}
					
				}
				else{ // middle middle;
					if(matrix[j][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k-1] == 'B'){
						num++;
					}
					if(matrix[j-1][k] == 'B'){
						num++;
					}
					if(matrix[j-1][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j][k+1] == 'B'){
						num++;
					}
					if(matrix[j+1][k+1] == 'B'){
						num++;
					}
					if(matrix[j+1][k] == 'B'){
						num++;
					}
					if(matrix[j+1][k-1] == 'B'){
						num++;
					}
					
					
				}
				imatrix[j][k] = char(num+ 48);
				if(matrix[j][k] != 'B'){
					matrix[j][k] = char(num + 48);

				}
				
			}
			
		}
		
	} 

	// getting checks;
	bool check2 = true, check3 = true; // check2 checks possible ends due to the operation2 // check3 checks possible ends due to the operation 3; 
	int c_num = 0; // c_num is the number of clear cells (cells without bombs) // when c_num equals to row*col-nrMines (there is no cells without boms) the player wins the game;
	while (check2 && check3){
		// getting the operation option;
		string operation;
		cout << "Press: " << endl << endl <<"1. If you want to find out the surrounding of a cell " << endl << endl << "2. If you want to open the cell " << endl << endl << "3. If you want to exit." << endl;
		cin >> operation;
		while(!(operation == "1" || operation== "2" ||operation == "3")){
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin >> operation;
		}

		if (operation == "1"){
			operation1(display, imatrix, row, col);
		}

		if(operation == "2"){
			operation2(check2, display, matrix, row, col, c_num);
			if(c_num == (row* col-nrMines)){
				cout << "Congratulations! All the non-mined cells opened successfully " << endl;
				cout << "You won!" << endl;
				cout << ">>>>> Game Over! <<<<<" << endl;
				check2 = false;
			}
		} 
	
		if (operation == "3"){
			cout << "Program exiting ..." << endl;
			check3 = false;
		}
	}

return 0;
}

void print(const vector<vector<char>> &matrix, const int & row, const int &col){
	cout << endl;
	for (int j= 0; j < row; j++){
		for (int k=0; k< col; k++){
			if(k < col-1){
				cout << matrix[j][k] << setw(3);
			}
			else{
				cout<< matrix[j][k];
			}
		}
		cout << endl << endl;
	}
	cout << endl;
}


void operation1(const vector<vector<char>> & display, const vector<vector<char>> & imatrix, int &row, int &col){
	// coordinates;
	int co_x, co_y;
	cout << "Give the coordinates: ";
	cin >> co_x >> co_y;

	while (co_x < 0 || co_x >= row || co_y < 0 || co_y >= col){
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> co_x >> co_y;
	}
	vector<vector<char>> temp(row, vector<char>(col, 'X'));
	temp = display;
	temp[co_x][co_y] = imatrix[co_x][co_y]; 
	cout << "Displaying the surrounding of (" << co_x << "," << co_y <<"): ";
	print(temp, row, col);
	cout << "Around (" << co_x  << "," << co_y << ") you have " << imatrix[co_x][co_y] <<" bomb(s)" << endl;
}



void operation2(bool &check2, vector<vector<char>> &display ,const vector<vector<char>> & matrix, int &row, int &col, int &c_num){ // opening a cell;
	// coordinates;
	int co_x, co_y;
	cout << "Give the coordinates: ";
	cin >> co_x >> co_y;

	while (co_x < 0 || co_x >= row || co_y < 0 || co_y >= col){
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> co_x >> co_y;
	}

	cout << "Opening cell ("<< co_x << "," << co_y << "): " << endl;
	display[co_x][co_y] = matrix[co_x][co_y]; 
	print(display, row, col);

	if( matrix[co_x][co_y] == 'B'){
		cout << "Unfortunately, you stepped on a mine" << endl << endl;
		cout << "Arrangement of mines: " << endl;
		print(matrix, row, col);
		cout << ">>>>> Game Over! <<<<<";
		check2 = false;
	} 
	else {
		c_num++;
	}

}	

