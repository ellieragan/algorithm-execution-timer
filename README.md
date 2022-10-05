#README for run.c and all\_files.sh
##author: Ellie Boyd
##date: 9/30/22


##all\_files.sh:
###Summary:
Loops through every directory in jhu\_apl containing an algorithm and runs run.c on that algorithm, outputting the execution times into all\_files.out in the format "algorithm name execution time: X microseconds"

###Usage:
all\_files.sh takes 0 arguments

###Running:
To run, use `all_files.sh`


##run.c:
###Summary:
Returns execution time for an algorithm by running algorithm repeatedly and averaging results to reduce error. Returns result in microseconds.

###Usage:
run.c takes 0 or 1 argument, if 0 arguments are provided the algorithm will be run 10 times and its execution time will be averaged over those 10 runs. If 1 argument is provided it should be an int and will be used as the new number of times to run the algorithm within the program to average the execution times. 

###Compiling and running:
To compile, use `make run`
To run, use `./run`
To clean, use `make clean` (also erases all\_files.out)

