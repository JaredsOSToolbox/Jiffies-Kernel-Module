#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

/*
 * Sourced from here: https://blog.sourcerer.io/writing-a-simple-linux-kernel-module-d9dc3762c234
*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jared Dyreson");

MODULE_DESCRIPTION("Jiffies Module");
MODULE_VERSION("0.01");

static int __init jiffie_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    printk(KERN_INFO "Value of the golden ratio is %lu\n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "Value of jiffies right now is: %lu\n", jiffies);
    printk(KERN_INFO "Value of HZ on this machine is : %lu\n", HZ);
    return 0;
}
static void __exit jiffie_exit(void) {
    printk(KERN_INFO "The value of the GCD of 3300 and 24 is %lu\n", gcd(3300, 24));
    printk(KERN_INFO "Value of jiffies after leaving the kernel is: %lu\n", jiffies);
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(jiffie_init);
module_exit(jiffie_exit);
