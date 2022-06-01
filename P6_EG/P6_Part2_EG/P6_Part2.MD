## Práctica 6 Parte 2:

### Código:
```
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN	21    //Pin 9 para el reset del RC522
#define SS_PIN	15   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
	Serial.begin(115200); //Iniciamos la comunicación  serial
	SPI.begin(14,12,13,15);        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	Serial.println("Lectura del UID");
}

void loop() {
	// Revisamos si hay nuevas tarjetas  presentes
	if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
  		//Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();         
            }      
	}	
}

```

### Descibir la salida por el puerto serie:
Compilamos y subimos el programa a la placa. Este programa hace que al pasar una tarjeta o unn llavero por delante del sensor que estamos utilizando, monitorizando el programos podamos ver un display en la pantalla del ordenador donde vamos a ver el código de la tarjeta o llavero que estemos pasando por el sensor.

![alt text](Captura.JPG)

### Explicar el funcionamiento:
Para poder utilizar este sensor primeramente hemos de instalar una libreria llamada "MFRC522" y declararla:
```
#include <SPI.h>
#include <MFRC522.h>
```

Seguidamente definimos los pines para los pines de reset y SDA. También creamos el objeto para estos:
```
#define RST_PIN	21    //Reset
#define SS_PIN	15   //(SDA)
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
```

En el setup primeramente inicializamos la comunicación serial, seguidamente inicializamos el bus SPI y el MFRC522. Finalmente imprimimos por pantalla un mensaje que se mostrara cuando podamos empezar ha pasar la tarjeta o e llavero por el sensor.
```
void setup() {
	Serial.begin(115200); //Iniciamos la comunicación  serial
	SPI.begin(14,12,13,15);        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	Serial.println("Lectura del UID");
}
```

Ya en el loop empezamos a trabajar con lo que vamos pasando por el sensor. En primer lugar el sensor va ir revisando si pasamos alguna cosa por delante, seguidamente selecciona la tarjeta que le hemos mostrado, de la cual por pantalla nos va a mostrar su UID. Y finalmente terminamos con la lectura de la tarjeta actual.
```
void loop() {
	// Revisamos si hay nuevas tarjetas  presentes
	if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
  		//Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();         
            }      
	}	
}
```
