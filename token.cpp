#pragma once
#include "ostream"
#include "token_types.cpp"

struct Token{
    TokenType type;
    string value;
    int i;


    void display_highlighted_token(const string code){
        Loop(code.length(), i){
            if (i == this->i){
                for (int j = 0; j < this->value.length(); ++j){
                    cout << "\033[1;32m" << this->value[j] << "\033[0m";
                }
            }
            cout << code[i];
        }
        cout << endl;
    }
};


std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Token{type=" << to_string(token.type)
       << ", value=\"" << token.value 
       << "\", i=" << token.i << "}";
    return os;
}
