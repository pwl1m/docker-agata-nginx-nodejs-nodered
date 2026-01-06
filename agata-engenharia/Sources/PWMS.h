/*
 * PWMS.h
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#ifndef SOURCES_PWMS_H_
#define SOURCES_PWMS_H_

#include <PE_Types.h>

typedef struct {uint32 SC, CONF, MODE, SYNCONF;} tFTM;
typedef struct {uint32 CnSC, COMBINE;} tFTM_CH;

#define SET(mask)                       mask
#define CLR(mask)                       0

#define FTM_CHANNEL_PWMNORMAL_COMBINE_COMP_DTEN_CONFIG                        \
(tFTM_CH)  {                                                                  \
/* CnSC    */ CLR(FTM_CnSC_CHIE_MASK)|SET(FTM_CnSC_MSB_MASK)|                 \
              CLR(FTM_CnSC_MSA_MASK)|SET(FTM_CnSC_ELSB_MASK)|                 \
              CLR(FTM_CnSC_ELSA_MASK)|CLR(FTM_CnSC_DMA_MASK),                 \
/* COMBINE */ SET(FTM_COMBINE_SYNCEN0_MASK)|SET(FTM_COMBINE_DTEN0_MASK)|      \
              SET(FTM_COMBINE_COMP0_MASK)|SET(FTM_COMBINE_COMBINE0_MASK)|     \
              SET(FTM_COMBINE_SYNCEN1_MASK)|SET(FTM_COMBINE_DTEN1_MASK)|      \
              SET(FTM_COMBINE_COMP1_MASK)|SET(FTM_COMBINE_COMBINE1_MASK)|     \
              SET(FTM_COMBINE_SYNCEN2_MASK)|SET(FTM_COMBINE_DTEN2_MASK)|      \
              SET(FTM_COMBINE_COMP2_MASK)|SET(FTM_COMBINE_COMBINE2_MASK)|     \
              SET(FTM_COMBINE_SYNCEN3_MASK)|SET(FTM_COMBINE_DTEN3_MASK)|      \
              SET(FTM_COMBINE_COMP3_MASK)|SET(FTM_COMBINE_COMBINE3_MASK),     \
}

#define FTM_MODULE_SYSCLK_DIVBY1_COMBINE_IRQ_CONFIG(noi)                      \
(tFTM)  {                                                                     \
/* SC      */ SET(FTM_SC_TOIE_MASK)|CLR(FTM_SC_CPWMS_MASK)|                   \
              SET(FTM_SC_CLKS(1))|SET(FTM_SC_PS(0)),                          \
/* CONF    */ SET(FTM_CONF_BDMMODE(3))|SET(FTM_CONF_NUMTOF(noi-1)),           \
/* MODE    */ SET(FTM_MODE_WPDIS_MASK)|SET(FTM_MODE_FTMEN_MASK),              \
/* SYNCONF */ SET(FTM_SYNCONF_SYNCMODE_MASK),                                 \
}

#define FTM0CH0_SetValue(x)           { FTM0_C0V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;}
#define FTM0CH1_SetValue(x)           { FTM0_C1V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH2_SetValue(x)           { FTM0_C2V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH3_SetValue(x)           { FTM0_C3V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH4_SetValue(x)           { FTM0_C4V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH5_SetValue(x)           { FTM0_C5V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH6_SetValue(x)           { FTM0_C6V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM0CH7_SetValue(x)           { FTM0_C7V = x;                         \
                                        FTM0_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM1CH0_SetValue(x)           { FTM1_C0V = x;                         \
                                        FTM1_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM1CH1_SetValue(x)           { FTM1_C1V = x;                         \
                                        FTM1_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM2CH0_SetValue(x)           { FTM2_C0V = x;                         \
                                        FTM2_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM2CH1_SetValue(x)           { FTM2_C1V = x;                         \
                                        FTM2_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH0_SetValue(x)           { FTM3_C0V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH1_SetValue(x)           { FTM3_C1V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH2_SetValue(x)           { FTM3_C2V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH3_SetValue(x)           { FTM3_C3V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH4_SetValue(x)           { FTM3_C4V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM3CH5_SetValue(x)           { FTM3_C5V = x;                         \
										FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK; }
#define FTM_DEATIME_SetValue(module,presc,value)                              \
        module##DEADTIME_SetValue(presc, value)

#define FTM0_SetModulo(x)             { FTM0_MOD = x; }

#define FTM_CHAN_SetValue(module,chan,value)  module##chan##_SetValue(value)

#define FTM0DEADTIME_SetValue(presc, value)                                   \
        { FTM0_DEADTIME = FTM_DEADTIME_DTPS(presc)|FTM_DEADTIME_DTVAL(value); }
#define FTM1DEADTIME_SetValue(presc, value)                                   \
        { FTM1_DEADTIME = FTM_DEADTIME_DTPS(presc)|FTM_DEADTIME_DTVAL(value); }
#define FTM2DEADTIME_SetValue(presc, value)                                   \
        { FTM2_DEADTIME = FTM_DEADTIME_DTPS(presc)|FTM_DEADTIME_DTVAL(value); }
#define FTM3DEADTIME_SetValue(presc, value)                                   \
        { FTM3_DEADTIME = FTM_DEADTIME_DTPS(presc)|FTM_DEADTIME_DTVAL(value); }

#define FTM_CHAN_Init(module,ch,cfg,value)    module##ch##_Init(cfg,value)

#define FTM_Init(module,cfg,iniVal,modVal)  module##_Init(cfg,   \
                                                        iniVal,modVal)

extern void FTM0_Init (tFTM ftm, uint16 iniVal, uint16 modVal);
extern void FTM3_Init (tFTM ftm, uint16 iniVal, uint16 modVal);
extern void FTM0CH0_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH1_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH2_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH3_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH4_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH5_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH6_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM0CH7_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM1CH0_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM1CH1_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM2CH0_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM2CH1_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH0_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH1_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH2_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH3_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH4_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH5_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH6_Init (tFTM_CH ftm_ch, uint16 value);
extern void FTM3CH7_Init (tFTM_CH ftm_ch, uint16 value);

#endif /* SOURCES_PWMS_H_ */
