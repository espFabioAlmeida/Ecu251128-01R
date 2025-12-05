///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasReles
//AUTOR:      Fábio Almeida
//CRIADO:     28/11/2025
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
#include "string.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
ACIONAMENTO RELE
==============================================================================*/
void acionamentoRele() {
	static uint8_t ultimoEstado = false;

	if(contadorTimeoutTransmissor >= TIMEOUT_TRANSMISSOR) {
		flagAcionamento = false;
	}

	if(ultimoEstado == flagAcionamento) {
		return;
	}

	ultimoEstado = flagAcionamento;

	if(flagAcionamento) {
		contadorRele1 = TEMPO_PULSO_RELE;
		contadorRele2 = 0;
		return;
	}

	contadorRele2 = TEMPO_PULSO_RELE;
	contadorRele1 = 0;
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
