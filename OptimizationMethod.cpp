#include "OptimizationMethod.h"

/** \file */

OptimizationMethod::OptimizationMethod(){
}

OptimizationMethod::OptimizationMethod(const OptimizationMethod& other) : target_func_(other.target_func_), area_(other.area_),
                                                                        stop_crit_(other.stop_crit_)
{
}

OptimizationMethod::OptimizationMethod(OptimizationMethod&& other) : target_func_(std::move(other.target_func_)),
                                                                     area_(std::move(other.area_)),
                                                                    stop_crit_(std::move(other.stop_crit_)),
                                                                    ndim_(other.ndim_)
{
    other.ndim_ = 0;
}

OptimizationMethod::OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit) : target_func_(func),
                                                                                             area_(area),
                                                                                             stop_crit_(crit),
                                                                                             ndim_(area_->dim()){
    if (target_func_->dim() != area->dim())
        throw std::invalid_argument("OptimizationMethod(Function*, BoxArea*, StopCriterion*): inequal number of dimensions.");
}

void OptimizationMethod::swap(OptimizationMethod& other) noexcept {
     std::swap(other.target_func_, target_func_);
     std::swap(area_, other.area_);
     std::swap(stop_crit_, other.stop_crit_);
     std::swap(ndim_, other.ndim_);
}


double OptimizationMethod::get_unif(double lower, double upper){
    std::uniform_real_distribution<double> unif_real(lower, upper);
    return unif_real(SingletonGenerator::get_mt());
}

void OptimizationMethod::search(){
    while (!stop_crit_->criterion(get_status())){
        make_iter();
        ++niter_;
    }
}

std::vector<double> operator+(const std::vector<double>& lhs, const std::vector<double>& rhs){
    if (lhs.size() != rhs.size())
        throw std::domain_error("Inequal sizes of vectors");
    std::vector<double> ans(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i)
        ans[i] = lhs[i] + rhs[i];
    return ans;
}

std::vector<double> operator-(const std::vector<double>& lhs, const std::vector<double>& rhs){
    if (lhs.size() != rhs.size())
        throw std::domain_error("Inequal sizes of vectors");
    std::vector<double> ans(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i)
        ans[i] = lhs[i] - rhs[i];
    return ans;
}

std::vector<double> operator*(const std::vector<double>& v, double a){
    std::vector<double> ans(v.size());
    for (size_t i = 0; i < ans.size(); ++i)
        ans[i] = v[i] * a;
    return ans;
}

std::vector<double> operator*(double a, const std::vector<double>& v){
    return v*a;
}

std::vector<double> operator/(const std::vector<double>& v, double a){
    if (fabs(a) < eps)
        throw std::domain_error("Division by zero");
    std::vector<double> ans(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        ans[i] = v[i] / a;
    return ans;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<double>& v){
    stream << "Vector of size " << v.size() << ": ";
    for (auto iter = v.begin(); iter != v.end(); ++iter)
        stream << *iter << " ";
    return stream;
}

size_t OptimizationMethod::get_n_iter() const{
    return niter_;
}

dimension_limits OptimizationMethod::area_limits(size_t ind) const{
    return area_->get_limits(ind);
}

double OptimizationMethod::eval_func(std::vector<double> x) const{
    return target_func_->eval(x);
}

std::vector<double> OptimizationMethod::get_x(size_t iter) const{
    if (iter > x_trajectory_.size())
        throw std::invalid_argument("Invalid index");
    return x_trajectory_[iter];
}
