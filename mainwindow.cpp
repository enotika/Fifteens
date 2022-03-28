#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "puzzle.h"
#include <QMessageBox>
Puzzle pz;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ms = 0;
    s = 0;
    m = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1);
    ui->setupUi(this);
    for (auto i = 0; i < 4; i++) {
        ui -> twTable -> setColumnWidth(i, 70);
        ui -> twTable -> setRowHeight(i, 70);
    }
    ui->twTable->setEditTriggers(0);
    ui->lbCount->setStyleSheet("background-color: #ADFF2F");
    ui->lbCount->setAlignment(Qt::AlignCenter);
    ui->lbTime->setStyleSheet("background-color: #87CEEB");
    ui->lbTime->setAlignment(Qt::AlignCenter);
    ui->lbCount->setText(QString::number(pz.getCount()));
    ui->twTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    showTable();
}

void MainWindow::showTable()
{
    for (auto i = 0; i < 4; i++){
        for (auto j = 0; j < 4; j++){
           QTableWidgetItem* item = new QTableWidgetItem(*tableCell);
           item->setText(QString::number(pz.getItem(i, j)));
           if(pz.getItem(i, j) == 0){
               item->setText(" ");
           }
           ui->twTable->setItem(i, j, item);
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_twTable_cellDoubleClicked(int row, int column)
{
    pz.reCalc(row,column);
    showTable();
    if (pz.isFinished())
    {
        timer->stop();
        if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
            QApplication::quit();
        } else {
            ms = 0;
            s = 0;
            m = 0;
            timer->start(1);
            pz.startGame();
            showTable();
        }
    }
    ui->lbCount->setText(QString::number(pz.getCount()));
}

void MainWindow::on_restart_triggered()
{
    timer->stop();
    pz.restartGame();
    showTable();
    ms = 0;
    s = 0;
    m = 0;
    timer->start(1);
}

void MainWindow::on_newGame_triggered()
{
    timer->stop();
    pz.startGame();
    showTable();
    ms = 0;
    s = 0;
    m = 0;
    timer->start(1);
}

void MainWindow::on_exit_triggered()
{
    timer->stop();
    QApplication::quit();
}

void MainWindow::timerSlot()
{
    ms++;
    if(ms == 1000){
        ms = 0;
        s++;
    }
    if(s == 60){
        s = 0;
        m++;
    }
    ui->lbTime->setText(QString::number(m) + ":" + QString::number(s) + ":" + QString::number(ms));
}
