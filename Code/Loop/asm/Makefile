
.PHONY: loop

disable-aslr:
	sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"

# Print addresses for cases where aliasing occurs. Need to use
# assembly code to avoid observer effects.

loop: loop.s
	cc $+ -o $@

# i, j, k is statically allocated (0x601028, 0x60102c, 0x601030)
# With this offset, g and inc collides with (7fffffffe02c, 7fffffffe028)
# Exact same results for c-version of the code -- no observer effect
test: loop disable-aslr
	perf stat -e cycles:u,r0107:u env -i ./loop
	perf stat -e cycles:u,r0107:u env -i X=`head -c 3420 </dev/zero | tr '\0' '0'` ./loop


