#include "zf_common_headfile.h"
#define ADC_CHANNEL1            ADC_IN12_C2
#define ADC_CHANNEL2            ADC_IN13_C3
#define ADC_CHANNEL3            ADC_IN14_C4
#define ADC_CHANNEL4            ADC_IN15_C5


uint64_t MainTime;

void TimeSet(void){
	MainTime=0;
}

void GPIOD_Init(){
    gpio_init(D8, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(D9, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(D10,GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(D11, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(D5, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(A8, GPO, GPIO_LOW, GPO_PUSH_PULL);
}

uint16_t WaterPump(uint16_t KeySig) {
	if (KeySig == 0) {
		gpio_set_level(D8, GPIO_LOW);
	} else {
		gpio_set_level(D8, GPIO_HIGH);
	}
	return 0;
}


uint16_t WaterOff(uint16_t KeySig) {
	if (KeySig == 0) {
		gpio_set_level(D10, GPIO_LOW);
	} else {
		gpio_set_level(D10, GPIO_HIGH);
	}
	return 0;
}

uint16_t Feed(uint16_t KeySig) { 
	if (KeySig == 0) {
		gpio_set_level(D5, GPIO_LOW);
	} else {
		gpio_set_level(D5, GPIO_HIGH);
	}
	return 0;
}

uint16_t Boil(uint16_t KeySig) {
	if (KeySig == 0) {
		gpio_set_level(A8, GPIO_LOW);
	} else {
		gpio_set_level(A8, GPIO_HIGH);
	}
	return 0;
}



uint16_t AirFrs(uint16_t KeySig) {
    if (KeySig == 0) {
        gpio_set_level(D11, GPIO_LOW);
    } else {
        gpio_set_level(D11, GPIO_HIGH);
    }
    return 0;
}



uint16_t ReadPol(void){
	return adc_convert(ADC_CHANNEL1, ADC_12BIT);
}


uint16_t ReadHig(void){
	return adc_convert(ADC_CHANNEL2, ADC_12BIT);
}

uint16_t ReadTemp(void){
    return adc_convert(ADC_CHANNEL3, ADC_12BIT);
}



void MainDelay_us(uint64_t Time){
	system_delay_us(Time);
	MainTime+=Time;
}


void MainDelay_ms(uint64_t Time){
    system_delay_ms(Time);
    MainTime+=Time;
}






