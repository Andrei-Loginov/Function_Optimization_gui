#pragma once
#ifndef STOHASTICOPTIMIZATION_H
#define STOHASTICOPTIMIZATION_H

#include "OptimizationMethod.h"
#include "StohIterStop.h"

/** \file */

/*!
 * \brief Класс StohasticOptimization содержит в себе реализацию случайного поиска точки минимума функции в области.
 */

class StohasticOptimization : public OptimizationMethod
{
protected:
    double p_; //!< Параметр, определяющий вероятность моделирования точки в $\delta$-окрестности $x_i$.
    double delta_; //! Радиус $\delta$-окрестности точки $x_i$.
    double curr_y_;//! Наименьшее значение функции, достигнутое к текущей итерации.
    std::vector<double> first_point_; //! Точка $x_0$.
    void make_iter(); //! Метод, осуществляющий 1 итерацию случайного поиска.
    size_t niter_after_improvment_ = 0; //! Число итераций после последнего уменьшения curr_y_.
    void swap(StohasticOptimization& other) noexcept;
public:
    //! Конструктор по умолчанию.
    StohasticOptimization();
    //! Конструктор копирования.
    StohasticOptimization(const StohasticOptimization& other);
    //! Конструктор перемещения.
    StohasticOptimization(StohasticOptimization&& other);
    //! Конструктор, задающий функцию, область, критерий остановки, параметр p_, delta_ и first_point_.
    StohasticOptimization(Function* func, BoxArea* area, StopCriterion* crit, double p = 0.5, double delta = 0.5,
                          const std::vector<double>& first_point = std::vector<double>());
    //! Деструктор.
    ~StohasticOptimization() {first_point_.clear();}

    //! Оператор присваивания.
    StohasticOptimization& operator=(StohasticOptimization other) noexcept;
    //!Сеттер начальной точки.
    bool set_first_point(const std::vector<double>& point);
    //! Метод, осуществляющий поиск точки минимума и вовращающий результат работы алгоритма.
    Result optimize();
    Result optimize(const std::vector<double>& start);
    //! Метод генерирует объект типа StohStatus и возвращает указатель на него.
    MethodStatus* get_status() const;

};

#endif // STOHASTICOPTIMIZATION_H
