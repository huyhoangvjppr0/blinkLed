#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>

//led1 pin 7
//led2 pin 8
//button pin 9

LED led1(LED_PIN_1, LED_ACT);
LED led2(LED_PIN_2, LED_ACT);

void btnPush();
void btnDoubleClick();
void btnHold();

OneButton button(BTN_PIN, !BTN_ACT);
int led_select = 1;
bool isBlinking = false;

void setup()
{
    led1.on();
    led2.off();
    button.attachClick(btnPush);
    button.attachDoubleClick(btnDoubleClick);
    button.attachLongPressStart(btnHold);
}

void loop()
{
    button.tick();

    if (isBlinking) {
        if (led_select == 1) {
            led1.blink(200);
            led1.loop();
        } else {
            led2.blink(200);
            led2.loop();
        }
    } else {

        led1.loop();
        led2.loop();
    }
}

void btnDoubleClick()
{
    isBlinking = false;
    if (led_select == 1)
    {
        led_select = 2;
        led1.off();
        led2.on();
    }
    else
    {
        led_select = 1;
        led2.off();
        led1.on();
    }
}

void btnPush()
{
    isBlinking = false;
    if (led_select == 1)
    {
        led1.flip();
    }
    else
    {
        led2.flip();
    }
}

void btnHold()
{
    isBlinking = true;
}