//-----------------------------------------------------------------------------
template <typename T>
Tuple4<T>::Tuple4():
x_(0), y_(0), z_(0), w_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
template <typename T>
Tuple4<T>::Tuple4(T x, T y, T z, T w):
x_(x), y_(y), z_(z), w_(w)
{
    // empty
}

//-----------------------------------------------------------------------------
template <typename T>
void Tuple4<T>::clear()
{
    x_ = y_ = z_ = w_ = 0;
}


//-----------------------------------------------------------------------------
template <typename T>
void Tuple4<T>::set(T x, T y, T z, T w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}
