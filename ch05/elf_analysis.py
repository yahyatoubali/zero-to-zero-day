from pwn import *

elf = ELF('./vuln')

print(f"Entry point: {hex(elf.entry)}")
print(f"PIE: {elf.pie}")
print(f"NX: {elf.execstack}")

for section in elf.sections:
    print(f"  {section.name}: {hex(section.header.sh_addr)} size={section.header.sh_size}")

print(f"\nGOT entries:")
for name, addr in elf.got.items():
    print(f"  {name}: {hex(addr)}")

print(f"\nPLT entries:")
for name, addr in elf.plt.items():
    print(f"  {name}: {hex(addr)}")
