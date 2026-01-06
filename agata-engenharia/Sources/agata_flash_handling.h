/*
 * agata_flash_handling.h
 *
 *  Created on: 13/08/2024
 *      Author: marcos.butignol
 */

#ifndef SOURCES_AGATA_FLASH_HANDLING_H_
#define SOURCES_AGATA_FLASH_HANDLING_H_

void fnRotinaBackupMemoriaConfiguracaoValida(int timeStampBackup);

int checaSeValorValidoMemoria(unsigned char byteParaChecar, int tipoByte, unsigned char valorMinimo, unsigned char valorMaximo);

int fnChecaMemoriaConfiguracaoValida();



#endif /* SOURCES_AGATA_FLASH_HANDLING_H_ */
