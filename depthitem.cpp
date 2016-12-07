#include "depthitem.h"

bool DepthItem::isValid()
{

    if ( price >= 0.0 && volume >= 0.0 )
    {
        priceStr = QString::number(price);
        volumeStr = QString::number(volume);
        return true;
    }
    else
        return false;

}
