#include <stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<stdint.h>
#include<semaphore.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
// Video resolution
#define W 1280
#define H 720
sem_t semaphore;
// Allocate a buffer to store one frame
unsigned char frame[H][W][3] = {0};
void* colorInvert();
void* resolution();
void* image_stabilization();
//main function
int main()
{
   
   sem_init(&semaphore,0,1);
  pthread_t thread_id1,thread_id2,thread_id3;
  //thread creation for color inversion
  pthread_create(&thread_id1,NULL,colorInvert,NULL);
  pthread_join(thread_id1,NULL);
   //thread creation for changing the resolution
  pthread_create(&thread_id2,NULL,resolution,NULL);
  pthread_join(thread_id2,NULL);
  //creation of thread for image stabilization
  pthread_create(&thread_id3,NULL,image_stabilization,NULL);
  pthread_join(thread_id3,NULL);
    return 0;
}
//color Invert
void* colorInvert(){
    uint16_t x, y;
    uint32_t count;
    sem_wait(&semaphore);
    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    FILE *pipein = popen("ffmpeg -i webCam_output.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 webCam_coloredOutput.mp4", "w");
    
    //Error handling
      if(!pipein)
    {
        perror("Cannot open file\n");
        exit(EXIT_FAILURE);
    }
    
    // Process video frames
    while(1)
    {
        // Read a frame from the input pipe into the buffer
        count = fread(frame, 1, H*W*3, pipein);

        // If we didn't get a frame of video, we're probably at the end
        if (count != H*W*3) break;

        // Process this frame
        for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
        {
            // Invert each colour component in every pixel
            frame[y][x][0] = 255 - frame[y][x][0]; // red
            frame[y][x][1] = 255 - frame[y][x][1]; // green
            frame[y][x][2] = 255 - frame[y][x][2]; // blue
        }

        // Write this frame to the output pipe
        fwrite(frame, 1, H*W*3, pipeout);
        
    }
     
    // Flush and close input and output pipes
    fflush(pipein);
    pclose(pipein);
    fflush(pipeout);
    pclose(pipeout);
    printf("WebCam frames changing its color according to RGB\n");
    sleep(2);
    system("mplayer webCam_coloredOutput.mp4");
    sem_post(&semaphore);
   }

//for image resolution
void* resolution(){
   uint16_t x, y, Height,Width;
   uint32_t count;

   sem_wait(&semaphore);
    printf("enter the detailes to change the resoultion i.e height and width\n");
    scanf("%d %d",&Height,&Width);
    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    FILE *pipein = popen("ffmpeg -i webCam_coloredOutput.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 webCam_ResolutionOutput.mp4", "w");
    
     //Error handling
      if(!pipein)
    {
        perror("Cannot open file\n");
        exit(EXIT_FAILURE);
    }
    

    // Process video frames
    while(1)
    {
        // Read a frame from the input pipe into the buffer
        count = fread(frame, 1, Height*Width*3, pipein);

        // If we didn't get a frame of video, we're probably at the end
        if (count != Height*Width*3) break;
        // Write this frame to the output pipe
        fwrite(frame, 1, Height*Width*3, pipeout);
        
    }
    sem_post(&semaphore);
    // Flush and close input and output pipes
    fflush(pipein);
    pclose(pipein);
    fflush(pipeout);
    pclose(pipeout);
    printf("Webcam frames changing its resolution according to user input\n");
    sleep(2);
    system("mplayer webCam_ResolutionOutput.mp4");
   }
//Image Stabilization
void* image_stabilization(){
      printf("Image stabilization is not possible\n");
}
