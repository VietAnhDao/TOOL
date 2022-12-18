#include "VirtualScanner.h"
using namespace std;
typedef boost::tuple<int, int, int> det_pos;
VirtualScanner::VirtualScanner(int num_axial_crystal_per_block, 
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
                             )
{
    if(num_axial_bucket == 0 || num_transaxial_bucket == 0 || num_radial_bucket == 0
       || num_axial_crystal_per_block == 0 || num_radial_crystal_per_block == 0 || num_transaxial_crystal_per_block == 0
       || crystal_length == 0.0 || block_length == 0.0)
    {
        throw "num_crystal_axial_per_bucket,\n num_crystal_transaxial_per_bucket,\n num_crystal_radial_per_bucket,\n num_bucket_in_axial,\n num_bucket_in_transaxial,\n num_bucket_in_radial\n crystal_pitch\n block_pitch\n parameters for scanner cannot be zero";
    }
    this->num_axial_crystal_per_block = num_axial_crystal_per_block; // number of crystal in axial per block
    this->num_transaxial_crystal_per_block = num_transaxial_crystal_per_block; // number of crystal in transaxial per block
    this->num_radial_crystal_per_block = num_radial_crystal_per_block;// number of crystal in radial per block
    this->num_axial_block_per_bucket = num_axial_block_per_bucket;
    this->num_radial_block_per_bucket = num_radial_block_per_bucket;
    this->num_transaxial_block_per_bucket = num_transaxial_block_per_bucket;
    this->num_radial_bucket = num_radial_bucket; // number of block in radial
    this->num_axial_bucket = num_axial_bucket; // number of block in axial
    this->num_transaxial_bucket = num_transaxial_bucket; // number of block in transaxial
    this->effective_radius = effective_radius;
    this->average_doi = average_depth_of_interaction;
    this->axial_block_spacing = axial_block_spacing;
    this->transaxial_block_spacing = transaxial_block_spacing;
    this->axial_crystal_spacing = axial_crystal_spacing;
    this->transaxial_crystal_spacing = transaxial_crystal_spacing;
    this->crystal_length = crystal_length;
    this->block_depth = block_depth;
    this->num_sides = num_sides;
    this->num_axial_block = num_axial_block;
    this->num_transaxial_block = num_transaxial_blocks;
    this->num_detectors_per_ring = num_transaxial_crystal_per_block * num_transaxial_block;
    this->intrinsic_azimuthal_tilt = intrinsic_azimuthal_tilt;
}

VirtualScanner::~VirtualScanner()
{
}

arma::mat
VirtualScanner::get_rotation_matrix(float alpha) const
{
    arma::mat rot(3,3,arma::fill::zeros);
    rot(0,0) = 1.F;
    rot(0,1) = 0.F;
    rot(0,2) = 0.F;
    rot(1,0) = 0.F;
    rot(1,1) = std::cos(alpha);
    rot(1,2) = std::sin(alpha);
    rot(2,0) = 0.F;
    rot(2,1) = -1*std::sin(alpha);
    rot(2,2) = std::cos(alpha);
    return rot;
}

void VirtualScanner::GenerateCrystalMap()
{
	// local variables to describe scanner
    int num_axial_crystals_per_block = this->num_axial_crystal_per_block;
	int num_transaxial_crystals_per_block = this->num_transaxial_crystal_per_block;
	int num_transaxial_blocks_per_bucket = this->num_transaxial_block_per_bucket;
	int num_axial_blocks_per_bucket = this->num_axial_block_per_bucket;
    int num_axial_blocks = this->num_axial_block;
	int num_transaxial_buckets = this->num_transaxial_block/num_transaxial_blocks_per_bucket;
	int num_axial_buckets = num_axial_blocks/num_axial_blocks_per_bucket;
	int num_detectors_per_ring = this->num_detectors_per_ring;
	float axial_block_spacing = this->axial_block_spacing;
	float transaxial_block_spacing = this->transaxial_block_spacing;
	float axial_crystal_spacing = this->axial_crystal_spacing;
	float transaxial_crystal_spacing = this->transaxial_crystal_spacing;
    float intrinsic_azimuthal_tilt = this->intrinsic_azimuthal_tilt;
	boost::coord_map<int> cartesian_coord_map_given_detection_position_keys;
	/*Building starts from a bucket perpendicular to y axis, from its first crystal.
		see start_x*/

		//calculate start_point to build the map.

//    estimate the angle covered by half bucket, csi
    float csi=M_PI/num_transaxial_buckets;
    float trans_blocks_gap=transaxial_block_spacing-num_transaxial_crystals_per_block*transaxial_crystal_spacing;
    float ax_blocks_gap=axial_block_spacing-num_axial_crystals_per_block*axial_crystal_spacing;
    float csi_minus_csiGaps=csi-(csi/transaxial_block_spacing*2)*
            (transaxial_crystal_spacing/2+trans_blocks_gap);
//    distance between the center of the scannner and the first crystal in the bucket, r=Reffective/cos(csi)
    float r=this->effective_radius/cos(csi_minus_csiGaps);
    
	float start_z = -(axial_block_spacing*(num_axial_blocks_per_bucket)*num_axial_buckets
                       -axial_crystal_spacing - ax_blocks_gap
                       *(num_axial_blocks_per_bucket*num_axial_buckets-1))/2;
	float start_y = -1*this->effective_radius;
	float start_x = -1*r*sin(csi_minus_csiGaps);//(
//								((num_transaxial_blocks_per_bucket-1)/2.)*transaxial_block_spacing
//							+ ((num_transaxial_crystals_per_block-1)/2.)*transaxial_crystal_spacing
//											); //the first crystal in the bucket
    std::vector<float> temp_vec = {start_z, start_y, start_x};
    arma::vec3 start_point = arma::conv_to<arma::mat>::from(temp_vec);

	for (int ax_bucket_num=0; ax_bucket_num<num_axial_buckets; ++ax_bucket_num)
		for (int ax_block_num=0; ax_block_num<num_axial_blocks; ++ax_block_num)
			for (int ax_crys_num=0; ax_crys_num<num_axial_crystals_per_block; ++ax_crys_num)
				for (int trans_bucket_num=0; trans_bucket_num<num_transaxial_buckets; ++trans_bucket_num)
					for (int trans_block_num=0; trans_block_num<num_transaxial_blocks_per_bucket; ++trans_block_num)
						for (int trans_crys_num=0; trans_crys_num<num_transaxial_crystals_per_block; ++trans_crys_num)
	{
		// calculate detection position for a given detector
		// note: in STIR convention, crystal(0,0,0) corresponds to card_coord(z=0,y=-r,x=0)
		int tangential_coord;
			tangential_coord = trans_bucket_num*num_transaxial_blocks_per_bucket*num_transaxial_crystals_per_block
														+ trans_block_num*num_transaxial_crystals_per_block
														+ trans_crys_num;
		
		if (tangential_coord<0)
					tangential_coord += num_detectors_per_ring;

		int axial_coord = ax_bucket_num*num_axial_blocks_per_bucket*num_axial_crystals_per_block
														+ ax_block_num*num_axial_crystals_per_block 
														+ ax_crys_num;
		int radial_coord = 0;
		det_pos det = boost::make_tuple(tangential_coord, axial_coord, radial_coord);

		//calculate cartesian coordinate for a given detector
		std::vector<float> temp_transformation_matrix = {ax_block_num*axial_block_spacing + ax_crys_num*axial_crystal_spacing,0.,trans_block_num*transaxial_block_spacing + trans_crys_num*transaxial_crystal_spacing};
		arma::vec3 transformation_matrix = arma::conv_to<arma::mat>::from(temp_vec);
        float alpha = this->intrinsic_azimuthal_tilt+
                trans_bucket_num*(2*M_PI)/num_transaxial_buckets+csi_minus_csiGaps;

		arma::mat rotation_matrix = get_rotation_matrix(alpha);
		// to match index range of CartesianCoordinate3D, which is 1 to 3
		//rotation_matrix.set_min_index(1);
		//rotation_matrix[1].set_min_index(1);
		//rotation_matrix[2].set_min_index(1);
		//rotation_matrix[3].set_min_index(1);

		arma::vec3 transformed_coord = start_point + transformation_matrix;
		arma::vec3 cart_coord = rotation_matrix*transformed_coord;
		cartesian_coord_map_given_detection_position_keys[det] = cart_coord;
	}
}