#include "NelderMead.h"
//#define debug_nm

/** \file */

bool comp_point_y(const point_y& left, const point_y& right){
    return (left.value < right.value);
}

NelderMead::NelderMead(){

}

NelderMead::NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
                       double alpha, double beta, double gamma,
                       const std::vector<std::vector<double>>& simplex) : OptimizationMethod(func, area, crit), simplex_(simplex),
                       simplex_y_(std::vector<double>(func->dim() + 1)),
                       alpha_(alpha), beta_(beta), gamma_(gamma), dim_(func->dim()){

    //assert(simplex_.size() ==0 || (simplex_.size() == area_->dim() + 1 && simplex_[0].size() == area_->dim()));
    simplex_fun_.resize(target_func_->dim() + 1);
    simplex_y_.resize(target_func_->dim() + 1);

}

NelderMead::NelderMead(const NelderMead& other) : OptimizationMethod(other), simplex_(other.simplex_),
                                                  simplex_fun_(other.simplex_fun_), simplex_y_(other.simplex_y_),
                                                  centroid_(other.centroid_),
                                                  alpha_(other.alpha_), beta_(other.beta_), gamma_(other.gamma_),
                                                  out_of_area_flg_(other.out_of_area_flg_), dim_(other.dim_){
}

NelderMead::NelderMead(NelderMead&& other) : OptimizationMethod(other), simplex_(std::move(other.simplex_)),
                                             simplex_fun_(std::move(other.simplex_fun_)),
                                             simplex_y_(std::move(other.simplex_y_)),
                                               centroid_(std::move(other.centroid_)),
                                               alpha_(other.alpha_), beta_(other.beta_), gamma_(other.gamma_),
                                                out_of_area_flg_(other.out_of_area_flg_), dim_(other.dim_) {
    other.alpha_ = 0;
    other.beta_ = 0;
    other.gamma_ = 0;
    other.out_of_area_flg_ = 0;
    other.dim_ = 0;
}

void NelderMead::swap(NelderMead &other) noexcept {
    OptimizationMethod::swap(other);
    std::swap(simplex_, other.simplex_);
    std::swap(simplex_fun_, other.simplex_fun_);
    std::swap(simplex_y_, other.simplex_y_);
    std::swap(centroid_, other.centroid_);
    std::swap(alpha_, other.alpha_);
    std::swap(beta_, other.beta_);
    std::swap(gamma_, other.gamma_);
    std::swap(out_of_area_flg_, other.out_of_area_flg_);
    std::swap(dim_, other.dim_);
}

NelderMead& NelderMead::operator=(NelderMead other) noexcept {
    this->swap(other);
    return *this;
}

void NelderMead::init_simplex(){
    simplex_.resize(ndim_ + 1);
    for (size_t i = 0; i < ndim_ + 1; ++i){
        simplex_[i].resize(ndim_);
        for (size_t j = 0; j < ndim_; ++j)
            simplex_[i][j] =
                    get_unif(area_->get_limits(j).lower + 0.3 * (area_->get_limits(j).upper - area_->get_limits(j).lower),
                                      area_->get_limits(j).upper - 0.3 * (area_->get_limits(j).upper - area_->get_limits(j).lower));
    }
    niter_ = 0;
    x_trajectory_.resize(0);
}

Result NelderMead::optimize(){
    if (simplex_.size() == 0)
        init_simplex();
    eval_fun_simplex();
    //centroid_ = update_trajectory();
    search();
    return Result(x_trajectory_.back(), target_func_->eval(x_trajectory_.back()), niter_, x_trajectory_, out_of_area_flg_);
}

Result NelderMead::optimize(const std::vector<double>& start){
    simplex_.clear();
    niter_ = 0;
    x_trajectory_.clear();
    out_of_area_flg_ = false;
    simplex_.resize(dim_ + 1);
    for (size_t i = 0; i < dim_ + 1; ++i){
        simplex_[i].resize(dim_);
        for (size_t j = 0; j < dim_; ++j){
            double min = area_->get_limits(j).lower, max = area_->get_limits(j).upper;
            double delta = max - min;
            simplex_[i][j] = get_unif(std::max(start[j] - 0.1 * delta, min),
                                      std::min(start[j] + 0.1 * delta, max));
        }
    }
    return optimize();
}

void NelderMead::eval_fun_simplex(){
   for (size_t i = 0; i < simplex_.size(); ++i){
       simplex_fun_[i].idx = i;
       simplex_fun_[i].value = target_func_->eval(simplex_[i]);
       simplex_y_[i] = simplex_fun_[i].value;
   }
   std::sort(simplex_fun_.begin(), simplex_fun_.end(), comp_point_y);
}

void NelderMead::make_iter(){
    centroid_ = update_trajectory();
    std::vector<double> x_r, x_e, x_c;
    double f_r, f_e, f_c;
    size_t index_l = simplex_fun_[0].idx,
            index_h = simplex_fun_[simplex_fun_.size() - 1].idx;

    //reflection
    x_r = centroid_ + alpha_ * (centroid_ - simplex_[index_h]);
    if (!area_->is_in(x_r)){
        out_of_area_flg_ = true;
        return;
    }
    f_r = target_func_->eval(x_r);
    if (simplex_fun_[0].value <= f_r && f_r < simplex_fun_[simplex_fun_.size() - 2].value ){
        simplex_[index_h] = x_r;
        eval_fun_simplex();
        return;
    }

    if (f_r < simplex_fun_[0].value){
        x_e = centroid_ + gamma_ * (x_r - centroid_);
        if (!area_->is_in(x_e)){
            out_of_area_flg_ = true;
            return;
        }
        f_e = target_func_->eval(x_e);
        if (f_e < f_r) {
            simplex_[index_h] = x_e;
            eval_fun_simplex();
            return;
        } else {
            simplex_[index_h] = x_r;
            eval_fun_simplex();
            return;
        }
    }

    if (f_r < simplex_fun_[simplex_fun_.size() - 1].value){
        x_c = centroid_ + beta_ * (x_r - centroid_);
        if (!area_->is_in(x_c)){
            out_of_area_flg_ = true;
            return;
        }
        f_c = target_func_->eval(x_c);
        if (f_c < f_r){
            simplex_[index_h] = x_c;
            eval_fun_simplex();
            return;
        }
    } else { //f_r >= simplex_fun_[simplex_fun_.size() - 1].value
        x_c = centroid_ + beta_ * (simplex_[index_h] - centroid_);
        if (!area_->is_in(x_c)){
            out_of_area_flg_ = true;
            return;
        }
        f_c = target_func_->eval(x_c);
        if (f_c < simplex_fun_[simplex_fun_.size() - 1].value){
            simplex_[index_h] = x_c;
            eval_fun_simplex();
            return;
        }
    }

    //Shrink
    for (size_t i = 0; i < simplex_.size(); ++i){
        simplex_[i] = simplex_[i] + 0.5 * (simplex_[i] - simplex_[index_l]);
    }
    eval_fun_simplex();
    return;
}

MethodStatus* NelderMead::get_status() const{
    //std::cout << "\n";
    return new NMStatus(niter_, &simplex_y_, out_of_area_flg_);
}

std::vector<double> NelderMead::update_trajectory(){ //Центр масс всех, кроме точки с наибольшим значением функции
    std::vector<double> ans(target_func_->dim());
    for (size_t i = 0; i < simplex_.size() - 1; ++i){
        ans = ans + simplex_[simplex_fun_[i].idx];
    }
    ans = ans / target_func_->dim();
    x_trajectory_.push_back(ans);
    return ans;
}


