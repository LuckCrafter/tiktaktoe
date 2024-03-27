#include <iostream>
#include <string>
struct Board {
	private:
	char cell[3][3]{
	{'0', '1', '2'},
	{'3', '4', '5'},
	{'6', '7', '8'}};
	public:
	char& operator()(size_t x, size_t y)       {return cell[y][x];};
	char  operator()(size_t x, size_t y) const {return cell[y][x];};
};

void printboard(Board const& board) {
	std::cout << "+-+-+-+"<<std::endl;
	for (int i {0};i<9;++i) {
		std::cout << "|" << board(i%3,i/3);
		if (i%3==2) std::cout << "|" << std::endl << "+-+-+-+" << std::endl;
	}
}

bool check(Board const& board) {
	int check[6] {0};
	for (int i {0};i<9;++i) {
		check[i/3]+=board(i%3,i/3);
		check[(i/3)+3]+=board(i/3,i%3);
	}
	if (board(1,1)==board(0,0) && board(1,1)==board(2,2)) return true;
	if (board(1,1)==board(0,2) && board(1,1)==board(2,0)) return true;
	for (int i {0};i<6;++i) {
		if (check[i]=='X'+'X'+'X'||check[i]=='O'+'O'+'O') return true;
	}
	return false;
}

int getinput(Board const& board, bool player) {
	std::cout << std::endl << "Player " << player << " select cell: ";
	int input;
	std::cin >> input;
	if (!(0<=input && input<9)) {
		std::cout << std::endl << std::endl << "Select a number inside of the board (0-8)" << std::endl;
		input=getinput(board,player);
	}
	if (board(input%3,input/3)=='X'||board(input%3,input/3)=='O') {
		std::cout << std::endl << "Select a free cell" << std::endl;
		input=getinput(board,player);
	}
	return input;
}

int main() {
	Board board;
	int round=0;
	bool selectetplayer=false;
	while (round<9) {
		printboard(board);
		int input = getinput(board,selectetplayer);
		if (selectetplayer) board(input%3,input/3)='O';
		else 				board(input%3,input/3)='X';
		if (check(board)) {
			std::cout << "Player " << selectetplayer << " has won!" << std::endl;
			printboard(board);
			return 0;
		}
		selectetplayer ^= true;
		round+=1;
	}
	std::cout << "Draw!" << std::endl;
	return 0;
}