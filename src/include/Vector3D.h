#ifndef Vector3D_H
#define Vector3D_H
class Vector3D
{
private:
    double x;
    double y;
    double z;
public:
    Vector3D(double xIn, double yIn, double zIn);
    ~Vector3D();

    double getx();
    double gety();
    double getz();

    void setx(double xIn){this->x = xIn;};
    void sety(double yIn){this->y = yIn;};
    void setz(double zIn){this->z = zIn;};

    double dot(Vector3D& vec);
};

inline Vector3D operator+(Vector3D& lhs, Vector3D& rhs){
    Vector3D temp(lhs.getx() + rhs.getx(), lhs.gety() + rhs.gety(), lhs.getx() + rhs.getx());
    return temp;
}

inline Vector3D operator*(double& lhs, Vector3D& rhs){
    Vector3D temp(lhs*rhs.getx(), lhs*rhs.gety(), lhs*rhs.getz());
    return temp;
}

#endif