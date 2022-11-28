#include "SiPM.h"
#include "SiPMProperties.h"
SiPM::SiPM(float module_width, float module_pitch, int det_num_per_width,int det_num_per_pitch,float det_width,float det_pitch,float dead_space)
{
    sipm::SiPMProperties myProperties;
    myProperties.setDcr(250e3);
    myProperties.setProperty("Xt",0.03);
    myProperties.setPde(0.43);
    myProperties.setSize(4.0);
    myProperties.setSnr(0.03);
    std::cout<<myProperties<<"\n";
    this->sensor_properties = myProperties;
    this->module_width = module_width;
    this->module_pitch = module_pitch;
    this->det_num_per_width = det_num_per_width;
    this->det_num_per_pitch = det_num_per_pitch;
    this->det_width = det_width;
    this->det_pitch = det_pitch;
    this->dead_space = dead_space; 
}

SiPM::~SiPM()
{

}