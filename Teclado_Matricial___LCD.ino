
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

/* Display */
/* Display */
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int col = 0; // contador para la posición actual de la columna en el LCD

/* Keypad setup */
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

uint64_t value = 0;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2); // inicializa el LCD con dos filas de 16 caracteres cada una
  lcd.clear();
  lcd.cursor();

  lcd.setCursor(0, 0);
}

char operation = 0;
String memory = "";
String current = "";
uint64_t currentDecimal;
bool decimalPoint = false;

void processInput(char key) {
  if ('-' == key && current == "") {
    current = "-";
    lcd.print("-");
    col++; // aumenta el contador de la columna
    return;
  }

  if ('.' == key && current.indexOf('.') >= 0) {
    return;
  }

  if ('.' != key && current == "0") {
    current = String(key);
  } else if (key) {
    current += String(key);
  }

  lcd.print(key);
  col++; // aumenta el contador de la columna

  // si se han impreso 16 caracteres, cambia a la segunda fila del LCD
  if (col == 16) {
    lcd.setCursor(0, 1);
  }
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    processInput(key);
  }
}
s
