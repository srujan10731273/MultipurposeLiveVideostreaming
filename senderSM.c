#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Adjust the size as needed
#define SHM_SIZE 1000000 

int main() {
    key_t key = ftok("senderSM.c", 'R');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shm_ptr = shmat(shmid, NULL, 0);

    FILE *mp4File1 = fopen("camera_output.mp4", "rb");
    FILE *mp4File2 = fopen("drone_output.mp4", "rb");
    FILE *mp4File3 = fopen("webCam_output.mp4", "rb");
    
    if (!mp4File1) {
        perror("Error opening MP4 file");
        exit(EXIT_FAILURE);
    }
    if (!mp4File2) {
        perror("Error opening MP4 file");
        exit(EXIT_FAILURE);
    }if (!mp4File3) {
        perror("Error opening MP4 file");
        exit(EXIT_FAILURE);
    }

    // Read MP4 file content into shared memory
    fread(shm_ptr, 1, SHM_SIZE, mp4File1);
    fread(shm_ptr, 1, SHM_SIZE, mp4File2);
    fread(shm_ptr, 1, SHM_SIZE, mp4File3);
    fclose(mp4File1);
    fclose(mp4File2);
    fclose(mp4File3);

    shmdt(shm_ptr);

    return 0;
}

