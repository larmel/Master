Analyzing Contextual Bias of Program Execution on Modern CPUs
======

Variations in execution context has been shown to affect performance of programs on recent CPUs. Previous work
has looked at offsetting the stack and changing link order -- biasing performance measurements towards certain
configurations. Variables such as the placement of stack, heap and text segments in memory, combined with
memory access instructions, can impact program performance quite significantly.

The goal of this project is to model some of these effects for common use cases, and methods for avoiding them, in
order to avoiding bias and achieving peak performance. These effects might be highly platform dependent, so to limit
the scope we will focus on a particular architecture, the Intel Core i7 "Ivy Bridge".
Case studies will include small isolated programs, and ideally also "real" applications such as FFT algorithms.
