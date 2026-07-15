// O-3: Android Binder Analysis — Binder ioctl fuzzer
// Compile for Android NDK or Linux with binder headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define BINDER_WRITE_READ 0xc0186201

struct binder_write_read {
    unsigned long write_size;
    unsigned long write_consumed;
    unsigned long write_buffer;
    unsigned long read_size;
    unsigned long read_consumed;
    unsigned long read_buffer;
};

int main(void) {
    int fd = open("/dev/binder", O_RDWR);
    if (fd < 0) {
        perror("open /dev/binder (run as root or in Android emulator)");
        return 1;
    }

    struct binder_write_read bwr = {0};
    char buf[256];
    memset(buf, 0x41, sizeof(buf));

    bwr.write_size = sizeof(buf);
    bwr.write_buffer = (unsigned long)buf;

    int ret = ioctl(fd, BINDER_WRITE_READ, &bwr);
    printf("ioctl returned: %d\n", ret);
    close(fd);
    return 0;
}
