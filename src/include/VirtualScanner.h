#include <unordered_map>
#include <armadillo>
#ifndef VirtualScanner_H
#define VirtualScanner_H
class VirtualScanner
{
private:
    int number_of_crystal_axial;
    int number_of_crystal_transaxial;
    int number_of_crystal_radial;
public:
    VirtualScanner(int num_crystal_axial, int num_crystal_transaxial, int num_crystal_radial);
    ~VirtualScanner();
    void GenerateCrystalMap();
};

#endif