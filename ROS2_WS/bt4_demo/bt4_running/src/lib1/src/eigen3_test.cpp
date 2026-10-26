#include "lib1/eigen3_test.hpp"
#include "lib2/eigen3_test.hpp"

#include <Eigen/Dense>
#include <iostream>

namespace lib1 {

void run_eigen_vector_example()
{
    const Eigen::Vector3d vector(1.0, 2.0, 3.0);

    std::cout << "[lib1] Vector v = " << vector.transpose() << '\n';
    std::cout << "[lib1] Norm = " << vector.norm() << '\n';

    lib2::run_eigen_matrix_example();
}

}  // namespace lib1
