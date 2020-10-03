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
   - в режиме белого цвета, нет настроек

*/


//================================ НАСТРОЙКИ =============================

// настройки ленты
#define SEGMENT_LEDS 3  // кол. светодиодов в одном сегменте
#define LED_PIN 6       // пин подключение ленты
#define BRIGHTNESS 100   // яркость (0 - 255); (можно настроить с энкодера)

#define COLOR_ORDER GRB // кодировка цвета
#define LED_TYPE WS2811 // тип ленты


// пины энкодера
#define CLK 4
#define DT 3
#define SW 2

#define TYPE 2   // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый. Если ваш энкодер работает странно, смените тип


#define PHOTO_PIN A0  // пин фоторезистора


#define AUTO_BRIGHT 1        // автоматическая подстройка яркости от уровня внешнего освещения (1 - включить, 0 - выключить)
#define MAX_BRIGHT 255       // максимальная яркость (0 - 255)
#define MIN_BRIGHT 25        // минимальная яркость (0 - 255)
#define BRIGHT_CONSTANT 1000  // константа усиления от внешнего света (0 - 1023)
// чем МЕНЬШЕ константа, тем "резче" будет прибавляться яркость
#define COEF 0.8             // коэффициент фильтра (0.0 - 1.0), чем больше - тем медленнее меняется яркость

#define COLOR_MODE 0    // расцветка цыфр (0 - один цвет (COLOR); 1 - плавная смена цвета; 2 - радуга, каждая цыфра своим цветом; 3 - все цыфры белые;) (можно настроить с энкодера)
#define COLOR 80        // цвет по HSV (0 - 255); (можно настроить с энкодера)
#define SPEED 25        // скорость смены цвета в милисекундах; (можно настроить с энкодера)
#define COLOR_STEP 0    // шаг цвета в режиме радуги (чем больше, тем более разными цветами будет гореть цыфры); (можно настроить с энкодера)
#define RAINBOW_TIME 80 // время смены цвета в режиме радуги; (можно настроить с энкодера)
#define EFFECT_AMOUNT 3 // количество режимов


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
byte effect_amount = EFFECT_AMOUNT;

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
unsigned long bright_timer;

int new_bright, new_bright_f;

int hrs;
int mins;

int newHrs;
int newMins;

void setup() {

#if (TYPE == 1)
  enc.setType(TYPE1);
#endif

#if (TYPE == 2)
  enc.setType(TYPE2);
#endif


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, SEGMENT_LEDS * 7 * 4).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(bright);

  rtc.begin();

  if (rtc.lostPower()) {  //  при потере питания
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // установить время компиляции
  }
}

void loop() {

  writeTime();
  timeWork();
  enc.tick();

  switch (col_mode) {
    case 1: colors();
      break;
    case 2: rainbow();
      break;
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

void writeTime() {
  // обозначение времени
  DateTime now = rtc.now();
  hrs = now.hour();
  mins = now.minute();
}

void timeWork() {
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
}
