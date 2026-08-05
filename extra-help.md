# CODING PRACTICE

---

## STRATEGY FOR CODING SESSIONS

1. **Talk first, code second.** Say "I'm thinking about using X because Y" before typing.
2. **Start brute-force.** Working code scores higher than elegant code that doesn't compile.
3. **Use embedded-appropriate types:** `uint8_t`, `uint32_t`, `size_t`
4. **State assumptions out loud:** "I'm assuming size is always > 0 and a power of 2."
5. **Handle edge cases out loud:** "What if the buffer is full? I'll return an error code."
6. **State complexity when done:** "This runs in O(n) time, O(1) space."
7. **If stuck:** "Let me trace through a small example to make sure I have this right."

---

## CATEGORY 1: BIT MANIPULATION (Most Likely for Tony)

These are your HIGHEST priority. You know embedded registers. Treat every problem like a hardware register.

---

### Problem 1.1: Set, Clear, Toggle, Test Bit

```c
#include <stdint.h>
#include <stdbool.h>

/* Set bit N in register */
uint32_t set_bit(uint32_t reg, uint8_t n) {
    return reg | (1u << n);
}

/* Clear bit N in register */
uint32_t clear_bit(uint32_t reg, uint8_t n) {
    return reg & ~(1u << n);
}

/* Toggle bit N in register */
uint32_t toggle_bit(uint32_t reg, uint8_t n) {
    return reg ^ (1u << n);
}

/* Test if bit N is set */
bool test_bit(uint32_t reg, uint8_t n) {
    return (reg >> n) & 1u;
}
```

**Practice saying:** "In embedded systems, we use these patterns constantly for GPIO registers. Set uses OR, clear uses AND-NOT, toggle uses XOR."

---

### Problem 1.2: Count Set Bits (Hamming Weight)

```c
/* Count how many bits are 1 in a 32-bit value */
int count_bits(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Better: Brian Kernighan's trick — clears the lowest set bit each iteration */
int count_bits_fast(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  /* clears lowest set bit */
        count++;
    }
    return count;
}
```

**Practice saying:** "Brian Kernighan's trick: `n & (n-1)` always clears the lowest set bit. Number of iterations equals the number of 1-bits. This is O(number of set bits) not O(32)."

---

### Problem 1.3: Reverse Bits

```c
/* Reverse all 32 bits */
uint32_t reverse_bits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}
```

**Trace:** `n=0b1011` → result builds bit by bit from LSB to MSB → `0b1101`

---

### Problem 1.4: Extract and Insert Bitfield

```c
/* Extract N bits starting at position POS (like a register bitfield) */
uint32_t extract_field(uint32_t reg, uint8_t pos, uint8_t len) {
    uint32_t mask = (1u << len) - 1;
    return (reg >> pos) & mask;
}

/* Insert value V into N bits starting at position POS */
uint32_t insert_field(uint32_t reg, uint8_t pos, uint8_t len, uint32_t val) {
    uint32_t mask = ((1u << len) - 1) << pos;
    reg &= ~mask;               /* clear the field */
    reg |= (val << pos) & mask; /* insert new value */
    return reg;
}
```

**Use case:** "This is exactly how I read FPGA status registers and PTP timestamp fields — extract specific bit fields without touching adjacent bits."

---

### Problem 1.5: Power of Two Check

```c
/* Is n a power of 2? */
bool is_power_of_two(uint32_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

**Practice saying:** "Powers of 2 have exactly one bit set. `n & (n-1)` clears the lowest set bit. If the result is 0, there was only one bit. I use this in ring buffers—when size is a power of 2, I can use `& (size-1)` instead of `% size`, which is much faster on embedded processors with no hardware divider."

---

### Problem 1.6: Swap Without Temp (XOR Swap)

```c
void swap_xor(uint32_t *a, uint32_t *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
```

**Caution:** "XOR swap breaks if a and b are the same memory location. Always safer to use a temp variable in production. But it shows understanding of XOR properties."

---

### Problem 1.7: Find the Only Non-Duplicate

```c
/* In an array where every element appears twice except one, find the single. */
int find_single(int *arr, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}
```

**Trace:** `[1,2,1,3,2]` → XOR all → `1^2^1^3^2` → duplicates cancel → result = 3  
**Practice saying:** "XOR is commutative and associative. `x ^ x = 0` and `x ^ 0 = x`. So all pairs cancel out, leaving the single element."

---

## CATEGORY 2: RING BUFFER (Core Embedded Pattern — Very Likely)

This is the most important embedded data structure. Know it cold.

---

### Problem 2.1: Circular Ring Buffer

```c
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RING_BUF_SIZE 256  /* MUST be power of 2 */

typedef struct {
    uint8_t  data[RING_BUF_SIZE];
    uint32_t head;  /* write index */
    uint32_t tail;  /* read index */
    uint32_t count;
} ring_buf_t;

void ring_buf_init(ring_buf_t *rb) {
    rb->head = rb->tail = rb->count = 0;
}

bool ring_buf_full(const ring_buf_t *rb) {
    return rb->count == RING_BUF_SIZE;
}

bool ring_buf_empty(const ring_buf_t *rb) {
    return rb->count == 0;
}

/* Write one byte. Returns false if full. */
bool ring_buf_put(ring_buf_t *rb, uint8_t byte) {
    if (ring_buf_full(rb)) return false;
    rb->data[rb->head & (RING_BUF_SIZE - 1)] = byte;
    rb->head++;
    rb->count++;
    return true;
}

/* Read one byte. Returns false if empty. */
bool ring_buf_get(ring_buf_t *rb, uint8_t *byte) {
    if (ring_buf_empty(rb)) return false;
    *byte = rb->data[rb->tail & (RING_BUF_SIZE - 1)];
    rb->tail++;
    rb->count--;
    return true;
}
```

**Practice saying:**
- "I use `count` to track occupancy so I don't confuse a full buffer from an empty one when head == tail."
- "The bitmask `& (SIZE-1)` is faster than `% SIZE` on embedded processors without hardware divide—but it only works when SIZE is a power of 2."
- "In an ISR context, I'd make `head` and `tail` volatile and use critical sections or atomic ops for thread safety."

---

### Problem 2.2: Interrupt-Safe Ring Buffer (Embedded Reality)

```c
/* UART interrupt-safe version */
/* ISR calls ring_buf_put_isr, main loop calls ring_buf_get_safe */

volatile ring_buf_t uart_rx_buf;

/* Called from ISR — only writes head, main loop only reads head to check count */
void ring_buf_put_isr(volatile ring_buf_t *rb, uint8_t byte) {
    if (rb->count < RING_BUF_SIZE) {
        rb->data[rb->head & (RING_BUF_SIZE - 1)] = byte;
        rb->head++;
        rb->count++;  /* increment last — main loop sees update after data is written */
    }
}

/* Called from main loop — only writes tail */
bool ring_buf_get_safe(volatile ring_buf_t *rb, uint8_t *byte) {
    if (rb->count == 0) return false;
    *byte = rb->data[rb->tail & (RING_BUF_SIZE - 1)];
    rb->tail++;
    rb->count--;  /* decrement last */
    return true;
}
```

**Practice saying:** "In a single-producer, single-consumer scenario with an ISR and main loop, `count` acts as a memory barrier signal. The ISR writes data first, then increments count. The main loop checks count before reading. This avoids needing a mutex IF the count increment is atomic—which it is on most 32-bit ARM cores for 32-bit aligned variables."

---

## CATEGORY 3: STATE MACHINE (Very Common in Firmware)

---

### Problem 3.1: Simple Protocol State Machine

```c
/* Parse simple packet: START(0xAA) + LENGTH(1 byte) + DATA + CHECKSUM */

typedef enum {
    STATE_IDLE,
    STATE_LENGTH,
    STATE_DATA,
    STATE_CHECKSUM
} parse_state_t;

typedef struct {
    parse_state_t state;
    uint8_t       length;
    uint8_t       data[256];
    uint8_t       data_idx;
    uint8_t       checksum;
} parser_t;

#define START_BYTE 0xAA

void parser_init(parser_t *p) {
    p->state    = STATE_IDLE;
    p->data_idx = 0;
    p->checksum = 0;
}

/* Returns true when a complete valid packet is received */
bool parser_process_byte(parser_t *p, uint8_t byte) {
    switch (p->state) {
        case STATE_IDLE:
            if (byte == START_BYTE) {
                p->state    = STATE_LENGTH;
                p->checksum = byte;
            }
            break;

        case STATE_LENGTH:
            p->length   = byte;
            p->data_idx = 0;
            p->checksum ^= byte;
            p->state    = (byte > 0) ? STATE_DATA : STATE_CHECKSUM;
            break;

        case STATE_DATA:
            p->data[p->data_idx++] = byte;
            p->checksum ^= byte;
            if (p->data_idx >= p->length) {
                p->state = STATE_CHECKSUM;
            }
            break;

        case STATE_CHECKSUM:
            p->state = STATE_IDLE; /* always reset */
            return (p->checksum ^ byte) == 0;
    }
    return false;
}
```

**Practice saying:** "State machines are how I implement all protocol parsers in firmware. Each byte drives a transition. The key discipline: always have a valid 'reset to idle' path so a garbled packet doesn't lock the parser. I used this pattern for our GPSDO NMEA parser and for the WiseUpdater protocol."

---

## CATEGORY 4: STRINGS & ARRAYS (Likely for Jennifer)

---

### Problem 4.1: Reverse a String In-Place

```c
#include <string.h>

void reverse_string(char *str) {
    if (!str) return;
    int left  = 0;
    int right = (int)strlen(str) - 1;
    while (left < right) {
        char tmp  = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left++;
        right--;
    }
}
```

---

### Problem 4.2: Check if String is Palindrome

```c
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_palindrome(const char *str) {
    if (!str) return false;
    int left  = 0;
    int right = (int)strlen(str) - 1;
    while (left < right) {
        if (tolower(str[left]) != tolower(str[right])) return false;
        left++;
        right--;
    }
    return true;
}
```

---

### Problem 4.3: Find First Non-Repeating Character

```c
#include <string.h>

char first_unique_char(const char *str) {
    int count[256] = {0};  /* ASCII frequency table */
    for (int i = 0; str[i]; i++) count[(unsigned char)str[i]]++;
    for (int i = 0; str[i]; i++) {
        if (count[(unsigned char)str[i]] == 1) return str[i];
    }
    return '\0';
}
```

**Practice saying:** "I use a fixed 256-element array as a hash map indexed by ASCII value. O(n) time, O(1) space since the array is bounded."

---

### Problem 4.4: Two Sum (Classic)

```c
/* Find indices of two numbers that sum to target.
   Simple O(n^2) version — acceptable for small n. */
bool two_sum(int *nums, int n, int target, int *i_out, int *j_out) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                *i_out = i;
                *j_out = j;
                return true;
            }
        }
    }
    return false;
}
```

**Then say:** "The O(n^2) version works. For larger data sets, I'd use a hash table for O(n) time. But in embedded with small fixed arrays, O(n^2) is often acceptable and uses no heap allocation."

---

### Problem 4.5: Find Duplicate in Array

```c
/* Array has values 1..n with one duplicate. Find it. */
int find_duplicate(int *arr, int n) {
    /* XOR approach — works when exactly one number appears twice */
    int xor_all = 0;
    for (int i = 1; i <= n - 1; i++) xor_all ^= i;  /* XOR of 1..n-1 */
    for (int i = 0; i < n; i++)     xor_all ^= arr[i]; /* XOR with array */
    return xor_all;  /* duplicate is what remains */
}
```

---

### Problem 4.6: Move Zeros to End

```c
/* Move all zeros to the end while preserving non-zero order.
   Example: [1,0,2,0,3] -> [1,2,3,0,0] */
void move_zeros(int *arr, int n) {
    int write = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) arr[write++] = arr[i];
    }
    while (write < n) arr[write++] = 0;
}
```

---

## CATEGORY 5: LINKED LIST (Common Interview Topic)

---

### Problem 5.1: Reverse a Linked List

```c
typedef struct node {
    int         val;
    struct node *next;
} node_t;

node_t *reverse_list(node_t *head) {
    node_t *prev = NULL;
    node_t *curr = head;
    while (curr) {
        node_t *next = curr->next;
        curr->next   = prev;
        prev         = curr;
        curr         = next;
    }
    return prev;  /* new head */
}
```

**Practice saying:** "Three pointer technique: prev, curr, next. Walk forward one node at a time, flipping each pointer. Return prev because it ends up at the old tail, now the new head."

---

### Problem 5.2: Detect a Cycle (Floyd's Algorithm)

```c
bool has_cycle(node_t *head) {
    node_t *slow = head;
    node_t *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

**Practice saying:** "Slow moves one step, fast moves two. If there's a cycle, fast will eventually lap slow and they'll point to the same node. If there's no cycle, fast reaches NULL."

---

## CATEGORY 6: EMBEDDED-SPECIFIC PATTERNS

---

### Problem 6.1: Big-Endian to Little-Endian (Byte Swap)

```c
/* Swap 32-bit value endianness */
uint32_t swap32(uint32_t val) {
    return ((val & 0xFF000000u) >> 24) |
           ((val & 0x00FF0000u) >>  8) |
           ((val & 0x0000FF00u) <<  8) |
           ((val & 0x000000FFu) << 24);
}

uint16_t swap16(uint16_t val) {
    return (val >> 8) | (val << 8);
}
```

**Use case:** "I use this constantly with network protocols. PTP timestamps and NTP packet fields are big-endian, but i.MX28 ARM is little-endian. I swap on receive and transmit."

---

### Problem 6.2: Safe Memory-Mapped Register Read/Write

```c
/* Volatile pointer access for memory-mapped I/O */
#define REG_BASE 0x40020000u

typedef volatile struct {
    uint32_t CTRL;   /* offset 0x00 */
    uint32_t STATUS; /* offset 0x04 */
    uint32_t DATA;   /* offset 0x08 */
} my_peripheral_t;

static my_peripheral_t * const MY_PERIPH = (my_peripheral_t *)REG_BASE;

void enable_peripheral(void) {
    MY_PERIPH->CTRL |= (1u << 0);  /* set enable bit */
}

bool is_data_ready(void) {
    return (MY_PERIPH->STATUS & (1u << 4)) != 0;
}

uint32_t read_data(void) {
    return MY_PERIPH->DATA;
}
```

**Practice saying:** "The `volatile` keyword tells the compiler not to cache this value in a register—it must re-read from memory every time. This is essential for hardware registers because the hardware can change the value independently of software. Without volatile, the compiler might optimize away reads or writes it thinks are redundant."

---

### Problem 6.3: Simple GPIO Bitmask Pattern

```c
/* Register at 0x40021000: bits [7:0] are outputs, bits [15:8] are inputs */
#define GPIO_REG  (*(volatile uint32_t *)0x40021000u)

#define LED_GREEN   (1u << 0)
#define LED_RED     (1u << 1)
#define RELAY_OUT   (1u << 2)
#define BTN_INPUT   (1u << 8)

void led_green_on(void)  { GPIO_REG |=  LED_GREEN; }
void led_green_off(void) { GPIO_REG &= ~LED_GREEN; }
void led_toggle(void)    { GPIO_REG ^=  LED_GREEN; }
bool button_pressed(void){ return (GPIO_REG & BTN_INPUT) != 0; }
```

---

## CATEGORY 7: COMMON ALGORITHM PATTERNS

---

### Problem 7.1: Binary Search

```c
/* Returns index of target, or -1 if not found. Array must be sorted. */
int binary_search(int *arr, int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;  /* avoids overflow vs (l+r)/2 */
        if (arr[mid] == target) return mid;
        if (arr[mid] <  target) left  = mid + 1;
        else                    right = mid - 1;
    }
    return -1;
}
```

**Note:** `mid = left + (right - left) / 2` avoids integer overflow that `(left + right) / 2` can cause.

---

### Problem 7.2: Max Subarray Sum (Kadane's Algorithm)

```c
/* Find the maximum sum of any contiguous subarray */
int max_subarray(int *arr, int n) {
    int max_sum  = arr[0];
    int curr_sum = arr[0];
    for (int i = 1; i < n; i++) {
        curr_sum = (arr[i] > curr_sum + arr[i]) ? arr[i] : curr_sum + arr[i];
        if (curr_sum > max_sum) max_sum = curr_sum;
    }
    return max_sum;
}
```

---

### Problem 7.3: FizzBuzz (Classic Sanity Check)

```c
#include <stdio.h>
void fizzbuzz(int n) {
    for (int i = 1; i <= n; i++) {
        if      (i % 15 == 0) printf("FizzBuzz\n");
        else if (i % 3  == 0) printf("Fizz\n");
        else if (i % 5  == 0) printf("Buzz\n");
        else                  printf("%d\n", i);
    }
}
```

**Note:** Check 15 FIRST (both conditions), then 3, then 5.

---

## PRACTICE PLAN — TONIGHT ONLY (July 23)

### ✅ July 21 — Done
### ✅ July 22 — Done

### July 23 (Tonight — 45 min MAX, then STOP):
1. Trace Problems 1.1, 1.2 from memory (bit set/clear + count bits) — no looking
2. Trace Problem 2.1 (ring buffer) in your head — just mentally walk through put/get
3. Skim Category 4 quick-reference (strings: reverse, palindrome, first unique char)
4. Read the EMERGENCY PHRASES section below once out loud
5. **STOP. Close the laptop. Rest.**

**Do NOT start new topics tonight. You know enough. Fatigue hurts more than one more problem helps.**

---

## EMERGENCY PHRASES (If You're Stuck)

**"Let me think through a small example first..."**  
→ Trace through `[1, 2, 3]` or a 4-bit example. Buying time AND showing methodology.

**"My first approach would be brute force O(n²), but let me see if there's a better way..."**  
→ Shows you know complexity matters, even if you end up with the brute force.

**"Can I ask: is this performance-critical embedded code, or is readability more important?"**  
→ Shows embedded mindset. Context matters in firmware.

**"I want to make sure I handle edge cases: empty input, single element, overflow..."**  
→ Shows production code discipline.

**"This is similar to a ring buffer pattern I use for UART receive in production firmware..."**  
→ Connecting theory to real experience. Tony will love this.

---

## QUICK REFERENCE: C Gotchas to Know

| Topic | What to Say |
|-------|-------------|
| `volatile` | "Tells compiler to not cache — hardware can change value outside of software" |
| `static` in function | "Value persists between calls — like a module-level variable with function scope" |
| `const char *` | "Pointer to constant char — can't modify what it points to" |
| `char * const` | "Constant pointer to char — pointer can't change, value can" |
| Stack vs heap | "Stack: automatic, limited, fast. Heap: dynamic, flexible, fragmentation risk. Embedded: prefer stack." |
| Endianness | "Big-endian: MSB first (network byte order). Little-endian: LSB first (x86, ARM). Always check when parsing protocol packets." |
| `NULL` pointer deref | "Always check pointer before deref. In embedded: dereference of NULL may hard-fault silently." |
| Integer overflow | "Use `uint32_t` not `int` for bit ops. Use `left + (right - left) / 2` not `(left + right) / 2`." |

---

## RESOURCES USED IN PAST PREP
- `embedded-c-fundamentals/volatile-static-extern-reference.md`
- `embedded-c-fundamentals/advanced-concepts-reference.md`
- `memory-management/embedded-memory-reference.md`
- HackerRank Software Engineer Prep Kit (10 problems done)
- https://www.w3resource.com/c-programming-exercises/

**HackerRank practice link for July 24:** https://hr.gs/3c5ca27
