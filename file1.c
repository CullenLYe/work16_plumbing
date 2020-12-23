#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

char *rot1(char *input) {
  int i;
  for (i=0; i<strlen(input); i++) {
    if ((input[i]>=65&&input[i]<=90)||(input[i]>=97&&input[i]<=122)) {
      if (input[i]=='z') input[i]='a';
      else input[i]=input[i]+1;
    }
  }
  return input;
}

int main() {

  mkfifo("pipe2", 0644);

  while (1) {
    int fd;
    char buffer[200];

    fd = open("pipe1", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);

    char buffer2[200] = "Rot1 Encryption: ";
    strcat(buffer2, rot1(buffer));

    fd = open("pipe2", O_WRONLY);
    write(fd, buffer2, sizeof(buffer2));
    close(fd);

    printf("Input encrypted using Rot1.\n");
  }

  return 0;

}
