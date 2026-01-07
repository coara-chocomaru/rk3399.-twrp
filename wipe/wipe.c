#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define CACHE_MOUNT_POINT "/cache"
#define RECOVERY_DIR "/cache/recovery"
#define WIPE_END_PATH "/cache/recovery/wipe_end"

int main(int argc, char **argv) {
    int mount_result = system("twrp mount /cache");
    
    int fd = open(WIPE_END_PATH, O_RDONLY);
    if (fd >= 0) {
        close(fd);
        return 0;
    } else {
        system("twrp wipe data");
        system("twrp wipe cache");
        system("twrp mount /cache");
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
