#pragma once
#include "libs/common.cpp"

enum struct TokenType {
    COMMENT,
    IDENTIFIER,
    KEYWORD,
    PUNCTUATION,
    NUMBER,
    STRING,
    NOTHING
};

// Helper function to get string representation
inline std::string to_string(TokenType type) {
    switch (type) {
        case TokenType::COMMENT:      return "COMMENT";
        case TokenType::IDENTIFIER:   return "IDENTIFIER";
        case TokenType::KEYWORD:      return "KEYWORD";
        case TokenType::PUNCTUATION:  return "PUNCTUATION";
        case TokenType::NUMBER:       return "NUMBER";
        case TokenType::STRING:       return "STRING";
        case TokenType::NOTHING:      return "NOTHING";
        default:                      return "UNKNOWN";
    }
}



struct TokenTypeValidChars{
    const vector<char> startingChars;
    const vector<char> chars;
    TokenType type;
};



const vector<TokenTypeValidChars> TokenTypeValidCharsCategories = {
    {
        // IDENTIFIER start: a-z, A-Z, _
        {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
         '_'},
        // IDENTIFIER continue: a-z, A-Z, 0-9, _
        {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
         '0','1','2','3','4','5','6','7','8','9', '_'},
        TokenType::IDENTIFIER
    },
    {
        // NUMBER start: 0-9
        {'0','1','2','3','4','5','6','7','8','9'},
        // NUMBER continue: 0-9 and dot (.)
        {'0','1','2','3','4','5','6','7','8','9', '.'},
        TokenType::NUMBER
    },
    {
        // PUNCTUATION start/continue: all common punctuation marks
        {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
         ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '`', '{', '|', '}', '~'},
        {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
         ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '`', '{', '|', '}', '~'},
        TokenType::PUNCTUATION
    }
};