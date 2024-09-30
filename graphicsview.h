#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "sheetcutter.h"

#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QScrollBar>
#include <QObject>
#include <QWidget>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent = nullptr);

    void FitToParent();
    void Draw(SheetCutter *cutter);

private:
    QGraphicsScene *scene;
    QGraphicsItemGroup *group;

    void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHICSVIEW_H
