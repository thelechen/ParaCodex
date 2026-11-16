# Tiny Jacobi Stencil: Parallelization and Correctness Gate

- `reference.cpp` is the immutable golden serial program.
- `buggy_candidate.cpp` is a *prewritten* intentionally incorrect OpenMP candidate. Its failure is seeded, not model-generated.
- `work/candidate.cpp` is the only C++ file the OpenCode solver edits.
- `tools/gate.py` runs local `g++` builds and compares all array elements at multiple grid sizes and thread counts. It is not an LLM-powered judge.
- `runs/latest/` is regenerated for each new exercise, so copy it elsewhere if you want to retain earlier runs.

Run `python3 tools/gate.py init --mode normal` or `python3 tools/gate.py init --mode repair` from anywhere; paths are relative to this demo root. Then run `python3 tools/gate.py verify`; upon correctness+OpenMP pass run `python3 tools/gate.py bench` and `python3 tools/gate.py report`.

The task: outer time steps are sequential, but each interior cell reads the *previous* timestep grid (`a`) and writes a distinct location (`b`). Safely parallelize the spatial loop, not the time-step loop. Boundary values must remain unchanged. The comparison is numerical with strict relative/absolute tolerance. Timing is CPU-only and may be slower with more threads due to overhead and hardware limits.
