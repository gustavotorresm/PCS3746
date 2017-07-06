#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <asm/uaccess.h>

#define MAJOR_NUMBER 60
#define MINOR_NUMBER 0
#define BUFFER_SIZE 240

static ssize_t driver_fs_read(struct file * file, char * buf, size_t length, loff_t *ppos);
static ssize_t driver_write(struct file * file, const char * buf, size_t count, loff_t *ppos); 
static int driver_open(struct inode * inode, struct file * file);
static int driver_release(struct inode * inode, struct file * file);
static int __init driver_init(void);
static void __exit driver_exit(void);

static struct file_operations driver_fops = {
    .owner = THIS_MODULE,
    .read = driver_fs_read,
    .write = driver_write,
    .open =  driver_open,
    .release = driver_release
};
static char buflocal[255];


/* Inicializacão do driver */

module_init(driver_init);
module_exit(driver_exit);

static int __init driver_init(void) {
    if (register_chrdev(MAJOR_NUMBER, "driver", &driver_fops)) {
        printk ("Driver could not get major %d\n", MAJOR_NUMBER);
        return -EIO;
    }
    printk("Driver module loaded (major=%d)\n", MAJOR_NUMBER);
    return 0;
}
static void __exit driver_exit(void) {
    unregister_chrdev(MAJOR_NUMBER, "driver");
    printk("Driver module unloaded\n");
}


/* Operacões do driver */

static ssize_t driver_fs_read  (struct file * file, char * buf, size_t length, loff_t *ppos) {
    unsigned int minor = MINOR(file->f_dentry->d_inode->i_rdev);
    char tmp[32];
    if (minor!= MINOR_NUMBER) return ~ENODEV;
    if (try_module_get(driver_fops.owner)) {
        sprintf (tmp, "%ld\n", (int)(666));
        printk("LIXO %s\n", tmp);
        copy_to_user(buf, tmp, strlen(tmp));
        module_put(driver_fops.owner);
        return strlen(tmp)+2; /* Número de bytes usados no buffer */
    } else return -1;
}

static ssize_t driver_write(struct file * file, const char * buf, size_t count, loff_t *ppos) {
    unsigned int copy_size;
    copy_size = (count <= BUFFER_SIZE ? count : BUFFER_SIZE);
    if (copy_from_user(buflocal, buf, copy_size)) return -EFAULT;
    buflocal[copy_size] = 0; /* Forca o fim de string */
    printk("Print buffer: %s",buflocal);
    return copy_size;
}

static int driver_open(struct inode * inode, struct file * file) {
    printk("HAHA!!!\n");
    if (try_module_get(driver_fops.owner)) {
        printk("Driver opened\n");
        return 0;
    } else {
        printk("Unable to open driver\n");
        return -1;
    }
}

static int driver_release(struct inode * inode, struct file * file) {
    module_put(driver_fops.owner);
    printk("Driver released\n");
    return 0;
}