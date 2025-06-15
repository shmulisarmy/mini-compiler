#include "arena.cpp"






struct Node{
    char value;
    Arena_Index<Node> children[52];
    bool word_end;



    Node(char value): value(value) {
        for (int i = 0; i < 52; ++i){
            children[i].offset = Arena_Index_ns::Null_equiv;
        }
        word_end = false;
        
    }
};

struct Tree{
    Arena allocator = Arena::get();
    Arena_Index<Node> root;


    Tree(){
        root = allocator.alloc<Node>();
        allocator[this->root].word_end = false;
        for (int i = 0; i < 52; ++i){
            allocator[this->root].children[i].offset = Arena_Index_ns::Null_equiv;
        }
    }



    bool no_children(Arena_Index<Node> node){
        for (int i = 0; i < 52; ++i){
            if (!allocator[node].children[i].null_equiv()){
                return false;
            }
            // cout << "offset for " << i << " is " << allocator[node].children[i].offset << endl;
        }

        return true;
    }


    


    void insert(string word){
        Arena_Index<Node> current = this->root;
        for (auto c : word){
            if (this->allocator[current].children[c - 'a'].null_equiv()){
                this->allocator[current].children[c - 'a'] = allocator.alloc<Node>();
                new (&this->allocator[this->allocator[current].children[c - 'a']]) Node(c);
            }
            current = this->allocator[current].children[c - 'a'];
        }

        this->allocator[current].word_end = true;
    }

    bool contains(string word){
        Arena_Index<Node> current = this->root;
        for (auto c : word){
            if (this->allocator[current].children[c - 'a'].null_equiv()){
                return false;
            }
            current = this->allocator[current].children[c - 'a'];
        }

        return true;
    }

    bool is_word_end(string word){
        Arena_Index<Node> current = this->root;
        for (auto c : word){
            if (this->allocator[current].children[c - 'a'].null_equiv()){
                return false;
            }
            current = this->allocator[current].children[c - 'a'];
        }

        return this->allocator[current].word_end;
    }


    vector<string> get_words_by_longest(vector<char> letters){
        Arena_Index<Node> current = this->root;
        vector<string> results;
        vector<char> collected_word;

        for (auto c : letters){
            if (this->allocator[current].children[c - 'a'].null_equiv()){
                throw "word not found";
            }
            current = this->allocator[current].children[c - 'a'];
            collected_word.push_back(c);
            // 'this->no_children(current)' should never be true unless 'this->allocator[current].word_end' is 
            if (this->allocator[current].word_end && this->no_children(current)){
                results.push_back(string(collected_word.begin(), collected_word.end()));
                current = this->root;
            } else {
                cout << "hah" << endl;
            }
        }


        return results;

    }
};