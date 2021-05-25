#include <cmath>
#include "../include/Core"
#include "../include/Dense"
#include <iostream>

int main()
{

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a / b << std::endl;                             // a/b
    std::cout << std::sqrt(b) << std::endl;                      // √a
    std::cout << std::acos(-1) << std::endl;                     // arccos(−1)
    std::cout << std::sin(30.0 / 180.0 * acos(-1)) << std::endl; // sin(30)

    // Example of vector
    // 矩阵部分参考：https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
    Eigen::Vector3f w(1.0f, 0.0f, 0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i, j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;

    // matrix add i + j
    std::cout << "Example of matrix add\n";
    std::cout << i + j << std::endl;

    // matrix scalar multiply i * 2.0
    std::cout << "Example of matrix acalar multiply\n";
    std::cout << i * 2.0 << std::endl;

    // matrix multiply i * j
    std::cout << "Example of matrix multiply\n";
    std::cout << i * j << std::endl;

    // matrix multiply vector i * v
    std::cout << "Example of matrix multiply vector\n";
    std::cout << i * v << std::endl;

    // 给定一个点 P=(2,1), 将该点绕原点先逆时针旋转 45◦，再平移 (1,2), 计算出变换后点的坐标（要求用齐次坐标进行计算）。
    Eigen::Vector3d p(2.0, 1.0, 1.0);

    // 旋转部分
    // cosx -sinx
    // sinx cosx

    // 变换矩阵
    //  √2/2    -√2/2   1
    //  √2/2    √2/2    2
    //  0       0       1
    Eigen::Matrix3d matrix;
    matrix << 0.707, -0.707, 1.0, 0.707, 0.707, 2.0, 0.0, 0.0, 1.0;
    std::cout << "P(2,1) 变换后的结果为：\n";
    std::cout << matrix * p << std::endl;

    return 0;
}