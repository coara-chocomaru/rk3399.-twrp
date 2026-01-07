#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#define CACHE_MOUNT_POINT "/cache"
#define RECOVERY_DIR "/cache/recovery"
#define WIPE_END_FILE "/cache/recovery/wipe_end"
#define CACHE_BLOCK_DEVICE "/dev/block/by-name/cache"
#define USERDATA_BLOCK_DEVICE "/dev/block/by-name/userdata"
#define SBIN_SH "/sbin/sh"
#define TWRP_CMD "twrp"
#define MKE2FS_CMD "/sbin/mke2fs"

bool file_exists(const char* path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

int create_directory(const char* path, mode_t mode) {
    if (mkdir(path, mode) == -1) {
        if (errno != EEXIST) {
            perror("mkdir failed");
            return -1;
        }
    }
    return 0;
}

int create_empty_file(const char* path) {
    int fd = open(path, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open failed for create_empty_file");
        return -1;
    }
    close(fd);
    return 0;
}

int execute_shell_command(const char* cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return -1;
    } else if (pid == 0) {
        execl(SBIN_SH, "sh", "-c", cmd, (char*)NULL);
        perror("execl failed");
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1;
        }
    }
}

int format_with_f2fs(const char* device) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s -t f2fs %s", MKE2FS_CMD, device);
    return execute_shell_command(cmd);
}

int perform_twrp_wipes() {
    if (execute_shell_command(TWRP_CMD " wipe cache") != 0) {
        fprintf(stderr, "Failed to execute twrp wipe cache\n");
        return -1;
    }
    if (execute_shell_command(TWRP_CMD " wipe data") != 0) {
        fprintf(stderr, "Failed to execute twrp wipe data\n");
        return -1;
    }
    return 0;
}

int mount_cache() {
    return mount(CACHE_BLOCK_DEVICE, CACHE_MOUNT_POINT, "f2fs", 0, NULL);
}

int main(int argc, char** argv) {
    bool mount_success = (mount(CACHE_BLOCK_DEVICE, CACHE_MOUNT_POINT, "f2fs", 0, NULL) == 0);
    bool wipe_end_exists = false;

    if (mount_success) {
        wipe_end_exists = file_exists(WIPE_END_FILE);
    }

    if (wipe_end_exists) {
        if (mount_success) {
            umount(CACHE_MOUNT_POINT);
        }
        return 0;
    } else {
        if (format_with_f2fs(USERDATA_BLOCK_DEVICE) != 0) {
            fprintf(stderr, "Failed to format userdata with f2fs\n");
            if (mount_success) umount(CACHE_MOUNT_POINT);
            return -1;
        }
        if (format_with_f2fs(CACHE_BLOCK_DEVICE) != 0) {
            fprintf(stderr, "Failed to format cache with f2fs\n");
            if (mount_success) umount(CACHE_MOUNT_POINT);
            return -1;
        }

        if (perform_twrp_wipes() != 0) {
            if (mount_success) umount(CACHE_MOUNT_POINT);
            return -1;
        }

        if (mount_cache() != 0) {
            perror("mount cache failed after format and wipes");
            return -1;
        }

        if (create_directory(RECOVERY_DIR, 0755) != 0) {
            umount(CACHE_MOUNT_POINT);
            return -1;
        }

        if (create_empty_file(WIPE_END_FILE) != 0) {
            umount(CACHE_MOUNT_POINT);
            return -1;
        }

        umount(CACHE_MOUNT_POINT);
        return 0;
    }

    return 0;
}
