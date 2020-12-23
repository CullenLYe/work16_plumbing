#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

  mkfifo("pipe1", 0644);
  printf("Rot1 Encryption Program:\n\n");

  while (1) {
    printf("Input some text: ");
    int fd;
    char buffer[200];
    fgets(buffer, sizeof(buffer), stdin);
    size_t len = strlen(buffer)-1;
    if (buffer[len]=='\n') buffer[len] = '\0';

    fd = open("pipe1", O_WRONLY);
    write(fd, buffer, sizeof(buffer));
    close(fd);

    fd = open("pipe2", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    close(fd);

    printf("\n");
}


  return 0;

}
