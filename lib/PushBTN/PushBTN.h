/***
 * Buttons library for Arduino
 * Author: Nguyen Anh Tuan
 * Version: 2.1 (Mar. 2023) 
 * 
 ***/

#pragma once

#include <Arduino.h>

class PushBTN {
public:
    PushBTN(const byte pin, const bool push, void (&pushCallback)(), 
                        const int debounceTime=5);
                        
    PushBTN(const byte pin, const bool push, void (&pushCallback)(), void (&holdCallback)(), 
                        const int holdTime=2000, 
                        const int debounceTime=5);
    void loop();

private:
    const byte _pin;
    const bool _active; // LOW or HIGH
    std::function<void()> _pushCallback{ [](){} };
    std::function<void()> _holdCallback{ [](){} };

    unsigned long holdTimer = 0;
    const unsigned int _holdTime = 2000; // default 2000ms = 2s.
    const unsigned int _debounceTime = 5;

    enum States {
        RELEASE      = 0,
        PUSH_WAIT    = 1,
        HOLD_WAIT    = 2,
        PUSH         = 3,
        HOLD         = 4,
        RELEASE_WAIT = 5,
    } state = RELEASE;
};


/***** Implementation: *****/

PushBTN::PushBTN(const byte pin, const bool active, void (&pushCallback)(), 
                const int debounceTime)

    : _pin(pin), _active(active), 
      _pushCallback(pushCallback),
      _debounceTime(debounceTime)
{
    if (active == LOW)
        pinMode(_pin, INPUT_PULLUP);
    else
        pinMode(_pin, INPUT);
}

PushBTN::PushBTN(const byte pin, const bool active, void (&pushCallback)(), 
                void (&holdCallback)(), const int holdTime, 
                const int debounceTime)
                
    : _pin(pin), _active(active), 
      _pushCallback(pushCallback), 
      _holdCallback(holdCallback), 
      _holdTime(holdTime),
      _debounceTime(debounceTime) 
{
    if (active == LOW)
        pinMode(_pin, INPUT_PULLUP);
    else
        pinMode(_pin, INPUT);
}

void PushBTN::loop() {
    switch (state)
    {
    case RELEASE:
        if (digitalRead(_pin) == _active) {
            holdTimer = millis();
            state = PUSH_WAIT;
        }
        break;
    
    case PUSH_WAIT:
        if ((millis() - holdTimer) > _debounceTime) {
          if (digitalRead(_pin) == _active) { // still hold after 5ms
            state = HOLD_WAIT;
          }else {                           // mechanical/electrical noises
            state = RELEASE;
          }
        }
        break;

    case HOLD_WAIT:
        if (digitalRead(_pin) != _active) {   // just push (>5ms and <2000ms)
          state = PUSH;
        }else if ((millis() - holdTimer) > _holdTime) {
          state = HOLD;
        }
        break;

    case PUSH:
        _pushCallback();
        state = RELEASE_WAIT;
        break;

    case HOLD:
        _holdCallback();
        state = RELEASE_WAIT;
        break;

    case RELEASE_WAIT:
        if (digitalRead(_pin) != _active) {
          state = RELEASE;
        }
        break;
    }
}