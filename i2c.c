#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main()
{

    int fd;
    int num_rd, num_wr;
    int writebuf[10];
    int readbuf[10];
    int status = 0;

    fd = open("/dev/i2c-1", O_RDWR | O_CREAT);
    if (fd == -1)
    {  
        printf("Fejl i open \n");
    } 

    status = ioctl(fd, 0x0703, 0x08);
    if(status > 0)
    {
        printf("Fejl i ioctl\n");
    }   

    while(1)
    {    
        writebuf[0] = 0x1; // FX ORDER = ØL (0b00000001 svarer til øl, se protokol)
        writebuf[1] = 0x2; // FX BORD NR 2
        writebuf[2] = 0x3; // FX 3 ØL
        num_wr = write(fd, writebuf, 3);
        if (num_wr != 3)
        {
            printf("Fejl i write\n");
        }
        else
            printf("Der sendes! \n");

        sleep(1);

        num_rd = read(fd, readbuf, 3);
        if (num_rd == -1)
        {
            printf("Fejl i read\n");
        }
            printf("Der lases: %d, og %d, og %d \n", readbuf[0], readbuf[1], readbuf[2]);
            
        sleep(1);
    }
    
}
