#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

#define CACHE_DEV "/dev/block/by-name/cache"
#define CACHE_MOUNT_POINT "/cache"
#define RECOVERY_DIR "/cache/recovery"
#define WIPE_END_PATH "/cache/recovery/wipe_end"

int main(int argc, char **argv) {
    system("recovery --mount /cache");
    
    int fd = open(WIPE_END_PATH, O_RDONLY);
    if (fd >= 0) {
        close(fd);
        
        return 0;
    } else {
        
        char *cache_dev = CACHE_DEV;
        int dev_fd = open(cache_dev, O_RDWR);
        if (dev_fd < 0) {
            perror("open cache_dev failed");
    
        } else {
            long long size = 0;
            if (ioctl(dev_fd, BLKGETSIZE64, &size) != 0) {
                perror("ioctl BLKGETSIZE64 failed");
            } else if (size > 0) {
                char cmd[256];
                long long count = size / 4096;
                snprintf(cmd, sizeof(cmd), "dd if=/dev/zero of=%s bs=4096 count=%lld conv=notrunc", cache_dev, count);
                system(cmd);
            }
            close(dev_fd);
        }
        
        system("recovery --wipe_cache");
        system("recovery --wipe_data");
        system("recovery --mount /cache");
        
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
