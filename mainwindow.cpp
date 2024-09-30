#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMap>
#include <QPainter>
#include <sheetcutter.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphicsView = new GraphicsView(ui->frame_2);

    cutter = new SheetCutter(this);

    connect(cutter, SIGNAL(refreshed()), this, SLOT(on_cutterRefreshed()));
    connect(cutter, SIGNAL(maxHeightChanged(int)), this, SLOT(on_maxHeightChanged(int)));

    connect(ui->pushButtonApply, SIGNAL(clicked()), ui->statusbar, SLOT(clearMessage()));

    ui->lineEditSheetHeight->setText(QString::number(cutter->SheetHeight() / 1000));
    ui->lineEditSheetWidth->setText(QString::number(cutter->SheetWidth()));

    int width = IntFromString(ui->lineEditSheetWidth->text());
    int height = IntFromString(ui->lineEditSheetHeight->text());

    cutter->ResizeSheet(width, height * 1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAdd_clicked()
{
    ui->statusbar->clearMessage();
    int width = IntFromString(ui->lineEditPieceWidth->text());
    int height = IntFromString(ui->lineEditPieceHeight->text());
    RectD *rect = cutter->AddRect(width, height);
    if (rect != nullptr)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText("Изделие " + ui->lineEditPieceWidth->text() + "x" + ui->lineEditPieceHeight->text());
    }
    else
    {
        ui->statusbar->showMessage("Некорректный размер изделия");
    }
}

void MainWindow::on_pushButtonApply_clicked()
{
    ui->statusbar->clearMessage();
    int width = IntFromString(ui->lineEditSheetWidth->text());
    int height = IntFromString(ui->lineEditSheetHeight->text());
    cutter->ResizeSheet(width, height * 1000);
}

void MainWindow::on_pushButtonDel_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
    cutter->Clear();

    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QStringList sizeList = ui->listWidget->item(i)->text().split(" ").last().split("x", QString::KeepEmptyParts);
        int width = IntFromString(sizeList[0]);
        int height = IntFromString(sizeList[1]);
        cutter->AddRect(width, height);

    }
}

void MainWindow::on_maxHeightChanged(int maxHeight)
{
    ui->statusbar->showMessage("Максимальный расход " + QString::number(maxHeight));
}

void MainWindow::on_cutterRefreshed()
{
    graphicsView->Draw(cutter);
}

