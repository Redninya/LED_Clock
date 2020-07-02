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
    if (col_mode > 2) {
      col_mode = 0;
    }
  }
}

void brght() {
  // настройка яркости
  if (enc.isRight()) {
    bright += 10;
  }
  if (enc.isLeft()) {
    bright -= 10;
  }
  FastLED.setBrightness(bright);
}
