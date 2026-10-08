#include <Arduino.h>
#include "LED.h"

LED led(LED_PIN, LED_ACT);

void setup()
{
    led.off();
}

void loop()
{
    led.blink(500);
    led.loop();
}