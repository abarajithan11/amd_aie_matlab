#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

template <int DX, int DY>
void GemV(IN_STREAM(DTYPE) *__restrict in, OUT_STREAM(DTYPE) *__restrict out)
{
    aie::vector<DTYPE, DX> vx = readincr_v<DX>(in);
    
    aie::accum<acc48, DY> acc;
    aie::vector<DTYPE, DY> zeros = aie::zeros<DTYPE,DY>();
    acc.from_vector(zeros,0);

    DTYPE* mp = (DTYPE *) matrix;

    for (int ix=0; ix<DX; ix++) 
        chess_prepare_for_pipelining
    {
        aie::vector<DTYPE, DY> vm = aie::load_v<DY>(mp);
        acc = aie::mac(acc,vm, vx[ix]);

        mp += DX;
    }
    
    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0);
    writeincr(out, vy);
}