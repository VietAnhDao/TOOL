# Use current working directory and current modules
#$ -cwd
# Request Wallclock time of 6 hours
#$ -l h_rt=12:00:00

# number of tasks
#$ -t 1-499
# maximum number of task at once
#$ -tc 50

module load singularity
INDEX=${SGE_TASK_ID}
FILENAME=gate_out_$INDEX

echo "------ csorter ------"
singularity exec --bind ./:/tmp/. /nobackup/medvdao/image/csorter_true.sif /bop/cs/build/utilities/csorter_gate2SAFIRlm \
	-f /tmp/$FILENAME.root -o /tmp/"lm_trues_"$FILENAME --sigmat 255. --sigmae 0.06 -g /tmp/neurolfv01_geometry.yaml --cutse 50. --ewinlow 425. --ewinup 650. --cwindow 1800. --recover-scatters --max-crystal-distance 3
