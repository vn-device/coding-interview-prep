# C++ Core Mechanics & Assessment Study Checklist

Targeted study checklist for systems-level C++ mechanics, memory layout, and low-latency fundamentals (sourced from LearnCpp.com).

---

## 1. Priority 1: Core Mechanics, Memory & Lifetimes (Non-Negotiable)

- [ ] **Chapter 12: Compound Types (Lvalue References and Pointers)**
  - [ ] `12.1` — Value categories (lvalues and rvalues)
  - [ ] `12.2` — Lvalue references
  - [ ] `12.3` — Lvalue references to const
  - [ ] `12.4` — Pass by lvalue reference
  - [ ] `12.5` — Pass by const lvalue reference
  - [ ] `12.6` — Return by reference and return by address
  - [ ] `12.7` — Introduction to pointers
  - [ ] `12.8` — Null pointers and pointer arithmetic

- [ ] **Chapter 19: Dynamic Allocation**
  - [ ] `19.1` — Dynamic memory allocation with `new` and `delete`
  - [ ] `19.2` — Memory leaks and dangling pointers
  - [ ] `19.3` — Dynamically allocating arrays (`new[]` / `delete[]`)
  - [ ] `19.4` — Destructor invocation order and allocation failure handling

- [ ] **Chapter 21: Operator Overloading & Copy Semantics**
  - [ ] `21.11` — The copy constructor
  - [ ] `21.12` — The copy assignment operator
  - [ ] `21.13` — Shallow vs. deep copying
  - [ ] `21.14` — The copy-and-swap idiom and the Rule of 0/3/5

- [ ] **Chapter 22: Move Semantics & Smart Pointers**
  - [ ] `22.1` — Rvalue references (`&&`)
  - [ ] `22.2` — Move constructors and move assignment operators
  - [ ] `22.3` — `std::move` and move semantics
  - [ ] `22.4` — `std::unique_ptr` internals and custom deleters
  - [ ] `22.5` — `std::shared_ptr` and control block overhead
  - [ ] `22.6` — `std::weak_ptr` and resolving circular references
  - [ ] `22.7` — Perfect forwarding and `std::forward`

- [ ] **Chapter 25: Virtual Functions & Polymorphism**
  - [ ] `25.1` — Virtual functions and dynamic dispatch
  - [ ] `25.2` — The virtual table pointer (`vptr`) and virtual method table (`vtable`)
  - [ ] `25.3` — Memory footprint of polymorphism and devirtualization
  - [ ] `25.4` — The `override` and `final` specifiers
  - [ ] `25.5` — Virtual destructors and memory safety
  - [ ] `25.6` — Object slicing and memory layout hazards
  - [ ] `25.7` — Pure virtual functions and abstract base classes

---

## 2. Priority 2: Systems, Bitwise Operations & Low-Latency Patterns

- [ ] **Chapter O: Bit Manipulation**
  - [ ] `O.1` — Bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`)
  - [ ] `O.2` — Bitmasks, masking operations, and bit flags
  - [ ] `O.3` — Binary data serialization and bitfield packing
  - [ ] `O.4` — Fast bit manipulation primitives (`__builtin_clz`, `__builtin_popcount`)

- [ ] **Chapter 5: Constants and Strings**
  - [ ] `5.8` — `std::string_view` mechanics and non-owning string views
  - [ ] `5.9` — Lifetime hazards, view invalidation, and avoiding allocations

- [ ] **Chapters 13 & 14: User-Defined Types & Classes**
  - [ ] `13.1 – 13.12` — Struct layout, memory alignment (`alignas`/`alignof`), and padding rules
  - [ ] `14.1 – 14.17` — Member initialization lists, `explicit` constructors, and `constexpr` evaluation

- [ ] **Chapter 26: Templates and Classes**
  - [ ] `26.1` — Function templates and template argument deduction
  - [ ] `26.2` — Class templates
  - [ ] `26.3` — Template non-type parameters
  - [ ] `26.4` — Template specialization (full and partial)
  - [ ] `26.5` — Compile-time type deduction and static assertions (`static_assert`)

---

## 3. Practical Verification Harness

Verify understanding by implementing each from scratch without notes:

1. [ ] Custom dynamic array wrapper (`Vector<T>`) using placement `new` and implementing the Rule of 5.
2. [ ] Minimal `UniquePtr<T>` and reference-counted `SharedPtr<T>` with a separated control block.
3. [ ] Memory alignment inspector proving `sizeof` changes when reordering struct members.
4. [ ] Thread-safe bounded buffer using `std::mutex` and `std::condition_variable`.