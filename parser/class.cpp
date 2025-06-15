#include "tokenizer.cpp"


struct Class_field{
    string name;
    string type;
    vector<Token> default_value;
};




Class_field get_class_field(const string code, int &i){
    Class_field field;
    Token tempToken = get_next_token(code, i);
    #define next tempToken = get_next_token(code, i);
    cout << "tempToken: " << tempToken << endl;
    
    expect( code, tempToken, TokenType::IDENTIFIER, "Expected field name or field type", FILELINE ); 
    // assert(tempToken.type == TokenType::IDENTIFIER, "Expected field name or field type instead of " + tempToken.value);
    Token peeked = peek_next_token(code, i);
    if (peeked.type == TokenType::PUNCTUATION && peeked.value == "="){
        next
        field.name = tempToken.value;
        next
        field.default_value = {};
        while (tempToken.type != TokenType::PUNCTUATION || tempToken.value != ";"){
            field.default_value.push_back(tempToken);
            next
        }
    } else {
        assert(built_in_types.find(tempToken.value) == built_in_types.end() && user_defined_types.find(tempToken.value) == user_defined_types.end(), "Expected field type");
        field.type = tempToken.value;

        next
        expect( code, tempToken, TokenType::IDENTIFIER, "Expected field name", FILELINE );
        field.name = tempToken.value;

        field.default_value = {};
        while (tempToken.type != TokenType::PUNCTUATION || tempToken.value != ";"){
            field.default_value.push_back(tempToken);
            next
        }
    }
    return field;
}







struct Class_Definition{
    string name;
    vector<Class_field> fields;


    friend std::ostream& operator<<(std::ostream& os, const Class_Definition& def) {
        os << "Class: " << def.name << "\n";
        os << "Fields:\n";
        for (const auto& field : def.fields) {
            os << "  " << field.name;
            if (!field.type.empty()) {
                os << " : " << field.type;
            }
            if (!field.default_value.empty()) {
                os << " = ";
                for (const auto& token : field.default_value) {
                    os << token.value << " ";
                }
            }
            os << "\n";
        }
        return os;
    }



    string to_c_code() {
        string result = "typedef struct {\n";
        for (const auto& field : fields) {
            result += "    ";
            if (!field.type.empty()) {
                // Map common types to C types
                if (field.type == "string") {
                    result += "char*";
                } else if (field.type == "int") {
                    result += "int";
                } else {
                    result += field.type; // Use type as-is for other types
                }
            }
            result += " " + field.name;
            if (!field.default_value.empty()) {
                result += " = ";
                for (const auto& token : field.default_value) {
                    result += token.value + " ";
                }
            }
            result += ";\n";
        }
        result += "} " + name + ";\n";
        return result;
    }
};


Class_Definition define_class(const string code, int &i){
    // only gonna do field stuff for now
    Class_Definition class_def;
    Token tempToken = get_next_token(code, i);
    #define next tempToken = get_next_token(code, i);
    assert(tempToken.type == TokenType::IDENTIFIER, "Expected class name, (cannot use keyword, etc.)");
    string className = tempToken.value;
    next
    assert(tempToken.type == TokenType::PUNCTUATION && tempToken.value == "{", "Expected { after classname");
    next
    while (peek_next_token(code, i).type != TokenType::PUNCTUATION || peek_next_token(code, i).value != "}"){ //@optimize
        Class_field field = get_class_field(code, i);
        class_def.fields.push_back(field);
    }
    return class_def;
}