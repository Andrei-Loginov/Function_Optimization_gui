#include "NMStatus.h"

/** \file */

NMStatus::NMStatus(){

}

NMStatus::NMStatus(const NMStatus& other) : MethodStatus(other), value(other.value){

}

NMStatus::NMStatus(size_t niter, const std::vector<double>* values, bool area_flg) : MethodStatus(niter), value(values),
                                                                                     out_of_area_flg_(area_flg){

}


void NMStatus::swap(NMStatus& other) noexcept{
    MethodStatus::swap(other);
    std::swap(value, other.value);
    std::swap(out_of_area_flg_, other.out_of_area_flg_);
}

NMStatus& NMStatus::operator=(NMStatus other) noexcept {
    this->swap(other);
    return *this;
}

double NMStatus::get_value(size_t ind){
    return value->at(ind);
}

size_t NMStatus::get_npoints() const noexcept{
    return value->size();
}

bool NMStatus::get_out_of_area_flg() const{
    return out_of_area_flg_;
}
