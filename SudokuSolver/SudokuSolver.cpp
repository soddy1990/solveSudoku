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

bool solver(vector<vector<char>>& board, int i, int j, int n, vector<vector<vector<int>>> &available){
	if(j == n){
		j = 0;
		i++;
	}
	if(i == n){
		return true;
	} 
	if(board[i][j] != '.'){
		if(j<n)
			return solver(board, i, j+1, n, available);
		else
			return solver(board, i+1, 0, n, available);
	}else{
		for(int k = 0; k<available[i][j].size(); k++){
			board[i][j] = available[i][j][k]+48;
			//cout<<endl;
			//show(board);
			if(groupcheck(board,i,j) && rowcheck(board, j) && columncheck(board, i)){
				if(j<n){
					if(solver(board, i, j+1, n, available)){
						return true;
					}
					else{
						board[i][j] = '.';
						continue;
					}
				}
				else{
					if(solver(board, i+1, j, n, available)){
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

			n = rows;
			solver(board, 0, 0, n, available);
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