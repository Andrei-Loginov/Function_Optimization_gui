#pragma once
#ifndef STOHITERSTOP_H
#define STOHITERSTOP_H

#include "StopCriterion.h"
#include "StohStatus.h"

/** \file */

/*!
 * @brief Класс StohIterStop содержит в себе реализацию критерия остановки стохастического поиска по числу итераций с момента последнего улучшения.
 * Также осуществляется проверка общего числа итераций.
 */

class StohIterStop : public StopCriterion
{
protected:
    //! Максимальное число итераций после последнего улучшения.
    size_t max_iter_after_improvment = 10000;
public:
    //! Конструктор по умолчанию
    StohIterStop();
    //! Конструктор, задающий общее максимальное число итераций и максимальное число итераций после последнего улучшения.
    StohIterStop(size_t max_iter, size_t max_after_improve = 10000);
    //! Конструктор перемещения
    StohIterStop(StohIterStop&& other);
    //! Конструктор копирования
    StohIterStop(const StohIterStop& other);

    ~StohIterStop() {}
    //! Метод swap
    void swap(StohIterStop& other) noexcept;
    //! Оператор присваивания
    StohIterStop& operator=(StohIterStop other) noexcept;
    //! Критерий остановки
    bool criterion(MethodStatus* status);
};

#endif // STOHITERSTOP_H
