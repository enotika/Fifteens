#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_twTable_cellDoubleClicked(int row, int column);

    void on_restart_triggered();

    void on_newGame_triggered();

    void on_exit_triggered();
     void timerSlot();

private:
    Ui::MainWindow *ui;
    void showTable();
    QTableWidgetItem* tableCell = new QTableWidgetItem;
    QTableWidgetItem* emptyCell = new QTableWidgetItem;
    QTimer * timer;
    int ms, s, m;
};
#endif // MAINWINDOW_H
