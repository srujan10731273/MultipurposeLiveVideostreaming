#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
// Video resolution
#define Width 480
#define Height 864

// Allocate a buffer to store one frame
unsigned char frame[Height][Width][3] = {0};

int main()
{
    int x, y, count;

    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    FILE *pipein = popen("ffmpeg -i webCam.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 webCam_output.mp4", "w");
    
    //Error check
    if(!pipein)
    {
    	perror("File not found\n");
    	exit(EXIT_FAILURE);
    }
    
    // Process video frames
    while(1)
    {
        // Read a frame from the input pipe into the buffer
        count = fread(frame, 1, Height*Width*3, pipein);

        // If we didn't get a frame of video, we're probably at the end
        if (count != Height*Width*3)
         break;

        // Write this frame to the output pipe
        fwrite(frame, 1, Height*Width*3, pipeout);
    }

    // Flush and close input and output pipes
    fflush(pipein);
    pclose(pipein);
    fflush(pipeout);
    pclose(pipeout);
    printf("webCam viedo processing and converting into frames\n");
    sleep(2);
    system("mplayer webCam_output.mp4");

    return 0;
}
