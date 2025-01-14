#ifndef STATS_H_
#define STATS_H_
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Stats {
    private:
        vector<long int> numbers;
        string fileName;
    public: 
        Stats();
        Stats(string fileName);
        int capacity();
        int count();
        int countEven();
        int countOdd();
        int countFib();
        float avgAll();
        float avgEven();
        float avgOdd();
        long double avgFib();
};






#endif