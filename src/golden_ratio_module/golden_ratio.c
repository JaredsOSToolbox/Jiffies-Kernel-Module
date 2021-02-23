#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/gcd.h>
#include <linux/hash.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jared Dyreson");

MODULE_DESCRIPTION("stay gold pony boy");
MODULE_VERSION("0.01");

#define BUFFER_SIZE 128


static int __init proc_init(void) {
    printk(KERN_INFO "The golden ratio has the value of %zu\n", GOLDEN_RATIO_PRIME);
    /*proc_create(PROC_NAME, 0666, NULL, &proc_ops);*/
    return 0;
}
static void __exit proc_exit(void) {
    printk(KERN_INFO "The resultant of gcd(3300, 24) is %zu\n", gcd(3300, 24));
    /*remove_proc_entry(PROC_NAME, NULL);*/
}

module_init(proc_init);
module_exit(proc_exit);
