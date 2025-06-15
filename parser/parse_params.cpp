#pragma once
#include "../libs/common.cpp"
#include "../token_types.cpp"
#include "../token.cpp"
#include "../tokenizer.cpp"

vector<Token> get_tokens_till_unscoped_comma(const string code, int &i){
    vector<Token> tokens;
    vector<char> scope_stack;


    unordered_map<char, char> openerToCloser = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}
    };
    
    while (i < code.length()) {
        Token token = get_next_token(code, i);
        
        // Skip if we hit the end
        if (token.type == TokenType::NOTHING) {
            break;
        }
        
        // Track scopes
        if (token.type == TokenType::PUNCTUATION) {
            if (token.value == "(" || token.value == "[" || token.value == "{") {
                scope_stack.push_back(token.value[0]);
            } else if (token.value == ")" || token.value == "]" || token.value == "}") {
                assert(!scope_stack.empty(), "Unexpected closing scope without opener"); 
                assert(scope_stack.back() == openerToCloser[token.value[0]], "Mismatched closing punctuation");
                scope_stack.pop_back();
            } else if (token.value == "," && scope_stack.empty()) {
                // Found an unscoped comma - we're done
                break;
            }
        }
        
        // Add token to our list
        tokens.push_back(token);

        if (scope_stack.empty() && token.type == TokenType::PUNCTUATION && token.value == ",") {
            break;
        }
    }
    
    return tokens;
}