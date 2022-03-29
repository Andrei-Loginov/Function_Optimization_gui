/** \file */
#pragma once
#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H
#include "SingletonGenerator.h"
#include "BoxArea.h"
#include "function.h"
#include "MethodStatus.h"
#include "StopCriterion.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <array>
#include <stdexcept>

#define eps 1e-5

/*!
 * \brief Класс Result содержит результаты работы метода оптимизации.
 *
 * \details Класс содержит точку минимума функции, ее значение в этой точке, число совершенных итераций, флаг выхода за пределы области.
 */
struct Result{
    std::vector<double> x; //!< Предполагаема точка минимума
    double y; //!< Значение функции в точке x
    size_t niter; //!< Число итераций
    std::vector<std::vector<double>> trajectory;
    bool out_of_area_flg = false; //!< Флаг выхода за пределы области
    //! Конструктор
    Result(std::vector<double> point, double value, size_t iterations,
           std::vector<std::vector<double>> x_trajectory, bool area_flg = false) : x(point),
                                                                                                y(value),
                                                                                                niter(iterations),
                                                                                                trajectory(x_trajectory),
                                                                                                out_of_area_flg(area_flg){}
    Result(){}
};

//! Оператор сложения векторов одинаковой длины.
std::vector<double> operator+(const std::vector<double>& lhs, const std::vector<double>& rhs);
//! Оператор вычетания векторов одинаковой длины.
std::vector<double> operator-(const std::vector<double>& lhs, const std::vector<double>& rhs);
//! Умножение вектора на константу
std::vector<double> operator*(const std::vector<double>& v, double a);
//! Умножение вектора на константу
std::vector<double> operator*(double a, const std::vector<double>& v);
//! Деление вектора на константу
std::vector<double> operator/(const std::vector<double>&v, double a);
//! Оператор вывода для вектора.
std::ostream& operator<<(std::ostream& stream, const std::vector<double>& v);


/*!
 * \brief Абстрактный базовый класс методов оптимизации
 */

class OptimizationMethod
{
protected:
    //! Конструктор по умолчанию
    OptimizationMethod();
    //! Конструктор копирования
    OptimizationMethod(const OptimizationMethod& other);
    //! Конструктор перемещения
    OptimizationMethod(OptimizationMethod&& other);
    //! Конструктор, задающий target_func_ = func, area_ = area, stop_crit_ = crit.
    OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit);

    //! Метод обмена.
    void swap(OptimizationMethod& other) noexcept;
    //! Указатель на функцию, для которой нужно найти минимум.
    Function *target_func_ = nullptr;
    //! Укзатель объект BoxArea, задающий границы области.
    BoxArea *area_ = nullptr;
    //! Указатель на критерий остановки.
    StopCriterion *stop_crit_ = nullptr;
    //! Размерность аргумента функции.
    size_t ndim_;
    //! Число совершенных итераций.
    size_t niter_ = 0;
    //! Предполагаемые точки мнимума на каждой итерации.
    std::vector<std::vector<double>> x_trajectory_;
    //bool out_of_range_flg_ = false;

    //! Метод создает объект MethodStatus, содержащий информацию о текущем состоянии алгоритма, и возвращает указатель на этот объект.
    virtual MethodStatus* get_status() const = 0;
    //! Шаг алгоритма оптимизации.
    virtual void make_iter() = 0;
    //! Метод, осуществляющий поиск точки минимума функции.
    void search();
    //! Метод, возвращающий число осущественных итераций.
    size_t get_n_iter() const;

public:
    //! Вызов функции search. Возвращает результат работы.
    virtual Result optimize() = 0;
    virtual Result optimize(const std::vector<double>& start) = 0;
    virtual ~OptimizationMethod() {x_trajectory_.clear();}
    dimension_limits area_limits(size_t ind) const;
    double eval_func(std::vector<double>) const;
    std::vector<double> get_x(size_t iter) const;
    //! Метод, моделирующий случайную величину, равномерно распределенную на интервале (lower, upper).
    double get_unif(double lower = 0, double upper = 1);
};

#endif // OPTIMIZATIONMETHOD_H
