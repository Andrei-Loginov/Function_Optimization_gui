#pragma once
#ifndef FUNCTIONPLOT_H
#define FUNCTIONPLOT_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include "StohasticOptimization.h"
#include "NelderMead.h"

class FunctionPlot : public QLabel{
public:
    FunctionPlot(OptimizationMethod* optim, bool is_nm);


protected:
    void mousePressEvent(QMouseEvent *event);

private:
    OptimizationMethod *optim_ = nullptr;

    Result res_;
    QImage *img = nullptr;
    QPixmap mainFrame;
    std::vector<std::vector<double>> grid;
    int width = 960, height = 960;
    std::vector<std::vector<double>> fun_value;
    bool isNM;

    void count_fn();
    void drawPlot();
    std::pair<double, double> fun_min_max();
    int x_to_idx(double x);
    int y_to_idx(double y);

};

#endif // FUNCTIONPLOT_H
