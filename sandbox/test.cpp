#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ifstream F("bc.pgm");
  if(!F.is_open()) {
    cout <<  "COULD NOT OPEN THE FILE" << endl;
  }

  string line;
  getline(F, line);
  cout << line << endl;

  return 0;
}
