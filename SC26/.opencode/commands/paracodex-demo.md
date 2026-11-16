---
description: SC26 ParaCodex-style end-to-end OpenMP CPU parallelization tutorial
agent: build
---

Run the SC26 ParaCodex-style educational end-to-end exercise using the model currently selected in OpenCode. Do NOT switch models, install a GPU SDK, or ask for an OpenAI API key. The current model may be a free hosted model or a local model.

Important: this is an EDUCATIONAL CPU adaptation of the paper's Analyze → Plan → Parallelize → Verify → Profile → Refine workflow; it is NOT the full NVIDIA GPU ParaCodex implementation. You must NOT describe the CPU timing as GPU profiling.

Repository-relative demo root: `tutorial_demo/paracodex_opencode`. Work exclusively inside this root. Reference (`reference.cpp`), bug seed (`buggy_candidate.cpp`), and `tools/gate.py` are read-only. No git operations, pip installs, network fetches or unrelated file edits. Avoid editing or using the original ParaCodex workdirs or pipelines.

Perform the following steps in order, using the OpenCode task/subagent facility for each agent delegation. Make the REAL test run and evidence visible in your conversation:

1. Execute: `python3 tutorial_demo/paracodex_opencode/tools/gate.py init --mode normal`
2. Invoke `pc-analyzer` subagent: read `reference.cpp`, explain outer time-step dependence vs independent inner grid updates; write `work/analysis.md` and `work/data_plan.md`. Include loop type, correct OpenMP region, boundary handling, and what "data movement" means for CPU (no H2D copies in this exercise).
3. Invoke `pc-solver` subagent: edit ONLY `work/candidate.cpp` to create an OpenMP CPU version, preserving the CLI/output contract and math. Write `work/solver_notes.md`. No changes to the golden code or verifier. Must contain a real `#pragma omp parallel for` on a dependency-safe loop. You may use schedule(static) or collapse(2) when appropriate; do not parallelize across the time-step loop.
4. Execute: `python3 tutorial_demo/paracodex_opencode/tools/gate.py verify`. Show the real result. A status of PASS_NUMERICS plus OPENMP_ACTIVE is the required functional-and-parallel criterion.
5. On failure, invoke `pc-reviewer` subagent to inspect `runs/latest/attempt_XX.json` and `work/candidate.cpp`, write `work/reviewer_feedback.md` with concise evidence-based repair guidance; then invoke `pc-solver` again to apply the minimal fix. Rerun `verify`. Allow at most TWO repair rounds. Never conceal a failed gate.
6. Only if correctness passes and OpenMP is active, execute `python3 tutorial_demo/paracodex_opencode/tools/gate.py bench`. This measures CPU kernel-loop time and may show slowdown; report actual measurements without inventing speedup. Have `pc-analyzer` or the main agent write `work/optimization_plan.md` interpreting evidence, without further source edits unless a small, clearly validated adjustment is justified; if adjusted rerun `verify` before claiming success.
7. Write `work/correctness_verification.md` with the actual attempt status and number of tests. Execute `python3 tutorial_demo/paracodex_opencode/tools/gate.py report`.
8. Summarize what each agent did; include exact paths: `runs/latest/transcript.md`, `runs/latest/attempt_*.json`, `runs/latest/performance.json` when available. Explain that this transcript is assembled from agent-authored files and real local tool outputs, NOT a complete OpenCode session export. A session export is separate.

Never claim that a model-generated code sample passed tests without a passing real gate. Stop if the compiler is unavailable and report the setup issue rather than fabricate results.
