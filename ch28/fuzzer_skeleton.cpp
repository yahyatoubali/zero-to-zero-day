// fuzzer_skeleton.cpp — libFuzzer harness skeleton
// Compile: clang++ -g -fsanitize=address,fuzzer -o fuzzer fuzzer_skeleton.cpp
#include <cstdint>
#include <cstddef>

extern "C" int parse_packet(const uint8_t *buf, size_t len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    parse_packet(data, size);
    return 0;
}
