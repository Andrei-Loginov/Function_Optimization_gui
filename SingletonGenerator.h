#pragma once
#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H
#include <random>
/** \file */

/*!
 * \brief Класс SingletonGenerator позволяет использовать один ГПСЧ во всей программе.
 */

class SingletonGenerator
{
    static std::mt19937 mersennetwister;
public:
    static std::mt19937& get_mt();
};

#endif // SINGLETONGENERATOR_H
