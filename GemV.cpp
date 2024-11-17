

#include <adf.h>  
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include "matrix.h"

template <int DX, int DY>
void GemV(adf::input_buffer<DTYPE>& __restrict in, 
               adf::output_buffer<DTYPE>& __restrict out)
{
    const DTYPE* __restrict px=(DTYPE*)in.data();
    DTYPE* __restrict py=(DTYPE*)out.data();

    aie::vector<DTYPE, DX> vx = aie::load_v<DX>(px);
    aie::accum<acc48, DY> acc;
    
    aie::vector<DTYPE, DY> zeros = aie::zeros<DTYPE,DY>();
    acc.from_vector(zeros,0);
    
    DTYPE* mp = (DTYPE *) matrix;

    for (int ix=0; ix<DX; ix++) {
        aie::vector<DTYPE, DY> vm = aie::load_v<DY>(mp);
        acc =aie::mac(acc,vm,vx[ix]);

        mp += DX;
    }
    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0); // 0: shift
    aie::store_v(py, vy);
}