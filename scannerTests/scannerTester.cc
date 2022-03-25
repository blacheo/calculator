#include <iostream>
#include <string>
#include <vector>
#include "../scanner.h"
using namespace std;

int main () {
    string line;
    try {
    while (getline(cin, line)) {
        
        vector<Token> tokens = Token::scan(line);
        for (auto &t : tokens) {
                cout << t << endl;
            }
        
    }
    } catch (ScanningFailure &f) {
            cout << "ERROR:" << f.what() << endl;
            return 1;
        }
}