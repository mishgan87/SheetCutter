#include "rectd.h"

RectD::RectD(int x, int y, int w, int h)
{
    width = w;
    height = h;
    posX = x;
    posY = y;
    isAllocated = false;
}

QRectF RectD::ToQRectF()
{
    return QRectF((qreal)posX, (qreal)posY, (qreal)width, (qreal)height);
}

int RectD::getPosX() const
{
    return posX;
}

void RectD::setPosX(int newPosX)
{
    if (posX == newPosX)
        return;
    posX = newPosX;
}

int RectD::getPosY() const
{
    return posY;
}

void RectD::setPosY(int newPosY)
{
    if (posY == newPosY)
        return;
    posY = newPosY;
}

int RectD::getWidth() const
{
    return width;
}

void RectD::setWidth(int newWidth)
{
    if (width == newWidth)
        return;
    width = newWidth;
}

int RectD::getHeight() const
{
    return height;
}

void RectD::setHeight(int newHeight)
{
    if (height == newHeight)
        return;
    height = newHeight;
}

bool RectD::IsAllocated() const
{
    return isAllocated;
}

void RectD::setAllocated()
{
    if (isAllocated)
        return;
    isAllocated = true;
}

void RectD::resetAllocated()
{
    if (!isAllocated)
        return;
    isAllocated = false;
}

void RectD::Flip()
{
    int tmp = width;
    width = height;
    height = tmp;
}
