#include "scanner.h"
#include <ctype.h>

Token::Token(Symbol s, string lexeme) : s{s}, lexeme{lexeme} {}

vector<Token> Token::scan(const string &stream) {
    vector<Token> tokens;
    int length = stream.length();
    string lexeme;
    ScannerDFA::State state = ScannerDFA::State::START;
    for (int i = 0; i < length;) {
        if (ScannerDFA::transition(state, stream.at(i)) == ScannerDFA::State::FAIL) {
            if (ScannerDFA::accepting(state)) {
                tokens.emplace_back(ScannerDFA::stateToSymbol(state), lexeme);
                lexeme.clear();
                state = ScannerDFA::State::START;
                if (stream.at(i) == ' ') {
                    i++;
                }
            } else {
                throw ScanningFailure{"Not a token"};
            }
        }  else {
            state = ScannerDFA::transition(state, stream.at(i));
            lexeme += stream.at(i);
            i++;
        }
    }

    if (ScannerDFA::accepting(state)) {
        tokens.emplace_back(ScannerDFA::stateToSymbol(state), lexeme);
    } else {
        throw ScanningFailure{"Not a token"};
    }
    return tokens;
}

ScannerDFA::State ScannerDFA::transition(State state, char nextChar) {
    if (state == State::START) {
        if (isdigit(nextChar)) {
            return State::NUM;
        }
        if (isalpha(nextChar)) {
            return State::ID;
        }
        switch(nextChar) {
            case '+':
                return State::PLUS;
            case '-':
                return State::MINUS;
            case '^':
                return State::CARET;
            case '(':
                return State::LPAREN;
            case ')':
                return State::RPAREN;
            case '*':
                return State::STAR;
        }
    }
    if (state == State::NUM && isdigit(nextChar)) {
        return State::NUM;
    }
    if (state == State::ID && (isalpha(nextChar) || isdigit(nextChar))) {
        return State::ID;
    }
    
    return State::FAIL;
}

ostream & operator<<(ostream &out, const Token &t) {
    switch (t.s) {
        case Symbol::NUM:
            cout << "NUM";
            break;
        case Symbol::PLUS:
            cout << "PLUS";
            break;
        case Symbol::MINUS:
            cout << "MINUS";
            break;
        case Symbol::STAR:
            cout << "STAR";
            break;
        case Symbol::CARET:
            cout << "CARET";
            break;
        case Symbol::LPAREN:
            cout << "LPAREN";
            break;
        case Symbol::RPAREN:
            cout << "RPAREN";
            break;
        case Symbol::ID:
            cout << "ID";
            break;
    }
    cout << ' ' << t.lexeme;
    return out;
}   

const set<ScannerDFA::State> ScannerDFA::acceptingStates = {State::NUM, State::PLUS, State::MINUS,
 State::CARET, State::LPAREN, State::RPAREN, State::ID, State::STAR};
 

Symbol ScannerDFA::stateToSymbol(State s) {
    switch (s) {
        case State::CARET:
        return Symbol::CARET;
        case State::PLUS:
        return Symbol::PLUS;
        case State::MINUS:
        return Symbol::MINUS;
        case State::STAR:
        return Symbol::STAR;
        case State::LPAREN:
        return Symbol::LPAREN;
        case State::RPAREN:
        return Symbol::RPAREN;
        case State::NUM:
        return Symbol::NUM;
        case State::ID:
        return Symbol::ID;
    }
    throw ScanningFailure{"Failed"};
}

bool ScannerDFA::accepting(State s) {
    if (acceptingStates.count(s) == 1) {
        return true;
    }
    return false;
}

ScanningFailure::ScanningFailure(string message): message{move(message)} {}

const string &ScanningFailure::what() const{
    return message;
}