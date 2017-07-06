#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <asm/uaccess.h>

#define MAJOR_NUMBER 666
#define MINOR_NUMBER 0
#define BUFFER_SIZE 240

static ssize_t driver_fs_read(struct file * file, char * buf, size_t length, loff_t *ppos);
static ssize_t driver_write(struct file * file, const char * buf, size_t count, loff_t *ppos); 
static int driver_open(struct inode * inode, struct file * file);
static int driver_release(struct inode * inode, struct file * file);
int __init driver_padrao_init(void);
void __exit driver_exit(void);

static struct file_operations driver_fops = {
    .owner = THIS_MODULE,
    .read = driver_fs_read,
    .write = driver_write,
    .open =  driver_open,
    .release = driver_release
};
static char buflocal[255];


/* Inicializacão do driver */

module_init(driver_padrao_init);
// module_exit(driver_exit);

int __init driver_padrao_init(void) {
    struct class *cl;
    dev_t first;
    struct cdev c_dev;
    struct file_operations fops;

    if (register_chrdev(MAJOR_NUMBER, "levy", &driver_fops)) {
        printk ("Driver could not get major %d\n", MAJOR_NUMBER);
        return -EIO;
    }

    first = MKDEV(MAJOR_NUMBER, MINOR_NUMBER);

    if ((cl = class_create(THIS_MODULE, "driver")) == NULL) {
        unregister_chrdev_region(first, 1);
        return -1;
    }

    if (device_create(cl, NULL, first, NULL, "levy") == NULL) {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }

    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, first, 1) == -1) {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    printk("Driver module loaded (major=%d)\n", MAJOR(first));
    return 0;
}
void __exit driver_exit(void) {
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