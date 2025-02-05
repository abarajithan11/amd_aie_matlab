#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

// GemV:  clocks
// Main: 
// II  : 
// Lat : 


template <int DX, int DY>
void GemV(
    adf::input_buffer <DTYPE>& __restrict in, 
    adf::output_buffer<DTYPE>& __restrict out)
{
    aie::accum<acc48, DY> acc (aie::zeros<acc48,DY>());
    aie::vector<DTYPE,DY> m [Q];
    aie::vector<DTYPE,DX> vx = aie::load_v<DX>((DTYPE*)in.data());

    for (int i=0, id=0; i<DX; i+=Q, id+=DY) {
        for (int q=0; q<Q; q++)
            m[q] = aie::load_v<DY>((DTYPE*)matrix[q] + id);
        
        // https://www.xilinx.com/htmldocs/xilinx2022_2/aiengine_intrinsics/intrinsics/group__vect__mult__16x16.html#ga1e00ad6eedd92916e22e27f83abe5f01
        // int8: DY=16 lanes/rows/accs, DX=32 cols/clocks
        acc = mac16(
            acc,                // v16acc48

            concat(MQS),        // v64int8 // can concat 4 rows
            0,                  // xstart
            0x73727170,         // xoffsets
            4,                  // xstep (mul of 4)
            0x3120,             // xsquare 

            vx,                 // v32int8
            i,                  // zstart
            0x0,                // zoffsets
            2,                  // zstep (mul of 2)
            0x3120              // zsquare
        );
    }

    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0);
    aie::store_v((DTYPE*)out.data(), vy);
}
