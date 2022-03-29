#include "FunctionPlot.h"

FunctionPlot::FunctionPlot(OptimizationMethod* optim, bool is_nm) : optim_(optim), isNM(is_nm){
    drawPlot();
}



void FunctionPlot::count_fn(){
    double max_x = optim_->area_limits(0).upper, min_x = optim_->area_limits(0).lower,
            max_y = optim_->area_limits(1).upper, min_y = optim_->area_limits(1).lower;
    double step_x = (max_x - min_x) / width, step_y = (max_y - min_y) / height;

    fun_value.clear();
    fun_value.resize(height);
    for (int i = 0; i < height; ++i) {
        fun_value[i].resize(width);
        for (int j = 0; j < width; ++j)
            fun_value[i][j] = optim_->eval_func({min_x + j * step_x, max_y - i * step_y});
    }

}

std::pair<double, double> FunctionPlot::fun_min_max(){
    if (!fun_value.size()) count_fn();
    double min = fun_value[0][0], max = fun_value[0][0];
    for (size_t i = 0; i < fun_value.size(); ++i)
        for (size_t j = 0; j < fun_value[i].size(); ++j){
            if (fun_value[i][j] < min) min = fun_value[i][j];
            if (fun_value[i][j] > max) max = fun_value[i][j];
        }
    return {min, max};
}

void FunctionPlot::drawPlot(){
    count_fn();
    std::pair<double, double> min_max = fun_min_max();

    if (img) delete img;
    img = new QImage(width, height, QImage::Format_RGB32);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < height; ++j){
            int intensity = int(256 * (fun_value[i][j] - min_max.first) / (min_max.second - min_max.first));
            img->setPixel(j, i, qRgb(intensity, intensity / 2, 70));
        }

    resize(width, height);
    mainFrame = QPixmap::fromImage(*img);
    this->setPixmap(mainFrame);
    this->show();
}

void FunctionPlot::mousePressEvent(QMouseEvent *event) {
    //QMessageBox::warning(this, "welcome", "clicked");
    double max_x = optim_->area_limits(0).upper, min_x = optim_->area_limits(0).lower,
            max_y = optim_->area_limits(1).upper, min_y = optim_->area_limits(1).lower;

    double x = event->pos().x() * (max_x - min_x) / width + min_x;
    double y = (1 - double(event->pos().y()) / height) * (max_y - min_y) + min_y;

    /*if (!isNM) {
        StohasticOptimization *optimizer = dynamic_cast<StohasticOptimization*>(optim_);
        res_ = optimizer->optimize({x, y});
    } else {
        NelderMead *optimizer = dynamic_cast<NelderMead*>(optim_);
        res_ = optimizer->optimize({x, y});
    }*/
    //QMessageBox::warning(this, "Info", "Before optimize");
    res_ = optim_->optimize({x, y});
    //QMessageBox::warning(this, "Info", "After optimize");
    QPixmap frame = mainFrame;
    QPainter p(&frame);
    p.setPen(Qt::green);


    //QMessageBox::warning(this, "Info", QString::number(res_.trajectory.size()) + " " + QString::number(int(res_.out_of_area_flg)));
    if (res_.out_of_area_flg) QMessageBox::warning(this, "Out of area", "Went out of area");
    for (size_t i = 0; i + 1 < res_.trajectory.size(); ++i){
        p.drawLine(x_to_idx(res_.trajectory[i][0]),
                   y_to_idx(res_.trajectory[i][1]),
                   x_to_idx(res_.trajectory[i + 1][0]),
                   y_to_idx(res_.trajectory[i+1][1]));
    }
    int iter = res_.trajectory.size();
    p.drawText(QPointF(x_to_idx(res_.trajectory[0][0]), y_to_idx(res_.trajectory[0][1])),
            "(" + QString::number(res_.trajectory[0][0]) + ", " + QString::number(res_.trajectory[0][1]) + ")");
    p.drawText(QPointF(x_to_idx(res_.trajectory[iter - 1][0]), y_to_idx(res_.trajectory[iter - 1][1])),
        "f(" + QString::number(res_.trajectory[0][0]) + ", " + QString::number(res_.trajectory[0][1]) + ") = " +
            QString::number(optim_->eval_func(res_.trajectory[iter - 1])));

    p.end();
    this->setPixmap(frame);
    this->show();
}


int FunctionPlot::x_to_idx(double x) {
    dimension_limits lim = optim_->area_limits(0);
    return (int(width * (x - lim.lower) / (lim.upper - lim.lower)));
}

int FunctionPlot::y_to_idx(double y) {
    dimension_limits lim = optim_->area_limits(1);
    return (height - int(height * (y - lim.lower) / (lim.upper - lim.lower)));
}

