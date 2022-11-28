#ifndef SiPM_H
#define SiPM_H
#include "SiPMProperties.h"
class SiPM
{
private:
    float module_width;
    float module_pitch;
    int det_num_per_width;
    int det_num_per_pitch;
    float det_width;
    float det_pitch;
    float dead_space;
    sipm::SiPMProperties sensor_properties;
public:
    SiPM(float module_width, float module_pitch, int det_num_per_width,int det_num_per_pitch,float det_width,float det_pitch,float dead_space);
    ~SiPM();
};

#endif