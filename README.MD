to run the program: gcc stack.c -o stack then gcc stack.c -o stack  
./stack

# c-practice

Nice — I’ll show **every single step** (for each operand & operator) using one non-trivial example so you can see exactly how the stacks and outputs change.

**Expression (infix):**

```
A + B * ( C - D ) ^ E - F / G
```

Tokens: `A  +  B  *  (  C  -  D  )  ^  E  -  F  /  G`

---

# Infix → Postfix (Shunting-Yard) — step by step

Rules reminder (used below):

- operands → immediately to output.
- operators → pop from operator stack while top has **greater precedence**, or **equal precedence and left-associative**; then push current operator.
- `(` pushed, `)` pops until matching `(`.
- Precedences: `^` > `*` `/` > `+` `-`. `^` is **right-associative**; others are left-assoc.

Stack shown with **top on the right**.

| Step | Token | Action (what we do)                                                                                                     | Stack (top → right) | Output (postfix so far)     |
| ---: | :---: | :---------------------------------------------------------------------------------------------------------------------- | :------------------ | :-------------------------- |
|    0 |   —   | start                                                                                                                   | `[]`                | ` `                         |
|    1 |  `A`  | operand → append to output                                                                                              | `[]`                | `A`                         |
|    2 |  `+`  | push `+`                                                                                                                | `[ + ]`             | `A`                         |
|    3 |  `B`  | operand → append                                                                                                        | `[ + ]`             | `A B`                       |
|    4 |  `*`  | `*` has higher prec than `+` → push `*`                                                                                 | `[ + , * ]`         | `A B`                       |
|    5 |  `(`  | push `(`                                                                                                                | `[ + , * , ( ]`     | `A B`                       |
|    6 |  `C`  | operand → append                                                                                                        | `[ + , * , ( ]`     | `A B C`                     |
|    7 |  `-`  | top is `(` → push `-`                                                                                                   | `[ + , * , ( , - ]` | `A B C`                     |
|    8 |  `D`  | operand → append                                                                                                        | `[ + , * , ( , - ]` | `A B C D`                   |
|    9 |  `)`  | pop until `(`: pop `-` → output; discard `(`                                                                            | `[ + , * ]`         | `A B C D -`                 |
|   10 |  `^`  | `^` has higher prec than `*` → push `^`                                                                                 | `[ + , * , ^ ]`     | `A B C D -`                 |
|   11 |  `E`  | operand → append                                                                                                        | `[ + , * , ^ ]`     | `A B C D - E`               |
|   12 |  `-`  | pop higher/equal: pop `^` → out; pop `*` → out; `+` has equal prec and `-` is left-assoc → pop `+` → out; then push `-` | `[ - ]`             | `A B C D - E ^ * +`         |
|   13 |  `F`  | operand → append                                                                                                        | `[ - ]`             | `A B C D - E ^ * + F`       |
|   14 |  `/`  | `/` has higher prec than `-` → push `/`                                                                                 | `[ - , / ]`         | `A B C D - E ^ * + F`       |
|   15 |  `G`  | operand → append                                                                                                        | `[ - , / ]`         | `A B C D - E ^ * + F G`     |
|   16 |  end  | pop remaining ops: pop `/` then `-` → output                                                                            | `[]`                | `A B C D - E ^ * + F G / -` |

**Final Postfix:**

```
A B C D - E ^ * + F G / -
```

---

# Postfix → Infix (stack) — step by step

Algorithm: scan postfix left→right. Push operands. On operator, pop **right operand (b)** then **left operand (a)**, form `(a op b)` and push back.

Postfix tokens: `A B C D - E ^ * + F G / -`

| Step | Token | Action                                                                | Stack (top → right)                         |
| ---: | :---: | :-------------------------------------------------------------------- | :------------------------------------------ |
|    0 |   —   | start                                                                 | `[]`                                        |
|    1 |  `A`  | push `A`                                                              | `[ A ]`                                     |
|    2 |  `B`  | push `B`                                                              | `[ A , B ]`                                 |
|    3 |  `C`  | push `C`                                                              | `[ A , B , C ]`                             |
|    4 |  `D`  | push `D`                                                              | `[ A , B , C , D ]`                         |
|    5 |  `-`  | pop `D`, `C` → push `(C - D)`                                         | `[ A , B , (C - D) ]`                       |
|    6 |  `E`  | push `E`                                                              | `[ A , B , (C - D) , E ]`                   |
|    7 |  `^`  | pop `E`, `(C - D)` → push `((C - D) ^ E)`                             | `[ A , B , ((C - D) ^ E) ]`                 |
|    8 |  `*`  | pop `((C - D)^E)`, `B` → push `(B * ((C - D) ^ E))`                   | `[ A , (B * ((C - D) ^ E)) ]`               |
|    9 |  `+`  | pop `(B*...)`, `A` → push `(A + (B * ((C - D) ^ E)))`                 | `[ (A + (B * ((C - D) ^ E))) ]`             |
|   10 |  `F`  | push `F`                                                              | `[ (A + (B * ((C - D) ^ E))) , F ]`         |
|   11 |  `G`  | push `G`                                                              | `[ (A + (B * ((C - D) ^ E))) , F , G ]`     |
|   12 |  `/`  | pop `G`, `F` → push `(F / G)`                                         | `[ (A + (B * ((C - D) ^ E))) , (F / G) ]`   |
|   13 |  `-`  | pop `(F/G)`, `(A+...)` → push `((A + (B * ((C - D) ^ E))) - (F / G))` | `[ ((A + (B * ((C - D) ^ E))) - (F / G)) ]` |

**Final Infix (fully parenthesized):**

```
((A + (B * ((C - D) ^ E))) - (F / G))
```

(You can drop the outermost parentheses for normal notation.)

---

# Postfix → Prefix (stack) — step by step

Algorithm: scan postfix left→right. Push operands. On operator, pop `b`, pop `a`, form `operator a b` (prefix) and push.

Postfix tokens: `A B C D - E ^ * + F G / -`

| Step | Token | Action                                                    | Stack (top → right)             |
| ---: | :---: | :-------------------------------------------------------- | :------------------------------ |
|    0 |   —   | start                                                     | `[]`                            |
|    1 |  `A`  | push `A`                                                  | `[ A ]`                         |
|    2 |  `B`  | push `B`                                                  | `[ A , B ]`                     |
|    3 |  `C`  | push `C`                                                  | `[ A , B , C ]`                 |
|    4 |  `D`  | push `D`                                                  | `[ A , B , C , D ]`             |
|    5 |  `-`  | pop `D`, `C` → push `- C D`                               | `[ A , B , - C D ]`             |
|    6 |  `E`  | push `E`                                                  | `[ A , B , - C D , E ]`         |
|    7 |  `^`  | pop `E`, `- C D` → push `^ - C D E`                       | `[ A , B , ^ - C D E ]`         |
|    8 |  `*`  | pop `^ - C D E`, `B` → push `* B ^ - C D E`               | `[ A , * B ^ - C D E ]`         |
|    9 |  `+`  | pop `*...`, `A` → push `+ A * B ^ - C D E`                | `[ + A * B ^ - C D E ]`         |
|   10 |  `F`  | push `F`                                                  | `[ + A * B ^ - C D E , F ]`     |
|   11 |  `G`  | push `G`                                                  | `[ + A * B ^ - C D E , F , G ]` |
|   12 |  `/`  | pop `G`, `F` → push `/ F G`                               | `[ + A * B ^ - C D E , / F G ]` |
|   13 |  `-`  | pop `/ F G`, `+ A ...` → push `- + A * B ^ - C D E / F G` | `[ - + A * B ^ - C D E / F G ]` |

**Final Prefix:**

```
- + A * B ^ - C D E / F G
```

(Readable grouping: `- ( + A ( * B ( ^ ( - C D ) E ) ) ) ( / F G )`)

---

# Infix → Prefix (recommended two-step method)

Easiest/most reliable approach: **Infix → Postfix** (we already did) then **Postfix → Prefix** (we already did). So:

- Infix → Postfix result: `A B C D - E ^ * + F G / -`
- Postfix → Prefix result: `- + A * B ^ - C D E / F G`

So **Final Prefix** (from original infix):

```
- + A * B ^ - C D E / F G
```

> Note: another classic way is to reverse the infix, swap parentheses, run the shunting yard (to produce postfix of the reversed), then reverse result — that also works but is easy to get wrong if you mis-handle associativity, so I prefer the two-step method above.

---

# Prefix → Infix (stack) — step by step

Algorithm: scan prefix **right→left**. Push operands. If operator encountered, pop `a` (first popped), pop `b` (second), form `(a op b)` and push. (This ordering recovers left/right correctly.)

Prefix tokens used: `-  +  A  *  B  ^  -  C  D  E  /  F  G`

Right→left sequence: `G  F  /  E  D  C  -  ^  B  *  A  +  -`

| Step | Token | Action                                                                    | Stack (top → right)                         |
| ---: | :---: | :------------------------------------------------------------------------ | :------------------------------------------ |
|    0 |   —   | start                                                                     | `[]`                                        |
|    1 |  `G`  | push `G`                                                                  | `[ G ]`                                     |
|    2 |  `F`  | push `F`                                                                  | `[ G , F ]`                                 |
|    3 |  `/`  | pop `F`, `G` → push `(F / G)`                                             | `[ (F / G) ]`                               |
|    4 |  `E`  | push `E`                                                                  | `[ (F / G) , E ]`                           |
|    5 |  `D`  | push `D`                                                                  | `[ (F / G) , E , D ]`                       |
|    6 |  `C`  | push `C`                                                                  | `[ (F / G) , E , D , C ]`                   |
|    7 |  `-`  | pop `C`, `D` → push `(C - D)`                                             | `[ (F / G) , E , (C - D) ]`                 |
|    8 |  `^`  | pop `(C - D)`, `E` → push `((C - D) ^ E)`                                 | `[ (F / G) , ((C - D) ^ E) ]`               |
|    9 |  `B`  | push `B`                                                                  | `[ (F / G) , ((C - D) ^ E) , B ]`           |
|   10 |  `*`  | pop `B`, `((C - D)^E)` → push `(B * ((C - D) ^ E))`                       | `[ (F / G) , (B * ((C - D) ^ E)) ]`         |
|   11 |  `A`  | push `A`                                                                  | `[ (F / G) , (B * ((C - D) ^ E)) , A ]`     |
|   12 |  `+`  | pop `A`, `(B * ...)` → push `(A + (B * ((C - D) ^ E)))`                   | `[ (F / G) , (A + (B * ((C - D) ^ E))) ]`   |
|   13 |  `-`  | pop `(A + ...)`, `(F / G)` → push `((A + (B * ((C - D) ^ E))) - (F / G))` | `[ ((A + (B * ((C - D) ^ E))) - (F / G)) ]` |

**Final Infix:**

```
((A + (B * ((C - D) ^ E))) - (F / G))
```

---

# Prefix → Postfix (stack) — step by step

Algorithm: scan prefix **right→left**. Push operands. If operator encountered, pop `a`, pop `b`, form `a b operator` (postfix) and push.

Using same prefix tokens, right→left sequence: `G F / E D C - ^ B * A + -`

| Step | Token | Action                                                    | Stack (top → right)             |
| ---: | :---: | :-------------------------------------------------------- | :------------------------------ |
|    0 |   —   | start                                                     | `[]`                            |
|    1 |  `G`  | push `G`                                                  | `[ G ]`                         |
|    2 |  `F`  | push `F`                                                  | `[ G , F ]`                     |
|    3 |  `/`  | pop `F`, `G` → push `F G /`                               | `[ F G / ]`                     |
|    4 |  `E`  | push `E`                                                  | `[ F G / , E ]`                 |
|    5 |  `D`  | push `D`                                                  | `[ F G / , E , D ]`             |
|    6 |  `C`  | push `C`                                                  | `[ F G / , E , D , C ]`         |
|    7 |  `-`  | pop `C`, `D` → push `C D -`                               | `[ F G / , E , C D - ]`         |
|    8 |  `^`  | pop `C D -`, `E` → push `C D - E ^`                       | `[ F G / , C D - E ^ ]`         |
|    9 |  `B`  | push `B`                                                  | `[ F G / , C D - E ^ , B ]`     |
|   10 |  `*`  | pop `B`, `C D - E ^` → push `B C D - E ^ *`               | `[ F G / , B C D - E ^ * ]`     |
|   11 |  `A`  | push `A`                                                  | `[ F G / , B C D - E ^ * , A ]` |
|   12 |  `+`  | pop `A`, `B C ...` → push `A B C D - E ^ * +`             | `[ F G / , A B C D - E ^ * + ]` |
|   13 |  `-`  | pop `A B ...`, `F G /` → push `A B C D - E ^ * + F G / -` | `[ A B C D - E ^ * + F G / - ]` |

**Final Postfix:**

```
A B C D - E ^ * + F G / -
```

(Which matches the earlier postfix.)

---

## Quick summary (results for the example)

- Infix: `A + B * (C - D) ^ E - F / G`
- Postfix: `A B C D - E ^ * + F G / -`
- Prefix: `- + A * B ^ - C D E / F G`
- All conversions shown **token-by-token** above.

---

If you want, I can:

- produce a **C program** (single file) that prints the step-by-step stack/output states (very handy for labs), or
- produce a small **interactive demo** (Python / JS) where you can paste any expression and see the per-token table.

Which one would you like next?
