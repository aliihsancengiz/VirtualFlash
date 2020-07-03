#ifndef VIRTUAL_FLASH_DOUBLES_
#define VIRTUAL_FLASH_DOUBLES_

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define KB(x) (1024*x)
#define FLASH_MASS_ERASE 0xAC


typedef struct flash_t flash_t;

// flash object and some utilities
struct flash_t
{
    uint8_t *flashptr;
    uint8_t locked;
    uint32_t size;
    void (*flash_write)(flash_t *self,uint8_t sector,uint8_t *data,uint32_t len);
    void (*flash_read)(flash_t *self,uint8_t sector,uint8_t *data,uint32_t len);
    void (*flash_erase)(flash_t *self,uint8_t sector,uint8_t number,uint8_t mass);
    void (*flash_lock)(flash_t *self);
    void (*flash_unlock)(flash_t *self);
};


// Public functions
void flash_init(flash_t* self,uint8_t *memptr,uint32_t size);
uint32_t get_sizeof_sector(uint8_t sector);
#endif

