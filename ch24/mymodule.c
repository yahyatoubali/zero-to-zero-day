// mymodule.c — Vulnerable kernel module with procfs entry
// Build: make -C /lib/modules/$(uname -r)/build M=$PWD modules
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "vuln"
#define BUF_SIZE 32

static char kernel_buf[BUF_SIZE];

static ssize_t proc_write(struct file *file, const char __user *ubuf,
                          size_t len, loff_t *off) {
    // VULNERABILITY: copies user input into fixed-size stack buffer
    // without checking length
    char stack_buf[BUF_SIZE];

    if (len > BUF_SIZE) {
        printk(KERN_WARNING "Input too long: %zu\n", len);
        // BUG: still copies even when len > BUF_SIZE!
    }

    if (copy_from_user(stack_buf, ubuf, len)) {
        return -EFAULT;
    }

    memcpy(kernel_buf, stack_buf, len);
    return len;
}

static const struct proc_ops proc_fops = {
    .proc_write = proc_write,
};

static int __init mymodule_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_fops);
    printk(KERN_INFO "mymodule loaded. /proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit mymodule_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "mymodule unloaded\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
