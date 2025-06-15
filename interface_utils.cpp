#include "token.cpp"







void expect(const string code, Token token, const TokenType type, const string message, const string file_and_line){
    if (token.type != type){
        token.display_highlighted_token(code);
        cout << "Expected: " << to_string(type) << " but got: " << to_string(token.type) << endl;
        cout << "token: " << token << endl;
        cout << file_and_line << endl;
        throw message;
    }
}