/* ###################################################################
**     Filename    : Events.h
**     Project     : PROJETO_AGATA_02_04_2019 - REV00
**     Processor   : MK22FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-04-03, 10:32, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H

/* MODULE Events */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "SINAL_DAS_AREAS.h"
#include "AdcLdd1.h"
#include "TENSAO_DAS_AREAS.h"
#include "AdcLdd2.h"
#include "PORTA.h"
#include "USB_PC.h"
#include "ASerialLdd1.h"
#include "SERIAL_ETHERNET.h"
#include "ASerialLdd2.h"
#include "CAN.h"
#include "PORTB.h"
#include "PORTC.h"
#include "POTENCIOMETRO_DIGITAL.h"
#include "SMasterLdd1.h"
#include "RTC1.h"
#include "Control_LCD.h"
#include "BitsIoLdd4.h"
#include "DADOS.h"
#include "BitsIoLdd1.h"
#include "Solenoide.h"
#include "TimerIntLdd5.h"
#include "TU6.h"
#include "Reserved_Solenoid.h"
#include "PwmLdd6.h"
#include "BitsIoLdd5.h"
#include "FLASH_INTERNA.h"
#include "IntFlashLdd1.h"
#include "PWM_INFRAS.h"
#include "PwmLdd1.h"
#include "PWM_BUZZER.h"
#include "PwmLdd2.h"
#include "TU1.h"
#include "TU2.h"
#include "DEBOUNCING_1ms.h"
#include "TimerIntLdd1.h"
#include "TU3.h"
#include "TEMPORIZADOR_10ms.h"
#include "TimerIntLdd2.h"
#include "PWM_TX.h"
#include "PwmLdd3.h"
#include "TU5.h"
#include "PWM_RX1.h"
#include "PwmLdd4.h"
#include "PWM_RX2.h"
#include "PwmLdd5.h"
#include "PORTD.h"
#include "PORTE.h"
#include "TEMPORIZADOR_100ms.h"
#include "TimerIntLdd3.h"
#include "TEMPORIZADOR_1s.h"
#include "TimerIntLdd4.h"
#include "TU4.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif 

void SINAL_AD_OnEnd(void);
/*
** ===================================================================
**     Event       :  SINAL_AD_OnEnd (module Events)
**
**     Component   :  SINAL_AD [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SINAL_AD_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  SINAL_AD_OnCalibrationEnd (module Events)
**
**     Component   :  SINAL_AD [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  DEBOUNCING_1ms_OnInterrupt (module Events)
**
**     Component   :  DEBOUNCING_1ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DEBOUNCING_1ms_OnInterrupt(void);

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_100ms_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_100ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_100ms_OnInterrupt(void);

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_10ms_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_10ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_10ms_OnInterrupt(void);

/*
** ===================================================================
**     Event       :  CAN0_OnFreeTxBuffer (module Events)
**
**     Component   :  CAN0 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is empty after a
**         successful transmit of a message. This event is available
**         only if method SendFrame is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Receive message buffer index.
*/
/* ===================================================================*/
void CAN0_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  CAN0_OnFullRxBuffer (module Events)
**
**     Component   :  CAN0 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is full after a
**         successful receive a message. This event is available only
**         if method ReadFrame or SetRxBufferState is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Transmit buffer index.
*/
/* ===================================================================*/
void CAN0_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_1s_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_1s [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_1s_OnInterrupt(void);

/*
** ===================================================================
**     Event       :  RFControl_OnError (module Events)
**
**     Component   :  RFControl [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RFControl_OnError(void);

/*
** ===================================================================
**     Event       :  RFControl_OnRxChar (module Events)
**
**     Component   :  RFControl [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RFControl_OnRxChar(void);

/*
** ===================================================================
**     Event       :  RFControl_OnTxChar (module Events)
**
**     Component   :  RFControl [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RFControl_OnTxChar(void);

/*
** ===================================================================
**     Event       :  RFControl_OnFullRxBuf (module Events)
**
**     Component   :  RFControl [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RFControl_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  RFControl_OnFreeTxBuf (module Events)
**
**     Component   :  RFControl [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RFControl_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  CAN_OnFreeTxBuffer (module Events)
**
**     Component   :  CAN [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is empty after a
**         successful transmit of a message. This event is available
**         only if method SendFrame is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Receive message buffer index.
*/
/* ===================================================================*/
void CAN_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  CAN_OnFullRxBuffer (module Events)
**
**     Component   :  CAN [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is full after a
**         successful receive a message. This event is available only
**         if method ReadFrame or SetRxBufferState is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Transmit buffer index.
*/
/* ===================================================================*/
void CAN_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnRxChar (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SERIAL_ETHERNET_OnRxChar(void);

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnTxChar (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SERIAL_ETHERNET_OnTxChar(void);

/*
** ===================================================================
**     Event       :  USB_PC_OnError (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnError(void);

/*
** ===================================================================
**     Event       :  USB_PC_OnRxChar (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnRxChar(void);

/*
** ===================================================================
**     Event       :  USB_PC_OnTxChar (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnTxChar(void);

void TENSAO_DAS_AREAS_OnEnd(void);
/*
** ===================================================================
**     Event       :  TENSAO_DAS_AREAS_OnEnd (module Events)
**
**     Component   :  TENSAO_DAS_AREAS [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TENSAO_DAS_AREAS_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  TENSAO_DAS_AREAS_OnCalibrationEnd (module Events)
**
**     Component   :  TENSAO_DAS_AREAS [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SINAL_DAS_AREAS_OnEnd(void);
/*
** ===================================================================
**     Event       :  SINAL_DAS_AREAS_OnEnd (module Events)
**
**     Component   :  SINAL_DAS_AREAS [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SINAL_DAS_AREAS_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  SINAL_DAS_AREAS_OnCalibrationEnd (module Events)
**
**     Component   :  SINAL_DAS_AREAS [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  USB_PC_OnFullRxBuf (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  USB_PC_OnFreeTxBuf (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnFullRxBuf (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SERIAL_ETHERNET_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  Solenoide_OnInterrupt (module Events)
**
**     Component   :  Solenoide [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Solenoide_OnInterrupt(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
