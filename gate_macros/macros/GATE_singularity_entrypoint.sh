# Use current working directory and current modules
#$ -cwd -V
# Request Wallclock time of 6 hours
#$ -l h_rt=12:00:00

# number of tasks
#$ -t 1-500
# maximum number of task at once
#$ -tc 40

#Get email at start and end of the job

#Now run the job
module load singularity                                                                                                                
FILENAME="condition_"$SGE_TASK_ID".mac"
### run job in background
singularity run --bind ./:/APP /nobackup/medvdao/image/official_gate.sif $FILENAME 2>&1 | tee $FILENAME".log"
