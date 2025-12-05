///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasLoRa
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
#include "string.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
RESPOSTA LORA
==============================================================================*/
void respostaLora() {
	char headerEnvioLora[8];
	memset(headerEnvioLora, 0x00, 8);
	headerEnvioLora[0] = make8(enderecoLoraTransmissor, 1);
	headerEnvioLora[1] = make8(enderecoLoraTransmissor, 0);
	headerEnvioLora[2] = canalLora;

	HAL_UART_Transmit(&huart3, &headerEnvioLora, 3, 300);
	HAL_UART_Transmit(&huart3, "$,01,\r\n", 7, 200);
}
/*==============================================================================
COMANDO 1: RECEBE ACIONAMENTO
==============================================================================*/
void comandoRecebeAcionamento(uint8_t index) {

	if(bufferLora[index + 5] == '1') {
		flagAcionamento = true;
	}
	else {
		flagAcionamento = false;
	}

	respostaLora();
}
/*==============================================================================
PROTOCOLO LORA
==============================================================================*/
void protocoloLora() {

	if(flagPacoteLora) {
		signed int index = indexOf(bufferLora, "$,01,");

		if(index >= 0) {
			uint8_t comando = charToByte(bufferLora[index + 2]);
			comando *= 10;
			comando += charToByte(bufferLora[index + 3]);
			flagLedCOM = true;
			contadorTimeoutTransmissor = 0;
			if(comando == 1) {
				comandoRecebeAcionamento(index);
			}
		}

		flagPacoteLora = false;
		apagaLoraBuffer();
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
