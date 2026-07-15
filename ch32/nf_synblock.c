// nf_synblock.c — Netfilter hook to block TCP SYN to port 22
// Build: make -C /lib/modules/$(uname -r)/build M=$PWD modules
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

static struct nf_hook_ops nfho;

static unsigned int hook_func(void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state) {
    struct iphdr *iph = ip_hdr(skb);
    struct tcphdr *tcph;

    if (!iph || iph->protocol != IPPROTO_TCP)
        return NF_ACCEPT;

    tcph = tcp_hdr(skb);
    if (ntohs(tcph->dest) == 22 && tcph->syn && !tcph->ack)
        return NF_DROP;

    return NF_ACCEPT;
}

static int __init init(void) {
    nfho.hook = hook_func;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = NFPROTO_IPV4;
    nfho.priority = NF_IP_PRI_FIRST;
    return nf_register_net_hook(&init_net, &nfho);
}

static void __exit exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
}

module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");
