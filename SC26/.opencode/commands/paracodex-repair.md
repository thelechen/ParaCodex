---
description: SC26 ParaCodex-style guaranteed compile-pass numerical-fail repair exercise
agent: build
---

Run the ParaCodex-style repair mini-lab with the MODEL CURRENTLY SELECTED by the OpenCode user (do not override model). This is an educational OpenMP CPU adaptation, not full ParaCodex GPU offload.

Work only inside `tutorial_demo/paracodex_opencode`. Never edit `reference.cpp`, `buggy_candidate.cpp`, or `tools/gate.py`; no installations, external commands or git operations.

1. Run `python3 tutorial_demo/paracodex_opencode/tools/gate.py init --mode repair` to copy the INTENTIONALLY BUGGY example into the work candidate. Explicitly tell attendees: the seed bug was intentionally introduced by tutorial authors and is NOT evidence that a model failed.
2. Run `python3 tutorial_demo/paracodex_opencode/tools/gate.py verify`. Show actual compile success and numeric failure. NEVER skip this first failure.
3. Invoke `pc-reviewer` subagent: compare golden code, candidate code, and the failure JSON; write `work/reviewer_feedback.md` with the first failing numerical coordinate, cause, and a minimal recommended fix.
4. Invoke `pc-solver` subagent: fix ONLY `work/candidate.cpp` based on reviewer evidence; preserve OpenMP and CLI/output contract; write `work/solver_notes.md` describing modification.
5. Run `python3 tutorial_demo/paracodex_opencode/tools/gate.py verify`. If it still fails, repeat reviewer→solver→verify at most twice in total; preserve all attempt evidence.
6. On passing correctness with OPENMP_ACTIVE, run `python3 tutorial_demo/paracodex_opencode/tools/gate.py bench`; mention CPU-only timing; no promises of speedup.
7. Write `work/correctness_verification.md` from observed results and execute `python3 tutorial_demo/paracodex_opencode/tools/gate.py report`.
8. Summarize real gate results and show `runs/latest/transcript.md` and saved candidate attempts. Do not call the scripted initial failure "model-generated".
