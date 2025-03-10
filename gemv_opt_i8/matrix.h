#ifndef MATRIX_H
#define MATRIX_H

#define DTYPE int8
#define Q 4
#define MQS m[0],m[1],m[2],m[3]
#define CONCAT(a,b) a##b
#define IN_STREAM(T) CONCAT(input_stream_,T)
#define OUT_STREAM(T) CONCAT(output_stream_,T)

alignas(32) const int8 matrix[4][8][16] = {
    { // matrix block 0
        {1, 0, 0, 2, 2, 0, -2, -1, 0, -1, 0, -2, -1, 0, -2, 2},
        {1, 0, 0, 1, 0, -2, 1, 0, 1, 1, -2, 0, -2, -2, -1, 2},
        {2, 1, 0, 1, -1, -1, -1, -1, 1, 1, -1, -2, 0, 0, 0, 1},
        {0, -2, -2, -2, -1, 0, -2, 1, 0, 2, -1, 0, -2, -1, 1, -1},
        {0, 0, -1, 0, 1, 0, -2, -2, -1, -2, 0, -1, 0, -1, -1, 0},
        {1, 0, 2, 1, 2, 2, 0, -1, 0, 2, -1, -1, 2, -1, 2, -2},
        {1, 1, 1, -2, 2, 0, 1, 1, -2, -2, 2, 0, -2, -2, -1, 1},
        {-1, 1, 0, -1, 0, -2, -2, -2, 1, -1, -2, 1, 0, -2, 1, 0}
    },
    { // matrix block 1
        {1, 1, 1, -1, 2, -1, 1, -2, 0, -1, -1, -2, 1, 2, 2, -2},
        {0, 2, 2, -1, 2, -1, 1, -1, 1, -1, 1, 2, -1, 0, 2, 1},
        {2, -1, -1, 0, -1, -1, -2, 2, 1, -1, -1, -1, 1, -1, 0, -2},
        {0, 2, 1, 0, 2, 2, -2, 1, -1, -2, 2, 1, -2, -2, -2, 1},
        {1, -2, 1, -2, 2, 0, 1, -2, -2, -1, -1, 2, 0, 2, -1, 1},
        {2, -1, 1, 2, 1, 0, 1, -2, 2, 1, -2, -2, -2, -2, 1, 0},
        {-2, -2, 0, 1, 1, 2, -2, -2, 0, -1, 2, 2, -2, -2, -2, 2},
        {1, -1, -2, -2, 0, 0, 2, 2, 0, 0, -1, 2, 0, 2, 1, 0}
    },
    { // matrix block 2
        {0, 0, 2, -1, -1, 1, 0, 2, -1, 0, 2, 1, -1, -1, 1, 2},
        {2, 0, 0, -2, 1, 2, 1, 2, 1, -2, 2, 1, 0, -1, 2, -1},
        {-1, -1, 0, 0, 1, -1, 0, -2, -1, -2, -2, -1, 0, -2, 2, 0},
        {-2, 2, 1, -2, 2, 0, 1, 0, -1, -1, 1, 0, 1, -1, 0, 0},
        {0, 2, -1, 0, -2, -2, 1, 0, -1, -1, -1, 1, -1, 2, 2, -1},
        {2, -1, -2, 0, 2, -2, 2, 0, -2, 2, 2, 1, 2, -1, 2, -2},
        {2, 1, -2, 0, 2, -2, 1, -1, -1, -2, -2, 1, 1, -1, -1, 1},
        {-1, -1, 1, 2, 2, -1, 2, 1, 0, -2, -1, 2, 1, 2, -1, 2}
    },
    { // matrix block 3
        {-1, -2, -2, -1, -2, 1, 2, 0, 1, -1, -2, 0, -2, 2, 1, -1},
        {-2, -2, 0, -1, -1, 0, 1, -2, -2, -2, -2, 1, -2, 1, -2, -2},
        {-2, -1, 0, 2, 1, 2, -1, -2, -2, 1, -1, 1, 2, -1, -1, 0},
        {2, -2, 2, -1, 0, 0, -1, -1, -1, -1, 1, 1, -2, -1, 1, 0},
        {2, 2, 1, 1, 0, 0, 1, 2, 1, 1, -1, -1, -1, 2, 2, 1},
        {-2, 1, 0, 2, -2, -2, -2, -1, 2, 2, 1, 2, 2, 2, 1, -2},
        {1, 1, 1, 0, -1, -2, 2, 1, -1, 1, -2, 2, -2, -2, -2, -1},
        {1, -2, 0, -2, -2, 1, 0, -1, -2, 2, 0, 2, 1, 0, -2, 1}
    }
};

#endif // MATRIX_H
