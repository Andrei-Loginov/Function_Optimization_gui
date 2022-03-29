#pragma once
#ifndef STOHSTATUS_H
#define STOHSTATUS_H

#include "MethodStatus.h"

/** \file */

/*!
 * \brief StohStaatus содержит информацию о текущем состоянии объекта StohasticOptimization для критерия остановки.
 */

class StohStatus : public MethodStatus
{
protected:
    //! Число итераций после последнего уменьшения значения функции.
    size_t niter_after_improve_ = 0;
    //! Swap noexcept.
    void swap(StohStatus& other) noexcept;
public:
    //! Конструктор по умолчанию.
    StohStatus();
    StohStatus(size_t niter, size_t iter_after_improve);
    //! Конструктор перемещения.
    StohStatus(StohStatus&& other);
    //! Конструктор копирования
    StohStatus(const StohStatus& other);
    ~StohStatus() {}
    //! Оператор присваивания noexcept.
    StohStatus& operator=(StohStatus other) noexcept;
    //! Геттер niter_after_improve_.
    size_t get_niter_after_improve() const;
};

#endif // STOHSTATUS_H
