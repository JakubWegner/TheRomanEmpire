#include "point.h"

CPoint::CPoint()
{
    x = y = 0;
}

CPoint::CPoint(int i)
{
    x = y = i;
}

CPoint::CPoint(int i, int i2)
{
    x = i;
    y = i2;
}
