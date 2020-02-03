#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
int file;
char *filename = "/dev/i2c-1";
char buff[4]={0x03,0,0,0};

if ((file = open(filename, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
}
printf("Opened it ok: %d\n", write(file, buff, 1));
close(file);

}
