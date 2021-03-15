//*****************************************************************************
//File: Test_Harness.cc
//Author: David W. Juedes
//Date: Spring 2021
//Purpose:  Test Harness for CS 4000, HW #3.
//****************************************************************************

#include <iostream>
#include <vector>

using namespace std;
#include "GameOfLife.h"
#include "thread.h"

#define NTHREADS 4
static thread_t threads[NTHREADS];

//*****************************************************************************
//Function: print_board.
//Purpose: Prints the contents of the matrix "board" to the standard output.
//
//****************************************************************************
void print_board(vector<vector<int> > &board) {
  int n = board.size();
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}
//***************************************************************************
//Function: main()
//Purpose: Reads in the data from the standard input (cin), calls the
//appropriate function in GameOfLife class (SimulateLife), and
//prints out final board.
//**************************************************************************
int main() {
  int n;
  cin >> n;
  vector<vector<int> > board;
  board.resize(n);
  for (int i=0;i<n;i++) {
    board[i].resize(n);
    for (int j=0;j<n;j++) {
      cin >> board[i][j];
    }
  }
  int k;
  cin >> k;

  GameOfLife obj;
  vector<vector<int> > result;

  cout<<endl<<"N: "<<n;
  cout<<endl<<"K: "<<k<<endl;

  result = obj.SimulateLife(board,k);
  print_board(result);

}

vector<vector<int>> GameOfLife::SimulateLife(vector<vector<int>> &board, int k){

  int board_size = board.size();// gives us the constraints for our for loop
  int l = 0;//  length of "life cycles"

  vector<vector<int>> next_board;
  next_board.resize(board_size);
  for(int i = 0; i < board_size; i++){
    next_board[i].resize(board_size);
  }

  next_board = board;


  // for(int i = 0; i < board_size; i++){
  //   for(int j = 0; j < board_size; j++){
  //     next_board
  //   }
  // }

  while(l < k){

    for(int i = 0; i < board_size; i++){// looping through the board so we can check the cells
      for(int j = 0; j < board_size; j++){

          int neighbour_count = 0;

          //  checking to see if it's neighbour cells are alive

          if(board[(board_size+i+1)%board_size] [j] == 1){//  down one
            neighbour_count++;
          }

          if(board[(board_size+i-1)%board_size] [j] == 1){//  up one
            neighbour_count++;
          }

          if(board[(board_size+i-1)%board_size] [(board_size+j+1)%board_size] == 1){//  up one and right one
            neighbour_count++;
          }

          if(board[(board_size+i-1)%board_size] [(board_size+j-1)%board_size] == 1){//  up one left one
            neighbour_count++;
          }

          if(board[(board_size+i+1)%board_size] [(board_size+j+1)%board_size] == 1){//  down one and right one
            neighbour_count++;
          }

          if(board[(board_size+i+1)%board_size] [(board_size+j-1)%board_size] == 1){//  down one and left one
            neighbour_count++;
          }

          if(board[i] [(board_size+j+1)%board_size] == 1){// right one
            neighbour_count++;
          }

          if(board[i] [(board_size+j-1)%board_size] == 1){// left one
            neighbour_count++;
          }

          if(neighbour_count >= 4){
            if(board[i][j] == 1){
              next_board[i][j] = 0;
            }
          }

          if(neighbour_count == 1 || neighbour_count == 0){
            if(board[i][j] == 1){
              next_board[i][j] = 0;
            }
          }

          if(neighbour_count == 3){
            if(board[i][j] == 0){
              next_board[i][j] = 1;
            }
          }

        }
      }
      board = next_board;
      l++; // increment "cycles"
  }

  return board;
}
