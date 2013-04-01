SHELL := /bin/bash

chunks: clean
	for N in {1..16}; do \
		cc chunks.c -O3 -falign-loops=32 -DN=$$N -o chunks; \
		printf " %3d " "$$N"; \
		perf stat -x" " -e cycles:u,r01a8:u ./chunks 0>&1 >/dev/null | sed ':a;N;$$!ba;s/\n/ /g' | \
			(read -a words; \
				if (( $$(echo "$${words[2]} > 100000" | bc -l) )); then \
					echo -ne -e "\e[0;32mOK\e[0m       "; else \
					echo -ne -e "\e[0;31mOverflow\e[0m "; \
				fi; \
				echo "{ $${words[@]} } "; \
			); \
		rm -f chunks; \
	done

micro-ops: clean
	cc micro-ops.c -O3 -falign-loops=32 -S
	for N in {6..60}; do \
		sed -i '10a\\taddl\t$$1, %ebx' micro-ops.s; \
		cc micro-ops.s -o micro-ops; \
		printf " %3d " "$$N"; \
		perf stat -x" " -e cycles:u,r0120:u,r01a8:u ./micro-ops 0>&1 >/dev/null | sed ':a;N;$$!ba;s/\n/ /g' | \
			(read -a words; \
				if (( $$(echo "$${words[2]} == 0" | bc -l) )); then \
					echo -ne -e "\e[0;32mOK\e[0m            "; else \
					echo -ne -e "\e[0;31mLSD_OVERLFLOW\e[0m "; \
				fi; \
				echo "{ $${words[@]} } "; \
			); \
		rm -f micro-ops; \
	done
	rm -f micro-ops.s

branches: clean
	cat branches.c > branches-tmp.c
	for N in {1..20}; do \
		sed -i '7a\        if (i) i = 1;' branches-tmp.c; \
		cc branches-tmp.c -o branches; \
		printf " %3d " "$$N"; \
		perf stat -x" " -e cycles:u,r0120:u,r01a8:u ./branches 0>&1 >/dev/null | sed ':a;N;$$!ba;s/\n/ /g' | \
			(read -a words; \
				if (( $$(echo "$${words[4]} > 100000" | bc -l) )); then \
					echo -ne -e "\e[0;32mOK\e[0m            "; else \
					echo -ne -e "\e[0;31mLSD_OVERLFLOW\e[0m "; \
				fi; \
				echo "{ $${words[@]} } "; \
			); \
		rm -f branches; \
	done
	rm -f branches-tmp.c

clean:
	rm -f chunks
	rm -f micro-ops
	rm -f branches


