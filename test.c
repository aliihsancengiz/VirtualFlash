#include<stdio.h>
#include "vir_flash.h"

uint8_t MEM_FLASH[KB(1024)];

int main()
{
    uint8_t sector=0;
    const uint32_t size=get_sizeof_sector(sector);
    int i=0;
    uint8_t w_buffer[size],r_buffer[size];
    
    // Setting Write buffer 0xff and read buffer to 0
    memset(w_buffer,0xff,size);
    memset(r_buffer,0,size);
    
    // Creating a virtual flash
    flash_t myflash;
    flash_init(&myflash,MEM_FLASH,KB(1024));
    
    // Write to flash sector $(sector)
    myflash.flash_unlock(&myflash);
    myflash.flash_write(&myflash,sector,w_buffer,size);
    myflash.flash_lock(&myflash);

    // Read from flash sector $(sector)
    myflash.flash_unlock(&myflash);
    myflash.flash_read(&myflash,sector,r_buffer,size);
    myflash.flash_lock(&myflash);

    // Compare them to ensure we get what we write
    for ( i = 0; i < size; i++)
    {
        if(r_buffer[i] != w_buffer[i])
        {
            printf("Error occured we are not reading what we write\n");
        }
    }

    // perform mass erase
    myflash.flash_unlock(&myflash);
    myflash.flash_erase(&myflash,sector,1,FLASH_MASS_ERASE);
    myflash.flash_lock(&myflash);

    // dump 100 bytes of flash from sector $(sector)
    for ( i = 0; i < 100; i++)
    {
        if (i%10 ==0)
        {
            printf("\n");
        }
        printf("%d\t",myflash.flashptr[i]);
    }

    return 0;
}