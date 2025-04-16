#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

/*
python -m esptool --port com8 --baud 921600 write_flash 0x00000 C:\Users\stacja\Downloads\JC8048W550\backup_16MB.bin
esptool.py --port com8 --baud 921600 write_flash 0x00000 /mnt/c/Users/stacja/Downloads/JC8048W550/backup_16MB.bin
*/