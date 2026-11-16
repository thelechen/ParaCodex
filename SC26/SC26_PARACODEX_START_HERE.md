# SC26 Tutorial: ParaCodex-style OpenCode End-to-End Hands-on

**Purpose.** A tiny, CPU-only OpenMP classroom adaptation of the ParaCodex paper's **Analyze → Data Plan → Parallelize → Correctness Gate → Measure → Refine** workflow. It does not replace the project's NVIDIA GPU offload pipeline. It is intended to be reproducible on attendee laptops and use whatever (including free) LLM is already selected in OpenCode.

## Setup

1. Install OpenCode and a C++17 compiler with OpenMP support (on Linux: GCC/g++; on macOS use Homebrew GCC, not Apple's default Clang if you want real OpenMP).
2. Clone the tutorial repository and enter its `SC26` directory:

   ```bash
   git clone https://github.com/thelechen/ParaCodex.git
   cd ParaCodex/SC26
   ```

3. Optionally check the tool before opening OpenCode:

   ```bash
   python3 tutorial_demo/paracodex_opencode/tools/gate.py init --mode repair
   python3 tutorial_demo/paracodex_opencode/tools/gate.py verify
   # Expected for repair seed: compilation succeeds, numerical equivalence fails.
   ```

4. Start `opencode` from the `SC26` directory and select a working free/default model in the TUI (the addon deliberately specifies **no model**).

## Start a fresh run

Exit OpenCode, then run this from the `SC26` directory:

```bash
make clean
opencode
```

`make clean` removes only generated files under `tutorial_demo/paracodex_opencode/runs/latest/`, generated agent files under `work/`, and local Python caches. It preserves the golden reference, bug fixture, gate tool, `.opencode/` configuration, QA evidence, documentation, and Makefile.

## One-command exercises

**Normal end-to-end:** `/paracodex-demo`

OpenCode uses three specialized agents: analyzer → solver → reviewer when needed. The analyzer writes loop/dependency and data plans, the solver edits OpenMP C++, the independent `gate.py` compiles and compares EVERY numeric element for several grid sizes and 1/2/4 threads; after PASS the runner measures CPU kernel time. If generated code is correct immediately, no repair step is artificially claimed.

**Guaranteed failure-and-repair:** `/paracodex-repair`

This intentionally loads an incorrect *prewritten* OpenMP C++ implementation, confirms a real numeric mismatch, then asks reviewer and solver to fix it. The initial error is **injected for teaching**, not a failure of a particular LLM. The verifier and golden reference remain unchanged.

## Files to show attendees

- `tutorial_demo/paracodex_opencode/work/analysis.md` — which loops can be parallelized?
- `tutorial_demo/paracodex_opencode/work/data_plan.md` — dependencies, buffers, loop ownership
- `tutorial_demo/paracodex_opencode/work/candidate.cpp` — generated/edited OpenMP code
- `tutorial_demo/paracodex_opencode/runs/latest/candidate_attempt_XX.cpp` — exact source at each gate
- `tutorial_demo/paracodex_opencode/runs/latest/attempt_XX.json` — **actual** compiler/test outcomes
- `tutorial_demo/paracodex_opencode/work/reviewer_feedback.md` — reviewer diagnosis when failed
- `tutorial_demo/paracodex_opencode/runs/latest/performance.json` — **CPU** timing, only after gate PASS
- `tutorial_demo/paracodex_opencode/runs/latest/transcript.md` — artifact-based teaching recap; NOT a complete OpenCode session transcript

If `g++ -fopenmp` fails on macOS/Apple Clang, the verifier can compile serial fallback and record `NOT_PROVEN_PARALLEL`; these runs are not reported as parallel speedups. Set `CXX=g++-15` (or the version installed by Homebrew) and retry. The fallback must not be mistaken for OpenMP acceleration.

To export the **actual** OpenCode session and tool/subagent messages, run `opencode session list` to get its ID and then `opencode session export <SESSION_ID> --sanitize > opencode-session.json`. Review/redact generated code or sensitive content before sharing. This is different from the educational `transcript.md` assembled from saved artifacts.

The independent gate checks the golden-source SHA and refuses to run if the reference changes. It does not automatically prove that no data races exist; multiple thread counts and numerical comparison are useful smoke tests, not a substitute for a race detector.

## Five-minute audience script

1. (1 min) Show the serial code and ask: *Can we parallelize the time-step loop?*
2. (1 min) `/paracodex-demo` — read `analysis.md` and the code diff.
3. (1 min) Show `attempt_01.json` with actual compilation and numeric checks.
4. (1 min) `/paracodex-repair` — watch seeded failure → reviewer → solver → PASS.
5. (1 min) Discuss timing: *A correct parallel version can still be slower.*

Use the paper's original GPU workdirs, GATE SDK, and NVIDIA `nsys` profiling only in a separately prepared GPU environment. The upstream README still lists OpenCode engine as "Coming soon", although `pipeline/utils/run_opencode.py` is present; this addon does not claim the upstream web app's OpenCode path is fully integrated or verified.

**Note:** Running any AI-generated executable code has risks. Use the trusted demo code and an isolated attendee environment. Do not give the agent unrestricted access to your laptop or private files.

Source: <https://github.com/Scientific-Computing-Lab/ParaCodex>
