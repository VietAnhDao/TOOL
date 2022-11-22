#include <iostream>
#include "VirtualScanner.h"
using namespace std;

VirtualScanner::VirtualScanner(int num_crystal_axial, int num_crystal_transaxial, int num_crystal_radial)
{
    this->number_of_crystal_axial = num_crystal_axial;
    this->number_of_crystal_transaxial = num_crystal_transaxial;
    this->number_of_crystal_radial = num_crystal_radial;
}

VirtualScanner::~VirtualScanner()
{
}

void VirtualScanner::GenerateCrystalMap()
{
    
}
