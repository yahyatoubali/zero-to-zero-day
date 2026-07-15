// O-1: Kernel Module Bug (privilege escalation)
// Vulnerable kernel module with ioctl UAF
// Build: make -C /lib/modules/$(uname -r)/build M=$PWD modules
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

struct vuln_data {
    void *ptr;
    int size;
};

static struct vuln_data *data;

static long vuln_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case 0xdead:
            // Allocate
            data = kmalloc(sizeof(struct vuln_data), GFP_KERNEL);
            if (!data) return -ENOMEM;
            data->ptr = kmalloc(64, GFP_KERNEL);
            data->size = 64;
            break;
        case 0xbeef:
            // Free — BUG: no NULL assignment after kfree!
            kfree(data->ptr);
            break;
        case 0xcafe:
            // Use-after-free
            if (copy_from_user(data->ptr, (void __user *)arg, data->size)) {
                return -EFAULT;
            }
            break;
    }
    return 0;
}

static const struct file_operations vuln_fops = {
    .unlocked_ioctl = vuln_ioctl,
};

static struct miscdevice vuln_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vuln_dev",
    .fops = &vuln_fops,
};

static int __init init(void) {
    return misc_register(&vuln_dev);
}

static void __exit exit(void) {
    misc_deregister(&vuln_dev);
}

module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");
