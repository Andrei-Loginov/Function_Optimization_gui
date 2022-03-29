#pragma once
#ifndef NMSTATUS_H
#define NMSTATUS_H
#include<vector>
#include "MethodStatus.h"
/** \file */
/*!
 * \brief Класс NMStatus содержит информацию о текщем состоянии NelderMead
 */

class NMStatus : public MethodStatus
{
    //! Значения функции в точках симплекса.
    const std::vector<double>* value;
    //! Метод swap с NMStatus& other.
    void swap(NMStatus& other) noexcept;
    //! Флаг выхода за пределы области.
    bool out_of_area_flg_ = false;
public:
    //! Конструтор по умолчанию.
    NMStatus();
    //! Конструктор копирования.
    NMStatus(const NMStatus& other);
    //! Конструктор перемещения.
    NMStatus(NMStatus&& other);
    //! Конструктор, задающий значения полей n_iter_, value, out_of_area_flg.
    NMStatus(size_t niter, const std::vector<double>* values, bool area_flg = false);
    //! Деструктор.
    ~NMStatus(){}
    //! noexcept оператор присваивания.
    NMStatus& operator=(NMStatus other) noexcept;
    //! Метод, вовзращающий значение функии в вершине симплекса с индекосм ind.
    double get_value(size_t ind);
    //! Геттер числа вершин в симплексе.
    size_t get_npoints() const noexcept;
    //! Геттер флага выхода за пределы области.
    bool get_out_of_area_flg() const;
};

#endif // NMSTATUS_H
