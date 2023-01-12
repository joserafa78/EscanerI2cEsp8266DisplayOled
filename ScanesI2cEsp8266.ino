// Autor: Jose Rafael Jimenez
// https://github.com/joserafa78/EscanerI2cEsp8266DisplayOled.git
//  Herramienta para el Taller:
// Escanea el Bus de comunicacion I2C. (3.3V)
// Nota: Para Escanear linea I2C de 1.8V Se requiere un "Covertido de Nivel Logico"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int LED = D7;
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 0
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

void setup()
{
    Wire.begin();
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.begin(115200);
    Serial.println("\n Escaner Linea I2C");
    pinMode(LED, OUTPUT);
    //----------------
    oled.fillScreen(0);
    oled.setFont();
    oled.setTextSize(1);
    oled.setTextColor(1, 0);
    oled.setCursor(0, 0);
    oled.println("Github:@Joserafa78");
    oled.setTextSize(2);
    oled.print("Scaner.");
    oled.setTextSize(3);
    oled.setTextColor(0, 1); // Color Invertido.
    oled.setCursor(0, 32);
    oled.print("__I2C__");
    , ,
        oled.display();
    delay(5000);
}

void loop()
{
    byte error, address;
    int nDevices;
    String TextoLcd;
    Serial.println("Escaneando Linea...");
    MuestraOLED(".....", 3, 35, 1);
    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            nDevices++;
            Serial.print("I2C Dispositivo encontrado en la Direccion 0x");
            TextoLcd = TextoLcd + "(0x";
            if (address < 16)
            {
                Serial.print("0");
                TextoLcd = TextoLcd + "0";
            }
            Serial.println(address, HEX);
            TextoLcd = TextoLcd + address + ") ";
            Serial.println(TextoLcd);
            digitalWrite(LED, HIGH);
        }
        else if (error == 4)
        {
            Serial.print("Error desconocido en la Direecion 0x");
            TextoLcd = TextoLcd + "Error Direcion 0x";
            if (address < 16)
            {
                Serial.print("0");
                TextoLcd = TextoLcd + "0";
            }
            Serial.println(address, HEX);
            TextoLcd = TextoLcd + address + ") ";
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C Dispositivos \n");
        TextoLcd = TextoLcd + "No Dispositivos I2C ";
    }
    else
    {
        Serial.println("Hecho\n");
        // TextoLcd=TextoLcd+" @Joserafa78 ";
    }
    TextoLcd = TextoLcd + "<N:" + nDevices + ">";

    MuestraOLED(TextoLcd, 5, 35, 1);
    digitalWrite(LED, LOW);
    delay(2000);
}
void MuestraOLED(String TEXTO, int x, int y, int t)
{
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.setTextSize(2);
    oled.print("Scaner.I2C");
    oled.setTextColor(WHITE);
    oled.setCursor(x, y);
    oled.setTextSize(t);
    oled.print(TEXTO);
    oled.display();
}