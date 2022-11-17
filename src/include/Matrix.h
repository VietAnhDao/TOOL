#include <vector>
#ifndef Matrix_H
#define Matrix_H
class Matrix
{
private:
    double x, y, z
public:
    Matrix(double x, double y, double z);
    ~Matrix();
    double x();
    double y();
    double z();
};

inline Matrix operator+(Matrix& lhs, Matrix& rhs){
}

inline Matrix operator*(Matrix& lhs, Matrix& rhs){
}

inline Matrix operator*(Matrix& lhs, std::vector<T>& vec){

}

#endif