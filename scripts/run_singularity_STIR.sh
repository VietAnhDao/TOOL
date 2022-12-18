#Run with current environment (-V) and in the current directory (-cwd)
#$ -V -cwd

#Request some time- min 15 mins - max 48 hours
#$ -l h_rt=48:00:00

# number of tasks
#$ -t 1-499
# maximum number of task at once
#$ -tc 499

module load singularity
## ${SGE_TASK_ID}
SAFIR_FILENAME=lm_trues_gate_out_66.clm.safir
singularity exec --bind ./:/workdir,$SOFTWARE/:/software $IMAGE/STIR.sif bash -c "source /software/scripts/source-dep.sh && cd /workdir && export INPUT_SAFIR=${SAFIR_FILENAME} && export OUT_PROJ_FILENAME=proj_${SGE_TASK_ID}_s && export OUT_IMAGE=out && lm_to_projdata lm_to_projdata.par && exit" &> run_singularity_STIR_${SGE_TASK_ID}.log
