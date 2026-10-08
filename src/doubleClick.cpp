#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>
//Boot button 0
//LED pin 7
LED led(LED_PIN, LED_ACT);

void btnPush();
void btnDoubleClick();
OneButton button(BTN_PIN, !BTN_ACT);

void setup()
{
    led.off();
    button.attachClick(btnPush);
    button.attachDoubleClick(btnDoubleClick);
}

void loop()
{
    led.loop();
    button.tick();
}

void btnPush()
{
    led.flip();
}

void btnDoubleClick()
{
    led.blink(200);
}