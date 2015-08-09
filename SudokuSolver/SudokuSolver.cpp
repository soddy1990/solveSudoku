#include <set>
#include <vector>
#include <iostream>
using namespace std;


void show(vector<vector<char>>& board){
	for(int i = 0; i < board[0].size(); i++){
		for(int j = 0; j < board.size(); j++){
			cout<<board[i][j] <<"\t";
		}
		cout<<endl;
	}
}

bool groupcheck(vector<vector<char>>& board, int i, int j) {
	int qu_i = i/3;
	int qu_j = j/3;
	set<int> checkboard;
	int count = 0;
	for(int p = 0; p<3; p++){
		for(int q =0; q<3; q++){
			if(board[3*qu_i+p][3*qu_j+q] != '.'){
				count++;
				checkboard.insert(board[3*qu_i+p][3*qu_j+q]);
			}
		}
	}
	if(count != checkboard.size()){
		return false;
	}
	return true;
}
bool rowcheck(vector<vector<char>>& board, int j) {
	set<int> checkboard;
	int count = 0;
	for(int k = 0; k < board.size(); k++){
		if(board[k][j] != '.'){
			count++;
			checkboard.insert(board[k][j]);
		}
	}
	if(count != checkboard.size()){
		return false;
	}
	return true;
}

bool columncheck(vector<vector<char>>& board, int i) {
	set<int> checkboard;
	int count = 0;
	for(int k = 0; k < board.size(); k++){
		if(board[i][k] != '.'){
			count++;
			checkboard.insert(board[i][k]);
		}
	}
	if(count != checkboard.size()){
		return false;
	}
	return true;
}

bool solver(vector<vector<char>>& board, int i, int j, int n){
	if(j == n){
		j = 0;
		i++;
	}
	if(i == n){
		return true;
	} 
	if(board[i][j] != '.'){
		if(j<n)
			return solver(board, i, j+1, n);
		else
			return solver(board, i+1, 0, n);
	}else{
		for(int k = 1; k<=9; k++){
			board[i][j] = k+48;
			//cout<<endl;
			//show(board);
			if(groupcheck(board,i,j) && rowcheck(board, j) && columncheck(board, i)){
				if(j<n){
					if(solver(board, i, j+1, n)){
						return true;
					}
					else{
						board[i][j] = '.';
						continue;
					}
				}
				else{
					if(solver(board, i+1, j, n)){
						return true;
					}
					else{
						board[i][j] = '.';
						continue;
					}
				}
			}
			board[i][j] = '.';
		}
		return false;
	}
}

void solveSudoku(vector<vector<char>>& board) {
	int rows = board.size();
	if(rows>0){
		int cols = board[0].size();
		int n = 0;
		if(cols == rows){
			n = rows;
			solver(board, 0, 0, n);
		}
	}
}

void main(){
	vector<vector<char>> board;
	vector<char> line;

	line.push_back('5');
	line.push_back('3');
	line.push_back('.');
	line.push_back('.');
	line.push_back('7');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	board.push_back(line);

	line.clear();
	line.push_back('6');
	line.push_back('.');
	line.push_back('.');
	line.push_back('1');
	line.push_back('9');
	line.push_back('5');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	board.push_back(line);
	line.clear();

	line.push_back('.');
	line.push_back('9');
	line.push_back('8');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('6');
	line.push_back('.');
	board.push_back(line);
	line.clear();

	line.push_back('8');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('6');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('3');
	board.push_back(line);
	line.clear();

	line.push_back('4');
	line.push_back('.');
	line.push_back('.');
	line.push_back('8');
	line.push_back('.');
	line.push_back('3');
	line.push_back('.');
	line.push_back('.');
	line.push_back('1');
	board.push_back(line);
	line.clear();

	line.push_back('7');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('2');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('6');
	board.push_back(line);
	line.clear();

	line.push_back('.');
	line.push_back('6');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('2');
	line.push_back('8');
	line.push_back('.');
	board.push_back(line);
	line.clear();

	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('4');
	line.push_back('1');
	line.push_back('9');
	line.push_back('.');
	line.push_back('.');
	line.push_back('5');
	board.push_back(line);
	line.clear();

	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('.');
	line.push_back('8');
	line.push_back('.');
	line.push_back('.');
	line.push_back('7');
	line.push_back('9');
	board.push_back(line);
	line.clear();
		
	show(board);
	cout<<endl;
	solveSudoku(board);
	//cout<<isValidSudoku(board);
	show(board);
	getchar();
}