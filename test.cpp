
#include "NumCpp.hpp"

#include <array>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>

struct Slicer{

  template<typename Op>
  void slicer_2d(std::vector<double> &ds, Op& fn, std::size_t from){
    nc::NdArray<double> ar{ds.data() + from, dims[0], dims[1], nc::PointerPolicy::SHELL};
    nc::NdArray<double> ar{ds.data() + from, dims[0], dims[1], nc::PointerPolicy::SHELL};
    fn(ar);
  }

  template<typename Op>
  void operator()(std::vector<double> & ds, Op fn){
    auto slice = dims[0] * dims[1];
    for(std::size_t k = 0; k < dims[2]; ++k){
      slicer_2d(ds, fn, k * slice);
    }
  }

  std::array<std::size_t, 3> dims;
};


int main(){
  std::vector<double> ds(27);
  for(std::size_t i = 0; i < ds.size(); ++i) ds[i] = i;

  Slicer{3,3,3}(ds, [](auto& ar){
      std::cout << ar << std::endl;
      ar+=1.;
  });

  assert(ds.front()==1);
  return 0;
}
