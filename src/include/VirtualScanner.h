#include <iostream>
#include "extend_armadillo.h"
#include "extend_boost.h"
#ifndef VirtualScanner_H
#define VirtualScanner_H
class VirtualScanner
{
private:
    int num_axial_crystal_per_block;
    int num_transaxial_crystal_per_block;
    int num_radial_crystal_per_block;
    int num_axial_block_per_bucket;
    int num_transaxial_block_per_bucket;
    int num_radial_block_per_bucket;
    int num_axial_block;
    int num_transaxial_block;
    int num_axial_bucket;
    int num_transaxial_bucket;
    int num_radial_bucket;
    int num_sides;
    int num_detectors_per_ring;
    float effective_radius; // mm
    float average_doi; // mm
    float axial_crystal_spacing; // mm
    float transaxial_crystal_spacing;// mm
    float axial_block_spacing; // mm
    float transaxial_block_spacing;// mm
    float crystal_length; // mm
    float block_depth; // mm
    float intrinsic_azimuthal_tilt;
    boost::coord_map<float, int> euclid_to_det;
    boost::coord_map<int, float> det_to_euclid;
public:
    VirtualScanner(int num_axial_crystal_per_block, 
                    int num_axial_block_per_bucket,
                    int num_axial_bucket,
                    int num_transaxial_crystal_per_block,
                    int num_transaxial_block_per_bucket,
                    int num_transaxial_bucket,
                    int num_radial_crystal_per_block,
                    int num_radial_block_per_bucket,
                    int num_radial_bucket,
                    int num_axial_block,
                    int num_transaxial_blocks,
                    float effective_radius, // mm
                    float average_depth_of_interaction, // mm
                    float crystal_length, // mm
                    float axial_crystal_spacing, // mm
                    float transaxial_crystal_spacing,// mm
                    float crystal_depth, // mm
                    float block_length, // mm
                    float axial_block_spacing, // mm
                    float transaxial_block_spacing,// mm
                    float block_depth, // mm
                    int num_sides,
                    float intrinsic_azimuthal_tilt
                );
    ~VirtualScanner();
    void GenerateCrystalMap();
    void GenerateSiPMMap();
    arma::mat get_rotation_matrix(float alpha) const;
};

#endif