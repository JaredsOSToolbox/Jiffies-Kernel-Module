#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

/*
 * ^ instead of <asm/uaccess.h>
 * https://lkml.org/lkml/2017/9/30/189
 * There seems to be a kernel bug here
*/

/*
 * Since I was having issues with the proc file system, I decided to use this blog post for help
 * https://tuxthink.blogspot.com/2019/10/creating-proc-read-write-function-in.html
 * https://stackoverflow.com/questions/50868218/alternative-to-create-proc-entry-and-read-proc-in-linux-kernel-code
 *
 * There also does not seem to be *any* function calls to proc_read in the linux kernel so I am confused here
 * https://elixir.bootlin.com/linux/v4.15/A/ident/proc_read
 * Well I am going to leave these comments to exhibit my inability to read instructions
 * Thanks for providing a function definition
*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jared Dyreson");

MODULE_DESCRIPTION("proc module");
MODULE_VERSION("0.01");

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    if(completed){
        completed = 0;
        return 0;
    }
    completed = 1;
    rv = sprintf(buffer, "%lu\n", jiffies);
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
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
