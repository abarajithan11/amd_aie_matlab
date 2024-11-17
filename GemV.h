
#include <adf.h>
#include "matrix.h"

template <int DX, int DY>
void GemV(adf::input_buffer<DTYPE>& __restrict in, 
               adf::output_buffer<DTYPE>& __restrict out);
