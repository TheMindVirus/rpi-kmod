#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include <asm/io.h>

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
    unsigned long start  = 0xFEC04000;
    unsigned long end    = 0xFEC04FFF;
    unsigned long offset = 0;
    void __iomem* base   = 0;

    char c[5] = { ' ', ' ', ' ', ' ', '\0' };
    unsigned int value = 0;
    unsigned int tmp = 0;

    printk(KERN_INFO "<<<KMOD>>>\n");
    debug("[CALL]: init_module");
    base = ioremap(start, end - start);

    debug("[INFO]: BEGIN_READ");
    for (offset = 0; offset <= (end - start); offset += 4)
    {
        strcpy(c, "    ");
        value = readl(base + offset);
        tmp = (value >> 24) & 0xFF; if ((tmp >= 32) && (tmp < 127)) { c[0] = tmp; }
        tmp = (value >> 16) & 0xFF; if ((tmp >= 32) && (tmp < 127)) { c[1] = tmp; }
        tmp = (value >>  8) & 0xFF; if ((tmp >= 32) && (tmp < 127)) { c[2] = tmp; }
        tmp = (value >>  0) & 0xFF; if ((tmp >= 32) && (tmp < 127)) { c[3] = tmp; }
        debug("[MMIO]: Address: 0x%08lX | Value: 0x%08lX | %s",
            start + offset, value, c);
    }
    debug("[INFO]: END_READ");

    iounmap(base);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "<<<KMOD>>> - Unload Complete.\n");
    debug("[CALL]: cleanup_module");
}
