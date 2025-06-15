#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>   // for std::byte
#include <cstring>   // for std::memcpy
#include <algorithm>   // for std::max
#include "./common.cpp"   // for std::max


using namespace std;

// Strongly-typed arena index
template<typename T>
struct Arena_Index {
    int offset = -1;


    inline bool null_equiv() {
        return offset == -1;
    }
};


namespace Arena_Index_ns
{
    int Null_equiv = -1;

    template<typename T>
    Arena_Index<T> Null() {
        Arena_Index<T> out;
        out.offset = Null_equiv;
        return out;
    }

} // namespace Arena_Index









class Arena;
extern vector<Arena> ArenaPool;
extern vector<Arena*> ArenaInstances;










class Arena {
public:
    vector<std::byte> memory;
    int index_upto = 0;
    vector<std::function<void(const Arena* arena)>> on_clears;
    int arena_index;


    template<typename T>
    struct Full_Arena_Indexer {
        int offset;
        int arena_index;
        T* ptr() {
            return (T*)&ArenaInstances[arena_index]->memory[offset];
        }
    };

    static vector<Arena*> instances;
    Arena(int initial_size) {
        cout << "creating a new arena: " << initial_size << endl;
        memory.resize(initial_size);
        ArenaInstances.push_back(this);
        arena_index = ArenaInstances.size() - 1;
    }

    template<typename Type_to_allocate, typename... args>
    Arena_Index<Type_to_allocate> make(args... initializer_args) {
        int byte_count = sizeof(Type_to_allocate);
        
        if (index_upto + byte_count > memory.size()) {
            cout << "resizing" << endl;
            memory.resize(max((size_t)index_upto + byte_count, memory.size() * 2));
        }

        Arena_Index<Type_to_allocate> return_ptr{ index_upto };


        on_clears.push_back([return_ptr](const Arena* arena) {
            auto ptr = (Type_to_allocate*)&arena->memory[return_ptr.offset];
            ptr->~Type_to_allocate(); 
        });

        // std::memcpy(&memory[index_upto], &object, byte_count); //could lead to undefined behavior with c++ optimizations turned on bc it doesn't fully understand the kind of value that theres there
        Type_to_allocate* ptr = new (&memory[index_upto]) Type_to_allocate(initializer_args...);
        index_upto += byte_count;

        return return_ptr;
    }



    template<typename Type_to_allocate>
    Arena_Index<Type_to_allocate> alloc() {
        int byte_count = sizeof(Type_to_allocate);
        
        if (index_upto + byte_count > memory.size()) {
            cout << "resizing" << endl;
            memory.resize(max((size_t)index_upto + byte_count, memory.size() * 2));
        }

        Arena_Index<Type_to_allocate> return_ptr{ index_upto };


        on_clears.push_back([return_ptr](const Arena* arena) {
            auto ptr = (Type_to_allocate*)&arena->memory[return_ptr.offset];
            ptr->~Type_to_allocate(); 
        });

        this->index_upto += byte_count;

        return return_ptr;
    }

    template<typename Type_to_allocate>
    Full_Arena_Indexer<Type_to_allocate> alloc2() {
        int byte_count = sizeof(Type_to_allocate);
        
        if (index_upto + byte_count > memory.size()) {
            cout << "resizing" << endl;
            memory.resize(max((size_t)index_upto + byte_count, memory.size() * 2));
        }

        Full_Arena_Indexer<Type_to_allocate> return_ptr{ index_upto, this->arena_index };


        on_clears.push_back([return_ptr](const Arena* arena) {
            auto ptr = (Type_to_allocate*)&arena->memory[return_ptr.offset];
            ptr->~Type_to_allocate(); 
        });

        this->index_upto += byte_count;

        return return_ptr;
    }

    template<typename T>
    T& operator[](Arena_Index<T> index) {
        return *(T*)&(memory[index.offset]);
    }



    void done() {
        this->index_upto = 0;
        for (auto on_clear : on_clears) {
            on_clear(this);
        }
        on_clears.clear();

        ArenaPool.push_back(*this);

    }

    static Arena get(int initial_size = 10000) {
        if (ArenaPool.size() == 0) {
            return Arena(initial_size);
        } else {
            Arena last_arena = ArenaPool.back();
            ArenaPool.pop_back();
            return last_arena;
        }
    }

    static Arena get_with_initial_or_greater_size(int initial_size) {
        if (ArenaPool.size()) {
            for (auto arena: ArenaPool){
                if (arena.memory.capacity() >= initial_size){
                    return arena;
                }
            }
        }
            
        return Arena(initial_size);
    }
};

vector<Arena> ArenaPool;
vector<Arena*> ArenaInstances;







// class Person;
// template class Arena_Index<Person>;
// template class Arena::Full_Arena_Indexer<Person>;