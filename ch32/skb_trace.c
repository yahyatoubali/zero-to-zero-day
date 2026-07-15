// skb_trace.c — Kprobe module to trace sk_buff lifecycle
// Build: make -C /lib/modules/$(uname -r)/build M=$PWD modules
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/skbuff.h>

static struct kprobe kp;

static int handler_pre(struct kprobe *p, struct pt_regs *regs) {
    struct sk_buff *skb = (struct sk_buff *)regs->di;
    if (skb) {
        printk(KERN_INFO "kfree_skb: proto=%u len=%u\n",
               skb->protocol, skb->len);
    }
    return 0;
}

static int __init kprobe_init(void) {
    kp.symbol_name = "__kfree_skb";
    kp.pre_handler = handler_pre;
    return register_kprobe(&kp);
}

static void __exit kprobe_exit(void) {
    unregister_kprobe(&kp);
}

module_init(kprobe_init);
module_exit(kprobe_exit);
MODULE_LICENSE("GPL");
