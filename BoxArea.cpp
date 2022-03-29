/** \file */
#include "BoxArea.h"
#include <iostream>

BoxArea::BoxArea(){
}

BoxArea::BoxArea(size_t ndim, const std::vector<dimension_limits>& lim) : ndim_(ndim), limits_(lim){
    assert(limits_.size() == ndim);
}

BoxArea::BoxArea(const BoxArea& other) : ndim_(other.ndim_), limits_(other.limits_){
}

BoxArea::BoxArea(BoxArea&& other) : ndim_(other.ndim_), limits_(other.limits_) {
    other.ndim_ = 0;
    other.limits_.resize(0);
}

BoxArea::~BoxArea(){
    limits_.clear();
}

bool BoxArea::is_in(const std::vector<double>& point) const{
    if (point.size() != limits_.size()) return false;
    //std::cout << "is_in()\n";
    for (size_t i = 0; i < point.size(); ++i)
        if (point[i] < limits_[i].lower || point[i] > limits_[i].upper) return false;
    return true;
}


void BoxArea::swap(BoxArea &other) noexcept {
    std::swap(ndim_, other.ndim_);
    std::swap(limits_, other.limits_);
}

void BoxSwap(BoxArea& lhs, BoxArea& rhs){
    lhs.swap(rhs);
}

BoxArea& BoxArea::operator=(BoxArea other) noexcept {
    this->swap(other);
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const BoxArea& area){
    stream << "Dimensions: " << area.ndim_ << "\n";
    for (const auto& iter : area.limits_)
        stream << iter.lower << " " << iter.upper << "\n";
    return stream;
}

size_t BoxArea::dim() const{
    return limits_.size();
}

dimension_limits BoxArea::get_limits(size_t i) const {
    return limits_[i];
}
