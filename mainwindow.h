#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <sheetcutter.h>
#include "graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int IntFromString(QString str)
    {
        bool ok;
        int num = str.toInt(&ok, 10);
        if (ok)
            return num;
        return 0;
    }

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonApply_clicked();
    void on_pushButtonDel_clicked();
    void on_maxHeightChanged(int);
    void on_cutterRefreshed();

private:
    Ui::MainWindow *ui;
    GraphicsView *graphicsView;
    SheetCutter *cutter;

};
#endif // MAINWINDOW_H
