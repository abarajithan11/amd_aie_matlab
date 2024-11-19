#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

template <int DX, int DY>
void GemV(IN_STREAM(DTYPE) *__restrict in, OUT_STREAM(DTYPE) *__restrict out)
{
    aie::vector<DTYPE, DX> vx = readincr_v<DX>(in);
    aie::accum<acc32, DY> acc (aie::zeros<acc32,DY>());

    auto m_citer = aie::cbegin_vector_circular<DY,DX*DY>((DTYPE *)matrix);

    // DTYPE *mp = (DTYPE *) matrix;

    for (int ix=0; ix<DX; ix++) 
        chess_prepare_for_pipelining
    {
        // acc = aie::mac(acc,*m_citer++, (DTYPE)readincr(in));
        acc = aie::mac(acc,*m_citer++, vx[ix]);
        // aie::vector<DTYPE, DY> vm = aie::load_v<DY>(mp + ix*DY);
        // acc = mac16(acc,vm, 0, 0x73727170, 0x77767574, 0x3120, vx, ix, 0, 0, 1);
        // aie::vector<DTYPE, DY> vx2 = aie::broadcast<DTYPE, DY>(vx[ix]);
        // acc = mac (acc, vm, vx2);
    }
    
    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0);
    writeincr(out, vy);
}