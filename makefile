.PHONY: .DEFAULT_GOAL
.DEFAULT_GOAL: task1 

task1: solution.c 
	gcc -o solution solution.c -lpthread




.PHONY: clean
clean: 
	-rm solution
