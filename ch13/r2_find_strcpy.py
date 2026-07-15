#!/usr/bin/env python3
"""
radare2 script to find all strcpy() references in a binary.
Usage: r2 -q -i r2_find_strcpy.py /path/to/binary
"""

import r2pipe

def find_strcpy_usage(binary_path):
    r2 = r2pipe.open(binary_path)
    r2.cmd("aaa")  # Full analysis

    # Find strcpy in imports
    strcpy_refs = r2.cmd("axt `is~strcpy[2]`").split()

    print(f"\n=== strcpy() usage analysis for {binary_path} ===")
    print(f"Found {len(strcpy_refs)} references to strcpy\n")

    for ref in strcpy_refs:
        ref = ref.strip()
        if not ref:
            continue
        print(f"strcpy called at: {ref}")
        print(r2.cmd(f"pd 10 @ {ref}"))
        print("-" * 40)

    r2.quit()


if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python r2_find_strcpy.py <binary>")
        sys.exit(1)
    find_strcpy_usage(sys.argv[1])
