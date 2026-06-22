#include <bits/stdc++.h>
using namespace std;

int main() {
  cout << 3 << endl;
  string s;
  cin >> s;
  
  int num = 0;
  if (s == "BATU") {
    num = 1;
  }

  for (int i = 0; i < 3; ++i) {
    cout << "RDR"[i] << endl;
    cin >> s;
    num *= 2;
    if (s == "BATU") {
      ++num;
    }
  }

  if (num == 2) {
    cout << "1 1" << endl;
  } else if (num == 5) {
    cout << "1 2" << endl;
  } else if (num == 11) {
    cout << "1 3" << endl;
  } else if (num == 3) {
    cout << "1 4" << endl;
  } else if (num == 14) {
    cout << "2 1" << endl;
  } else if (num == 9) {
    cout << "2 2" << endl;
  } else if (num == 7) {
    cout << "2 3" << endl;
  } else if (num == 15) {
    cout << "2 4" << endl;
  } else if (num == 13) {
    cout << "3 1" << endl;
  } else if (num == 10) {
    cout << "3 2" << endl;
  } else if (num == 4) {
    cout << "3 3" << endl;
  } else if (num == 12) {
    cout << "3 4" << endl;
  } else if (num == 1) {
    cout << "4 1" << endl;
  } else if (num == 6) {
    cout << "4 2" << endl;
  } else if (num == 8) {
    cout << "4 3" << endl;
  } else if (num == 0) {
    cout << "4 4" << endl;
  }
  return 0;
}
