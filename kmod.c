#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>

#define LOGPATH   "/home/pi/Desktop/logfile.txt"

MODULE_LICENSE("GPL");

void debug(char* format, ...)
{
    char buffer[255] = "";
    char path[255] = "";
    struct file* filp = 0;
    unsigned long long offset = 0;

    va_list va;
    va_start(va, format);
    vsprintf(buffer, format, va);
    va_end(va);
    strcat(buffer, "\n");

    strcpy(path, LOGPATH);
    filp = filp_open(path, O_RDWR|O_CREAT|O_APPEND, 0644);
    offset = 0;
    kernel_write(filp, buffer, strlen(buffer), &offset);
    filp_close(filp, 0);
}

int init_module(void)
{
    printk(KERN_INFO "<<<KMOD>>>\n");
    debug("[CALL]: KMOD init_module");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "<<<KMOD>>> - Unload Complete.\n");
    debug("[CALL]: KMOD cleanup_module");
}
