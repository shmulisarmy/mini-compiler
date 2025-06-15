#pragma once
#include "libs/common.cpp"
#include "libs/arena.cpp"
#include "token_types.cpp"
#include "token.cpp"
#include "unordered_set"
#include "types.cpp"
#include "scope_utils.cpp"
#include "interface_utils.cpp"




vector space_chars = {' ', '\t', '\n', '\r'};








string consume_chars_of(const string code, int &i, const vector<char> chars){
    int start = i;
    while (i < code.length() && find(chars.begin(), chars.end(), code[i]) != chars.end()){
        ++i;
    }
    return code.substr(start, i - start);
}


string consume_chars_until(const string code, int &i, const char looking_for_char){
    // until, including
    int start = i;
    while (i < code.length() && code[i] != looking_for_char){
        ++i;
    }
    ++i;
    return code.substr(start, (i-1) - start);
}



void consume_space_chars(const string code, int &i){
    consume_chars_of(code, i, space_chars);
}




const vector<char> quotes = {'"', '\'', '`'};



const unordered_set<string> keyword_set = {
    "if",
    "else",
    "while",
    "for",
    "do",
    "break",
    "continue",
    "return",
    "switch",
    "case",
    "default",
    "try",
    "catch",
    "finally",
    "throw",
    "synchronized",
    "native",
    "static",
    "class",
    "function",
};



Token get_next_token(const string code, int &i){
    if (i >= code.length()){
        return {TokenType::NOTHING, code.substr(i, 1), i};
    }
    consume_space_chars(code, i);


    if (code[i] == '/' && i + 1 < code.length() && code[i+1] == '/'){
        return {TokenType::COMMENT, consume_chars_until(code, i, '\n'), i};
    }


    for (auto quote : quotes){
        if (code[i] == quote){
            ++i;
            return {TokenType::STRING, consume_chars_until(code, i, quote), i};
            
        } 
    }


    for (auto category : TokenTypeValidCharsCategories){
        if (find(category.startingChars.begin(), category.startingChars.end(), code[i]) != category.startingChars.end()){
            auto grabbed = consume_chars_of(code, i, category.chars);
            if (category.type == TokenType::IDENTIFIER){
                if (keyword_set.find(grabbed) != keyword_set.end()){
                    return {TokenType::KEYWORD, grabbed, i};
                }
            }
            return {category.type, grabbed, i};
        }
    }
}


Token peek_next_token(const string code, int i){
    return get_next_token(code, i);
}








