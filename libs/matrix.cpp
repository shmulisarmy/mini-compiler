#include <initializer_list>



template<int width, int height, typename T>
struct Matrix{
    T matrix[height*width];



    inline bool quick_out_of_bounds(int index){
        return index < 0 || index >= constexpr width*height;

    }
    inline T& access(int x, int y){
        if(quick_out_of_bounds(x, y)) throw "out of bounds";
        return matrix[y*width + x];
    }

    Matrix(std::initializer_list<std::initializer_list<T>> list){
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                access(x, y) = list[y][x];
            }
        }

    }
};
