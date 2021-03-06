void zero() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 6 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 6 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void one() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 3 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 3 + pos; i < SEGMENT_LEDS * 5 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 5 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void two() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS + pos; i < SEGMENT_LEDS * 2 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 2 + pos; i < SEGMENT_LEDS * 4 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 4 + pos; i < SEGMENT_LEDS * 5 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 5 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void three() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 2 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 2 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void four() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS + pos; i < SEGMENT_LEDS * 2 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 2 + pos; i < SEGMENT_LEDS * 3 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 3 + pos; i < SEGMENT_LEDS * 5 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 5 + pos; i < SEGMENT_LEDS * 6 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 6 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void five() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS + pos; i < SEGMENT_LEDS * 3 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 3 + pos; i < SEGMENT_LEDS * 4 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 4 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void six() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 3 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 3 + pos; i < SEGMENT_LEDS * 4 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 4 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void seven() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 2 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS * 2 + pos; i < SEGMENT_LEDS * 5 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  for (byte i = SEGMENT_LEDS * 5 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void eight() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}

void nine() {
  for (byte i = 0 + pos; i < SEGMENT_LEDS + pos; i++) {
    leds[i] = CRGB::Black;
  }
  for (byte i = SEGMENT_LEDS + pos; i < SEGMENT_LEDS * 7 + pos; i++) {
    if (col_mode != 3) {
      leds[i] = CHSV(color, 255, 255);
    }
    else if (col_mode == 3) {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
}
