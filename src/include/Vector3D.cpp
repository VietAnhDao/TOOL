#include "Vector3D.h"

Vector3D::Vector3D(double xIn, double yIn, double zIn)
{
    this->setx(xIn);
    this->sety(yIn);
    this->setz(zIn);
}

Vector3D::~Vector3D()
{
}

double Vector3D::getx(){
    return this->x;
}

double Vector3D::gety(){
    return this->y;
}

double Vector3D::getz(){
    return this->z;
}

double Vector3D::dot(Vector3D& vec){
    return this->getx() * vec.getx() + this->gety() * vec.gety() + this->getz() * vec.getz();
}