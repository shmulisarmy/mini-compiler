#include "tokenizer.cpp"






struct Func_Param{
    string name;
    string type;
    vector<Token> default_value;
};




Func_Param get_func_param(const string code, int &i){
    Func_Param func_param;
    Token tempToken = get_next_token(code, i);
    #define next tempToken = get_next_token(code, i);
    cout << "tempToken: " << tempToken << endl;
    
    expect( code, tempToken, TokenType::IDENTIFIER, "Expected field name or field type", FILELINE ); 
    // assert(tempToken.type == TokenType::IDENTIFIER, "Expected field name or field type instead of " + tempToken.value);
    Token peeked = peek_next_token(code, i);
    if (peeked.type == TokenType::PUNCTUATION && peeked.value == "="){
        next
        func_param.name = tempToken.value;
        next
        func_param.default_value = {};
        while (tempToken.type != TokenType::PUNCTUATION || tempToken.value != ","){
            func_param.default_value.push_back(tempToken);
            next
        }
    } else {
        assert(built_in_types.find(tempToken.value) == built_in_types.end() && user_defined_types.find(tempToken.value) == user_defined_types.end(), "Expected func_param type");
        func_param.type = tempToken.value;

        next
        expect( code, tempToken, TokenType::IDENTIFIER, "Expected func_param name", FILELINE );
        func_param.name = tempToken.value;

        func_param.default_value = {};
        while (tempToken.type != TokenType::PUNCTUATION || tempToken.value != ","){
            func_param.default_value.push_back(tempToken);
            next
        }
    }
    return func_param;
}