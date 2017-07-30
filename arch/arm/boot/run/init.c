#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <dirent.h> 
#include <string.h>
#include <linux/types.h>
#include <linux/kdev_t.h>

const char* get_scenario(int argc, char* argv[]) {
    if (argc < 2) {
        return "peterson";
    } else if (strcmp(argv[1], "dummy") == 0) {
        return "dummy_process";
    } else if (strcmp(argv[1], "peterson") == 0) {
        return "peterson";
    }
}

const int get_scheduler(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    } else if (strcmp(argv[2], "true") == 0) {
        return 1;
    } else if (strcmp(argv[2], "false") == 0) {
        return 0;
    }
} 

const void create_node(void) {
    dev_t dev = MKDEV(666, 1);
    if (mknod("/dev/driver", 'c', dev) != 0) {
        printf("Could not create device\n");
        exit(-1);
    }
    printf("Created node\n");
}

const void load_module(void) {
    int fd = open("driver.ko", O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    size_t image_size = st.st_size;
    void *image = malloc(image_size);
    read(fd, image, image_size);
    close(fd);
    if (init_module(image, image_size, "") != 0) {
        printf("VISH\n");
    }
}

void main(int argc, char* argv[]) {

    while (1) 
        if (!fork()) {
            int *p = 0x1;
            int i;

            printf("HAHAHA\n");

            for (i = 0; i < 10000; ++i);

            syscall(374, 2, NULL);

            printf("%d\n", *p);
        }
}

