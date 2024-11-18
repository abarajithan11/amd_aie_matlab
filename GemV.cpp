#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

template <int DX, int DY>
void GemV(IN_STREAM(DTYPE) *__restrict in, OUT_STREAM(DTYPE) *__restrict out)
{
    // aie::vector<DTYPE, DX> vx;
    // aie::accum<acc48, DY> acc;
    // 
    // aie::vector<DTYPE, DY> zeros = aie::zeros<DTYPE,DY>();
    // acc.from_vector(zeros,0);
    // 
    // DTYPE* mp = (DTYPE *) matrix;
    // 
    // for (int ix=0; ix<DX; ix++) 
    // {
    //     aie::vector<DTYPE, DY> vm = aie::load_v<DY>(mp);
    //     acc = aie::mac(acc,vm, readincr_v<DX>(in));
    // 
    //     mp += DX;
    // }
    // aie::vector<DTYPE, DY> out_v = acc.template to_vector<DTYPE>(0);
    // writeincr(out, out_v);

    aie::vector<DTYPE, DX> v = readincr_v<DX>(in);

    writeincr(out, v);
}