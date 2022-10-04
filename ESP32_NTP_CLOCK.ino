//SIMULACIÓN DEL PROYECTO: https://wokwi.com/projects/344601628728361555
/*
 * Date:    04/10/2022
 * Title:   LCD 16x2 ESP32
 * Author:  urish's projects
 * Edit:    RELL9030
 * References: https://docs.wokwi.com/guides/esp32-wifi
 *              
*/
/*
 *****************************************************
 *
 *    LIBRERIAS
 *
 *****************************************************
*/
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <ESP32Time.h>
/*
 *****************************************************
 *
 *    VARIABLES DEFINIDAS.
 *
 *****************************************************
*/
#define RS 19 //PIN D19 o D5
#define EN 18 //PIN D18 o TX2 GPIO17
#define DB4 5 //PIN D5 o RX2 GPIO16
#define DB5 4 //PIN D4
#define DB6 2 //PIN D2
#define DB7 15 //PIN D15
LiquidCrystal LCD(RS, EN, DB4, DB5, DB6, DB7); //INICIALIZACION LCD 16x2
#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     -18000     
//UTC PAIS  x  3600seconds = hora del paìs buscado
#define UTC_OFFSET_DST 0
/*
 *****************************************************
 *
 *    SETUP
 *
 *****************************************************
*/
void setup() {
  Serial.begin(115200);
  LCD.begin(16, 2);

  LCD.setCursor(0, 0);
  LCD.print("Connecting to ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Online");
  LCD.setCursor(0, 1);
  LCD.println("Updating time...");

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}
/*
 *****************************************************
 *
 *    LOOP
 *
 *****************************************************
*/ 
void loop() {
  printLocalTime();
  delay(250);
}
/*
 *****************************************************
 *
 *    FUNCIONES
 *
 *****************************************************
*/ 
void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    LCD.setCursor(0, 1);
    LCD.println("Connection Err");
    return;
  }

  LCD.setCursor(8, 0);
  LCD.println(&timeinfo, "%H:%M:%S");

  LCD.setCursor(0, 1);
  LCD.println(&timeinfo, "%d/%m/%Y   %Z");
}
