#include "tokenizer.cpp"
#include "parser.cpp"

int main(){

    string code = 
    "class Car{\n"
    "    int miles\n"
    "}"
    // "    function add(int a, int b){"
    // "        return a + b;"
    // "    }"
    // "    function say_hello(){"
    // "        print(\"Hello!\");"
    // "    }"
    "class Person{\n"
    "    Car car\n"
    "    string name\n"
    "    string email\n"
    "    int age = 90\n"
    "}";



    debug(code)


    int i = 0;







    while (i < code.length()){
        Token token = get_next_token(code, i);
        if (token.type == TokenType::KEYWORD && token.value == "class"){
            cout << "getting Class: " << endl;
            Class_Definition class_ = define_class(code, i);
            cout << "Class: " << class_ << endl;
            cout << "C Code: " << endl;
            cout << class_.to_c_code() << endl;
        }
    }





    

    
}