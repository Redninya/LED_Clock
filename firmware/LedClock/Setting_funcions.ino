void timeSet() {
  DateTime now = rtc.now();
  hrs = now.hour();
  mins = now.minute();

  switch (loc) {
    case 1: hrs1();
      break;
    case 2: hrs2();
      break;
    case 3: mins1();
      break;
    case 4: mins2();
      break;
  }
}

// настройка времени
void timeSetting() {
  enc.tick();

  if (enc.isRight()) {
    newMins++;
  }
  if (enc.isLeft()) {
    newMins--;
  }
  if (enc.isRightH()) {
    newHrs++;
  }
  if (enc.isLeftH()) {
    newHrs--;
  }

  rtc.adjust(DateTime(2020, 4, 20, newHrs, newMins, 0));
  timeSet();
}


void sett() {
  if (col_mode == 2) {
    if (enc.isRightH()) {
      rainSet -= 5;
    }
    if (enc.isLeftH()) {
      rainSet += 5;
    }
  }

  if (enc.isRight()) {
    if (col_mode == 0) color += 5;        // если выключена плавная смена цвета, при повороте зажатого экодера, меняется цвет
    else if (col_mode == 1) spd--;        // если включена плавная смена цвета, при повороте зажатого экодера, меняется скорость смены цвета
    else if (col_mode == 2) colStep += 5; // если включен режим радуга, при повороте зажатого экодера, меняется шаг цвета цыфр
  }

  if (enc.isLeft()) {
    if (col_mode == 0) color -= 5;
    else if (col_mode == 1) spd++;
    else if (col_mode == 2) colStep -= 5;
  }

  if (enc.isSingle()) {
    col_mode++;
    if (col_mode > effect_amount) {
      col_mode = 0;
    }
  }
}

void brght() {
  // настройка яркости
  if (AUTO_BRIGHT) {                         // если включена адаптивная яркость
    if (millis() - bright_timer > 100) {     // каждые 100 мс
      bright_timer = millis();               // сброить таймер
      new_bright = map(analogRead(PHOTO_PIN), 0, BRIGHT_CONSTANT, MIN_BRIGHT, MAX_BRIGHT);   // считать показания с фоторезистора, перевести диапазон
      new_bright = constrain(new_bright, MIN_BRIGHT, MAX_BRIGHT);
      bright = bright * COEF + new_bright * (1 - COEF);
      FastLED.setBrightness(bright);      // установить новую яркость
    }
  }

  else if (!AUTO_BRIGHT) {
    if (enc.isRight()) {
      bright += 10;
    }
    if (enc.isLeft()) {
      bright -= 10;
    }
    FastLED.setBrightness(bright);
  }
}
