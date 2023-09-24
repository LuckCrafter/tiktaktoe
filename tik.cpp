#include <iostream>
#include <string>

struct Board {
	int feld[3][3] {};
	int& operator()(size_t x, size_t y) { return feld[y][x]; };
	int operator()(size_t x, size_t y) const { return feld[y][x]; };
};

bool check (Board const& board) {
  int check[8] {};
  for (int i=0;i<9;++i) {
    check[i/3]+=board(i%3,i/3);
    check[(i%3)+3]+=board(i%3,i/3);
    if (i==0||i==4||i==8) check[6]+=board(i%3,i/3);
    if (i==2||i==4||i==6) check[7]+=board(i%3,i/3);
  }
  for (int i=0;i<8;++i) {
    if (check[i]==9||check[i]==12) return true;
  }
  return false;
}

void print(Board const& board) {
  std::cout << "+-+-+-+\n";
  for (int i=0;i<9;++i) {
    if (board(i%3,i/3)==0) std::cout << "|"<<i;
    if (board(i%3,i/3)==3) std::cout << "|X";
    if (board(i%3,i/3)==4) std::cout << "|O";
	if (i%3==2) std::cout << "|\n+-+-+-+\n";
  }
}

void turn(bool secondplayer, Board board) {
  int input;
  int checks=0;
  for (int i=0;i<9;++i) if (board(i%3,i/3)==0) ++checks;
  if (checks==0){
    print(board);
    std::cout << "\nGame draw!\n";
    return;
  }
  print(board);
  std::cout << "\nPlayer "<<secondplayer+1<<", select feld: ";
  std::cin >> input;
  std::cout << std::endl;
  if (0 <= input && input < 9 && board(input%3,input/3)==0) {
    if (secondplayer) board(input%3,input/3)=3;
    else board(input%3,input/3)=4;
	if (check(board)) {
      std::cout << "Player "<<secondplayer+1<<" have won!\n";
      print(board);
    }
    else turn(!secondplayer,board);
  }
  else {
    std::cout << "\nWrong Input\n";
    turn(secondplayer, board);
  }
}

int main() {
  Board board;
  turn(false,board);
  return 0;
}