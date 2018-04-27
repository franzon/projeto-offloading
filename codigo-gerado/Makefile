parallel-regions: parallel-regions.c clean
	gcc-4.8 -O0 -Wall -Wextra -fopenmp -fdump-tree-ompexp-graph parallel-regions.c -o parallel-regions

clean:
	rm -rf parallel-regions
	rm -rf *.ompexp
	rm -rf *.dot