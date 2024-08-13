/*
 * ADC.c
 *
 *  Created on: Jun 18, 2024
 *      Author: Danial
 */


#include "ADC.h"
void ADC_Init()
{
  SysCtrlRegs.HISPCP.all = 0x0003;
  InitAdc();
  AdcRegs.ADCTRL1.bit.SUSMOD = 0x00;
  AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
  AdcRegs.ADCTRL1.bit.ACQ_PS = 0xF;
  AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;
  AdcRegs.ADCTRL1.bit.CPS = 0;
  AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
  AdcRegs.ADCTRL3.bit.SMODE_SEL  = 1;
  AdcRegs.ADCTRL1.bit.CONT_RUN = 1;
  AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x00;
//  AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x01;
  AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x1;
  AdcRegs.ADCREFSEL.bit.REF_SEL = 0;
  AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;
  AdcRegs.ADCOFFTRIM.bit.OFFSET_TRIM = 200;
  AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
  AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}

Uint16 SampleTable1[1024];
Uint16 SampleTable2[1024],mi = 0;
Uint64 res = 0;
void ADC_Read()
{
int i;
res = 0;
for(i = 0; i < 60; i++)
{
    while(AdcRegs.ADCST.bit.INT_SEQ1 ==  0) {}
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    SampleTable1[i] = AdcMirror.ADCRESULT0 ;
    SampleTable2[i] = AdcMirror.ADCRESULT1 ;
    res += SampleTable2[i];
}
 mi = res / 60;
}
