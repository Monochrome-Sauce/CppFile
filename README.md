C++ provides `streams`, which can differentiate between input and output, but also allow both. C only provides `FILE*` which gives us no indication of input and output.

My issues with `streams` include their complexity, overhead, available methods and more. I prefer C's simple `f*()` API for files, but I also want to have clear ownership, IO direction and RAII for exceptions.<br />
For these personal reasons, I created this simple repository for 6 types of files which wrap C's `FILE*`:

	InputFile - Can only use methods for reading. No destructor, can shallow-copy.
	OutputFile - Can only use methods for writing. No destructor, can shallow-copy.
	IOFile - Can use methods for both reading and writing. No destructor, can shallow-copy.
	UniqueInputFile - InputFile with destructor and move semantics.
	UniqueOutputFile - OutputFile with destructor and move semantics.
	UniqueIOFile - IOFile with destructor and move semantics.

The `unique` versions can be cast to non-`unique` versions, so passing to functions a non-owning `File` is simple. Do not pass them by reference, as a copy is a single pointer copy and hence more performant.<br />
The `IO` versions can be cast to either `Output` or `Input` versions.

The implementation file should not be included directly.
