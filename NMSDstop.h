#pragma once
#ifndef NMSDSTOP_H
#define NMSDSTOP_H
#include "NMStatus.h"
#include "StopCriterion.h"
#include <cmath>
/** \file */
/**
 * @brief Класс NMSDstop реализует критерий остановки алгоритма Нелдера-Мида по стандартному отклонению значений функции в вершинах симплекса и по числу итераций.
 *
 */

class NMSDstop : public StopCriterion
{
    //! Вычисление среднего значения функции в вершинах симплекса.
    double val_mean(NMStatus* status) noexcept;
    //! Выборочное стандартное отклоненик значения функции в вершинах сиплекса.
    double val_sd(NMStatus*status) noexcept;
    //! Пороговое значение стандартного отклонения
    double epsilon = 1e-8;
    //! Метод swap this и other.
    void swap(NMSDstop& other) noexcept;
public:
    //! Конструктор по умолчанию
    NMSDstop();
    //! Конструктор, создающий критерий остановки только по числу итераций
    NMSDstop(size_t niter);
    //! Конструктор, устанавливающий максимальное число итераций и точность.
    NMSDstop(size_t niter, double epsi);
    //! Конструктор копирования
    NMSDstop(const NMSDstop& other);
    //! Конструктор перемещения
    NMSDstop(NMSDstop&& other);
    //! noexcept Оператор присваивания
    NMSDstop& operator=(NMSDstop other) noexcept;
    //! Критерий остановки
    bool criterion(MethodStatus* status);
};

#endif // NMSDSTOP_H
