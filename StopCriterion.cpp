#include "StopCriterion.h"

/** \file */

StopCriterion::StopCriterion(){

}

StopCriterion::StopCriterion(size_t max_n_iter) : max_iter(max_n_iter){
}

StopCriterion::StopCriterion(const StopCriterion& other) : name(other.name){}

StopCriterion::StopCriterion(StopCriterion&& other) noexcept : name(std::move(other.name)){}

void StopCriterion::swap(StopCriterion& other) noexcept {
    std::swap(name, other.name);
}

bool StopCriterion::operator()(MethodStatus* method){
    return criterion(method);
}
