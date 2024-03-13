#include <linux/kernel.h>
#include <linux/syscalls.h>

void my_custom_function(void)
{
    printk(KERN_INFO "my_custom_function called with arg = \n");
}

SYSCALL_DEFINE1(new_syscall, int, data)
{
	my_custom_function();
	printk(KERN_INFO "new_syscall!!!! %d\n", data);
	return data+1;
}
