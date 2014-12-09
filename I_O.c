/*I_O Control
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/

#include "headers/basic.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string.h>
#include <time.h>
#include "headers/I_O.h"
#include "headers/neolib.h"

#define color_fire 0x00FF00 //Orange
#define color_tree 0xFF0000 //Green
#define color_base 0x0000FF //Blue

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

int init_serial(int * fd)
{
	//Open the file descriptor for the serial port
	*fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY, 0);
	if(*fd == -1)
	{
		printf("Unable to open Serial port Bluetooh\n");
		return 1;
	}
	else
		fcntl(*fd,F_SETFL, FNDELAY);
	
	//Set the configurations acording to datasheet
	struct termios options;
	
	tcgetattr(*fd, &options);
	
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB; //NO PARITY
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE; //datasize mask
	options.c_cflag |= CS8;		//datasize
	options.c_cflag |= CRTSCTS; //HW control
	cfmakeraw(&options);
	
	tcflush(*fd, TCIFLUSH);
	tcsetattr(*fd, TCSANOW, &options);
	return 0;
}

int send_output(int fd, char * data)
{
	int n = 0;
	printf("data: %d\n", (int)strlen(data));
	if(fd != -1)
	{
		n = write(fd, data, strlen(data));
		if(n < 0)
		{
			printf("Erro writing data\n");
			return -1;
		}
	}
	return 0;
}

void openBluetooh(int fd)
{
	SDL_Delay(30);
	send_output(fd, "+\n");
	SDL_Delay(1);
	send_output(fd, "SF,1\n");
	SDL_Delay(1);
	send_output(fd, "SS,C0000000\n");
	SDL_Delay(1);
	send_output(fd, "SR,92000000\n");
	SDL_Delay(1);
	send_output(fd, "R,1\n");
	SDL_Delay(1500);
	send_output(fd, "F\n");
	SDL_Delay(1);
	send_output(fd, "X\n");
	SDL_Delay(1);
	send_output(fd, "E,0,001EC01B173B\n");
	SDL_Delay(3);
	send_output(fd, "I\n");
}


//Maybe send all the colors first and than send run
void send_tile(Spot table[][8], int i, int j)
{
	if(table[i][j].fire_lvl == 1)
	{
		writeTile(table[i][j].LED_ID, color_fire);
	}
	else if(table[i][j].fire_lvl == 0)
	{
		writeTile(table[i][j].LED_ID, color_tree);
	}
	else if(table[i][j].fire_lvl == -2)
	{
		writeTile(table[i][j].LED_ID, color_base);
	}
}

void read_heli(Spot table[][8], int fd , int ** dados)
{
	int exit = 1, i , j;
	unsigned int tile_id;
	
	tile_id = nextTaggedTile(fd);

	if (tile_id != -1)
		printf("saw tile %d\n", tile_id);
	
	if(tile_id == table[4][6].ID)
	{
		*(dados[2]) = 100;
		exit = 0;
	}
	for(i = 1; i < 7 && exit; i++)
		for(j = 1; j < 7 && exit; j++)
			if(tile_id == table[i][j].ID)
			{
				if(table[i][j].fire_lvl == 1)	
				{
					if(*(dados[2]) > 0)
					{
						table[i][j].fire_lvl = 0;
						*(dados[1]) = *(dados[1]) + 1;
						if(*(dados[0]) > 0)
							*(dados[0]) = *(dados[0]) - 1;
						*(dados[2]) = *(dados[2]) - 10;
						exit = 0;
					}
				}
			}
}
