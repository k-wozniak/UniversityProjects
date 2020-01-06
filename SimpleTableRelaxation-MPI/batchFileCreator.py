import math

for p in ["0.001"]:
	for size in [10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000]:
		for processes in [12, 20, 24, 28, 36, 40, 44, 48, 52, 56, 60]:
			filename = "MPI_" + str(processes) + "_" + str(size) + "_" + p + ".batch"
			
			nodes = math.ceil(processes/16)
			
			if processes > 16:
				tasks = 16
			else:
				tasks = processes

			with open(filename, 'a') as f:
    				f.write('#!/bin/bash\n\n')
    				f.write('#SBATCH --job-name=kkw28_job\n\n')
    				f.write('#SBATCH --account=cm30225\n\n')
    				f.write('#SBATCH --partition=teaching\n\n')
    				f.write('#SBATCH --nodes=' + str(nodes) + '\n\n')
    				f.write('#SBATCH --ntasks-per-node=' + str(tasks) + '\n\n')
    				f.write('#SBATCH --time=00:15:00\n\n')
    				f.write('#SBATCH --error=./output/MPI' + str(processes) + 'x' + str(size) + 'x' + p + '.err\n\n')
    				f.write('#SBATCH --output=./output/MPI' + str(processes) + 'x' + str(size) + 'x' + p + '.out\n\n')
    				f.write('\n')
    				f.write('module purge\n')
    				f.write('module load slurm\n')
    				f.write('module load openmpi\n')
    				f.write('\n')
    				f.write('echo $SLURM_NTASKS\n')
    				f.write('time mpirun -np ' + str(processes) + ' ./MPI_runnable -p ' + p + ' -testArray ' + str(size) + ' 5\n')
