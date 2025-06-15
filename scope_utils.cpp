#pragma once
#include "libs/common.cpp"
#include "token.cpp"

uint mark_next_end_of_scope(const vector<Token>& tokens, size_t startIndex, vector<char> scope_stack) {
    unordered_map<char, char> openerToCloser = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}
    };
    unordered_map<char, char> closerToOpener = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    for (size_t i = startIndex; i < tokens.size(); ++i) {
        const Token& token = tokens[i];

        if (token.type == TokenType::PUNCTUATION && token.value.size() == 1) {
            char ch = token.value[0];

            if (openerToCloser.find(ch) != openerToCloser.end()) {
                // Opening punctuation
                scope_stack.push_back(ch);
            } else if (closerToOpener.find(ch) != closerToOpener.end()) {
                // Closing punctuation
                if (scope_stack.empty()) {
                    assert(false, "Unexpected closing scope without opener");
                }
                char expected = closerToOpener[ch];
                if (scope_stack.back() != expected) {
                    assert(false, "Mismatched closing punctuation");
                }
                scope_stack.pop_back();

                if (scope_stack.empty()) {
                    return i; // This is the index where the scope closes
                }
            }
        }
    }

    assert(false, "Scope never closed");
    return tokens.size(); // fallback, should not happen
}