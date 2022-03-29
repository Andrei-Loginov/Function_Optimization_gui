#pragma once
#ifndef BOXAREA_H
#include <vector>
#include <cassert>
#include <fstream>
#define BOXAREA_H

/** \file */

struct dimension_limits{
    double lower = -1, upper = 1;
    dimension_limits() {}
    dimension_limits(double low, double up) : lower(low), upper(up) {}
    explicit dimension_limits(std::pair<double, double> lim) : lower(lim.first), upper(lim.second) {}
};

class BoxArea
{
protected:
    size_t ndim_ = 0;
    std::vector<dimension_limits> limits_;

public:
    BoxArea();
    BoxArea(size_t dim, const std::vector<dimension_limits>& lim);
    BoxArea(const BoxArea& other);
    BoxArea(BoxArea&& other);
    ~BoxArea();

    size_t dim() const;
    void swap(BoxArea& other) noexcept;
    BoxArea& operator=(BoxArea other) noexcept;
    bool is_in(const std::vector<double>& point) const;
    dimension_limits get_limits(size_t i) const;
    friend void BoxSwap(BoxArea& lhs, BoxArea& rhs);
    friend std::ostream& operator<<(std::ostream& stream, const BoxArea& area);

};

#endif // BOXAREA_H
