SHELL=/bin/bash
.PHONY: all disable-aslr
.DEFAULT: all

all: disable-aslr default tcmalloc hoard

disable-aslr:
	sudo bash -c 'echo 0 > /proc/sys/kernel/randomize_va_space'

default:
	cc address.c -o default
	./default

tcmalloc:
	cc address.c -o tcmalloc -ltcmalloc
	./tcmalloc

hoard:
	(export LD_PRELOAD=~/Allocators/Hoard/libhoard.so; cc address.c -o hoard; ./hoard)

clean:
	rm -f default tcmalloc hoard


