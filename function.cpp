/** \file */
#include "function.h"


double Beale(std::vector<double> x){
    double x_ = x[0], y_ = x[1];
    return (pow((1.5 - x_ + x_ * y_), 2) + pow(2.25 - x_ +x_ * pow(y_, 2), 2) + pow(2.625 - x_ + x_ * pow(y_, 3), 2));
}

double Bukin_N6(std::vector<double> x){  //https://youtu.be/Nm44Wpy7jlU
    double x_ = x[0], y_ = x[1];
    return(100 * sqrt(abs(y_ - 0.01 * pow(x_,2))) + 0.01 * (x_ + 10));
}

double Rosenbrock_2d(std::vector<double> x){
    return pow(1- x[0], 2) + 100 * pow(x[1] - pow(x[0],2), 2);
}

double Matyas(std::vector<double> x){
    return(0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1]);
}


Function::Function() {

}

Function::Function(int dim, double (*func)(std::vector<double>)) : ndim(dim), function(func){

}

Function::Function(const Function& other) : ndim(other.ndim), function(other.function){

}

Function::Function(Function&& other) noexcept : ndim(other.ndim), function(other.function){
    other.ndim = 0;
    other.function = nullptr;
}

double Function::eval(const std::vector<double>& args) const{
    return function(args);
}

double Function::operator()(const std::vector<double>& args) const{
    return eval(args);
}

void Function::swap(Function& other) noexcept{
    std::swap(ndim, other.ndim);
    std::swap(function, other.function);
}

Function& Function::operator=(Function other){
    this->swap(other);
    return *this;
}

size_t Function::dim() const {
    return ndim;
}

void Function::set_func(int new_dim, double (*new_func)(std::vector<double>)){
    ndim = new_dim;
    function = new_func;
}
