//
// Use one MAX7219 to control 8-digit seven-segment display
// the display module: http://www.icshop.com.tw/product_info.php/products_id/20686
//
// MAX7219 datasheet: https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
// ref: https://docs.labs.mediatek.com/resource/linkit7697-arduino/en/tutorial/driving-7-segment-displays-with-max7219
//

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)

// shutdown mode (datasheet table 3)
#define MAX7219_OFF             (0x0)
#define MAX7219_ON              (0x1)

// pin 13 of MAX7219 (CLK)
const int clock_pin = A3;
// pin 12 of MAX7219 (LOAD)
const int data_latch_pin = A2;
// pin 1 of MAX7219 (DIN)
const int data_input_pin = A1;

// digit pattern for a 7-segment display. datasheet table 5
const byte digit_pattern[16] = {
  B01111110,  // 0
  B00110000,  // 1
  B01101101,  // 2
  B01111001,  // 3
  B00110011,  // 4
  B01011011,  // 5
  B01011111,  // 6
  B01110000,  // 7
  B01111111,  // 8
  B01111011,  // 9
  B01110111,  // A
  B00011111,  // b
  B01001110,  // C
  B00111101,  // d
  B01001111,  // E
  B01000111   // F
};

#define DP_FLAG       (B10000000)
#define NUM_OF_DIGITS (8)

unsigned int counter = 0;
// digit_base should be <= 16
// for example, if digit_base := 2, binary values will be shown. If digit_base := 16, hexidecimal values will be shown
unsigned int digit_base = 10;

// update the register value of MAX7219
void set_register(byte address, byte value){
  digitalWrite(data_latch_pin, LOW);
  shiftOut(data_input_pin, clock_pin, MSBFIRST, address);
  shiftOut(data_input_pin, clock_pin, MSBFIRST, value);
  digitalWrite(data_latch_pin, HIGH);
}

void init_max7219(){
  // disable test mode. datasheet table 10
  set_register(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7 (0x0~0xF)
  set_register(MAX7219_INTENSITY_REG, 0xF);
  // turn off display. datasheet table 3
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register(MAX7219_DECODE_REG, B00000000);
}

void setup(){
  // init pin states
  pinMode(clock_pin, OUTPUT);
  pinMode(data_latch_pin, OUTPUT);    
  pinMode(data_input_pin, OUTPUT);
  // init MAX2719 states
  init_max7219();
}

void loop(){
  int i;
  unsigned int number;
  unsigned int digit_value;
  byte byte_data;
  number = counter++;
  // turn off display first
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // get every values in each position of those 8 digits based on "digit_base"
  for (i = 0; i < NUM_OF_DIGITS; i++){
    digit_value = number % digit_base;
    number /= digit_base;
    byte_data = digit_pattern[digit_value];
    if (counter % NUM_OF_DIGITS == i){
      byte_data |= DP_FLAG;
    }
    set_register(MAX7219_DIGIT_REG(i), byte_data);
  }
  // turn on display
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_ON);
  delay(50);
}