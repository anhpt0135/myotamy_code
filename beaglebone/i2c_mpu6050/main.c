#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>  // for null, int
#include <unistd.h> // for open, read, write, close
#include <fnctl.h>  // for open option (O_RDONLY/O_WRONLY/O_RDWR/O_APPEND)
#include <sys/ioctl.h>

#define MPU_6050_SLAVE_ADDR 68
#define I2C_O_MODULE = "/dev/i2c-2"

int fd;

int main(void){
	fd = open(I2C_O_MODULE, O_RDWR);
	if(fd < 1){
		printf("can not open the file descriptor");
		return -1;
	}
	if(ioctl(fd, I2C_SLAVE, MPU_6050_SLAVE_ADDR)){
		printf("Error: ioctrl");
		return -1;
	}

	mpu6050_init();

	while(1){
		
	}

	return 0;
}