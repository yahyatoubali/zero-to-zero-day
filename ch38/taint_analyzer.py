#!/usr/bin/env python3
"""
Toy Taint Analyzer — Chapter 38 Guided Lab

Builds a miniature taint tracker for a toy IR with five instructions:
  dst = src                # mov
  dst = src1 + src2        # add
  dst = src1 * src2        # mul
  store(dst, src)          # store src at address dst
  src = load(addr)         # load from address
  branch dst, Ltrue, Lfalse
  label:
"""

TOY_SOURCE = """
x = read()         # source
y = x + 1
z = 0
if y > 10:
    z = y
    w = load(z)
    syscall(w)     # sink
else:
    syscall(0)     # also a sink
"""

class TaintTracker:
    def __init__(self):
        self.tainted = set()
        self.sources = {'read'}
        self.sinks = {'syscall'}
        self.propagators = {'mov', 'add', 'mul', 'load'}

    def parse_ir(self, code):
        instructions = []
        for line in code.strip().split('\n'):
            line = line.split('#')[0].strip()
            if not line:
                continue
            instructions.append(line)
        return instructions

    def analyze(self, ir):
        lines = self.parse_ir(ir)
        for line in lines:
            if '=' in line:
                dst, expr = line.split('=', 1)
                dst = dst.strip()
                expr = expr.strip()

                if '(' in expr:  # function call
                    func_name = expr.split('(')[0].strip()
                    if func_name in self.sources:
                        self.tainted.add(dst)
                        print(f"[SOURCE] {dst} is tainted (from {func_name})")
                elif '+' in expr:
                    srcs = [s.strip() for s in expr.split('+')]
                    if any(s in self.tainted for s in srcs):
                        self.tainted.add(dst)
                        print(f"[PROPAGATE] {dst} is tainted (from {srcs})")
                elif '*' in expr:
                    srcs = [s.strip() for s in expr.split('*')]
                    if any(s in self.tainted for s in srcs):
                        self.tainted.add(dst)
                        print(f"[PROPAGATE] {dst} is tainted (from {srcs})")
                elif expr.startswith('load('):
                    addr = expr[5:-1].strip()
                    if addr in self.tainted:
                        self.tainted.add(dst)
                        print(f"[PROPAGATE] {dst} is tainted (load from {addr})")
                else:
                    if expr in self.tainted:
                        self.tainted.add(dst)
                        print(f"[PROPAGATE] {dst} is tainted (from {expr})")

            elif line.startswith('syscall('):
                arg = line[8:-1].strip()
                if arg in self.tainted:
                    print(f"[ALERT] Tainted data reaches sink: syscall({arg})")
                else:
                    print(f"[INFO] syscall({arg}) — not tainted")

        return self.tainted


if __name__ == "__main__":
    tracker = TaintTracker()
    print("=== Toy Taint Analyzer ===\n")
    print("Input IR:")
    print(TOY_SOURCE)
    print("\n" + "=" * 40)
    print("\nAnalysis Results:")
    tainted = tracker.analyze(TOY_SOURCE)
    print(f"\nFinal tainted set: {tainted}")
