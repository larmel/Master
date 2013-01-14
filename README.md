Understanding sources and effects of measurement context bias (Working Title)
======

Variations in execution context has been shown to affect performance of programs. Some previous work has looked at offseting the stack and changing link order -- biasing performance measurements towards certain configurations. Variables such as the placement of stack, heap and text segments in memory, combined with memory access instructions, can impact program performance quite significantly. A model of some of these effects for common use cases, and methods for avoiding them, could be useful for avoiding bias and achieving peak performance.

These effects might be highly platform dependent, so to limit the scope we will focus on a particular architecture, the Intel Core i7 "Ivy Bridge". We want a model or heuristic that explains potential performance variations from changing various parameters of the execution context, and method to avoid negative impact of these effects. Interesting case studies will be small isolated programs, and ideally also "real" applications such as FFT algorithms.

