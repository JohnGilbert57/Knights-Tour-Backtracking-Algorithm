#include <iostream>
#include <iomanip>
#include "knights_tour.h"
using namespace std;

KnightsTour::KnightsTour(int board_size) {
  this->board_size = board_size;

  this->board.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    this->board[i].resize(board_size);
  }
}

void KnightsTour::print() {
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++)
      cout << setw(4) << this->board[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
}

// Function: get_moves()
//    Desc: Get the row and column indices of all valid
//          knight moves reachable from position row, col.
//          An invalid move would be one that sends the
//          knight off the edge of the board or
//          to a position that has already been visited.
//          
//    int row         - Current row position of knight.
//    int col         - Current column position of knight.
//    int row_moves[] - Array to store row indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int col_moves[] - Array to store column indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int num_moves -   Number of valid moves found. Corresponds
//                      to the sizes of row_moves and col_moves.

void KnightsTour::get_moves(int row, int col, int row_moves[], int col_moves[], int& num_moves) {
  //initialize i to 0
  int i = 0;
  //initialize i to 0
  num_moves = 0;
  //line 48-53: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col - 2 < 5 && col - 2 >= 0) && (row + 1 < 5 && row + 1 >= 0) && this->board[row + 1][col - 2] == 0){
    num_moves++;
    row_moves[i] = row + 1;
    col_moves[i] = col - 2;
    i++;
  }
  //line 55-60: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col + 2 < 5 && col + 2 >= 0) && (row + 1 < 5 && row + 1 >= 0) && this->board[row + 1][col + 2] == 0){
    num_moves++;
    row_moves[i] = row + 1;
    col_moves[i] = col + 2;
    i++;
  }
  //line 62-67: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col - 2 < 5 && col - 2 >= 0) && (row - 1 < 5 && row - 1 >= 0) && this->board[row - 1][col - 2] == 0){
    num_moves++;
    row_moves[i] = row - 1;
    col_moves[i] = col - 2;
    i++;
  }
  //line 69-74: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col + 1 < 5 && col + 1 >= 0) && (row - 2 < 5 && row - 2 >= 0) && this->board[row - 2][col + 1] == 0){
    num_moves ++;
    row_moves[i] = row - 2;
    col_moves[i] = col + 1;
    i++;
  }
  //line 76-81: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col - 1 < 5 && col - 1 >= 0) && (row - 2 < 5 && row - 2 >= 0) && this->board[row - 2][col - 1] == 0){
    num_moves ++;
    row_moves[i] = row - 2;
    col_moves[i] = col - 1;
    i++;
  }
  //line 83-88: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col + 2 < 5 && col + 2 >= 0) && (row - 1 < 5 && row - 1 >= 0) && this->board[row - 1][col + 2] == 0){
    num_moves ++;
    row_moves[i] = row - 1;
    col_moves[i] = col + 2;
    i++;
  }
  //line 90-95: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col - 1 < 5 && col - 1 >= 0) && (row + 2 < 5 && row + 2 >= 0) && this->board[row + 2][col - 1] == 0){
    num_moves ++;
    row_moves[i] = row + 2;
    col_moves[i] = col - 1;
    i++;
  }
  //line 97-102: checks to see if one of the possible moves is applicable to the tour and loads into the array if it is
  if((col + 1 < 5 && col + 1 >= 0) && (row + 2 < 5 && row + 2 >= 0) && this->board[row + 2][col + 1] == 0){
    num_moves ++;
    row_moves[i] = row + 2;
    col_moves[i] = col + 1;
    i++;
  }
}

// Function: move() --> Recursive
//     int row        - Current row position of knight.
//     int col        - Current column position of knight.
//     int& m         - Current move id in tour.
//                      Stored in board at position
//                      row, col.
//     int& num_tours - Total number of tours found.

void KnightsTour::move(int row, int col, int& m, int& num_tours) {
  //sets num_moves to zero before each check for possible moves
  int num_moves = 0;
  //an array to store row moves with a maximum of 8 indexes because there is a maximum of 8 different types of moves a piece can take
  int row_moves[8];
  //an array to store column moves with a maximum of 8 indexes because there is a maximum of 8 different types of moves a piece can take
  int col_moves[8]; 
  //line 111-114: loads both arrays with -1 to initialize because -1 is not a potential move
  for (int i = 0; i < 8; i++) {
    row_moves[i] = -1;
    col_moves[i] = -1;
  }
  //place the piece of value m on the board
  this->board[row][col] = m;
  //increase value of m
  m++;
  //calls get_moves to load all potential moves
  get_moves(row, col, row_moves, col_moves, num_moves);
  //line 122-125: checks to see if the current board is a solution and prints it if it is and increments num_tours
  if(is_solution()){
    print();
    num_tours ++;
  }
  //line 126-133: recursive call that makes the moves on the board
  else{
    for(int i = 0; i < 8; i++){
      if(row_moves[i] != -1 && col_moves[i] != -1){
        move(row_moves[i], col_moves[i], m, num_tours);
      }
    }
  }
  //line 135-136: back functionality
  this->board[row][col] = 0;
  m--;
}
bool KnightsTour::is_solution(){
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++){
      if(this->board[i][j] == 0){
        return false;
      }
    }
  }
  return true;
}

int KnightsTour::generate(int row, int col) {
  int m = 1;
  int num_tours = 0;
  move(row, col, m, num_tours);
  return num_tours;
}
