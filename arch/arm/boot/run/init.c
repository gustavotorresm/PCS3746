#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
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
    dev_t dev = MKDEV(60, 0);
    int rc = mknod("/dev/levy", 'c', dev);
}

const void load_module(void) {
    int fd = open("/driver.ko", O_RDONLY);
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
    create_node();
    load_module();

    DIR           *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        printf("%s\n", dir->d_name);
      }

      closedir(d);
    }

    unsigned char buffer[8];
    FILE *file = fopen("/dev/levy", "rw");

    printf("%d\n", file);

    fread(buffer, sizeof buffer, 1, file);

    printf("HAHA: %s\n", buffer);
    
    // const char *scenario = get_scenario(argc, argv);
    // const int scheduler_enabled = get_scheduler(argc, argv);

    // printf("Using scenario %s with scheduler %s.\n", scenario, scheduler_enabled ? "enabled" : "disabled");

    // char *scheduler_status = scheduler_enabled ? "true": NULL;
    // const char *args[] = {scenario, scheduler_status, NULL};
    // execve(scenario, args, NULL);

    while(1);
}

