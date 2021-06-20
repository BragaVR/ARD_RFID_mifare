#include <SPI.h>
#include <RFID.h>

//D10:pin del lettore SDA. D9:pin del lettore RST
RFID rfid(10,9);
unsigned char status;
unsigned char str[MAX_LEN];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  Serial.println("inserire la carta nell'area di lettura...");
  

}

void loop() {
  if (rfid.findCard(PICC_REQIDL,str) == MI_OK) {
    Serial.println("carta rilevata!");
    //tipo della carta
    ShowCardType(str);
    //lettura del seriale
    if (rfid.anticoll(str) == MI_OK) {
      Serial.print("l'identificativo della carta è:  ");
      //mostra il seriale della carta:
      for (int i = 0; i < 4; i++) {
        Serial.print(0x0F & (str[i] >> 4), HEX);
        Serial.print(0x0F & str[i], HEX);
      }

    Serial.println("");

    }

    //sezione dedicata alla lettura della carta, per prevenire rindondanze e permettere la lettura continua


    rfid.selectTag(str);

  }

  rfid.halt();

}

void ShowCardType(unsigned char * type)
{
  Serial.print("tipo di carta: ");
  if (type[0] == 0x04 && type[1] == 0x00)
  Serial.println("MFOne-S50");

  else if (type[0] == 0x02 && type[1] == 0x00)
  Serial.println("MFOne-S70");

  else if (type[0] == 0x44 && type[1] == 0x00)
  Serial.println("MFS-UltraLight");

  else if (type[0] == 0x08 && type[1] == 0x00)
  Serial.println("MF-Pro");

  else if (type[0] == 0x44 && type[1] == 0x03)
  Serial.println("MF-Desire");

  else 
   Serial.println("UNknoW");


}
