# Chapter 16: Buffer Overflows & Stack Smashing

## Listings
- `vuln.c` — ret2shellcode target (no protections)
- `exploit_ret2shellcode.py` — Shellcode injection exploit
- `exploit_ret2libc.py` — ret2libc ROP exploit
- `challenge.c` — Canary + ASLR + format string leak challenge

## Labs
1. Guided Lab 1: ret2shellcode (NX disabled)
2. Guided Lab 2: ret2libc with ROP (NX enabled)
3. Unguided Challenge: Bypass canary + ASLR via format string leak
