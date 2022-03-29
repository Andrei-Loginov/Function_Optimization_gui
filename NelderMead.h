#pragma once
#ifndef NELDERMEAD_H
#define NELDERMEAD_H
#include "OptimizationMethod.h"
#include "NMStatus.h"
#include <algorithm>
/** \file */

//! Структура point_y позволяет осуществлять сотрировку вершин симплекса по значению функции в ней без перестановок самих координат точек.
struct point_y {
    double value;  //!< Значение функцци в вершине симплекса с индексом idx.
    size_t idx; //!< Индекс точки
};

//! Компаратор для point_y
bool comp_point_y(const point_y& left, const point_y& right);


/**
 * @brief Класс NelderMead содержит в себе реализацию алгоритма Нелдера-Мида поиска минимума функции, заданной объектом Function, в области
 * заданной объектом BoxArea.
 */

class NelderMead : public OptimizationMethod{
protected:
    std::vector<std::vector<double>> simplex_; //!< Точки симплекса
    std::vector<point_y> simplex_fun_; //!< Значения функции в вершинах симплекса и индексы точек.
    std::vector<double> simplex_y_;
    std::vector<double> centroid_; //!< Центр масс всех вершин симплекса, кроме той, что с наибольшим значением.
    double alpha_ = 1, beta_ = 0.5, gamma_ = 2; //!< Коэффициенты отражения, сжатия и растяжения.
    bool out_of_area_flg_ = false; //!< Флаг выхода за пределы области. В случае, если он принимает значение true, алгоритм останавливается.
    size_t dim_;

    void init_simplex(); //!< Инициализация симплекса случайными точками.
    void eval_fun_simplex(); //!< Вычисление значений фуннкции в вершинах симплекса.
    void sort_points_(); //!< Сортировка индексов вершин симплекса по значению функции в них.
    void make_iter(); //!< Метод, осуществляющий 1 итерацию алгоритма Нелдера-Мида.
    std::vector<double> update_trajectory();

    MethodStatus* get_status() const; //!< Метод, создающий указатель на объект типа MethodStatus (NMStatus), содержащий информацию о текущем состоянии алгоритма

public:
    //! Конструктор по умолчанию
    NelderMead();
    /**! Конструктор, задающий функцию, которую нужно оптимизировать, область, критерий остановки, коэффициенты сжатия, отражения, растяжения и начальный симплекс.
    *
    * Если simplex является пустым вектором, то симплекс инициализируется случайными точками.
    **/
    NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
               double alpha = 1, double beta = 0.5, double gamma = 2,
               const std::vector<std::vector<double>>& simplex = std::vector<std::vector<double>>());
    //! Констуктор перемещения
    NelderMead(NelderMead&& other);
    //! Конструктор копирования
    NelderMead(const NelderMead& other);
    //! Метод обмена noexcept
    void swap(NelderMead& other) noexcept;
    //! noexcept оператор присваивания
    NelderMead& operator=(NelderMead other) noexcept;
    //! Метод, осуществляющий поиск точки минимума и вовращающий результат работы алгоритма.
    Result optimize() override;
    Result optimize(const std::vector<double>& start) override;
};

#endif // NELDERMEAD_H
