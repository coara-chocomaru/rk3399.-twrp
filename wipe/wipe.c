#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <linux/fs.h>

#define CACHE_DEV "/dev/block/by-name/cache"
#define DATA_DEV "/dev/block/by-name/userdata"
#define CACHE_MOUNT_POINT "/cache"
#define RECOVERY_DIR "/cache/recovery"
#define WIPE_END_PATH "/cache/recovery/wipe_end"
#define SHELL "/sbin/sh"

int my_system(const char *command) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }
    if (pid == 0) {
        execl(SHELL, "sh", "-c", command, (char *)NULL);
        perror("execl failed");
        exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

int main(int argc, char **argv) {
    my_system("mount /cache");
    int fd = open(WIPE_END_PATH, O_RDONLY);
    if (fd >= 0) {
        close(fd);
        return 0;
    } else {
        my_system("umount /cache");
        int dev_fd = open(CACHE_DEV, O_RDWR);
        if (dev_fd < 0) {
            perror("open cache_dev failed");
        } else {
            long long size = 0;
            if (ioctl(dev_fd, BLKGETSIZE64, &size) != 0) {
                perror("ioctl BLKGETSIZE64 failed");
            } else if (size > 0) {
                char cmd[256];
                snprintf(cmd, sizeof(cmd), "dd if=/dev/zero of=%s bs=4096 count=%lld conv=notrunc", CACHE_DEV, (long long)(size / 4096));
                my_system(cmd);
            }
            close(dev_fd);
        }
        
        my_system("/sbin/recovery --wipe_cache");
        my_system("/sbin/recovery --wipe_data");
        my_system("mount /cache");
        
        struct stat st;
        if (stat(RECOVERY_DIR, &st) != 0) {
            if (mkdir(RECOVERY_DIR, 0755) != 0) {
                perror("mkdir failed");
            }
        }
        
        fd = open(WIPE_END_PATH, O_CREAT | O_WRONLY, 0644);
        if (fd >= 0) {
            close(fd);
        } else {
            perror("create wipe_end failed");
        }
    }
    
    return 0;
}
