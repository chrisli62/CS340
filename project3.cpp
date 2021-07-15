#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Process {
  int pid; //Process ID
  int priority; //Priority of process
  int btime; //Burst Time required
  int atime; //Arrival Time
};

//Keep track of the time in the system
int t = 0;
int timer;
int temp = 0; //Acts as key for printing

void print(Process proc[], int n){
  int wtime[n]; //Wait time
  int tatime[n]; //Turnaround time
  int rtime[n]; //Remaining time
  int timeQuantum = 10;
  int time, j, remaining;
  Process tempy[n];
  
  for(int i=0; i<n; i++){
    rtime[i] = proc[i].btime;
  }

  while(t<97){
    t++;
    for(time=0, j=0; remaining!=0;){
      if(rtime[j]<=timeQuantum && rtime[j]>0){
        timer += rtime[j];
        rtime[j] = 0;
        temp = 1;
      }
      else if(rtime[j] > 0){
        rtime[j] -= timeQuantum;
        timer += timeQuantum;
      }
      if(rtime[j] == 0 && temp == 1){
        remaining--;
        cout<<"\nProcess  "<<" Turnaround Time  "<<" Wait Time\n"<<proc[j].pid<<"\t\t\t"<<timer-proc[j].atime<<"\t\t\t\t"<<timer-proc[j].atime<<endl;
        temp = 0;
      }

      if(j == n-1){
        j = 0;
      }
      else if(proc[j+1].atime <= timer){
        j++;
      }
      else{
        j = 0;
      }  
    }  
  }
}

  //Testing code
  //cout<<"\nProcess  "<<" Turnaround Time  "<<" Wait Time\n";
  //for(int i=0; i<n; i++){
    //cout<<proc[i].pid<<"\t\t\t"<<wtime[i]<<"\t\t\t\t"<<tatime[i]<<endl;
  //}


int main() {
  //Proc layout manual test code
  //{Process #, Priority, Burst, Arrival}
  Process proc[] = {{1, 8, 15, 0}, {2, 3, 20, 0}, {3, 4, 20, 20}, {4, 4, 20, 25}, {5, 5, 5, 45}, {6, 5, 15, 55}};
  string fileName;
  cout<<"Input file name: ";
  cin>>fileName;
  std::fstream dataFile;
  //dataFile.open(fileName, std:io)
  

  int n = sizeof(proc)/sizeof(proc[0]);
  print(proc, n);
  return 0;
}