#pragma once
#ifndef METHODSTATUS_H
#include <stddef.h>
#include <stdexcept>
#define METHODSTATUS_H
/** \file */

/**
 * @brief Класс MethodStatus является абстрактным базовым для классов, содержащих информацию о текущем состоянии объекта OptimizationMethod.
 */
class MethodStatus{
public:
    //!Конструктор по умолчанию
    MethodStatus();
    //!Конструктор копирования
    MethodStatus(const MethodStatus& other);
    //!noexcept Конструктор перемещения
    MethodStatus(MethodStatus&& other) noexcept;
    //! Конструктор, устанавливающий n_iter_ = niter
    MethodStatus(size_t niter);
    virtual ~MethodStatus() {}
    //!noexcept метод обмена
    void swap(MethodStatus& other) noexcept;
    //!noexcept оператор присваивания
    MethodStatus& operator=(MethodStatus other);
    //!Данный метод возвращает номер текущей итерации
    size_t get_n_iter() const;
protected:
    size_t n_iter_;//!< Номер текущей итерации OptimizationMethod


};

#endif // METHODSTATUS_H
