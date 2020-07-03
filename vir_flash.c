#include "vir_flash.h"




static uint8_t * sector_to_address(flash_t *self,uint8_t sector)
{
    uint8_t *base_addr=(uint8_t *)self->flashptr;
    uint32_t addr=0;
    
    if(sector<=3)
    {
        addr+=sector*KB(16);
    }
    else if(sector==4)
    {
        addr+=4*KB(16);
    }
    else if(sector<=11)
    {
        addr+=KB(128)+(sector-5)*KB(128);
    }
    else
    {
        printf("Sector number is not valid");
        exit(-1);
    }
    return &base_addr[addr];
}
uint32_t get_sizeof_sector(uint8_t sector)
{
    if(sector<=3)
    {
        return KB(16);
    }
    else if(sector==4)
    {
        return KB(64);
    }
    else if(sector<=11)
    {
        return KB(128);
    }
    else
    {
        printf("Sector number is not valid");
        exit(0);
    }
}
static void flash_write_t(flash_t *self,uint8_t sector,uint8_t *data,uint32_t len)
{
    if(self->locked)
    {
        printf("Please at first unlock Flash");
        return ;
    }
    uint8_t *base=sector_to_address(self,sector);
    for (size_t i = 0; i < len; i++)
    {
        base[i]=data[i];
    }
}

static void flash_read_t(flash_t *self,uint8_t sector,uint8_t *data,uint32_t len)
{
    if(self->locked)
    {
        printf("Please at first unlock Flash");
        return ;
    }
    uint8_t *base=sector_to_address(self,sector);
    for (size_t i = 0; i < len; i++)
    {
        data[i]=base[i];
    }

}

static void flash_erase_t(flash_t *self,uint8_t sector,uint8_t number,uint8_t mass)
{
    if(self->locked)
    {
        printf("Unlock flash before performing any operation");
        exit(-1);
    }
    else
    {
        if (mass==FLASH_MASS_ERASE)
        {
            memset(self->flashptr,0xff,self->size);
        }
        else
        {
            uint8_t i;
            uint8_t *buffer;
            for ( i = sector; i <sector+number ; i++)
            {
                buffer=sector_to_address(self,i);
                memset(buffer,0xff,get_sizeof_sector(i));
            }
        }
    }
}
static void flash_lock_t(flash_t *self)
{
    self->locked=1;
}
static void flash_unlock_t(flash_t *self)
{
    self->locked=0;
}

void flash_init(flash_t* self,uint8_t *memptr,uint32_t size)
{
    self->flashptr=memptr;
    self->locked=1;
    self->size=size;
    self->flash_write=&flash_write_t;
    self->flash_read=&flash_read_t;
    self->flash_erase=&flash_erase_t;
    self->flash_lock=&flash_lock_t;
    self->flash_unlock=&flash_unlock_t;
}
