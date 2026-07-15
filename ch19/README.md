# Chapter 19: Return-Oriented Programming

## Listings
- `rop_lab.c` — Two-stage ROP chain target
- `exploit_rop.py` — Stage 1 leak + Stage 2 ret2libc exploit

## Lab
Build a ROP chain: leak libc address, compute base, call system("/bin/sh").
