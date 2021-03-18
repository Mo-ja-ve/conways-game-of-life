//*****************************************************************************
//File: Test_Harness.cc
//Author: David W. Juedes
//Date: Spring 2021
//Purpose:  Test Harness for CS 4000, HW #3.
//****************************************************************************

#include <iostream>
#include <vector>
#include <pthread.h>
//#include <thread.h>

using namespace std;
#include "GameOfLife.h"

//int i = 0, j = 0;

vector<vector<int>> next_board;

struct thread_args{
  vector<vector<int>> &board_ptr;
  int size;
  int row_number;

  int iindex;
  int jindex;

  thread_args(vector<vector<int>> &board_ptr, int size, int row_number, int iindex, int jindex)
             : board_ptr(board_ptr), size(size), row_number(row_number), iindex(iindex), jindex(jindex){ }
};

void *quad_search(void *args){
  //cout<<endl<<" howdy partner ";
  int neighbour_count = 0;

  thread_args this_threads_args = *(thread_args*)args;

  int size    = this_threads_args.size;
  int row_num = this_threads_args.row_number;
  vector<vector<int>> board2 = this_threads_args.board_ptr;

  int i = this_threads_args.iindex;
  int j = this_threads_args.jindex;

  //cout<<endl<<"board size:  "<<this_threads_args.size;
  //cout<<endl<<"row number:  "<<this_threads_args.row_number;

          //checking to see if it's neighbour cells are alive
    cout<<endl<<"I: "<<i;
    cout<<" J: "<<j;
    //cout<<endl<<"SIZE: "<<size;


            if(board2[(size+i+1)%size] [j] == 1){//  down one
              neighbour_count++;
            }

            if(board2[(size+i-1)%size] [j] == 1){//  up one
              neighbour_count++;
            }

            if(board2[(size+i-1)%size] [(size+j+1)%size] == 1){//  up one and right one
              neighbour_count++;
            }

            if(board2[(size+i-1)%size] [(size+j-1)%size] == 1){//  up one left one
              neighbour_count++;
            }

            if(board2[(size+i+1)%size] [(size+j+1)%size] == 1){//  down one and right one
              neighbour_count++;
            }

            if(board2[(size+i+1)%size] [(size+j-1)%size] == 1){//  down one and left one
              neighbour_count++;
            }

            if(board2[i] [(size+j+1)%size] == 1){// right one
              neighbour_count++;
            }

            if(board2[i] [(size+j-1)%size] == 1){// left one
              neighbour_count++;
            }

            //neighbour_count = 10;
            //cout<<endl<<"begin ifs: ";

            if(neighbour_count >= 4){
              if(board2[i][j] == 1){
                next_board[i][j] = 0;
              }
            }
            //cout<<endl<<"FIRST IF";
            if(neighbour_count == 1 || neighbour_count == 0){
              if(board2[i][j] == 1){
                next_board[i][j] = 0;
              }
            }
            //cout<<endl<<"neighbourcout: "<<neighbour_count;

            //cout<<endl<<"second IF";
            if(neighbour_count == 3){
              if(board2[i][j] == 0){
                next_board[i][j] = 1;
            }
          }
          //cout<<endl<<"third IF";

          //cout<<endl<<"CLEARED IF: ";
          //return 0;
}

//*****************************************************************************
//Function: print_board.
//Purpose: Prints the contents of the matrix "board" to the standard output.
//
//*****************************************************************************
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
//***************************************************************************
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

  result = obj.SimulateLife(board,k);
  print_board(result);

}

vector<vector<int>> GameOfLife::SimulateLife(vector<vector<int>> &board, int k){


  int board_size = board.size();// gives us the constraints for our for loop
  int l = 0;//  length of "life cycles"

  static pthread_t threads[4];

  vector<vector<int>> next_board;
  next_board.resize(board_size);
  for(int i = 0; i < board_size; i++){
    next_board[i].resize(board_size);
  }

  next_board = board;

  //thread_struct.board_ptr = board;
  // = board;


  //thread_struct.board_ptr.resize(board_size);
  //thread_struct.board_ptr = board;

  //while(l < k){
    //int thread_i = 0;

    for(int i = 0; i < board_size; i++){// looping through the board so we can check the cells
      for(int j = 0; j < board_size; j++){

        thread_args thread_struct(board,board_size,4,i,j);
        // void *ptr;
        // ptr = &thread_struct;

        pthread_create(&(threads[0]), NULL, &quad_search, &thread_struct);
        // pthread_create(&(threads[1]), NULL, &quad_search, &thread_struct);
        // pthread_create(&(threads[2]), NULL, &quad_search, &thread_struct);
        // pthread_create(&(threads[3]), NULL, &quad_search, &thread_struct);
        pthread_join(threads[0], NULL);
        // pthread_join(threads[1], NULL);
        // pthread_join(threads[2], NULL);
        // pthread_join(threads[3], NULL);

        //thread_i++;
      }
      cout<<endl<<"lil uzi ";
      board = next_board;
      l++; // increment "cycles"
    }
  //}

  return board;
}
