# Práctica 6 Parte 1:
### Código:
```
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
    Serial.begin(115200);
    Serial.print("Iniciando SD ...");
    SPI.begin(18,19,23,5);

    if (!SD.begin(5)) {
        Serial.println("No se pudo inicializar");
        return;
    }
    Serial.println("inicializacion exitosa");
    
    if(!SD.exists("/archivo.txt")){
            Serial.println("example.txt exists.");
    }

    else{
            Serial.println("example.txt no exists.");
    }

    myFile = SD.open("/archivo.txt", FILE_WRITE);
    myFile.close();

    if (SD.exists("/archivo.txt")){


            Serial.println("archivo.txt exists. ");
    }
    else{
            Serial.println("archivo.txt doesn't exist");
    }
    myFile = SD.open("/archivo.txt", FILE_WRITE);//abrimos  el archivo 
    myFile.println("Hola mundo");
    myFile.close();
    myFile=SD.open("/archivo.txt");
    if (myFile) {
        Serial.println("archivo.txt:");
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close(); //cerramos el archivo
    } else {
        Serial.println("Error al abrir el archivo");
    }
}

void loop()
{}
```

### Salida:
Este codigo lo que hace es que en la tarjeta SD incorporada en el lector de tarjetas se cree un archivo con un contenido dentro. 
Una vez creado el archivo, el mismo codigo hace que este archivo ya creado se abra y muestra por pantalla su contenido, en el caso de este "Hola mundo":

![alt text](Captura2.JPG)

### Explicar el funcionamiento:
Para poder ejecutar el programa utilixando el lector de tarjetas SD, primeramente hay que declarar las siguientes librerias:
```
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
```

Declaramos también la variable:
```
File myFile;
```

Ya dentro del setup empezamos a iniciando la comunicación serial, enviando un mensaje conforme iniciamos la tarjeta y declarand los pins VSPI:
```
Serial.begin(115200);
Serial.print("Iniciando SD ...");
SPI.begin(18,19,23,5);
```

Seguidamente iniciamos la tarjeta, en el caso que no se pueda inicializar nos mostrara por pantalla un mensaje conforme no se ha podido inicializar, y lo mismo si finalmente se ha iniciado éxito.
```
if (!SD.begin(5)) {
        Serial.println("No se pudo inicializar");
        return;
    }
Serial.println("inicializacion exitosa");
```

Con esta pequeña condición comprovamos si en la tarjeta hay algun archivo de texto dentro y nos muestar por panatalla un mensaje diferente dependiendo de lo que encuentre:
```
if(!SD.exists("/archivo.txt")){
            Serial.println("example.txt exists.");
    }

    else{
            Serial.println("example.txt no exists.");
    }

```

A continuación generamos un nuevo archivo:
```
myFile = SD.open("/archivo.txt", FILE_WRITE);
myFile.close();
```

Hacemos una nuevo condición para comprovar si se ha generado el fichero:
```
if (SD.exists("/archivo.txt")){
    Serial.println("archivo.txt exists. ");
}
else{
    Serial.println("archivo.txt doesn't exist.");
}
```

Abrimos el fichero y escribimos en el fichero:
```
myFile = SD.open("/archivo.txt", FILE_WRITE);//abrimos  el archivo 
myFile.println("Hola mundo");
myFile.close();
```

Finalmente, abrimos el documento y hacemos una condición donde en el caso de que cumpla que el documento este abierto nos mostrara por pantalla lo que haya escrito dentro de el documento y luego lo cerrara. Por otro lado si este archivo no se ha podido abrir nos mostrara por pantalla un mensaje informandonos de que no se ha podido abrir el documento:
```
myFile=SD.open("/archivo.txt");
if (myFile) {
    Serial.println("archivo.txt:");
    while (myFile.available()) {
        Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
} else {
    Serial.println("Error al abrir el archivo");
}
```

