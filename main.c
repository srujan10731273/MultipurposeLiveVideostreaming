#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int choice;
  int k = 0;
  while (1) {
    printf("\nEnter choice\n1. Camera frames\n2. Drone frames "
           "3. WebCam frames\n4. Camera color invert and resolution\n5. Drone color invert and resolution\n6. WebCam color invert and resolution\n7. Object detection\n8. Camera encoding and compression\n9. Drone encoding and compression\n10. WebCam encoding and compression\n11. Send through client socket\n12. Receive through socket\n13. Exit\n ");
    scanf("%d", &choice);
    printf("\n\n");
    do{
    switch (choice) {
    case 1:
      execvp("./cam", NULL);
      break;
      
    case 2:
      execvp("./drone", NULL);
      break;
      
    case 3:
      execvp("./webCam", NULL);
      break;
      
    case 4:
      execvp("./camcolres", NULL);
      break;
    
    case 5:
      execvp("./drocolres", NULL);
      break;
    
    case 6:
      execvp("./webcolres", NULL);
      break;
      
    case 7:
      execvp("./obj", NULL);
      break;
      
    case 8:
      execvp("./camencom", NULL);
      break;
      
    case 9:
      execvp("./droencom", NULL);
      break;
      
    case 10:
      execvp("./webencom", NULL);
      break;
      
    case 11:
      execvp("./client", NULL);
      break;
      
    case 12:
      execvp("./server", NULL);
      break;
      
    case 13:
      exit(0);
      break;

    default:
      printf("Enter a valid number 1 to 12\n");
    }
    }while(1);
  }

  return 0;
}

