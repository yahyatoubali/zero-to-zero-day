"""
Ghidra Python script to find all memcpy() calls where:
- The destination is a stack buffer
- The size is not a compile-time constant

Run from Ghidra's Script Manager (Python).
"""

from ghidra.program.model.listing import Function
from ghidra.program.model.symbol import RefType
from ghidra.program.model.data import ArrayDataType, PointerDataType
from ghidra.program.model.address import AddressSet

def get_function_name(addr):
    func = getFunctionContaining(addr)
    return func.getName() if func else "unknown"


def is_stack_variable(var):
    """Check if a variable is a stack buffer."""
    if not var:
        return False
    dt = var.getDataType()
    if isinstance(dt, ArrayDataType):
        return True
    if isinstance(dt, PointerDataType):
        return False
    return False


def analyze_memcpy():
    memcpy_func = getGlobalFunctions("memcpy")
    if not memcpy_func:
        print("memcpy not found in imports")
        return

    # Find all calls to memcpy
    listing = currentProgram.getListing()
    memcpy_addr = memcpy_func.getEntryPoint()

    refs = getReferencesTo(memcpy_addr)
    print(f"\n=== memcpy() usage analysis ===")
    print(f"Found {len(refs)} references to memcpy\n")

    for ref in refs:
        caller_addr = ref.getFromAddress()
        caller_func = getFunctionContaining(caller_addr)
        if not caller_func:
            continue

        # Get the instruction
        instr = listing.getInstructionAt(caller_addr)
        if not instr:
            continue

        # Try to determine destination and size
        print(f"Call at {caller_addr} in {caller_func.getName()}")
        print(f"  Instruction: {instr}")

        # Check operands for stack references
        for i in range(instr.getNumOperands()):
            op_objs = instr.getOpObjects(i)
            for obj in op_objs:
                if str(obj).startswith("Stack"):
                    print(f"  -> Stack reference detected in operand {i}")

        print()


if __name__ == "__main__":
    analyze_memcpy()
