// eigene Libary für Max485 BUS

#ifndef Max485_h
#define Max485_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class Max485 {
  public:

      Max485(SoftwareSerial * SerialConnection); // int RxPin, int TxPin, int enablePin, int setDevID);
      void begin(uint32_t baud);
      void setup(int enablePin, int setDevID);
      void receive();
      int getDevID();
      int getState();
      int getALV();
      int getValue(int _IncomeValue);
      void sendOUT(int _ActState, int _sendALV, int _sendValue1, int _sendValue2, int _sendValue3, int _sendValue4);

  private:

    int _enablePin, _setDevID, _IncomeValue, _IncomeALV;
    int _IncomeDevID, _IncomeState;
    int _ActState, _sendALV, _sendValue1, _sendValue2, _sendValue3, _sendValue4;
    int _IncomeValue1, _IncomeValue2, _IncomeValue3, _IncomeValue4;
    bool _strComplete;
    String _income;

    SoftwareSerial * _serial;

};

#endif
