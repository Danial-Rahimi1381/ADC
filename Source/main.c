

#include "DSP28x_Project.h"
#include "ADC.h"

/*Defines-------------------------------------------------------*/
#define         PROG_MODE   0
#define         ADC_BITS 12
#define         V_REF 3.0
#define       Tolerance    1.0336;
int arr1[100];
int i, mx, mn, n;
int result;
/*---------------------------------------------------------------*/


#if PROG_MODE == 1
#pragma CODE_SECTION(timer0_isr, ".TI.ramfunc");
#endif

/*Loop_Timer-------------------------------------------------------*/

/*Private_Functions-----------------------------------------------*/
__interrupt void timer0_isr(void);
unsigned long ADC();
//float s();
float ADC_Result,ADC_Result2;
float Voltage1,Voltage2,Voltage3;
int counter = 0;

int main(void)
{

    InitSysCtrl();
    InitPieCtrl();

    ADC_Init();

     #if PROG_MODE == 1

        MemCopy(RamfuncsLoadStart,RamfuncsLoadEnd,RamfuncsRunStart);
        InitFlash();

    #endif
                // Initialize PIE control registers to their default state
   InitPieVectTable();
            DINT;
            IER = 0x0000;
            IFR = 0x0000;
    // Configure CPU timer 0
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000); // 150MHz CPU, 500us period


                // Set up interrupt handling for CPU timer 0
    EALLOW;
      PieVectTable.TINT0 = &timer0_isr;
    EDIS;
                // Enable CPU timer 0 interrupt
            PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
                // Enable global interrupts
            IER |= M_INT1;
            EINT;
            // Start CPU tiemr 0

            StartCpuTimer0();
            while(1){}
}


__interrupt void timer0_isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    counter++;
    ADC_Read();

    Voltage2 = ((((double)SampleTable1[0])  * 0.000732421875) ) ; // 1.0297 ;
    Voltage3 = ((((double)SampleTable1[0] - mi)  *  0.000732421875))   ;
}

/*

float s()
{
 int i ;
 float Voltage;
 for(i = 0 ; i < 100; i++)
 {
     ADC_Result = ADC_Read(0);
     arr1[i]    = ADC_Result;
     DELAY_US(50);//10000
 }
 mx = arr1[0];
 mn = arr1[0];
 // Traverse the array to find the maximum and minimum elements
 for (i = 1; i < 100; i++)
 {
     // Update mx if the current element is greater
     if (arr1[i] > mx)
     {
         mx = arr1[i];
     }

     // Update mn if the current element is smaller
     if (arr1[i] < mn)
     {
         mn = arr1[i];
     }
     Array_Result += arr1[i];
}
result = mx - mn;
Array_Result /= 100;

Voltage = ((Vref * (  Array_Result / 4095.00)) - 0);


return Voltage;
}

*/
