#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

struct Process {
  string command; //command
  string process; //name of process
  int size; //size of process
  string type; //type
}proce;

int main(int argc, char *argv[]){
  int m, n;
  int p = -1;
  int memSize;
  int bsize = -1;
  int psize = -1;
  int blockSize[bsize];
  int processSize[psize];
  char line;
  bool tag;

  // Load the memory into the initial block
  memSize = atoi(argv[1]);
  blockSize[bsize++] = memSize;
  Process proc[p]; 

  //printf("%s\n", argv[1]);
  
  // Do not stop listening until QUIT is sent
  while(proc[p].command != "QUIT"){
    p++;
    cout << "allocator>";
    cin >> proc[p].command >> proc[p].process >> proc[p].size >> proc[p].type;

    // allocate the memory
    if(proc[p].command == "RL"){
      processSize[psize++] = proc[p].size;
      m = sizeof(blockSize)/sizeof(blockSize[0]);
      n = sizeof(processSize)/sizeof(processSize[0]);
      int allocation[n];
      memset(allocation, -1, sizeof(allocation));

      for(int i=0; i<n; i++){
        // Find the best fit block of memory
        int bestFit = -1;
        for(int j=0; j<m; j++){
          if(blockSize[j] >= processSize[i]){
            if(bestFit == -1){
              bestFit = j;
            }
            else if(blockSize[bestFit] > blockSize[j]){
              bestFit = j;
            }
          }
        }
          if(bestFit != -1){
            // allocate the block to the process
            allocation[i] = bestFit;
            blockSize[bestFit] -= processSize[i];
          }
      }
      // create empty block with remaining difference
      memSize -= proc[p].size;
      blockSize[bsize++] = memSize;
    }

    // deallocate
    if(proc[p].command == "RQ"){
      for(int i=0; i<bsize; i++){
        for(int j=0; j<p; j++){
          if(proc[j].process == proc[p].process){
            int s = proc[j].size;
            if(blockSize[i] == s){
              tag = 0;
            }
          }
        }
      }
    }

    // compact
    if(proc[p].command == "C"){
      
    }

    // report regions of free and allocated memory
    if(proc[p].command == "STAT"){
      for(int i=0; i<=bsize; i++){
        //cout<<"Addresses: [" + sizeof(blockSize[0]) + "]" + proc[p].process;
      }
    }

    // quit and end program
    if(proc[p].command == "QUIT"){
      return 0;
    }

  return 0;
  }
}

