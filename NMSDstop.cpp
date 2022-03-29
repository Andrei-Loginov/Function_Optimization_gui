#include "NMSDstop.h"
#include <iostream>

/** \file */

NMSDstop::NMSDstop()
{

}

NMSDstop::NMSDstop(size_t niter) : StopCriterion(niter){}

NMSDstop::NMSDstop(size_t niter, double epsi) : StopCriterion(niter), epsilon(epsi){

}

double NMSDstop::val_mean(NMStatus *status)noexcept {
    double sum = 0;
    for (size_t i = 0; i < status->get_npoints(); ++i)
        sum += status->get_value(i);
    return sum / status->get_npoints();
}

NMSDstop::NMSDstop(const NMSDstop& other) : StopCriterion(other), epsilon(other.epsilon){

}

NMSDstop::NMSDstop(NMSDstop&& other) : StopCriterion(other), epsilon(other.epsilon){
    other.epsilon = 0;
}

void NMSDstop::swap(NMSDstop& other) noexcept {
    StopCriterion::swap(other);
    std::swap(epsilon, other.epsilon);
}

NMSDstop& NMSDstop::operator=(NMSDstop other) noexcept{
    this->swap(other);
    return *this;
}

double NMSDstop::val_sd(NMStatus *status) noexcept {
    double mean = val_mean(status), sum = 0;
    for (size_t i = 0; i < status->get_npoints(); ++i)
        sum += pow(status->get_value(i) - mean, 2);
    return sum / status->get_npoints();
}

bool NMSDstop::criterion(MethodStatus *status){
    NMStatus* info = static_cast<NMStatus*>(status);
    if (!info) throw std::bad_cast();

    if (info->get_n_iter() > max_iter) return true;
    if (info->get_out_of_area_flg()) return true;
    if (info->get_npoints() == 0) throw std::invalid_argument("NMStatus::value has length NMStatus::get_n() = 0.");

    //std::cout << "Iteration " << status->get_n_iter() << "\n";
    if (val_sd(info) < epsilon || status->get_n_iter() > max_iter) {
       // std::cout << "SD = " << val_sd(info) << "\n";
        return true;
    }
    return false;
}
