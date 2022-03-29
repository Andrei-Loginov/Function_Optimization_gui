#pragma once
#ifndef STOPCRITERION_H
#include <vector>
#include <string>
#include "MethodStatus.h"
#define STOPCRITERION_H
/** \file */

class OptimizationMethod;

/*!
 * \brief Абстарктный класс критерия остановки метода оптимизации.
 */
class StopCriterion
{
protected:
    std::string name; //!< Название критерия.
    void swap(StopCriterion& other) noexcept; //!< Метод swap.
    StopCriterion(); //!< Конструктор по умолчанию.
    StopCriterion(size_t max_n_iter); //!< Конструктор, задающий максимальное число итераций.
    StopCriterion(const StopCriterion& other); //!< Конструктор копирования.
    StopCriterion(StopCriterion&& other) noexcept; //!< Конструктор перемещения.
    size_t max_iter = 100; //!< Максимальное число итераций.
public:
    //! Критерий остановки.
    virtual bool criterion(MethodStatus*) = 0;
    //! Оператор вызова критерия остановки.
    bool operator()(MethodStatus*);
    virtual ~StopCriterion(){}
};

#endif
