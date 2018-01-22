//https://hvera.wordpress.com/2011/03/03/simple-serial-port-program/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/types.h>

#include <string.h>

//#define BAUDRATE B115200
//#define BAUDRATE B57600
//#define BAUDRATE B38400
//#define BAUDRATE B19200
#define BAUDRATE B9600
//#define BAUDRATE B4800
//#define BAUDRATE B2400
//#define BAUDRATE B1200


#define FALSE 0
#define TRUE 1


volatile int STOP=FALSE;
void signal_handler_IO (int status);
int wait_flag=TRUE;

//char devicename[200] = "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller_D-if00-port0";
//char devicename[200] = "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller_D-if00-port0";
char devicename[200] = "/dev/ttyS0";
//char devicename[200] = "/dev/ttyUSB0";
char ch;
char CMD[150];
int status;

/*

(#RB3280909F09BA3FA$36)

*/
void Checksum(char *buffer)
{
	int a = 0;
	int i;
    char ck[3]={0};
	for(i=1; i<strlen(buffer); i++)
		a += *(buffer+i);
	sprintf(ck,"%X",a&0xFF);
	strcat(buffer,ck);
}

void 	Posto_CMD(char * cmd)
{
	char len[5]={0};
	
	unsigned int lencmd = strlen(cmd);
	sprintf(len,"%.04X",lencmd);
	memset(CMD,0, (int) strlen(CMD));
	strcat(CMD,">?");
	strcat(CMD,len);
	strcat(CMD,cmd);
	Checksum(CMD);

	printf("\n\nTX: %s\n", CMD);
//	AbreConexao();
	//Enviar( SocketPosto, CMD);
}

int main(int argc, char *argv[])
{
	int fd, res, i;
	struct termios newtio;
	struct sigaction saio;
	char buf[255];


	//open the device in non-blocking way (read will return immediately)
	//fd = open(devicename, O_RDWR | O_NOCTTY | O_NONBLOCK);
	fd = open(devicename, O_RDWR  | O_NOCTTY );
	if (fd < 0)
	{
		perror(devicename);
		exit(1);
	}



	//install the serial handler before making the device asynchronous
	saio.sa_handler = signal_handler_IO;
	sigemptyset(&saio.sa_mask);   //saio.sa_mask = 0;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction(SIGIO,&saio,NULL);



	// allow the process to receive SIGIO
	fcntl(fd, F_SETOWN, getpid());



	// make the file descriptor asynchronous
	fcntl(fd, F_SETFL, FASYNC);



	// set new port settings for canonical input processing
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);



	// loop while waiting for input. normally we would do something useful here
	while (STOP == FALSE)
	{

		char RFID[50];
		// read characters typed by user in non-blocking way
		//ch = getchar_unlocked();
		//if(ch > 0)
/*
		{
			char C[2+1] = {0};
			sprintf( C, "01");
			Posto_CMD(C);
			write(fd,CMD, (int) strlen(CMD));
		}
*/
/*
		{
			sprintf(CMD,"&A67");
			printf("\nCMD  %s", CMD);
			write(fd,CMD, (int) strlen(CMD));
		}
*/
//write(fd,&ch,1);
	


		sleep(1);
		// after receiving SIGIO, wait_flag = FALSE, input is available and can be read */
//		if (wait_flag == FALSE)  //if input is available
		{

			memset(RFID,0, (int) strlen(RFID));
			memset(buf,0, (int) strlen(buf));
			res = 0;
			while( res < 23 )
			{
				
			//	res += read(fd,buf,255);
				res += read(fd,&buf[res],1);
				
				//strcat(RFID, buf);
				//printf("%c",buf[res-1]);
			}

//			printf("\n\nRESP %s\n", RFID);
		printf("\nRESP %s", buf);

/*
			if (res > 0)
			{
				for (i=0; i < res; i++)  //for all chars in string
				{
					printf("%X", 0xFF & buf[i]);
				}
				printf("\n");
			}
			wait_flag = TRUE;      // wait for new input 
*/
		}

	}
	close(fd);

}
//
/***************************************************************************
* signal handler. sets wait_flag to FALSE, to indicate above loop that     *
* characters have been received.                                           *
***************************************************************************/
//
void signal_handler_IO (int status)
{
	//printf("received SIGIO signal.\n");
	wait_flag = FALSE;
}

//gcc serial.c -o serial
