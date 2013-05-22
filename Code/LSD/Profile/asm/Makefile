
.PHONY: chunks micro-ops branches

chunks: chunks.s
	cc chunks.s -o chunks
	perf stat -e cycles:u,r0120:u,r01a8:u ./chunks

micro-ops: micro-ops.s
	cc micro-ops.s -o micro-ops
	perf stat -e cycles:u,r0120:u,r01a8:u ./micro-ops

branches: branches.s
	cc branches.s -o branches
	perf stat -e cycles:u,r0120:u,r01a8:u ./branches

