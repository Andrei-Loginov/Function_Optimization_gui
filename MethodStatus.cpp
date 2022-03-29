#include "MethodStatus.h"

/** \file */

MethodStatus::MethodStatus()
{

}

MethodStatus::MethodStatus(const MethodStatus& other) : n_iter_(other.n_iter_){

}

MethodStatus::MethodStatus(MethodStatus&& other) noexcept : n_iter_(other.n_iter_){
    other.n_iter_ = 0;
}

MethodStatus::MethodStatus(size_t niter) : n_iter_(niter){}



void MethodStatus::swap(MethodStatus& other) noexcept {
    std::swap(this->n_iter_, other.n_iter_);
}


MethodStatus& MethodStatus::operator=(MethodStatus other){
    this->swap(other);
    return *this;
}

size_t MethodStatus::get_n_iter() const {
    return n_iter_;
}
