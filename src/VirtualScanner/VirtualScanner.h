#include <unordered_map>
#include <tuple>
#ifndef VirtualScanner_H
#define VirtualScanner_H
class VirtualScanner
{
private:
    int number_of_crystal_axial;
    int number_of_crystal_transaxial;
    int number_of_crystal_radial;
    std::unordered_map<std::tuple<double, double, double>, std::tuple<int, int, int>> euclid_to_det_coord;
    std::unordered_map<std::tuple<int, int, int>, std::tuple<double, double, double>> det_to_euclid_coord;
public:
    VirtualScanner(int num_crystal_axial, int num_crystal_transaxial, int num_crystal_radial);
    ~VirtualScanner();
    void GenerateCrystalMap();
};

#endif