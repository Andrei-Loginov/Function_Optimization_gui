#include "StohIterStop.h"

/** \file */

StohIterStop::StohIterStop(){

}

StohIterStop::StohIterStop(size_t max_iter, size_t max_after_improve) : StopCriterion(max_iter),
                                                                                max_iter_after_improvment(max_after_improve){
}

StohIterStop::StohIterStop(const StohIterStop& other) : StopCriterion(other),
                                                                    max_iter_after_improvment(other.max_iter_after_improvment){

}

StohIterStop::StohIterStop(StohIterStop&& other) : StopCriterion(other),
                                                               max_iter_after_improvment(other.max_iter_after_improvment){
    other.max_iter_after_improvment = 0;
}

void StohIterStop::swap(StohIterStop& other) noexcept {
    StopCriterion::swap(other);
    std::swap(max_iter_after_improvment, other.max_iter_after_improvment);
}

StohIterStop& StohIterStop::operator=(StohIterStop other) noexcept{
    this->swap(other);
    return *this;
}

bool StohIterStop::criterion(MethodStatus *status){
    StohStatus* info = static_cast<StohStatus*>(status);
    if (info->get_n_iter() > max_iter) return true;
    if (info->get_niter_after_improve() > max_iter_after_improvment) return true;
    return false;
}
