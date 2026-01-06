/*
 * PWMS.c
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

/* channels */
#include "PWMS.h"
#include <PE_Types.h>
#include "IO_Map.h"

void FTM0_Init (tFTM ftm, uint16 iniVal, uint16 modVal)
{
  FTM0_CNTIN    = iniVal;
  FTM0_CNT      = 0l; /* update the counter with its initial value (CNTIN)    */
  FTM0_MOD      = modVal;
  FTM0_SC       = ftm.SC;
  FTM0_CONF 	= ftm.CONF;
  FTM0_MODE	    = ftm.MODE;
  FTM0_SYNCONF	= ftm.SYNCONF;
}

void FTM3_Init (tFTM ftm, uint16 iniVal, uint16 modVal)
{

  FTM3_CNTIN    = iniVal;
  FTM3_CNT      = 0l; /* update the counter with its initial value (CNTIN)    */
  FTM3_MOD      = modVal;
  FTM3_SC       = ftm.SC;
  FTM3_CONF 	= ftm.CONF;
  FTM3_MODE	    = ftm.MODE;
  FTM3_SYNCONF	= ftm.SYNCONF;
}

void FTM0CH0_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C0SC = ftm_ch.CnSC;
    FTM0_C0V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<0)&ftm_ch.COMBINE);
}

void FTM0CH1_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C1SC = ftm_ch.CnSC;
    FTM0_C1V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<0)&ftm_ch.COMBINE);
}

void FTM0CH2_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C2SC = ftm_ch.CnSC;
    FTM0_C2V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<8)&ftm_ch.COMBINE);
}

void FTM0CH3_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C3SC = ftm_ch.CnSC;
    FTM0_C3V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<8)&ftm_ch.COMBINE);
}

void FTM0CH4_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C4SC = ftm_ch.CnSC;
    FTM0_C4V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<16)&ftm_ch.COMBINE);
}

void FTM0CH5_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C5SC = ftm_ch.CnSC;
    FTM0_C5V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<16)&ftm_ch.COMBINE);
}

void FTM0CH6_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C6SC = ftm_ch.CnSC;
    FTM0_C6V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<24)&ftm_ch.COMBINE);
}

void FTM0CH7_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM0_C7SC = ftm_ch.CnSC;
    FTM0_C7V  = value;
    FTM0_COMBINE |= ((uint32)(0x3F<<24)&ftm_ch.COMBINE);
}

void FTM3CH0_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C0SC = ftm_ch.CnSC;
    FTM3_C0V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<0)&ftm_ch.COMBINE);
}

void FTM3CH1_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C1SC = ftm_ch.CnSC;
    FTM3_C1V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<0)&ftm_ch.COMBINE);
}

void FTM3CH2_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C2SC = ftm_ch.CnSC;
    FTM3_C2V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<8)&ftm_ch.COMBINE);
}

void FTM3CH3_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C3SC = ftm_ch.CnSC;
    FTM3_C3V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<8)&ftm_ch.COMBINE);
}

void FTM3CH4_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C4SC = ftm_ch.CnSC;
    FTM3_C4V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<16)&ftm_ch.COMBINE);
}

void FTM3CH5_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C5SC = ftm_ch.CnSC;
    FTM3_C5V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<16)&ftm_ch.COMBINE);
}

void FTM3CH6_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C6SC = ftm_ch.CnSC;
    FTM3_C6V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<24)&ftm_ch.COMBINE);
}

void FTM3CH7_Init (tFTM_CH ftm_ch, uint16 value)
{
    FTM3_C7SC = ftm_ch.CnSC;
    FTM3_C7V  = value;
    FTM3_COMBINE |= ((uint32)(0x3F<<24)&ftm_ch.COMBINE);
}
