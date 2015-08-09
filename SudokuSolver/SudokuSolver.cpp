#include <set>
#include <vector>
#include <iostream>
using namespace std;

bool groupcheck(vector<vector<char>>& board) {
	for(int i = 0; i < board.size(); i+=3){
		for(int j = 0; j < board[i].size(); j+=3){
			set<int> checkboard;
			int count = 0;
			for(int k = 0; k<3; k++){
				for(int l = 0; l<3; l++){
					if(board[i+k][j+l] != '.'){
						count++;
						checkboard.insert(board[i+k][j+l]);
					}
				}
			}
			if(count != checkboard.size()){
				return false;
			}
		}
	}
	return true;
}

bool rowcheck(vector<vector<char>>& board) {
	for(int i = 0; i < board.size(); i++){
		set<int> checkboard;
		int count = 0;
		for(int j = 0; j < board[i].size(); j++){
			if(board[i][j] != '.'){
				count++;
				checkboard.insert(board[i][j]);
			}
		}
		if(count != checkboard.size()){
			return false;
		}
	}
	return true;
}

bool columncheck(vector<vector<char>>& board) {
	for(int i = 0; i < board[0].size(); i++){
		set<int> checkboard;
		int count = 0;
		for(int j = 0; j < board.size(); j++){
			if(board[j][i] != '.'){
				count++;
				checkboard.insert(board[j][i]);
			}
		}
		if(count != checkboard.size()){
			return false;
		}
	}
	return true;
}

bool isValidSudoku(vector<vector<char>>& board) {
	if(board.size()<3){
		return false;
	}
	for(int i = 0; i<board.size(); i++){
		if(board[i].size() != board.size())
			return false;
	}
	if(groupcheck(board) && rowcheck(board) && columncheck(board)){
		return true;
	}
	return false;
}

void show(vector<vector<char>>& board){
	for(int i = 0; i < board[0].size(); i++){
		for(int j = 0; j < board.size(); j++){
			cout<<board[i][j] <<"\t";
		}
		cout<<endl;
	}
}

bool solver(vector<vector<char>>& board, int i, int j, vector<vector<vector<int>>> &available){

	for(int k = 0; k<available[i][j].size(); k++){
		board[i][j] = available[i][j][k] + 48;
		//show(board);
		//cout<<endl;
		bool mark = false;
		if(isValidSudoku(board)){
			int row = i;
			int col = j;
			while(row < board.size()){
				while(col < board[row].size()){
					if(board[row][col] != '.'){
						col++;
					}
					else{
						break;
					}
				}
				if(col == board[row].size()){
					if(row+1<board.size()){
						row++;
						col = 0;
						continue;
					}
					return true;
				}else{
					if(!solver(board, row, col, available)){
						mark = true;
						break;
					}
				}
			}
			if(mark){
				continue;
			}
		}
	}
	board[i][j] = '.';
	//show(board);
	//cout<<endl;
	return false;
}

void solveSudoku(vector<vector<char>>& board) {
	int row = 0;
	int col = 0;


	vector<vector<vector<int>>> available; 
	for(int i = 0; i<board.size(); i++){
		vector<vector<int>> available_1;
		for(int j = 0; j<board[i].size(); j++){
			vector<int> available_2;
			bool available[9];
			for(int a_tab = 0; a_tab<9; a_tab++){
				available[a_tab] = true;
			}
			for(int a_tab = 0; a_tab< board.size(); a_tab++){
				if(board[a_tab][j] != '.'){
					available[board[a_tab][j] - 48 - 1] = false;
				}
			}
			for(int a_tab = 0; a_tab< board[i].size(); a_tab++){
				if(board[i][a_tab] != '.'){
					available[board[i][a_tab] - 48 - 1] = false;
				}
			}
			int group_i = i/3;
			int group_j = j/3;
			for(int k = 0; k<3; k++){
				for(int l = 0; l<3; l++){
					if(board[group_i*3 + k][group_j*3 + l] != '.'){
						available[board[group_i*3 + k][group_j*3 + l] - 48 - 1] = false;
					}
				}
			}
			for(int a_tab = 0; a_tab < 9; a_tab++){
				if(available[a_tab]){
					available_2.push_back(a_tab+1);
				}
			}
			available_1.push_back(available_2);
		}
		available.push_back(available_1);
	}

	while(row < board.size()){
		while(col < board[row].size()){
			if(board[row][col] != '.'){
				col++;
			}
			else{
				break;
			}
		}
		if(board[row][col] == '.'){
			solver(board, row, col, available);
		}else{
			if(row+1<board.size()){
				row++;
				col = 0;
				continue;
			}
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
	/*
	line.push_back('5');
	line.push_back('3');
	line.push_back('4');
	line.push_back('6');
	line.push_back('7');
	line.push_back('8');
	line.push_back('9');
	line.push_back('1');
	line.push_back('2');
	board.push_back(line);

	line.clear();
	line.push_back('6');
	line.push_back('7');
	line.push_back('2');
	line.push_back('1');
	line.push_back('9');
	line.push_back('5');
	line.push_back('3');
	line.push_back('4');
	line.push_back('8');
	board.push_back(line);
	line.clear();

	line.push_back('1');
	line.push_back('9');
	line.push_back('8');
	line.push_back('3');
	line.push_back('4');
	line.push_back('2');
	line.push_back('5');
	line.push_back('6');
	line.push_back('7');
	board.push_back(line);
	line.clear();

	line.push_back('8');
	line.push_back('5');
	line.push_back('9');
	line.push_back('7');
	line.push_back('6');
	line.push_back('1');
	line.push_back('4');
	line.push_back('2');
	line.push_back('3');
	board.push_back(line);
	line.clear();

	line.push_back('4');
	line.push_back('2');
	line.push_back('6');
	line.push_back('8');
	line.push_back('5');
	line.push_back('3');
	line.push_back('7');
	line.push_back('9');
	line.push_back('1');
	board.push_back(line);
	line.clear();

	line.push_back('7');
	line.push_back('1');
	line.push_back('3');
	line.push_back('9');
	line.push_back('2');
	line.push_back('4');
	line.push_back('8');
	line.push_back('5');
	line.push_back('6');
	board.push_back(line);
	line.clear();

	line.push_back('9');
	line.push_back('6');
	line.push_back('1');
	line.push_back('5');
	line.push_back('3');
	line.push_back('7');
	line.push_back('2');
	line.push_back('8');
	line.push_back('4');
	board.push_back(line);
	line.clear();

	line.push_back('2');
	line.push_back('8');
	line.push_back('7');
	line.push_back('4');
	line.push_back('1');
	line.push_back('9');
	line.push_back('6');
	line.push_back('3');
	line.push_back('5');
	board.push_back(line);
	line.clear();

	line.push_back('3');
	line.push_back('4');
	line.push_back('5');
	line.push_back('2');
	line.push_back('8');
	line.push_back('6');
	line.push_back('1');
	line.push_back('7');
	line.push_back('9');
	board.push_back(line);
	line.clear();*/

	solveSudoku(board);
	//cout<<isValidSudoku(board);
	show(board);
	getchar();
}