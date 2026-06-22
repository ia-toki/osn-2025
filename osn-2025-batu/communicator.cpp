#include <bits/stdc++.h>
using namespace std;

void AC() {
  cerr << "AC" << endl;
  exit(0);
}

void OK(int score) {
  cerr << "OK" << endl;
  cerr << score << endl;
  exit(0);
}

void WA(string errorMsg="") {
  cerr << "WA" << endl;
  if (errorMsg != "") {
    // cerr << errorMsg << endl;
  }
  exit(0);
}

int main(int argc, char* argv[]) {
  int tc;
  ifstream tc_in(argv[1]);
  tc_in >> tc;

  int x = tc / 4, y = tc % 4;

  vector<vector<int>> grid = {
    {0, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 1, 0, 1},
    {0, 0, 1, 0},
  };

  auto outputCell = [&](int x, int y) {
    int t = grid[x][y];
    if (t == 0) {
      printf("ES\n");
    } else {
      printf("BATU\n");
    }
    fflush(stdout);
  };

  int Q;
  if (scanf("%d", &Q) != 1) WA("No Q given"); // No Q given

  if (Q > 256 || Q < 0) {
    WA();
  }

  outputCell(x, y);

  char dirs[10];
  for (int i = 0; i < Q; ++i) {
    if (scanf("%5s", dirs) != 1) WA("No move given"); // No move given
    if (strlen(dirs) != 1) WA("Not single char"); // Not a single char

    if (dirs[0] == 'U') {
      --x;
    } else if (dirs[0] == 'D') {
      ++x;
    } else if (dirs[0] == 'L') {
      --y;
    } else if (dirs[0] == 'R') {
      ++y;
    } else {
      WA("Invalid char"); // Invalid char
    }

    x %= 4; y %= 4;
    if (x < 0) x += 4;
    if (y < 0) y += 4;

    outputCell(x, y);
  }

  int conX, conY;
  if (scanf("%d %d", &conX, &conY) != 2) WA("No final guess"); // No final guess
  if (conX - 1 != tc / 4 || conY - 1 != tc % 4) {
    // cerr << conX << " " << conY << endl;
    WA("wrong guess"); // Wrong guess
  }

  char dummy[10];
  if (scanf("%5s", dummy) == 1) WA("Extra output"); // Extra output

  if (Q > 16) OK(10);
  if (Q >= 13) OK(20);
  if (Q >= 9) OK(30);
  if (Q >= 7) OK(40);
  if (Q >= 6) OK(55);
  if (Q >= 5) OK(70);
  if (Q >= 4) OK(85);
  if (Q <= 3) AC();
}
