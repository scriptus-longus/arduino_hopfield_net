#include "Camino.h"

int x_dim_pins[3] = {2, 3, 4};
int y_dim_pins[3] = {5, 6, 7};
int pattern[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

  
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  camino.begin(9600);
}



void loop() {
  
  
  draw_pattern(pattern);
}
void ext_write_coord(byte dataLength, byte *data) {
  int x_coord = data[0];
  int y_coord = data[1];
  int val = data[2];

  for (int x = 0; x < 3; x++) {
    digitalWrite(x_dim_pins[x], val & (x_coord == x));
  }
  for (int y = 0; y < 3; y++) {
    digitalWrite(y_dim_pins[y], !(val & (y_coord == y)));
  }
  delay(1);
  
  for (int x = 0; x < 3; x++) {
    digitalWrite(x_dim_pins[x], LOW);
  }
  for (int y = 0; y < 3; y++) {
    digitalWrite(y_dim_pins[y], HIGH);
  }
}

void write_coord(int x_coord, int y_coord, int val) {
  for (int x = 0; x < 3; x++) {
    digitalWrite(x_dim_pins[x], val & (x_coord == x));
  }
  for (int y = 0; y < 3; y++) {
    digitalWrite(y_dim_pins[y], !(val & (y_coord == y)));
  }
  delay(1);
  
  for (int x = 0; x < 3; x++) {
    digitalWrite(x_dim_pins[x], LOW);
  }
  for (int y = 0; y < 3; y++) {
    digitalWrite(y_dim_pins[y], HIGH);
  }
}

void set_pattern(byte dataLength, byte *data) {
  pattern[0][0] = data[0]; 
  pattern[0][1] = data[1]; 
  pattern[0][2] = data[2]; 
  
  pattern[1][0] = data[3]; 
  pattern[1][1] = data[4]; 
  pattern[1][2] = data[5],
  
  pattern[2][0] = data[6]; 
  pattern[2][1] = data[7]; 
  pattern[2][2] = data[8]; 
  
}

void draw_pattern(int pattern[3][3]) {
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      write_coord(x, y, pattern[y][x]);
    }
  }
}

BEGIN_CALLABLES {
  {"write_coord", ext_write_coord},
  {"set_pattern", set_pattern},
} END_CALLABLES;
