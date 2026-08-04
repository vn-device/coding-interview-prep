# Attribute Parser

## Core Concept
* Hierarchical state serialization using a stack-based path tracker combined with an $\mathcal{O}(1)$ average lookup hash table.

## Algorithmic Strategy & Trade-offs
* **Erase-Remove Idiom:** Sanitizes input strings in-place (`<`, `>`, `"`) without allocating temporary heap buffers or performing string copies.
* **Scope Tracking:** Uses `std::vector<string>` as a LIFO stack to maintain the current nested tag depth.
* **Path Key Serialization:** Builds keys formatted as `tag1.tag2~attr` directly in the map during input intake to convert tree-traversal queries into flat hash map lookups.
* **Temporary String Keying:** Key construction inside the stream parsing loop uses `tagsPath + "~" + attrType` to avoid mutating the base `tagsPath` for subsequent attributes on the same line.

## Pitfalls & Edge Cases
* **Key Mutation Bug:** Modifying `tagsPath` directly in-place (`tagsPath += "~" + attrType`) corrupts the base path string for all subsequent attributes on that line.
* **Stream Buffer Residue:** Mixing `cin >>` with `getline()` leaves a `\n` in the I/O buffer. Omitting `cin.ignore()` causes the first `getline()` to ingest an empty line.
* **Trailing Delimiters:** Incorrect conditional checks during path serialization can append trailing dots (e.g., `tag1.tag2.`), breaking lookup match exactness.

## Complexity Breakdown
* **Time Complexity:** 
  * Intake & Parse: $\mathcal{O}(N \times L)$ where $N$ is total lines and $L$ is max line length.
  * Query Execution: $\mathcal{O}(Q)$ average case using $\mathcal{O}(1)$ `std::unordered_map` lookups.
* **Space Complexity:** $\mathcal{O}(N \times A)$ where $A$ is the average number of attributes per line, storing all fully qualified keys in heap memory.