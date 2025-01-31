#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

// GemV: 44 clocks
// Main: 42
// II  : 87
// Lat : 23


template <int DX, int DY>
void GemV(
    adf::input_buffer <DTYPE>& __restrict in, 
    adf::output_buffer<DTYPE>& __restrict out)
{
    aie::accum<acc48, DY> acc (aie::zeros<acc48,DY>());
    aie::vector<DTYPE,DY> buf_mat0, buf_mat1;
    aie::vector<DTYPE,DX> vx = aie::load_v<DX>((DTYPE*)in.data());

    for (int i=0, id=0; i<DX; i+=2, id+=DY) {

        buf_mat0 = aie::load_v<DY>((DTYPE*)matrix_0 + id);
        buf_mat1 = aie::load_v<DY>((DTYPE*)matrix_1 + id);
        
        acc = mac16(
            acc,
            concat(buf_mat0, buf_mat1), 
            0,
            0x73727170, 
            0x77767574, 
            0x3120, 
            vx, 
            i,
            0x0,
            0x0,
            1
        );
    }

    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0);
    aie::store_v((DTYPE*)out.data(), vy);
}
