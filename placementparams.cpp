#include "placementparams.h"

PlacementParams::PlacementParams(int w, int h, int _hf)
{
    width = w;
    height = h;
    hf = _hf;
}

int PlacementParams::getWidth() const
{
    return width;
}

void PlacementParams::setWidth(int newWidth)
{
    width = newWidth;
}

int PlacementParams::getHeight() const
{
    return height;
}

void PlacementParams::setHeight(int newHeight)
{
    height = newHeight;
}

int PlacementParams::getHf() const
{
    return hf;
}

void PlacementParams::setHf(int newHf)
{
    hf = newHf;
}
