#!/usr/bin/env python3
"""
angr solution script for crackme.c
Finds the correct 6-character password using symbolic execution.
"""
import angr
import claripy

proj = angr.Project('./crackme', auto_load_libs=False)

# Create state at main with symbolic argv[1]
argv1 = claripy.BVS('argv1', 8 * 7)  # 6 chars + null
state = proj.factory.entry_state(
    args=['./crackme', argv1]
)

simgr = proj.factory.simulation_manager(state)

# Find the "Correct!" address
simgr.explore(find=0x4011a2)  # Replace with actual address from objdump

if simgr.found:
    found = simgr.found[0]
    solution = found.solver.eval(argv1, cast_to=bytes)
    print(f"Password: {solution}")
else:
    print("No solution found")
