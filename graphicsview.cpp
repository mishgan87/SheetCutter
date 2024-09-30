#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scene = new QGraphicsScene();
    this->setScene(scene);

    group = new QGraphicsItemGroup();
    scene->addItem(group);

    FitToParent();
}

void GraphicsView::FitToParent()
{
    this->setGeometry(parentWidget()->pos().x() + 5, parentWidget()->pos().y() + 5, parentWidget()->width() - 5, parentWidget()->height() - 5);
}

void GraphicsView::Draw(SheetCutter *cutter)
{
    foreach(QGraphicsItem *item, scene->items(group->boundingRect()))
    {
       if(item->group() == group )
       {
          delete item;
       }
    }

    QPen penBlack(Qt::black);
    penBlack.setStyle(Qt::SolidLine);

    QRectF sheetRect = QRectF(0, 0, cutter->SheetWidth(), cutter->SheetHeight());

    scene->setSceneRect(0, 0, cutter->SheetWidth(), cutter->SheetHeight());
    group->addToGroup(scene->addRect(sheetRect, penBlack));

    penBlack.setStyle(Qt::DashLine);

    foreach (QRectF rect, cutter->RectsDestination())
    {
        group->addToGroup(scene->addRect(rect, penBlack));
    }

    this->fitInView(sheetRect, Qt::KeepAspectRatioByExpanding);
    this->verticalScrollBar()->setSliderPosition(0);
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    //FitToParent();
}
