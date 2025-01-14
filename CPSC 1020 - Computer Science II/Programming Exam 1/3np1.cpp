#include <iostream>
using namespace std;
int longestSequence(int max);
bool isOdd(int n);
int sumSeq3nPlus1(int n);
int len3nplus1(int n);
int longestSequence(int max);

bool isOdd(int n) {
  if (n % 2 != 0) {
    return true;
  }
  return false;
}

int len3nplus1(int n) {
  int s = 1;
  do {
    if (isOdd(n)) {
      n = (n * 3) + 1;
      s++;
    } else {
      n /= 2;
      s++;
    }
  } while (n > 1);
  return s;
}

int sumSeq3nPlus1(int n) {
  int sum = n;
  do {
    if (isOdd(n)) {
      n = (n * 3) + 1;
    } else {
      n /= 2;
    }
    sum += n;
  } while (n > 1);
  return sum;
}

int longestSequence(int max) {
  int s = 1;
  int previouS = 0;
  int longest = 0;
  int p = 1;
  for (; p < max; p++) {
    int n = p;
    s = 1;
    do {
      if (isOdd(n)) {
        n = (n * 3) + 1;
        s++;
      } else {
        n /= 2;
        s++;
      }
    } while (n > 1);

    if (s > previouS) {
      previouS = s;
      longest = p;
    }
  }
  return longest;
}