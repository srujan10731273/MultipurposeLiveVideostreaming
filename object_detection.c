#include <SDL2/SDL.h>
#include <stdio.h>
#include<SDL2/SDL_image.h>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Object Detection Example", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *imageSurface = IMG_Load("out_frame.jpg");
  //printf("object detected");
  if (imageSurface == NULL) {
    fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *imageTexture =
      SDL_CreateTextureFromSurface(renderer, imageSurface);
  if (imageTexture == NULL) {
    fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(imageSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Rect destRect = {0, 0, imageSurface->w, imageSurface->h};

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, imageTexture, NULL, &destRect);
  
  
  
  Uint32 *pixels = (Uint32 *)imageSurface->pixels;
    int objectFound = 0;

    for (int i = 0; i < imageSurface->w * imageSurface->h; ++i) {
        Uint8 r, g, b;
        SDL_GetRGB(pixels[i], imageSurface->format, &r, &g, &b);

        // Sample condition: If red component is high, consider it an "object"
        if (r < 100 && g < 100 && b > 200) {
            objectFound = 1;
            break;
        }
    }

    if (objectFound) {
        printf("Object detected!\n");
    } else {
        printf("Object not detected.\n");
    }

  
  
  SDL_RenderPresent(renderer);

  SDL_Delay(3000); // Show the image for 3 seconds

  SDL_DestroyTexture(imageTexture);
  SDL_FreeSurface(imageSurface);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
