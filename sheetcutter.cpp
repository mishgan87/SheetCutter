#include "sheetcutter.h"
#include "placementparams.h"

SheetCutter::SheetCutter(QObject *parent) : QObject(parent)
{
    height = DEFAULT_HEIGHT;
    width = DEFAULT_WIDTH;
}

SheetCutter::~SheetCutter()
{

}

int SheetCutter::SheetWidth()
{
    return width;
}

int SheetCutter::SheetHeight()
{
    return height;
}

void SheetCutter::ResizeSheet(int newWidth, int newHeight)
{
    if (width == newWidth && height == newHeight)
        return;
    width = newWidth;
    height = newHeight;
    CutSheet(true);
}

RectD *SheetCutter::AddRect(int w, int h)
{
    bool isSizeValid = w > 0 && h > 0 && w < width && h < height;
    if (isSizeValid)
    {
        rectsList.append(RectD(0, 0, w, h));
        CutSheet();
        return &rectsList.last();
    }
    return nullptr;
}

void SheetCutter::RemoveRect(RectD *rect)
{
    rectsList.removeAll(*rect);
    CutSheet();
}

void SheetCutter::Clear()
{
    rectsList.clear();
}

QList<QRectF> &SheetCutter::RectsDestination()
{
    return rectsDestinationList;
}

void SheetCutter::CutSheet(bool isResized)
{
    int maxHeight = 0;

    if (rectsList.empty())
    {
        if (isResized)
            emit refreshed();
        return;
    }

    QList<RectD> rectsListV;
    QList<RectD> rectsListH;

    foreach (RectD rect, rectsList)
    {
        rect.resetAllocated();
        RectD rectV = rect;
        if (rectV.getHeight() >= rectV.getWidth())
        {
            maxHeight += rectV.getHeight();
        }
        else
        {
            maxHeight += rectV.getWidth();
            rectV.Flip();
        }
        rectsListV.append(rectV);
        RectD rectH = rect;
        if((rectH.getWidth() < rectH.getHeight())&&(rectH.getHeight() <= width))
        {
            rectH.Flip();
        }
        rectsListH.append(rectH);
    }

    rectsDestinationList.clear();
    QList<QRectF> destListH;
    QList<QRectF> destListV;

    maxHeight = CalcMaxHeight(rectsList, &rectsDestinationList);
    int maxHeightH = CalcMaxHeight(rectsListH, &destListH);
    int maxHeightV = CalcMaxHeight(rectsListV, &destListV);

    if (maxHeight > maxHeightH)
    {
      maxHeight = maxHeightH;
      rectsDestinationList.clear();
      rectsDestinationList.append(destListH);
    }
    if (maxHeight > maxHeightV)
    {
      maxHeight = maxHeightV;
      rectsDestinationList.clear();
      rectsDestinationList.append(destListV);
    }

    emit refreshed();
    emit maxHeightChanged(maxHeight);
}

int SheetCutter::CalcMaxHeight(const QList<RectD> &rects, QList<QRectF> *destList)
{
    destList->clear();
    int maxHeight = rects.first().getHeight();
    QList<PlacementParams> floorList;
    floorList.append(PlacementParams(0, 0, rects.first().getHeight()));
    foreach (RectD rect, rects)
    {
        int FloorNumber = 0;
        for (; FloorNumber < floorList.size(); FloorNumber++)
        {
            if (rect.getWidth() <= width - floorList.at(FloorNumber).getWidth())
            {
                rect.setAllocated();
                break;
            }
        }

        if (!rect.IsAllocated())
        {
            maxHeight += rect.getHeight();
            floorList.append(PlacementParams(0, floorList.at(FloorNumber - 1).getHf(),  floorList.at(FloorNumber - 1).getHf() + rect.getHeight()));
        }

        RectD newRect = RectD(floorList.at(FloorNumber).getWidth(), floorList.at(FloorNumber).getHeight(), rect.getWidth(), rect.getHeight());
        floorList[FloorNumber].setWidth(floorList[FloorNumber].getWidth() + newRect.getWidth());
        destList->append(newRect.ToQRectF());
    }
    return maxHeight;
}



