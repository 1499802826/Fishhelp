
#include "zf_common_headfile.h"


uint8_t SET_B8(uint8_t MSE){
    if(MSE){
        gpio_init(B8, GPI, GPIO_LOW, GPI_PULL_UP);
    }
    else{
        gpio_init(B8, GPO, GPIO_LOW, GPO_PUSH_PULL);
    }
    return MSE;
}




uint8_t DS18B20Init(void){
    uint8_t A;
    SET_B8(0);
    //system_delay_us(5);
    gpio_set_level(B8, GPIO_HIGH);
    system_delay_us(80);
    gpio_set_level(B8, GPIO_LOW);
    system_delay_us(800);
    gpio_set_level(B8, GPIO_HIGH);
    //system_delay_us(140);
    SET_B8(1);
    system_delay_us(140);
    A=gpio_get_level(B8);
    system_delay_us(200);
    //A=gpio_get_level(B8);
    return A;
}



uint8_t WriteList(uint8_t ENT){
    uint8_t i;
    uint8_t STP;
    SET_B8(0);
    for(i=0,STP=0x01;i<8;i++,STP<<=1){
        gpio_set_level(B8, GPIO_LOW);
        system_delay_us(2);
        if(ENT&STP){
            system_delay_us(5);
            gpio_set_level(B8, GPIO_HIGH);
            system_delay_us(56);
        }
        else{
            system_delay_us(61);
            gpio_set_level(B8, GPIO_HIGH);
        }
        system_delay_us(2);
    }
    return 0;
}

uint16_t ReadList(void){
    uint8_t LP,HP;
    uint8_t i;
    uint8_t STP;
    uint16_t DIC;
    SET_B8(0);
    for(i=0,LP=0,STP=0x80;i<8;i++,STP>>=1){
        gpio_set_level(B8,GPIO_LOW);
        system_delay_us(2);
        gpio_set_level(B8,GPIO_HIGH);
        SET_B8(1);
        system_delay_us(22);
        if(gpio_get_level(B8)){
            LP=LP|STP;
        }
        system_delay_us(50);
    }
    for(i=0,HP=0,STP=0x80;i<8;i++,STP>>=1){
            gpio_set_level(B8,GPIO_LOW);
            system_delay_us(2);
            gpio_set_level(B8,GPIO_HIGH);
            SET_B8(1);
            system_delay_us(22);
            if(gpio_get_level(B8)){
                HP=HP|STP;
            }
            system_delay_us(50);
        }
    DIC=16*HP+LP;
    return DIC;
}

int32 TemTrans(uint16_t IPT){
    return (int16)IPT*5;
}



int32 ReadTem(void){
    DS18B20Init();
    WriteList(0xCC);
    WriteList(0x44);
    DS18B20Init();
    WriteList(0xCC);
    WriteList(0xBE);
    return TemTrans(ReadList());
}













