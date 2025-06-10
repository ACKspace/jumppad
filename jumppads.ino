#include <Keyboard.h>

typedef struct ButtonParameters {
  int pin;
  char key;
} ButtonParameters;

class Button {
public:
  Button() {
    resetTime();
    keyboardBegin();
  }

  void setParameters(ButtonParameters parameters) {
    _pin = parameters.pin;
    pinMode(_pin, INPUT_PULLUP);
    _key = parameters.key;
  }

  void handle() {
    boolean read = digitalRead(_pin);
    long currentTime = millis();
    if (read != _state) {
      _state = read;
      if (_state && !_time) {
        _time = currentTime;
        payload();
      }
    }
    if (_time && ((_time + _DELAY) < currentTime)) {
      resetTime();
    }
  }
private:
  static const int _DELAY = 500;
  static inline boolean _keyboardBegin = false;
  int _pin;
  char _key;
  boolean _state = true;
  long _time;

  void resetTime() {
    _time = 0;
  }

  void payload() {
    Keyboard.print(_key);
  }

  keyboardBegin() {
    if (!_keyboardBegin) {
      _keyboardBegin = true;
      Keyboard.begin();
    } 
  }
};

class ButtonList {
public:
  ButtonList(ButtonParameters parameterList[], int length) {
    _length = length;
    _buttonList = new Button[_length];
    for (int i = 0; i < _length; i++) {
      _buttonList[i].setParameters(parameterList[i]);
    }
  }

  handle() {
    for (int i = 0; i < _length; i++) {
      _buttonList[i].handle();
    }
  }
private:
  Button* _buttonList;
  int _length;
};

ButtonParameters parameterList[] = {
  { .pin =  8, .key = KEY_UP_ARROW    },
  { .pin =  7, .key = KEY_DOWN_ARROW  },
  { .pin = 13, .key = KEY_LEFT_ARROW  },
  { .pin = 12, .key = KEY_RIGHT_ARROW },
};
int length = sizeof(parameterList) / sizeof(ButtonParameters);
ButtonList buttonList(parameterList, length);

void setup() {
}

void loop() {
  buttonList.handle();
}
