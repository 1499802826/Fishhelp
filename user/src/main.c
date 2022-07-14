//本程序采用的头文件zf_common_headfile.h来自逐飞科技

//

#include "zf_common_headfile.h"

#include "fish.h"


#define ADC_CHANNEL1            ADC_IN12_C2
#define ADC_CHANNEL2            ADC_IN13_C3
#define ADC_CHANNEL3            ADC_IN14_C4
#define ADC_CHANNEL4            ADC_IN15_C5

uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();
    clock_init(SYSTEM_CLOCK_144M);
    debug_init();
    adc_init(ADC_CHANNEL1);
    adc_init(ADC_CHANNEL2);
    adc_init(ADC_CHANNEL3);
    adc_init(ADC_CHANNEL4);
    GPIOD_Init();
    interrupt_global_enable();
    int32 Tempra;
    uint64 OffStart=0,PumStart=0,FRS;
    int a,b,c,d,Makp;
    c=0;
    d=0;
    FRS=0;
    Makp=0;
    while(1)
    {
        if(ReadPol()<1700&&c==0){
            WaterOff(1);
            c=1;
            if(OffStart==0){
                OffStart=MainTime;
            }
        }


        if(ReadHig()<=1200){
            WaterPump(1);
            WaterOff(0);
            if(PumStart==0){
                PumStart=MainTime;
            }
        }

        if((MainTime-PumStart>=PumStart-OffStart)&&(OffStart!=0)&&(PumStart!=0)){
            WaterPump(0);
            OffStart=0;
            PumStart=0;
            c=0;
            Makp=1;
        }
        if(ReadTemp()>1940&&d==0){
            Boil(1);
            d=1;
        }
        if(ReadTemp()<1930&&d==1){
            Boil(0);
            d=0;
        }
        if(Makp==1){
            AirFrs(1);
            Feed(1);
            FRS=FRS+1;
        }
        if(FRS>80000){
            AirFrs(0);
            Feed(0);
            FRS=0;
            Makp=0;
        }
        MainDelay_ms(1);



        dat[0] = adc_convert(ADC_CHANNEL1, ADC_12BIT);
        dat[1] = adc_convert(ADC_CHANNEL2, ADC_12BIT);
        dat[2] = adc_convert(ADC_CHANNEL3, ADC_12BIT);
        dat[3] = adc_convert(ADC_CHANNEL4, ADC_12BIT);



    }
    return 0;
}
