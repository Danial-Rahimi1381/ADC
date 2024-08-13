/*
 * ADC.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Danial
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_
#include "DSP28x_Project.h"

extern Uint16 ChannelB,ChannelA;
extern Uint16 SampleTable1[1024];
extern Uint16 SampleTable2[1024];
extern Uint16 mi;
void ADC_Init();
void ADC_Read();
#endif /* INCLUDE_ADC_H_ */
