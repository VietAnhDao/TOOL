from numpy import genfromtxt
import sys

# read in arguments from bash
# filename with the specified time (s), location (x,y,z in mm) and rotation (theta, phi in radians)
#   file should be in the format with columns as follow:
#
#   t(s)    x(mm)   y(mm)   z(mm)   theta(rad)  phi(rad)
#
#   without the header for each column
#   further each row should only record when motion changes i.e. when speed or rotation changes.
#
args = sys.argv
if len(args)!=6:
    f = f'''
    Wrong number of arguments. {len(args)}; {args}\n
    Argument should be:\n
    macros output filename (i.e. filename), motion file (.txt), begin time (s), end time (s), number of slices (int).\n
    motion file should in the format of:\n
    \n
    t(s),x(mm),y(mm),z(mm),theta(rad),phi(rad)\n
    \n
    without the header for each column\n
    further each row should only record when motion changes i.e. when there is a change in displacement or rotation.\n
    '''
    sys.exit(f)
macros_filename = str(args[1])
motion_config_filename = str(args[2])
begin = float(args[3])
end = float(args[4])
number_of_slices = int(args[5])
table = genfromtxt(motion_config_filename, delimiter=",",dtype=float,skip_header=0)
time = table[:,0]
delta_time = (end-begin)/number_of_slices
for i in range(0, number_of_slices):
    found_start_time_index, found_end_time_index = False, False
    start_time = begin + i*delta_time
    end_time = begin + (i+1)*delta_time
    start_pos = []
    end_pos = []
    for j in range(0, len(time)):
        if start_time <= time[-1]:
            if time[j] <= start_time <= time[j+1]:
                start_pos = table[j]
                found_start_time_index = True
        else:
            start_pos = table[-1]
            found_start_time_index = True
        if end_time <= time[-1]:
            if time[j] <= end_time <= time[j+1]:
                end_pos = table[j]
                found_end_time_index = True
        else:
            end_pos = table[-1]
            found_end_time_index = True
        if found_end_time_index & found_start_time_index:
            found_start_time_index = False
            found_end_time_index = False
            break
    pos_x = (start_pos[1] + end_pos[1])/2.0
    pos_y = (start_pos[2] + end_pos[2])/2.0
    pos_z = (start_pos[3] + end_pos[3])/2.0
    theta = (start_pos[4] + end_pos[4])/2.0
    phi = (start_pos[5] + end_pos[5])/2.0
    activity=(start_pos[6]+end_pos[6])/2.0
    #print(f'index: {i}, start: {start_time}, end: {end_time}, start pos: {start_pos}, end pos: {end_pos}')
    file = '''
    # +-------------------------------+ #
    # |  R U N   C O N D I T I O N S  | #
    # +-------------------------------+ #

    # directory to run parameters
    /control/alias      run_dir            . 

    #  LOAD PARAMETERS  #
    /control/execute        ./parameters.mac

    #  SOURCE  #
    /control/alias      source_x            {source_x}
    /control/alias      source_y            {source_y}
    /control/alias      source_z            {source_z}
    /control/alias      phantom_x           {phantom_x}
    /control/alias      phantom_y           {phantom_y}
    /control/alias      phantom_z           {phantom_z}
    /control/alias      source_activity	    {activity}
    /control/alias      n_primaries         100000

    #Moliner phantom position
    /control/alias      airrod_x            {airrod_x}
    /control/alias      airrod_y            {airrod_y}
    /control/alias      airrod_z            {airrod_z}
    /control/alias      waterrod_x          {waterrod_x}
    /control/alias      waterrod_y          {waterrod_y}
    /control/alias      waterrod_z          {waterrod_z}
    #Moliner Source Position
    /control/alias      rod_12mm_x            {rod_12mm_x}
    /control/alias      rod_12mm_y            {rod_12mm_y}
    /control/alias      rod_12mm_z            {rod_12mm_z}
    /control/alias      rod_9mm_x          {rod_9mm_x}
    /control/alias      rod_9mm_y          {rod_9mm_y}
    /control/alias      rod_9mm_z          {rod_9mm_z}
    /control/alias      rod_6mm_x            {rod_6mm_x}
    /control/alias      rod_6mm_y            {rod_6mm_y}
    /control/alias      rod_6mm_z            {rod_6mm_z}
    /control/alias      rod_4mm_x          {rod_4mm_x}
    /control/alias      rod_4mm_y          {rod_4mm_y}
    /control/alias      rod_4mm_z          {rod_4mm_z}
    /control/alias      backgr_x            {backgr_x}
    /control/alias      backgr_y            {backgr_y}
    /control/alias      backgr_z            {backgr_z}


    #  PHANTOM  #
    /control/execute	./moliner_phantom.mac	

    #   output filename
    /control/alias      root_filename	gate_out_{index}
    /control/alias      ascii_filename	gate_out_{index}

    #   timing
    /control/alias      slice_time          {time_slice}
    /control/alias      start_time          {start}
    /control/alias      stop_time           {end}

    # energy cut
    /control/alias      min_energy          350. keV
    /control/alias      max_energy          650. keV

    # coincidences
    /control/alias      coincidence_window 5 ns
    /control/alias      multiple_coincidence_policy takeWinnerOfGoods

    # set rng seed
    /gate/random/setEngineName MersenneTwister 
    /gate/random/setEngineSeed 1649772209

    #  ReferenceDesign  #
    /control/execute    ./neurolfv01_geometry.mac

    /control/execute    ./setup_moliner.mac

    #  VISUALIZATION  #
    #/control/execute        visVRML2FILE.mac

    /gate/application/startDAQ
    exit
    '''.format(start=start_time, end=end_time, time_slice=delta_time,
                source_x=pos_x, source_y=pos_y, source_z=pos_z, 
                phantom_x=pos_x, phantom_y=pos_y, phantom_z=pos_z, 
                airrod_x=pos_x-16.875, airrod_y=pos_y-29.23, airrod_z=pos_z+26.5,
                waterrod_x=pos_x+16.875, waterrod_y=pos_y+29.23, waterrod_z=pos_z+26.5,
                rod_12mm_x=pos_x-16.875,rod_12mm_y=pos_y+29.23,rod_12mm_z=pos_z+26.5,
                rod_9mm_x=pos_x+33.75,rod_9mm_y=pos_y+0.0,rod_9mm_z=pos_z+26.5,
                rod_6mm_x=pos_x-33.75, rod_6mm_y=pos_y+0.0,rod_6mm_z=pos_z+26.5,
                rod_4mm_x=pos_x+16.875,rod_4mm_y=pos_y-29.23,rod_4mm_z=pos_z+26.5,
                backgr_x=pos_x,backgr_y=pos_y,backgr_z=pos_z,
                activity=activity, index=i)
    text_file = open(f'{macros_filename}_{i+1}.mac', "w")
    n = text_file.write(file)
    text_file.close()











