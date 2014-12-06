#include "headers/basic.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string.h>
#include <time.h>

char * str = (char *)malloc(5*sizeof(char));

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
	fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1)
		printf("Unable to open Serial port\n");
	else
		fcntl(fd,F_SETFL, FNDELAY);
	
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

int get_input(int fd, char * s, int size)
{
	int timeout = 10, debug = 1;
	char	b;
	char	*m;
	time_t	t0;
	t0 = time(NULL);
	if (debug) printf("readStrBluART: \"");
	m = s;
	while (*m != '\0') {
		read(fd, &b, sizeof (b));
		//if (debug) printf(isgraph(b) ? "%c" : "\\%03o", b);
		printf("\nreadStrBluART: %s", m);
		if (*m++ != b)
			m = s;
		if (t0 - time(NULL) > timeout) {
			if (debug) printf("\" ... timout\n");
			return -1;
		}
	}
	if (debug) printf("\" ... match\n");
	return 0;
// 	int n = 0, i = 0;
// 	char temp = ' ';
// 	if(fd != -1)
// 	{
// 		while(temp != '\0')
// 		{
// 			n = read(fd, &temp, 1);
// 			if(n < 0)
// 				printf("Erro reading data\n");
// 			else
// 			{
// 				*data = temp;
// 				data++;
// 			}
// 		}
// 		printf("Data: %s\n", data);
// 		return 1;
// 	}
// 	return 0;
	
}

int send_output(int fd, const char * data)
{
	int n = 0;
	printf("data: %d\n", (int)strlen(data));
	if(fd != -1)
	{
		n = write(fd, data, strlen(data));
		if(n < 0)
		{
// 			printf("Erro writing data\n");
			return -1;
		}
	}
	return 0;
}

void teste(Spot table[][8], int fd)
{
	
	int test = atoi(str);
	int test2;
	get_input(fd, str, sizeof(char));
	test2 = atoi(str);
	if( test != test2)
		printf("Str aoit: %d\n", test2);
	if(test == 1)
		table[1][1].fire_lvl = !table[1][1].fire_lvl;
	if(test == 2)
		table[2][2].fire_lvl = !table[2][2].fire_lvl;
	if(test == 3)
		table[3][3].fire_lvl = 1;//!table[3][3].fire_lvl;
	if(test == 4)
		table[4][4].fire_lvl = !table[4][4].fire_lvl;
	if(test == 5)
		table[5][5].fire_lvl = !table[5][5].fire_lvl;
	if(test == 6)
		table[6][6].fire_lvl = !table[6][6].fire_lvl;

}