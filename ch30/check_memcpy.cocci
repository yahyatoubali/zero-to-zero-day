@@
expression dst, src, n;
identifier f;
@@

f(...) {
    <+...
    memcpy(dst, src, n)
    ... when != n <= sizeof(*dst)
    ... when != n < sizeof(*dst)
    when != sizeof(*dst) >= n
    ...+>
}
