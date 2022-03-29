#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Function ros2d(2, Rosenbrock_2d);
    std::vector<dimension_limits> lim = {dimension_limits(-10, 10), dimension_limits(-10, 10)};
    std::vector<std::vector<double>> init_simpx(0);
    NelderMead optimRos(&ros2d, new BoxArea(2, lim), new NMSDstop(100), 1, 0.5, 2, init_simpx);
    Result result = optimRos.optimize({3, 3});

    if (result.out_of_area_flg)
        std::cout << "The method was stopped becuase one of points has gone outside the area.";
    std::cout << "Iterations: " << result.niter << "\n";
    std::cout << "f(" << result.x[0] << ", " << result.x[1] << "\n";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
