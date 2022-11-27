#include <iostream>
#include <armadillo>
#include "VirtualScanner.h"
#include "extend_armadillo.h"
#include "extend_boost.h"
using namespace std;
VirtualScanner::VirtualScanner(int num_crystal_axial_per_bucket, 
                             int num_crystal_transaxial_per_bucket,
                             int num_crystal_radial_per_bucket,
                             int num_bucket_in_axial,
                             int num_bucket_in_transaxial,
                             int num_bucket_in_radial)
{
    this->num_of_crystal_axial_per_bucket = num_crystal_axial_per_bucket;
    this->num_of_crystal_transaxial_per_bucket = num_crystal_transaxial_per_bucket;
    this->num_of_crystal_radial_per_bucket = num_crystal_radial_per_bucket;
    this->num_bucket_in_radial = num_bucket_in_radial;
    this->num_bucket_in_axial = num_bucket_in_axial;
    this->num_bucket_in_transaxial = num_bucket_in_transaxial;
}

VirtualScanner::~VirtualScanner()
{
}

void VirtualScanner::GenerateCrystalMap()
{
    arma::mat rot = arma::rot(0.0, 0.0, 0.0);
}
