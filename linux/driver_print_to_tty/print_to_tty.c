
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/tty.h> 
#include <linux/version.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("KM");
MODULE_LICENSE("GPL");

static void print(char *str)
{
    struct tty_struct *my_tty = current->signal->tty;
    if (my_tty != NULL) {
        ((my_tty->driver)->ops->write) (my_tty, str, strlen(str));
    } else {
        printk("tty not found\r\n");
    }
}

static int __init print_string_init(void)
{
    print("Kernel module init\r\n");
    return 0;
}

static void __exit print_string_exit(void)
{
    print("Kernel module exit\r\n");
}

module_init(print_string_init);
module_exit(print_string_exit);
