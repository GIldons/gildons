#include "headers/basic.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string.h>

static const char * portName = "/dev/ttyPS1"; // Change for the right port

void turn_onoff(int on_off)
{
	int fd;
	const char * pin90 = "90";
	const char * pin86 = "86";
	const char * out = "out";
	
	fd = open("/sys/class/gpio/export",  O_WRONLY);
	if(fd != -1)
	{
		write(fd, pin90, sizeof(pin90));
		write(fd, pin86, sizeof(pin86));
		close(fd);
		
		fd = open("/sys/class/gpio/gpio90/direction", O_WRONLY);
		if(fd != -1)
				write(fd, out, sizeof(out));
		else
			printf("Unable to opne gpio90_direction\n");
		close(fd);
		
		fd = open("/sys/class/gpio/gpio86/direction",  O_WRONLY);
		if(fd != -1)
				write(fd, out, sizeof(out));
		else
			printf("Unable to opne gpio86_direction\n");
		close(fd);
		
		const char * value;
		if(on_off)
			value = "1";
		else
			value = "0";
		
		fd = open("/sys/class/gpio/gpio90/value",  O_WRONLY);
		if(fd != -1)
			{
				write(fd, value, sizeof(value));
			}
		else
			printf("Unable to open gpio90_value\n");
		close(fd);
		
		fd = open("/sys/class/gpio/gpio86/value",  O_WRONLY);
		if(fd != -1)
			{
				write(fd, value, sizeof(value));
			}
		else
			printf("Unable to open gpio86_value\n");
		close(fd);
	}
	else
		printf("Unable to open export file\n");
	close(fd);
	
}

int init_serial()
{
	//Open the file descriptor for the serial port
	int fd;
	fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY, 0);
	if(fd == -1)
		printf("Unable to open Serial port\n");
	else
		fcntl(fd,F_SETFL, 0);
	
	//Set the configurations acording to datasheet
	struct termios options;
	
	tcgetattr(fd, &options);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB; //NO PARITY
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE; //datasize mask
	options.c_cflag |= CS8;		//datasize
	options.c_cflag |= CRTSCTS; //HW control
	
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
	
	return fd;
}

int get_input(int fd, char * data, int size)
{
	int n = 0;
	fcntl(fd, F_SETFL, FNDELAY);
	if(fd != -1)
	{
		n = read(fd, data, size);
		if(n < 0)
		{
			printf("Erro reading data\n");
			return -1;
		}
	}
	return 0;
	
}

int send_output(int fd, void * data, int size)
{
	int n = 0;
	if(fd != -1)
	{
		n = write(fd, data, size);
		if(n < 0)
		{
			printf("Erro writing data\n");
			return -1;
		}
	}
	return 0;
}
