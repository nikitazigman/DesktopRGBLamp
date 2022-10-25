#include <Adafruit_NeoPixel.h>
#define PIXEL_NUMBER 35
#define LED_DATA_PIN PA1
#define MAX_VALUE 255
#define STEP 63

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_NUMBER, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
class Button
{
  private:
      int button_pin;
      int power_pin;
      int ground_pin;
      bool pressed;
      bool event;

  public:
      Button(int button_pin, int power_pin, int ground_pin)
      {
          this->button_pin = button_pin;
          this->power_pin = power_pin;
          this->ground_pin = ground_pin;
          this->pressed = false;
          this->event = false;
      }
      void init(void)
      {
          pinMode(this->button_pin, INPUT);
          pinMode(this->power_pin, OUTPUT);
          pinMode(this->ground_pin, OUTPUT);
          
          digitalWrite(this->power_pin, HIGH);
          digitalWrite(this->ground_pin, LOW);
      }

      bool read_event(void){
        bool event = this->event;
        this->event = false;
        return event;
      }

      void run(void)
      {
          if (digitalRead(this->button_pin))
              this->pressed = true;

          if (this->pressed && !digitalRead(this->button_pin))
          {
              this->pressed = false;
              this->event = true;
          }
      }
};
Button red_button = Button(PA2,PA3,PA4);
Button green_button = Button(PA5,PA6,PA7);
Button blue_button = Button(PB0,PB10,PB11);

int red=0;
int green=0;
int blue=0;

void setup() {
  // put your setup code here, to run once:
  red_button.init();
  green_button.init();
  blue_button.init();

  pixels.begin();
}
void set_colour(){
  for(int i=0; i<PIXEL_NUMBER; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}
void loop() {
  red_button.run();
  green_button.run();
  blue_button.run();

  if (red_button.read_event()){
    red +=STEP;
  }
  if (green_button.read_event()){
    green +=STEP;
  }
  if (blue_button.read_event()){
    blue +=STEP;
  }

  if (red > MAX_VALUE){
    red=0;
  }
  if (green > MAX_VALUE){
    green=0;
  }
  if (blue > MAX_VALUE){
    blue=0;
  }
  set_colour();
  delay(10);
}

