#include "Vector3D.h"
#include <vector>
#ifndef Matrix_H
#define Matrix_H
using namespace std;
class Matrix2D
{
private:
    vector<vector<float> > &matrix;
    int w;
    int h;
public:
    Matrix2D(int w, int h);
    ~Matrix2D();
    int get_width();
    int get_height();
};

inline Matrix2D operator+(Matrix2D& lhs, Matrix2D& rhs){

}

inline Matrix2D operator*(Matrix2D& lhs, Matrix2D& rhs){
}

inline Matrix2D operator*(Matrix2D& lhs, Vector3D vec){

}

#endif