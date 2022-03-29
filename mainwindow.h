#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>

#include "function.h"
#include "BoxArea.h"
#include "NMSDstop.h"
#include "StohIterStop.h"
#include "StohasticOptimization.h"
#include "NelderMead.h"
#include "FunctionPlot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plotButton_clicked();


    void on_xLowerBox_valueChanged(double arg1);

    void on_xUpperBox_valueChanged(double arg1);

    void on_yLowerBox_valueChanged(double arg1);

    void on_rbRosenbrock_pressed();

    void on_rbBukin_pressed();

    void on_rbBeale_pressed();

    void on_rbMatyas_pressed();


    void on_epsilonBox_valueChanged(double arg1);

    void on_maxIterBox_valueChanged(int arg1);

    void on_maxIterAfterImproveBox_valueChanged(int arg1);

    void on_pBox_valueChanged(double arg1);

    void on_deltaBox_valueChanged(double arg1);

    void on_alphaBox_valueChanged(double arg1);

    void on_betaBox_valueChanged(double arg1);

    void on_gammaBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    double xLowerBound = -10, xUpperBound = 10, yLowerBound = -10, yUpperBound = 10;
    double alpha = 1, beta = 0.5, gamma = 2, delta = 0.2, p = 0.5, epsilon = 1e-7;
    size_t max_iter = 10000, max_iter_after = 1000;
    void limitsBoxUpdate();
    Function *f = nullptr;
    BoxArea *area = nullptr;
    StopCriterion* crit = nullptr;
    OptimizationMethod* optim = nullptr;
    std::vector<dimension_limits> limits;
    FunctionPlot *plot = nullptr;
};

#endif // MAINWINDOW_H
