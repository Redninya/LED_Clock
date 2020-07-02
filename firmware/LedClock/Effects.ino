
// режим плавной смены цвета
void colors() {
  if (millis() - colTime > spd) {
    color++;
    colTime = millis();
  }
}

// режим радуги
void rainbow() {
  if (millis() - rainTime > rainSet) {
    col1 += 3;
    rainTime = millis();
  }
  col2 = col1 + 30 + colStep;
  col3 = col2 + 30 + colStep;
  col4 = col3 + 30 + colStep;

  switch (loc) {
    case 1: color = col1;
      break;
    case 2: color = col2;
      break;
    case 3: color = col3;
      break;
    case 4: color = col4;
  }
}
