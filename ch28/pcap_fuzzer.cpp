// pcap_fuzzer.cpp — libFuzzer harness for PCAP parser
// Compile: clang++ -g -fsanitize=address,fuzzer -o pcap_fuzzer pcap_fuzzer.cpp
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>

// Simple PCAP parser for fuzzing
extern "C" int parse_pcap(const uint8_t *data, size_t size) {
    if (size < 24) return -1;  // Minimum PCAP header

    // Parse global header
    uint32_t magic = *(uint32_t *)(data);
    if (magic != 0xa1b2c3d4 && magic != 0xd4c3b2a1) return -1;

    uint16_t link_type = *(uint16_t *)(data + 20);

    // Parse packets
    size_t offset = 24;
    while (offset + 16 < size) {
        uint32_t incl_len = *(uint32_t *)(data + offset + 8);

        if (offset + 16 + incl_len > size) break;

        // Process link-layer data based on type
        if (link_type == 1 && incl_len >= 14) {
            // Ethernet frame
            uint16_t eth_type = *(uint16_t *)(data + offset + 16 + 12);
            if (eth_type == 0x0800 && incl_len >= 34) {
                // IPv4 — check for potential vulnerabilities
                uint8_t ip_ver = (data[offset + 16 + 14] >> 4) & 0x0F;
                if (ip_ver == 4) {
                    // Exercise more parsing paths
                    size_t header_len = (data[offset + 16 + 14] & 0x0F) * 4;
                    if (header_len >= 20 && incl_len > 14 + header_len) {
                        uint8_t protocol = data[offset + 16 + 23];
                        if (protocol == 6 && incl_len > 14 + header_len + 20) {
                            // TCP — parse ports
                            uint16_t dport = *(uint16_t *)(data + offset + 16 + header_len + 2);
                            if (dport == 80 || dport == 443) {
                                // HTTP/HTTPS traffic
                            }
                        }
                    }
                }
            }
        }
        offset += 16 + incl_len;
    }
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    parse_pcap(data, size);
    return 0;
}
