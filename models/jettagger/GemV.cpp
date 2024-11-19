
template <int DX, int DY>
void GemV(IN_STREAM(DTYPE) *__restrict in, OUT_STREAM(DTYPE) *__restrict out)
{
    aie::vector<DTYPE, DX> vx = readincr_v<DX>(in);
    aie::accum<acc32, DY> acc (aie::zeros<acc32,DY>());

    auto m_citer = aie::cbegin_vector_circular<DY,DX*DY>((DTYPE *)matrix);

    for (int ix=0; ix<DX; ix++) 
        chess_prepare_for_pipelining
    {
        acc = aie::mac(acc,*m_citer++, vx[ix]);
    }
    
    aie::vector<DTYPE, DY> vy = acc.template to_vector<DTYPE>(0);
    writeincr(out, vy);
}