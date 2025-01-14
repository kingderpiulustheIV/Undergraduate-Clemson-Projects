#include "stats.h"
Stats::Stats() {
    numbers.resize(100);
    fileName = "";
  }

Stats::Stats(string fileName) {
ifstream myFile(fileName);
  if(myFile.is_open()) {
        int value = 0;
        while(myFile >> value){
          numbers.push_back(value);
        }
        myFile.close();
    }
}

int Stats::capacity() {
    return numbers.capacity();
}

int Stats::count() {
    return numbers.size();
}
int Stats::countEven() {
    int total = 0;
    for( unsigned int  i = 0; i < numbers.size(); i++) {
        if (numbers[i] % 2 == 0)
            total ++;
    }        
    return total;
}

int Stats::countOdd() {
    int total= 0;
    for ( unsigned int  i = 0; i < numbers.size(); i++) {
        if (numbers[i] % 2 != 0) 
            total ++;
    }
    return total;
}

int Stats::countFib(){
    int total = 0;
    for ( unsigned int  i = 0; i < numbers.size(); i++) {
        if (numbers[i] == ((numbers[i] -1) + (numbers[i]-2))) 
            total ++;
    }
    return total;
}

float Stats::avgAll() {
    int total= 0;
    int sum = 0;
    for ( unsigned int  i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
        total++;
    }
    return sum / total;
}

float Stats::avgEven() {
    int total= 0;
    int sum = 0;
    for ( unsigned int  i = 0; i < numbers.size(); i++) {
        if (numbers[i] % 2 == 0) {
            sum += numbers[i];
            total ++;
        }
    }
    return sum / total;
}

float Stats::avgOdd() {
    int total= 0;
    int sum = 0;
    for ( unsigned int  i = 0; i < numbers.size(); i++) {
        if (numbers[i] % 2 != 0) {
            sum += numbers[i];
            total ++;
        }
    }
    return sum / total;
}
long double Stats::avgFib() {
    long int total= 0;
    long int sum = 0;
    for ( unsigned int i = 0; i < numbers.size(); i++) {
       if (numbers[i] == ((numbers[i] -1) + (numbers[i]-2))) {
       if (numbers[i] == 2971215073) {
            sum += numbers[i];
            total ++;
            break;
        }
            sum += numbers[i];
            total ++;
        }
    }
    return sum / total;
}