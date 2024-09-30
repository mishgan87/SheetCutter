#ifndef SHEETCUTTER_H
#define SHEETCUTTER_H

#include <placementparams.h>
#include <QObject>
#include <QRect>
#include <QSize>
#include <QString>
#include <rectd.h>

#define DEFAULT_WIDTH 286
#define DEFAULT_HEIGHT 15000

class SheetCutter : public QObject
{
    Q_OBJECT
public:
    explicit SheetCutter(QObject *parent = nullptr);
    ~SheetCutter();

    int SheetWidth();
    int SheetHeight();

    void ResizeSheet(int newWidth, int newHeight);

    RectD *AddRect(int w, int h);
    void RemoveRect(RectD *rect);
    void Clear();

    QList<QRectF> &RectsDestination();

signals:
    void refreshed();
    void maxHeightChanged(int);

private:
    int width;
    int height;
    QList<RectD> rectsList;
    QList<QRectF> rectsDestinationList;

    void CutSheet(bool isResized = false);
    int CalcMaxHeight(const QList<RectD> &rects, QList<QRectF> *destList);
};

#endif // SHEETCUTTER_H
