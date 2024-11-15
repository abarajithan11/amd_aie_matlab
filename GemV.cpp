

#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>


#define ACC_SHIFT 14

// Sine-Cosine values for a frequency shifting of fs/8
// alignas (32) int16_t  cos_sin[16] = 
// { One, 0, RS2, RS2, 0, One, -RS2, RS2, -One, 0, -RS2, -RS2, 0, -One, RS2, -RS2 };

alignas (32) int16_t matrix [8][8] = {
        {  7,   9,  -8,   9,   3,  -8,  -5,   1 },
        { 10,  10,  -7,  10,  10,   0,   6,  -8 },
        { -2,   9,   6,  10,   3, -10,   7,   9 },
        {  4,   5,   5,  -2,   3,  -7,   4, -10 },
        { -5, -10,  -8,   7,   4,  -4,   9, -10 },
        { -1,  -2,   6,   6,  -7,   0,  -1,   3 },
        {  4,   5,  -5,   4,   3,  -7,  -8,   0 },
        { 10,  -3,   2,  -6,   5,  -5,   0,   4 }
    };

template <int FRAME_LENGTH>
void GemV(adf::input_buffer<int16>& __restrict in, 
               adf::output_buffer<int16>& __restrict out)
{
    const int16* __restrict px=(int16*)in.data();
    int16* __restrict py=(int16*)out.data();

    aie::vector<int16, FRAME_LENGTH> vx = aie::load_v<FRAME_LENGTH>(px);
    aie::vector<int16, FRAME_LENGTH> vy;

    for (int n=0; n<FRAME_LENGTH; n++) {
        vy[n] = 0;

        for (int k=0; k<FRAME_LENGTH; k++)
            vy[n] = vy[n] + matrix[k][n] * vx[k];

    }

    aie::store_v(py, vy);
}