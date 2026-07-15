#!/usr/bin/env bash
set -euo pipefail

echo "[*] Zero to Zero-Day — Automated Lab Setup"
echo "[*] Target: Ubuntu 22.04 LTS"

# System packages
sudo apt-get update
sudo apt-get install -y \
    build-essential gdb gcc-11 g++-11 clang-14 nasm \
    python3.10 python3-pip python3-dev \
    qemu-system-x86 qemu-utils \
    curl wget git \
    libcapstone-dev elfutils \
    linux-headers-$(uname -r) \
    bc flex bison libncurses-dev libssl-dev

# Python packages
python3 -m pip install --upgrade pip
python3 -m pip install pwntools angr claripy \
    capstone unicorn keystone-engine \
    ropper ROPgadget \
    z3-solver

# pwndbg
if [ ! -d "$HOME/pwndbg" ]; then
    git clone https://github.com/pwndbg/pwndbg "$HOME/pwndbg"
    cd "$HOME/pwndbg"
    ./setup.sh
fi

# GEF
if [ ! -f "$HOME/.gdbinit-gef.py" ]; then
    wget -O "$HOME/.gdbinit-gef.py" https://github.com/hugsy/gef/raw/main/gef.py
    echo "source $HOME/.gdbinit-gef.py" >> "$HOME/.gdbinit"
fi

# AFL++ (from source for latest)
if [ ! -d "$HOME/AFLplusplus" ]; then
    git clone https://github.com/AFLplusplus/AFLplusplus "$HOME/AFLplusplus"
    cd "$HOME/AFLplusplus"
    make -j$(nproc)
    sudo make install
fi

echo "[+] Setup complete. Run 'pwndbg' or 'python3' to verify."
