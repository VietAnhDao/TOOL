#ifndef VirtualScanner_H
#define VirtualScanner_H
class VirtualScanner
{
private:
    int num_of_crystal_axial_per_bucket;
    int num_of_crystal_transaxial_per_bucket;
    int num_of_crystal_radial_per_bucket;
    int num_bucket_in_axial;
    int num_bucket_in_transaxial;
    int num_bucket_in_radial;
    int num_sides;
public:
    VirtualScanner(int num_crystal_axial,
                 int num_crystal_transaxial,
                 int num_crystal_radial,
                 int num_bucket_in_axial,
                 int num_bucket_in_transaxial,
                 int num_bucket_in_radial);
    ~VirtualScanner();
    void GenerateCrystalMap();
};

#endif