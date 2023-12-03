#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Adjust the size as needed
#define SHM_SIZE 1000000  

int main() {
    key_t key = ftok("sender.c", 'R');
    int shmid = shmget(key, SHM_SIZE, 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shm_ptr = shmat(shmid, NULL, 0);

    FILE *receivedFile1 = fopen("camera_received.mp4", "wb");
    FILE *receivedFile2 = fopen("drone_received.mp4", "wb");
    FILE *receivedFile3 = fopen("webCam_received.mp4", "wb");
    if (!receivedFile1) {
        perror("Error creating received MP4 file");
        exit(EXIT_FAILURE);
    }
    if (!receivedFile2) {
        perror("Error creating received MP4 file");
        exit(EXIT_FAILURE);
    }
    if (!receivedFile3) {
        perror("Error creating received MP4 file");
        exit(EXIT_FAILURE);
    }

    // Write shared memory content to received MP4 file
    fwrite(shm_ptr, 1, SHM_SIZE, receivedFile1);
    fwrite(shm_ptr, 1, SHM_SIZE, receivedFile2);
    fwrite(shm_ptr, 1, SHM_SIZE, receivedFile3);
    fclose(receivedFile1);
    fclose(receivedFile2);
    fclose(receivedFile3);

    shmdt(shm_ptr);

    // Clean up shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

