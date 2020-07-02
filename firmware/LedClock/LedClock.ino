/*
   Скетч часов на Ардуино из адресной светодиодной
   ленты и модуля часов реалного времени.
   Управление осушествляется энкодером.

   By Dairis Mivreniks 2020
*/


/*
   =========================== ИНСТРУКЦИЯ =============================

   В "главном меню"

   - при вращении энкодера меняется яркость


   При удержании кнопки энкодера, попадаешь и так же выходишь из настроек времеи

   - при вращении меняется минуты
   - при вращении с зажатым энкодером меняются часы


   При двойном клике кнопки энкодера, попадаешь и так же выходишь из настроек цветов и эффектов

   - по клику кнопки энкодера меняется режим цвета (статический / плавная смена цвета/ радуга)
   - в режиме статического цвета и вращении энкодера меняется цвет
   - в режиме плавной смены цвета и вращении энкодера меняется скорость плавной смены цветов
   - в режиме радуги и вращении энкодера меняется шаг цвета
   - в режиме радуги и вращении зажатого энкодера меняется скорость радуги

*/


//================================ НАСТРОЙКИ =============================

// настройки ленты
#define SEGMENT_LEDS 3  // кол. светодиодов в одном сегменте
#define LED_PIN 6       // пин подключение ленты
#define BRIGHTNESS 100   // яркость (0 - 255); (можно настроить с энкодера)

#define COLOR_ORDER GRB // кодировка цвета
#define LED_TYPE WS2811 // тип ленты


// пины энкодера
#define CLK 4   // жилательно не менять пины энка, потому что он сделан через прерывания
#define DT 3
#define SW 2

#define TYPE 2   // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый. Если ваш энкодер работает странно, смените тип


#define COLOR_MODE 1    // расцветка цыфр (0 - один цвет (COLOR); 1 - плавная смена цвета; 2 - радуга, каждая цыфра своим цветом); (можно настроить с энкодера)
#define COLOR 80        // цвет по HSV (0 - 255); (можно настроить с энкодера)
#define SPEED 25        // скорость смены цвета в милисекундах; (можно настроить с энкодера)
#define COLOR_STEP 0    // шаг цвета в режиме радуги (чем больше, тем более разными цветами будет гореть цыфры); (можно настроить с энкодера)
#define RAINBOW_TIME 80 // время смены цвета в режиме радуги; (можно настроить с энкодера)


//========================= ДЛЯ РАЗРОБОТЧИКОВ =================================

#include <FastLED.h>
#include <Wire.h>
#include <RTClib.h>
#include "GyverEncoder.h"


RTC_DS3231 rtc;

CRGB leds[SEGMENT_LEDS * 7 * 4];

Encoder enc(CLK, DT, SW);


byte color = COLOR;
byte col_mode = COLOR_MODE;
byte spd = SPEED;
byte bright = BRIGHTNESS;
byte colStep = COLOR_STEP;
byte rainSet = RAINBOW_TIME;

byte loc;
byte pos;

byte col1;
byte col2;
byte col3;
byte col4;


boolean mode = 0;
boolean setting;

unsigned long colTime;
unsigned long rainTime;

int hrs;
int mins;

int newHrs;
int newMins;

void setup() {

  Serial.begin(9600);


#if (TYPE == 1)
  enc.setType(TYPE1);
#endif

#if (TYPE == 2)
  enc.setType(TYPE2);
#endif


  attachInterrupt(0, isrCLK, CHANGE);    // прерывание на 2 пине! CLK у энка
  attachInterrupt(1, isrDT, CHANGE);    // прерывание на 3 пине! DT у энка

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, SEGMENT_LEDS * 7 * 4).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(bright);



  rtc.begin();

  if (rtc.lostPower()) {  //  при потере питания
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // установить время компиляции
  }

}

void isrCLK() {
  enc.tick();  // отработка в прерывании
}
void isrDT() {
  enc.tick();  // отработка в прерывании
}


void loop() {

  // обозначение времени
  DateTime now = rtc.now();
  hrs = now.hour();
  mins = now.minute();

  enc.tick();

  Serial.println(rainSet);

  // ход времини
  if (mins > 59) {
    mins = 0;
    hrs++;
  }
  if (mins < 0) {
    mins = 59;
    hrs--;
  }
  if (hrs > 23) {
    hrs = 0;
  }
  if (hrs < 0) {
    hrs = 23;
  }

  if (newMins > 59) {
    newMins = 0;
    newHrs++;
  }
  if (newMins < 0) {
    newMins = 59;
    newHrs--;
  }
  if (newHrs > 23) {
    newHrs = 0;
  }
  if (newHrs < 0) {
    newHrs = 23;
  }



  if (col_mode == 1) {
    colors();
  }
  else if (col_mode == 2) {
    rainbow();
  }


  // вход и выход в настройки
  if (enc.isHolded()) {
    mode = !mode;
    newHrs = hrs;
    newMins = mins;
    rtc.adjust(DateTime(2020, 4, 20, newHrs, newMins, 0));
  }

  if (enc.isDouble()) {
    setting = !setting;
  }

  if (!setting && !mode) {
    brght();
  }

  switch (setting) {
    case 0:
      break;
    case 1: sett();
  }

  switch (mode) {
    case 0: timeSet();
      break;
    case 1: timeSetting();
      break;
  }

  // расположение цыфр на цыфербладе
  pos = loc * (SEGMENT_LEDS * 7);

  loc++;

  if (loc > 4) {
    loc = 0;
  }
}
