#!/usr/bin/env python3
"""
bpftrace one-liners for kernel tracing (Chapter 29 examples)
"""
import subprocess

examples = [
    'bpftrace -e \'kprobe:do_sys_open { printf("open: %s\\n", str(args->filename)); }\'',
    'bpftrace -e \'kprobe:kmem_cache_alloc { @[str(args->cachep->name)] = count(); }\'',
    'bpftrace -e \'kprobe:commit_creds { printf("UID changed: %d\\n", args->new->uid.val); }\'',
    'bpftrace -e \'kprobe:tcp_sendmsg { printf("len: %d\\n", args->size); }\'',
]

for i, ex in enumerate(examples):
    print(f"Example {i+1}:")
    print(f"  {ex}")
    print()
