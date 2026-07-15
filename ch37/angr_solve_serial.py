#!/usr/bin/env python3
"""
angr solution script for serial.c
Finds a valid 8-character serial number that sums to 1337.
"""
import angr
import claripy

proj = angr.Project('./serial', auto_load_libs=False)

# Symbolic argv[1] — 8 chars + null
argv1 = claripy.BVS('argv1', 8 * 9)
state = proj.factory.entry_state(
    args=['./serial', argv1]
)

simgr = proj.factory.simulation_manager(state)

# Find "Valid serial!" print address
simgr.explore(find=0x4011b0)  # Replace with actual address

if simgr.found:
    found = simgr.found[0]
    solution = found.solver.eval(argv1, cast_to=bytes)
    print(f"Serial: {solution}")
else:
    print("No solution found")
