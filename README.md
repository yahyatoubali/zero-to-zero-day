# Zero to Zero-Day: The Complete Course in Vulnerability Research

<p align="center">
  <a href="https://a.co/d/07NGUMaN">
    <img src="https://pictures.abebooks.com/isbn/9798186975847-us.jpg" alt="Zero to Zero-Day Book Cover" width="300"/>
  </a>
</p>

<p align="center">
  <strong>Available on Amazon:</strong>
  <a href="https://a.co/d/07NGUMaN">https://a.co/d/07NGUMaN</a>
</p>

---

This repository contains all companion materials for **Zero to Zero-Day: The Complete Course in Vulnerability Research** by Yahya Toubali.

Each chapter has its own directory (`ch01/` through `ch43/`) containing:
- Source code listings (numbered to match the book)
- Lab solution scripts and exploit proofs-of-concept
- Dockerfiles for reproducible lab environments
- Walkthroughs and expected output

## Quick Start

```bash
git clone https://github.com/yahyatoubali/zero-to-zero-day
cd zero-to-zero-day

# Automated setup (installs pwndbg, pwntools, gef, AFL++, angr)
chmod +x scripts/setup.sh && ./scripts/setup.sh

# Or use Docker for an isolated environment:
docker build -t z2z:ubuntu22.04 -f environments/Dockerfile.ubuntu22.04 .
docker run -it z2z:ubuntu22.04
```

## Prerequisites

The lab environment appendix in the book pins these tool versions:

| Tool | Version |
|------|---------|
| Ubuntu | 22.04 LTS |
| Linux Kernel | 6.2.x |
| GCC | 11.4 |
| Clang | 14.0 |
| Python | 3.10 |
| GDB | 13.1 |
| pwndbg | 2024.08 |
| pwntools | Latest |
| AFL++ | 4.09 |
| libFuzzer | (Clang 14 built-in) |
| Syzkaller | master (~2024.12) |
| angr | 9.2 |
| Triton | 0.9 |
| KLEE | 2.3 |
| QEMU | 8.1 |

## Repository Structure

```
zero-to-zero-day/
├── README.md
├── environments/       # Dockerfiles for reproducible labs
│   ├── Dockerfile.ubuntu22.04
│   ├── Dockerfile.glibc-2.26
│   └── Dockerfile.kernel-lab
├── scripts/
│   └── setup.sh        # Automated tool installation
├── prompts/            # LLM prompt templates (Chapter 39)
├── ch01/ through ch43/ # Chapter companion materials
```

## Chapter Index

| Volume | Chapters | Topic Area |
|--------|----------|------------|
| **I: Foundations** | 1–15 | Bits, CPU, Memory, Linux, ELF, C, Assembly, Reversing |
| **II: The Exploitation Engine** | 16–30 | Memory Corruption, ROP, Heap, Kernel Exploitation, Fuzzing, Auditing |
| **III: The Kernel & Beyond** | 31–43 | Filesystems, Networking, Hypervisors, Browsers, Mobile, AI-Assisted Research |

## License

All code in this repository is provided for educational and research purposes only.
