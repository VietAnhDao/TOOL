# %%
import stir
import stirextra
import matplotlib.pyplot as plt
from python_module import stir_helper

#%%

stir.set_num_threads(7)

# %%
# generate the python scanner template
proj_data_info = stir_helper.generate_BPET_proj_data()

# %%
# create an image data
zoom=1.2
image_data=stir.FloatVoxelsOnCartesianGrid(proj_data_info, zoom)
# %%
projmatrix=stir.ProjMatrixByBinUsingRayTracing()
projmatrix.set_up(proj_data_info, image_data)
forwardprojector=stir.ForwardProjectorByBinUsingProjMatrixByBin(projmatrix)
forwardprojector.set_up(proj_data_info, image_data)
backprojector=stir.BackProjectorByBinUsingProjMatrixByBin(projmatrix)
backprojector.set_up(proj_data_info, image_data)

# %%
# We'll create the data in memory here
exam_info=stir.ExamInfo()
projdataout=stir.ProjDataInMemory(exam_info, proj_data_info)
# Note: we could write to file, but it is right now a bit complicated to open a
#  projection data file for read/write:
inout=stir.ios.trunc|stir.ios.ios_base_in|stir.ios.out
projdataout=stir.ProjDataInterfile(exam_info, proj_data_info, 'BPET_projection.hs',inout)


#%%

# we'll put it in the middle of the scanner
# This is currently a bit difficult in STIR due to its
# choice of origin (the middle of the first ring).
length=60
radius=40
middle_slice=(image_data.get_max_z()+image_data.get_min_z())//2
z_centre=middle_slice*image_data.get_voxel_size().z()
# create a coordinate for the centre (note the z,y,x order)
centre=stir.FloatCartesianCoordinate3D(z_centre,0,0)
# create a geometrical shape
shape=stir.EllipsoidalCylinder(length, radius, radius,
                               centre)
shape.construct_volume(image_data, stir.IntCartesianCoordinate3D(1,1,1))
# %%
maxforplot=image_data.find_max(); # save for display
image_data_array=stirextra.to_numpy(image_data)
plt.figure()
plt.subplot(1,2,1)
plt.imshow(image_data_array[middle_slice,:,:])
plt.clim(0,maxforplot)
plt.title('slice %d' % middle_slice)
plt.subplot(1,2,2)
plt.imshow(image_data_array[middle_slice+5,:,:])
plt.title('slice %d' % (middle_slice+5))
plt.clim(0,maxforplot)


# %%
# forward project the image
forwardprojector.forward_project(projdataout, image_data)


# %%
seg=projdataout.get_segment_by_sinogram(0)
seg_array=stirextra.to_numpy(seg)
import matplotlib.animation as animation
bitmaps=[]
fig=plt.figure()
for sino in range(seg_array.shape[0]):
    bitmap=plt.imshow(seg_array[sino,:,:])
    plt.clim(0,seg_array.max())
    plt.axis('off')
    bitmaps.append([bitmap])

ani = animation.ArtistAnimation(fig, bitmaps, interval=100, blit=True, repeat_delay=1000)


# %%
stir.Float
# %%
