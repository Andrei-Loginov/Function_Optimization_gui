#pragma once
#ifndef FUNCTION_H
#include <vector>
#define FUNCTION_H


double Beale(std::vector<double> x);

double Bukin_N6(std::vector<double> x);

double Matyas(std::vector<double> x);

double Rosenbrock_2d(std::vector<double> x);


/** \file */

/*!
 * \brief Данный класс является оберткой для укзателя на вещественнозначную функцию, принимающую в качестве аргумента std::vector<double>.
 */

class Function
{
    int ndim = 0; //!< Размерность аргумента функции
    double (*function)(std::vector<double>) = nullptr; //!< Непосредственно функция

public:
    /*! Конструктор по умолчанию.*/
    Function();
    //! Конструктор, устанавливающий function = func размерности dim.
    Function(int dim, double (*func)(std::vector<double>));
    //! Конструктор копирования.
    Function(const Function& other);
    //! Конструктор перемещения.
    Function(Function&& other) noexcept;
    //! Оператор обмена.
    void swap(Function& other) noexcept;
    //! noexcept оператор присваивания.
    Function& operator=(Function other);
    //! Оператор вычисления значения функции в точке args.
    double operator()(const std::vector<double>& args) const;
    //! Метод вычисления значения функции в точке args.
    double eval(const std::vector<double>& args) const;
    //! Метод, присваивающий function функцию new_func размерности new_dim.
    void set_func(int new_dim, double (*new_func)(std::vector<double>));
    //! Метод, возвращающий размерность аргумента function.
    size_t dim() const;
};

#endif // FUNCTION_H
