// Scanner for the calculator

// Currently accepts the following tokens
// NUMS (Negative and Positive Integers)
// PLUS
// MINUS
// STAR
// CARET (for exponents)
// LPAREN
// RPAREN
// ID (strings starting with a letter. Used for variables and functions)
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

enum class Symbol {NUM, PLUS, MINUS, STAR, CARET, LPAREN, RPAREN, ID};

class Token {
    public:
    
    Token(Symbol s, string lexeme);
    Symbol s;
    string lexeme;
   
    static vector<Token> scan(const string &stream); 
    private:
    friend ostream &operator<<(ostream &out, const Token &t);
};

class ScannerDFA {
    public:
    enum class State {START, FAIL, NUM, PLUS, MINUS, STAR, CARET, LPAREN, RPAREN, WHITESPACE, ID};
    static const set<State> acceptingStates;

    static State transition(State state, char nextChar);
    static bool accepting(State state);
    static Symbol stateToSymbol(State state);
};

class ScanningFailure {
    string message;

  public:
    ScanningFailure(string message);
    const string &what() const;
};