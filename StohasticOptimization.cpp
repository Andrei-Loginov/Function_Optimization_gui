#include "StohasticOptimization.h"

/** \file */

StohasticOptimization::StohasticOptimization() : OptimizationMethod() {}

StohasticOptimization::StohasticOptimization(const StohasticOptimization& other) : OptimizationMethod(other),
                                            p_(other.p_), delta_(other.delta_), curr_y_(other.curr_y_),
                                            first_point_(other.first_point_), niter_after_improvment_(other.niter_after_improvment_) {}

StohasticOptimization::StohasticOptimization(StohasticOptimization&& other) : OptimizationMethod(other),
                                            p_(other.p_), delta_(other.delta_), curr_y_(other.curr_y_),
                                            first_point_(std::move(other.first_point_)),
                                            niter_after_improvment_(other.niter_after_improvment_){
    other.p_ = 0;
    other.delta_ = 0;
    other.curr_y_ = 0;
    other.niter_after_improvment_ = 0;
}

void StohasticOptimization::swap(StohasticOptimization& other) noexcept {
    OptimizationMethod::swap(other);
    std::swap(p_, other.p_);
    std::swap(delta_, other.delta_);
    std::swap(curr_y_, other.curr_y_);
    std::swap(first_point_, other.first_point_);
    std::swap(niter_after_improvment_, other.niter_after_improvment_);
}

StohasticOptimization& StohasticOptimization::operator=(StohasticOptimization other) noexcept{
    this->swap(other);
    return *this;
}

StohasticOptimization::StohasticOptimization(Function* func, BoxArea* area, StopCriterion* crit, double p, double delta,
                                             const std::vector<double>& first_point) :
    OptimizationMethod(func, area, crit), p_(p), delta_(delta), first_point_(first_point){
    if (first_point_.size() && func->dim() != first_point_.size())
        throw std::invalid_argument(
     "StohasticOptimization(Function*, BoxArea*, StopCriterion*, double, double, const vector<double>&): inequal number of dimensions");
}



bool StohasticOptimization::set_first_point(const std::vector<double> &point){
    if (target_func_->dim() == point.size()){
        first_point_ = point;
        return true;
    }
    return false;
}

Result StohasticOptimization::optimize(){
    if (!first_point_.size()){
        first_point_.resize(ndim_);
        for (size_t i = 0; i < ndim_; ++i)
            first_point_[i] = get_unif(area_->get_limits(i).lower, area_->get_limits(i).upper);
    }
    x_trajectory_.push_back(first_point_);
    curr_y_ = target_func_->eval(x_trajectory_.back());
    search();
    return Result(x_trajectory_.back(), curr_y_, niter_, x_trajectory_);
}

void StohasticOptimization::make_iter(){
    std::vector<double> candidate(ndim_);
    std::vector<double> curr_x = x_trajectory_.back();
    if (get_unif(0, 1) > p_)
        for (size_t i = 0; i < ndim_; ++i)
            candidate[i] = get_unif(area_->get_limits(i).lower, area_->get_limits(i).upper);
    else {
        for (size_t i = 0; i < ndim_; ++i)
            candidate[i] = get_unif(std::max(curr_x[i] - delta_, area_->get_limits(i).lower),
                                    std::min(curr_x[i] + delta_, area_->get_limits(i).upper));
    }
    double candidate_y = target_func_->eval(candidate);
    if (candidate_y < curr_y_){
        curr_y_ = candidate_y;
        x_trajectory_.push_back(candidate);
    } else ++niter_after_improvment_;
}

Result StohasticOptimization::optimize(const std::vector<double>& start){
    x_trajectory_.clear();
    first_point_ = start;
    niter_ = 0;
    niter_after_improvment_ = 0;
    return optimize();
}

MethodStatus* StohasticOptimization::get_status() const {
    return new StohStatus(niter_, niter_after_improvment_);
}
