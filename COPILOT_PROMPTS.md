# GitHub Copilot Prompt Reference

A curated list of high-context prompts to automate repository setup, code generation, problem note creation, and Git version control workflows.

---

## 1. Solution & Notes Generation

### Generate Problem Solution + Notes (Single Problem)
> "Act as a Principal C++ Systems Engineer. I am working on the [PROBLEM_NAME] problem under `[PLATFORM]/[DOMAIN]/[PROBLEM_SLUG]`. Please generate two files:
> 1. `solution.cpp`: A complete, functional implementation using C++14/C++17, explicit standard types (e.g., `uint32_t`, `long long`), Fast I/O, and strictly following Allman bracing style.
> 2. `notes.md`: Structured notes following `.github/NOTE_TEMPLATE.md`, covering core concepts, algorithmic strategy, memory trade-offs, pitfalls/edge cases, and LaTeX complexity analysis."

---

## 2. Git & Repository Automation

### Automatic Commit & Push (@terminal)
> "@terminal Stage all current changes, draft a conventional commit message based on my git diff (e.g., `feat([PLATFORM]): add [PROBLEM_NAME] solution and systems notes`), and push to the `main` branch on GitHub."

### Check Workspace Status
> "@terminal Check git status, show uncommitted files, and verify if the local branch is up to date with origin/main."

---

## 3. Code Optimization & Code Review

### Systems & Performance Audit
> "Review my current C++ solution for [PROBLEM_NAME]. Identify any hidden performance hazards, unnecessary heap allocations, cache misses, missing `const` qualifiers, or memory traps (e.g., dangling references, integer overflows). Suggest low-level optimizations."

### Refactor for Allman Bracing & Clean Code
> "Refactor my current code to strictly follow the Allman bracing style (opening braces on their own line, vertically aligned). Add concise inline comments explaining non-trivial bitwise operations, memory management, or pointer manipulation."

---

## 4. Scorecard Maintenance

### Update Master README.md
> "Scan my newest solution and notes under `[FILE_PATH]`. Update the Master Scorecard table in the root `README.md` to include this problem with its Platform, Domain, Name, Time Complexity, Space Complexity, and Core Concept."