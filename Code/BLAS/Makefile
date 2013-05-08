

atlas: atlas.c
	cc -std=c99 -O3 -march=native $+ -o $@ -libatlas

test: atlas
	perf stat -e cycles:u,r0107:u ./atlas


