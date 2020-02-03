#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>
//#include <i2c/smbus.h>

#include "ultrasonic.h"

// Returns current Reading
double Ultrasonic::getUltrasonicData()
{
	int file;
	char *filename = "/dev/i2c-1"
	char buff[] = { 1, 0, 0, 0 };
	unsigned raw = 0;
	double filt = 0.0;
	int = 0;
	bool adequateHeight = true;

	if ((file = open(filename, O_RDWR)) < 0) {
		// ERROR HANDLING: you can check eerno to see what went wrong
		perror("Failed to open the i2c bus");
		//exit(1);
		return -1;
	}

	if (ioctl(file, I2C_SLAVE, 0x03) < 0){
		printf("Failed to acquire bus access and/or talk to slave.\n");
		// ERROR HANDLING: you can check errno to see what went wrong
		//exit(1);
		return -1;
	}

	printf("Wrote for data: %d\n", write(file, buff, 1));
	usleep(20000);
	memset(buff, 0, sizeof(buff));
	printf("Read two bytes: %d\n", read(file, buff, 2));
	printf("Buff %x %x\n", (int)buff[0], (int)buff[1]);
	printf("Value: %d\n", (((unsigned int)buff[0]) << 8) | (unsigned int)buff[1]);

	while(1)
	{
		buff[0] = 1;
		if(write(file, buff, 1) < 1)
		{
			break;
		}
		usleep(10000);
		memset(buff, 0, sizeof(buff));
		if(read(file, buff, 2) < 2)
		{
			break;
		}
		raw = (((unsigned int)buff[0]) << 8) | (unsigned int)buff[1];
		// filt gets rid of outliers
		filt = (raw + 15.0*filt)/16.0;

		//return filt
		printf("%u %5u %.0lf\n", i++, raw, filt);
	}

	close(file);
}


	
