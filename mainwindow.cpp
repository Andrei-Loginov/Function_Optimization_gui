#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->rbRosenbrock->setChecked(true);
    ui->rbStohastic->setChecked(true);

    ui->xUpperBox->setMinimum(-1000);
    ui->xLowerBox->setMinimum(-1000);
    ui->yUpperBox->setMinimum(-1000);
    ui->yLowerBox->setMinimum(-1000);

    ui->alphaBox->setMinimum(0.01);
    ui->betaBox->setMinimum(0.01);
    ui->betaBox->setMaximum(0.5);
    ui->gammaBox->setMinimum(1.01);
    ui->epsilonBox->setMinimum(1e-8);

    ui->alphaBox->setValue(1);
    ui->betaBox->setValue(0.5);
    ui->gammaBox->setValue(2);
    ui->epsilonBox->setValue(epsilon);


    ui->deltaBox->setMinimum(0.01);
    ui->deltaBox->setValue(delta);
    ui->pBox->setMinimum(0.01);
    ui->pBox->setMaximum(1);
    ui->pBox->setValue(p);

    ui->maxIterBox->setMinimum(100);
    ui->maxIterBox->setMaximum(100000);
    ui->maxIterAfterImproveBox->setMinimum(100);
    ui->maxIterAfterImproveBox->setMaximum(10000);

    ui->maxIterBox->setValue(int(max_iter));
    ui->maxIterAfterImproveBox->setValue(int(max_iter_after));

    limitsBoxUpdate();

    ui->fun0Box->setValue(1000);
    //scene = new QGraphicsScene(*this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (!f) delete f;
    if (!area) delete area;
    if (!crit) delete crit;
    if (!plot) delete plot;

}

void MainWindow::on_plotButton_clicked(){
    ui->fun0Box->setValue(Rosenbrock_2d({1, 1}));
    if (!f) delete f;
    if (ui->rbRosenbrock->isChecked()) {
        f = new Function(2, Rosenbrock_2d);
    } else if (ui->rbBukin->isChecked()){
        f = new Function(2, Bukin_N6);
    } else if (ui->rbMatyas->isChecked()){
        f = new Function(2, Matyas);
    } else if (ui->rbBeale->isChecked()){
        f = new Function(2, Beale);
    }

    if (!area) delete area;
    limits = {dimension_limits(xLowerBound, xUpperBound), dimension_limits(yLowerBound, yUpperBound)};
    area = new BoxArea(2, limits);

    if (!optim) delete optim;
    if (!crit) delete crit;
    if (!plot) delete plot;
    if (ui->rbNelderMead->isChecked()){
        crit = new NMSDstop(max_iter, epsilon);
        optim = new NelderMead(f, area, crit, alpha, beta, gamma, std::vector<std::vector<double>>(0));
        plot = new FunctionPlot(optim, true);
    } else {
        crit = new StohIterStop(max_iter, max_iter_after);
        optim = new StohasticOptimization(f, area, crit, p, delta, std::vector<double>(0));
        plot = new FunctionPlot(optim, false);
    }
    plot->show();

}

void MainWindow::on_xLowerBox_valueChanged(double newXLower){
    if (newXLower >= xUpperBound) {
        ui->xLowerBox->setValue(xLowerBound);
    } else {
        xLowerBound = newXLower;
    }
}

void MainWindow::on_xUpperBox_valueChanged(double newXUpper){
    if (newXUpper <= xLowerBound){
        ui->xUpperBox->setValue(xUpperBound);
    } else {
        xUpperBound = newXUpper;
    }
}

void MainWindow::on_yLowerBox_valueChanged(double newYLower){
    if (newYLower >= yUpperBound) {
            ui->yLowerBox->setValue(yLowerBound);
        } else {
            yLowerBound = newYLower;
        }
}

void MainWindow::on_rbRosenbrock_pressed()
{
    xLowerBound = -10;
    xUpperBound = 10;
    yLowerBound = -10;
    yUpperBound = 10;
    limitsBoxUpdate();

}

void MainWindow::limitsBoxUpdate(){
    ui->xLowerBox->setValue(xLowerBound);
    ui->yLowerBox->setValue(yLowerBound);
    ui->xUpperBox->setValue(xUpperBound);
    ui->yUpperBox->setValue(yUpperBound);
}

void MainWindow::on_rbBukin_pressed()
{
    xLowerBound = -15;
    xUpperBound = -5;
    yLowerBound = -3;
    yUpperBound = 3;
    limitsBoxUpdate();
}

void MainWindow::on_rbBeale_pressed()
{
    xLowerBound = -5;
    xUpperBound = 5;
    yLowerBound = -5;
    yUpperBound = 5;
    limitsBoxUpdate();
}

void MainWindow::on_rbMatyas_pressed()
{
    xLowerBound = -10;
    xUpperBound = 10;
    yLowerBound = -10;
    yUpperBound = 10;
    limitsBoxUpdate();
}


void MainWindow::on_epsilonBox_valueChanged(double newEps){
    epsilon = newEps * 1e-4;
}

void MainWindow::on_maxIterBox_valueChanged(int arg1)
{
    if (arg1 < 0)
        ui->maxIterBox->setValue(int(max_iter));
    else
        max_iter = size_t(arg1);
}

void MainWindow::on_maxIterAfterImproveBox_valueChanged(int arg1)
{
    if (arg1 < 0)
        ui->maxIterAfterImproveBox->setValue(int(max_iter_after));
    else
        max_iter_after = size_t(arg1);
}

void MainWindow::on_pBox_valueChanged(double arg1)
{
    if (arg1 > 1 || arg1 < 0)
        ui->pBox->setValue(p);
    else
        p = arg1;
}

void MainWindow::on_deltaBox_valueChanged(double arg1)
{
    if (arg1 < 0)
        ui->deltaBox->setValue(delta);
    else
        delta = arg1;
}



void MainWindow::on_alphaBox_valueChanged(double new_alpha){
    if (new_alpha <= 0)
        ui->alphaBox->setValue(alpha);
    else alpha = new_alpha;
}

void MainWindow::on_betaBox_valueChanged(double new_beta){
    if (new_beta <= 0 || new_beta > 0.5)
        ui->betaBox->setValue(beta);
    else
        beta = new_beta;
}

void MainWindow::on_gammaBox_valueChanged(double new_gamma){
    if (new_gamma <= 1)
        ui->gammaBox->setValue(gamma);
    else
        gamma = new_gamma;
}

