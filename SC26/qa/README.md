# Local gate self-check — NOT OpenCode model outputs

These JSON files are actual outputs from the independent compiler/numerical gate, obtained with GNU g++ 14.2 in this build environment:

- `seeded_failure_real_gate.json`: intentionally wrong *prewritten* stencil candidate compiled but produced a numerical mismatch.
- `fixed_candidate_real_gate.json`: manually corrected candidate with `#pragma omp parallel for` passed 18/18 checks across six grid sizes and thread counts 1/2/4.
- `cpu_performance_local_example.json`: measurements from a separate correct candidate in the same environment. Performance was not accelerated on the test machine, and no GPU profiling was done.

These data are provided as a factual reference and trouble-shooting aid. They are **not** a recorded OpenCode session, are **not** evidence of model behavior, and should not be reported as results from attendees' live models.
