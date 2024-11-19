#ifndef MATRIX_H
#define MATRIX_H

#define DTYPE int8
#define CONCAT(a,b) a##b
#define IN_STREAM(T) CONCAT(input_stream_,T)
#define OUT_STREAM(T) CONCAT(output_stream_,T)

alignas (32) const int8 matrix[32][32] = {
    {2, -1, 2, 0, -1, 1, 0, 2, 1, 2, -2, 1, 2, 0, 1, 1, 0, -2, 1, -2, 0, -2, -2, 0, -1, 1, 1, -2, 0, 0, 2, 1},
    {2, -2, 2, 0, 2, -1, 0, 2, -1, 0, -1, 0, 2, -1, -1, 1, 1, 1, -2, 2, 1, -2, -2, -1, -1, -2, -2, -1, -1, 0, 1, 2},
    {-2, -2, 0, -2, 0, -1, 0, 0, -1, -2, 2, 1, 1, -2, 2, 1, 0, -1, 2, 1, -2, -2, 1, -2, 1, 1, -1, 1, -2, -2, -2, 0},
    {2, 2, -2, -1, 2, 0, -1, -2, 2, -1, 2, 1, -1, 1, -2, 2, 2, 0, 2, 2, 1, 1, -1, -1, -2, -2, -1, 1, 1, -2, 0, 1},
    {1, 1, -2, -2, -2, -2, 0, -1, -2, 2, -2, -2, 0, 1, 0, -1, -1, 1, 0, 0, -1, 0, 2, 2, -2, -2, 0, -2, 2, -1, -1, 2},
    {-2, -1, -1, 1, -1, -2, 0, 0, 2, -2, -1, -2, -2, 0, 0, 1, -2, -1, 2, 0, -2, -2, -2, -2, 1, 1, -2, -2, -2, -1, 0, 0},
    {-1, 2, 2, -1, -2, 2, 2, 0, 2, 0, 0, 2, 2, -2, 0, -1, -2, 1, 0, 2, 0, 2, 2, -1, 1, -1, 0, -2, -1, 1, -1, -2},
    {0, -2, -1, 0, -2, 2, 1, -1, 1, -2, 0, -2, 2, -1, 1, -2, -2, -1, -2, -1, -2, 1, 0, -2, 0, 1, -2, -2, -1, 2, 0, 2},
    {2, 0, 2, -2, 2, 0, 1, 1, -2, 2, 1, -2, 2, -2, -1, 1, 0, 1, -2, 0, -2, 1, 1, 0, 1, 1, -2, 0, -2, 2, -2, 1},
    {2, -1, -1, 1, 0, -2, -1, 1, -1, 1, 1, 0, -1, -1, 1, 0, 0, 1, 0, 2, -1, -2, 2, -2, 1, 0, 1, 1, 1, 0, -1, -1},
    {-2, 1, 2, -1, 0, -1, 2, -1, -1, 0, -1, 2, 0, 0, 0, 0, -1, 0, 1, 0, -2, 2, -1, 2, 1, 1, -1, 1, 0, -1, -2, 2},
    {2, 1, -1, 1, -2, -1, 0, -2, 1, 0, 0, 1, -2, 0, -2, 1, 1, -2, 2, 2, -2, 2, 0, -2, -1, -1, 1, 0, 2, 1, 2, -1},
    {2, -2, -2, 1, 2, 2, -1, -1, -2, -2, -2, -2, 0, 0, -2, 1, 1, -1, 1, 1, -2, 2, 0, -2, 1, 1, 2, -2, 0, 1, 1, 1},
    {0, 0, -1, 1, 1, -2, 2, -1, 1, 1, 2, -1, -1, 2, 1, -1, 1, 0, -1, 0, 1, 2, 1, -1, 0, 2, 0, 1, 1, 1, 2, 1},
    {2, 0, 1, 0, -1, -2, 2, 0, -2, -2, -2, 0, -2, 0, 0, 1, 2, -1, 0, -1, -1, 1, 2, 0, -1, 2, 1, -2, -2, 1, -2, -1},
    {-2, 1, 0, -2, 0, -2, 0, 0, 1, -2, -2, 2, -2, 2, -2, 0, 2, -2, -2, 1, 0, 0, -2, -2, -2, -2, 1, -2, -1, -2, 2, -2},
    {0, 1, -1, -1, 0, 1, 1, -2, 0, 0, -1, -2, 0, 1, -1, 2, -2, 2, -2, -2, 1, -2, -2, 2, 1, -1, 0, -2, -2, 1, 1, -2},
    {2, 1, 2, 2, -2, 1, 0, -1, 1, -2, -2, 2, -2, 2, 1, 2, -2, 0, -2, 1, 0, -1, -1, -1, -1, -1, 1, -2, 1, 0, 0, 0},
    {1, -1, 0, -2, -1, 1, -1, 2, 1, 2, 0, 1, 0, -1, -2, -1, 1, 2, 1, 1, 0, -2, -2, -1, 1, 1, -2, -2, 2, -1, 0, -2},
    {2, 1, 0, 2, -2, 0, -1, -2, 2, 2, -1, -1, 0, 1, 1, 1, -2, -1, 0, 1, 0, -2, 0, -2, 1, 0, 2, -2, -1, -2, -1, 1},
    {1, 1, 2, 0, -2, 0, 0, 2, 2, 1, 2, -2, 1, -1, -1, 0, 0, 1, -2, 2, -2, 2, -1, -1, -2, 1, -2, -1, 1, 2, 1, -1},
    {-2, -2, -1, 2, -1, -1, -1, 1, -1, -2, 2, 0, 1, 1, 2, 0, 0, -1, 0, 2, 0, -1, -2, -2, -2, -1, -1, -1, -1, -2, -1, 2},
    {2, -2, 1, -2, 0, 1, 2, 0, 1, 1, -2, 0, 1, 1, -1, 2, 2, 2, -2, 1, 2, -1, -1, 0, 0, -1, 1, -1, 0, -2, -2, 1},
    {2, 0, 1, 0, -2, -2, -2, 0, -2, 0, 1, -2, -2, -2, 1, -1, 0, 1, -2, 0, 2, -1, 2, 1, 0, -2, 0, -1, 2, 1, 1, 0},
    {1, 2, -1, -2, 2, 1, -1, -1, -2, 2, -1, 0, -2, -1, -2, -1, -1, -1, 2, 2, -1, 0, 1, 1, 2, 1, 1, 2, 0, 2, 1, -2},
    {1, -1, 0, 2, 2, -2, -2, 0, 1, 1, 0, -1, -1, -1, -1, -2, 1, -1, 0, 0, -1, 1, 0, -2, 1, -1, -1, 1, -1, 0, 1, 2},
    {1, 0, -2, -2, 0, -1, -1, 2, 0, 2, 0, -1, 0, 1, -2, 2, 1, 1, 2, -2, 0, -2, 2, -2, 1, -1, -1, 0, -1, 1, 1, -1},
    {-1, -1, -2, 1, 0, 1, 0, 0, 0, 0, 2, 0, 1, 2, 0, 1, 0, 2, 1, -2, 1, 2, -2, 1, -2, 0, -2, -2, 0, -2, 0, 2},
    {1, 1, 0, 2, -1, 1, -1, 0, 2, 0, 0, -1, 0, -1, 1, 0, -1, -1, 0, 2, 0, 0, 1, 2, -2, -1, 1, -1, 0, 2, -1, -1},
    {-2, -1, 1, 2, 2, -2, 2, -1, 1, 2, 2, -1, 2, 1, 0, 1, -2, 1, 2, 0, -1, 2, 1, 0, -2, 1, 0, -2, -1, 0, 2, -1},
    {1, 0, 2, -2, -1, 2, 0, 0, 1, -2, -1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, -1, 0, -2, 1, 0, 0, 2, 0, 1, -1, -2},
    {-2, 1, -2, -1, -2, 1, -2, 1, 2, -2, 1, -1, 2, -2, 1, 1, -1, 2, 2, -1, -2, 0, -2, 2, 2, -2, 1, 1, 1, -2, 2, 1}
};

#endif // MATRIX_H