#include "StohStatus.h"

/** \file */

StohStatus::StohStatus() : MethodStatus() {}

StohStatus::StohStatus(size_t niter, size_t iter_after_improve) : MethodStatus(niter),
                                                                            niter_after_improve_(iter_after_improve){

}

StohStatus::StohStatus(StohStatus&& other) : MethodStatus(other), niter_after_improve_(other.niter_after_improve_){
}

StohStatus::StohStatus(const StohStatus& other) : MethodStatus(other), niter_after_improve_(other.niter_after_improve_){}

void StohStatus::swap(StohStatus& other) noexcept {
    MethodStatus::swap(other);
    std::swap(niter_after_improve_, other.niter_after_improve_);
}

StohStatus& StohStatus::operator=(StohStatus other) noexcept{
    this->swap(other);
    return *this;
}

size_t StohStatus::get_niter_after_improve() const {
    return niter_after_improve_;
}
