#include <SPI.h>          // Biblioteca para comunicação SPI
#include <MFRC522.h>      // Biblioteca do módulo RFID RC522

// Definição dos pinos usados na comunicação
int SS_PIN = 10;          // Pino SDA (SS) conectado ao pino 10 do Arduino
int RST_PIN = 9;          // Pino RST conectado ao pino 9 do Arduino

// Cria o objeto RFID passando os pinos SS e RST
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {

  Serial.begin(9600);     // Inicia comunicação serial a 9600 bps
  SPI.begin();            // Inicia a comunicação SPI
  rfid.PCD_Init();        // Inicializa o módulo RFID

  Serial.println("Aproxime o cartao...");  // Mensagem inicial
}

void loop() {

  // Verifica se existe um novo cartão presente
  if (!rfid.PICC_IsNewCardPresent()) {
    return;  // Se não houver cartão, sai do loop e reinicia
  }

  // Tenta ler os dados do cartão
  if (!rfid.PICC_ReadCardSerial()) {
    return;  // Se falhar na leitura, sai do loop
  }

  Serial.print("UID do cartao: ");  // Texto no monitor serial

  // Percorre cada byte do UID
  for (byte i = 0; i < rfid.uid.size; i++) {

    // Mostra cada byte em formato hexadecimal
    Serial.print(rfid.uid.uidByte[i], HEX);

    Serial.print(" ");  // Espaço entre os bytes
  }

  Serial.println();  // Pula para a próxima linha

  delay(1000);  // Pequena pausa para evitar múltiplas leituras rápidas
}