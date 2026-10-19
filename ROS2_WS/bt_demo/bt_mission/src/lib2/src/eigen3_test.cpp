#include "lib2/eigen3_test.hpp"

#include <Eigen/Dense>
#include <iostream>

namespace lib2 {

void run_eigen_matrix_example()
{
    Eigen::Matrix2d matrix;
    matrix << 1.0, 2.0,
              3.0, 4.0;

    std::cout << "[lib2] Matrix m =\n" << matrix << '\n';
    std::cout << "[lib2] Determinant = " << matrix.determinant() << '\n';
}

}  // namespace lib2
