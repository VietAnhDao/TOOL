# create a new ProjData instance from a numpy array
import stir
import stirextra
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
import numpy as np
def to_projdata(numpy_array, proj_data_info, exam_info):
  projdataout=stir.ProjDataInMemory(exam_info, proj_data_info)
  projdataout.fill(numpy_array.flat)
  return projdataout

def plot_image(voxels_on_cartesian_grid, vmax=0, cmap="viridis", ticks=True, cbar_label=""):
  image = stirextra.to_numpy(voxels_on_cartesian_grid)
  (dim_z, dim_y, dim_x) = image.shape

  fig, axs = plt.subplots(1,3)
  plt.subplots_adjust(bottom=0.25)

  start_index = dim_z // 2
  if vmax:
    l_z = axs[0].imshow(image[start_index, :, :], vmax=vmax, cmap=cmap)
  else:
    l_z = axs[0].imshow(image[start_index, :, :], cmap=cmap)
  axs[0].tick_params(axis='both', which='both', bottom=ticks, left=ticks, labelbottom=ticks, labelleft=ticks)
  axs[0].set_title("Transverse (x-y) Plane")
  ax_slider_z = plt.axes([0.15, 0.1, 0.18, 0.03])
  slider_z = Slider(
    ax_slider_z, "z coordinate", 0, dim_z - 1,
    valinit=start_index, valstep=1,
    initcolor='none'  # Remove the line marking the valinit position.
  )
  def update_z(val):
    l_z.set_data(image[slider_z.val, :, :])
    fig.canvas.draw_idle()
  cb = plt.colorbar(l_z, ax=[axs[0]], location="left")
  slider_z.on_changed(update_z)

  start_index = dim_y // 2
  if vmax:
    l_y = axs[1].imshow(image[:, start_index, :], vmax=vmax, cmap=cmap)
  else:
    l_y = axs[1].imshow(image[:, start_index, :], cmap=cmap)
  axs[1].tick_params(axis='both', which='both', bottom=ticks, left=ticks, labelbottom=ticks, labelleft=ticks)
  axs[1].set_title("Coronal (x-z) Plane")
  ax_slider_y = plt.axes([0.44, 0.1, 0.18, 0.03])
  slider_y = Slider(
    ax_slider_y, "y coordinate", 0, dim_y - 1,
    valinit=start_index, valstep=1,
    initcolor='none'  # Remove the line marking the valinit position.
  )
  def update_y(val):
    l_y.set_data(image[:, slider_y.val, :])
    fig.canvas.draw_idle()
  slider_y.on_changed(update_y)

  start_index = dim_x // 2
  if vmax:
    l_x = axs[2].imshow(image[:, :, start_index], vmax=vmax, cmap=cmap)
  else:
    l_x = axs[2].imshow(image[:, :, start_index], cmap=cmap)
  axs[2].tick_params(axis='both', which='both', bottom=ticks, left=ticks, labelbottom=ticks, labelleft=ticks)
  axs[2].set_title("Sagittal (y-z) plane")
  ax_slider_x = plt.axes([0.72, 0.1, 0.18, 0.03])
  slider_x = Slider(
    ax_slider_x, "x coordinate", 0, dim_x - 1,
    valinit=start_index, valstep=1,
    initcolor='none'  # Remove the line marking the valinit position.
  )
  def update_x(val):
    l_x.set_data(image[:, :, slider_x.val])
    fig.canvas.draw_idle()
  slider_x.on_changed(update_x)

  plt.show()

# function to plot ProjData
def plot_proj(proj_data_obj, vmax=0, vmin=0):
  seg = proj_data_obj.get_segment_by_sinogram(0)
  seg_array=stirextra.to_numpy(seg);
  
  fig, axs = plt.subplots(1,2)
  plt.subplots_adjust(bottom=0.25)

  middle_slice = seg_array.shape[0] // 2
  if vmax:
    sino = axs[0].imshow(seg_array[middle_slice, :, :], vmax=vmax, vmin=vmin)
  else:
    sino = axs[0].imshow(seg_array[middle_slice, :, :])
  axs[0].set_title("projection as sinogram")
  axs[0].set_xlabel("tangential")
  axs[0].set_ylabel("view")
  ax_slider_sino = plt.axes([0.2, 0.1, 0.2, 0.03])
  slider_sino = Slider(
    ax_slider_sino, "axial index", 0, seg_array.shape[0] - 1,
    valinit=middle_slice, valstep=1,
    initcolor='none'  # Remove the line marking the valinit position.
  )
  def update_sino(val):
    sino.set_data(seg_array[slider_sino.val, :, :])
    fig.canvas.draw_idle()
  slider_sino.on_changed(update_sino)
  
  if vmax:
    view = axs[1].imshow(seg_array[:, 0, :], vmax=vmax, vmin=vmin)
  else:
    view = axs[1].imshow(seg_array[:, 0, :])
  axs[1].set_title("projection as viewgram")
  axs[1].set_xlabel('tangential')
  axs[1].set_ylabel('plane')
  ax_slider_view = plt.axes([0.57, 0.1, 0.33, 0.03])
  slider_view = Slider(
    ax_slider_view, "angular index", 0, seg_array.shape[1] - 1,
    valinit=0, valstep=1,
    initcolor='none'  # Remove the line marking the valinit position.
  )
  def update_view(val):
    view.set_data(seg_array[:, slider_view.val, :])
    fig.canvas.draw_idle()
  slider_view.on_changed(update_view)


def generate_BPET_proj_data():
    # setting template projdata info and exam info
    time_frame_def = stir.TimeFrameDefinitions()
    time_frame_def.set_num_time_frames(1)  # frames are not allowed to overlap within one call to LmToProjData
    time_frame_def.set_time_frame(1, 0, 1e9)

    tmpl_exam_info = stir.ExamInfo()
    tmpl_exam_info.set_high_energy_thres(650)
    tmpl_exam_info.set_low_energy_thres(425)
    tmpl_exam_info.set_time_frame_definitions(time_frame_def)

    # define scanner geometry
    detectors_per_ring = 192
    number_of_rings = 30
    arccorrected_bins = 150
    inner_ring_radius_mm = 127
    avg_interaction_depth_mm = 4.3
    crystal_spacing_mm = 4.2
    ring_spacing_mm = crystal_spacing_mm
    bin_size_mm = crystal_spacing_mm / 2
    intrinsic_tilt_rad = -0.38956 # this is the radial equivalent of -22.32°
    num_axial_blocks_per_bucket = 5
    num_transaxial_blocks_per_bucket = 4
    num_axial_crystals_per_block = 6
    num_transaxial_crystals_per_block = 6
    num_crystals_per_block = 1
    num_detector_layers = 1
    energy_resolution = 0.17
    reference_energy = 511
    axial_block_spacing_mm = 25.8
    transaxial_block_spacing_mm = 25.8
    BPET_scanner = stir.Scanner(stir.Scanner.User_defined_scanner, "BPET_Prototype_Leipzig", detectors_per_ring, number_of_rings, 
                        arccorrected_bins, arccorrected_bins, inner_ring_radius_mm, avg_interaction_depth_mm, ring_spacing_mm, bin_size_mm, 
                        intrinsic_tilt_rad, num_axial_blocks_per_bucket, num_transaxial_blocks_per_bucket, 
                        num_axial_crystals_per_block, num_transaxial_crystals_per_block, num_crystals_per_block, num_crystals_per_block, 
                        num_detector_layers, energy_resolution, reference_energy, "BlocksOnCylindrical", 
                        crystal_spacing_mm, crystal_spacing_mm, axial_block_spacing_mm, transaxial_block_spacing_mm)

    # define projection settings
    span = 1
    max_ring_diff = 29
    num_views = 96
    num_tangential_pos = arccorrected_bins
    do_arc_correction = False
    BPET_proj_data_info = stir.ProjDataInfo.construct_proj_data_info(BPET_scanner, span, max_ring_diff, num_views, num_tangential_pos, do_arc_correction)
    return BPET_proj_data_info