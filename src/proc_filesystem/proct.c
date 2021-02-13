#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/procs.h>

/*
 * Sourced from here: https://blog.sourcerer.io/writing-a-simple-linux-kernel-module-d9dc3762c234
*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jared Dyreson");

MODULE_DESCRIPTION("proc module");
MODULE_VERSION("0.01");

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
    .owner = "proc module",
    .read = proc_read,
};


static int __init proc_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    return 0;
}
static void __exit proc_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
}

module_init(proc_init);
module_exit(proc_exit);
