# Few-Shot Examples — LLM-Assisted Code Audit

## Example 1: Buffer Overflow (True Positive)

### Input Code
```c
void process_message(const char *input) {
    char buf[64];
    char cmd[128];
    int len = strlen(input);

    if (len > 64) {
        printf("Message too long\n");
        return;
    }

    strcpy(buf, input);
    sprintf(cmd, "echo %s", buf);
    system(cmd);
}
```

### Expected LLM Output
- **Type**: Buffer overflow + Command injection
- **Severity**: CRITICAL
- **Location**: process_message:9
- **Description**: Off-by-one: buf is 64 bytes, check is `len > 64`, so len=64 passes the check but strcpy writes 65 bytes (64 + null). Additionally, system(cmd) is command injection via shell metacharacters.
- **Confidence**: HIGH

---

## Example 2: Missing NULL Check (True Positive)

### Input Code
```c
void process(struct foo *p) {
    char *buf = kmalloc(64, GFP_KERNEL);
    buf[0] = 0;
    strcpy(buf, p->name);
}
```

### Expected LLM Output
- **Type**: Missing NULL check after allocation
- **Severity**: MEDIUM
- **Location**: process:2
- **Description**: kmalloc may return NULL. Dereferencing buf without a NULL check causes a kernel NULL pointer dereference.
- **Confidence**: HIGH
