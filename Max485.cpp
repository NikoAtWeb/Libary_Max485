#include "Arduino.h"
#include "Max485.h"

Max485::Max485(SoftwareSerial * SerialConnection)
{
  // init SerialConnection
  _serial = SerialConnection;

// initialize values
  _income = "";
  _IncomeDevID = 0;
  _IncomeState = 0;
  _IncomeValue1 = 9999;
  _IncomeValue2 = 9999;
  _IncomeValue3 = 9999;
  _IncomeValue4 = 9999;
  _strComplete = false;
}

void Max485::setup(int enablePin, int setDevID)
{
  _enablePin  = enablePin;
  _setDevID   = setDevID;

  // set the Max485-Enable Pin
  pinMode(_enablePin, OUTPUT);

  digitalWrite(_enablePin, LOW);

}

void Max485::begin(uint32_t baud)
{
  _serial->begin(baud);
}

void Max485::receive()
{
  while (_serial->available()>0)
  {
    char inChar = (char)_serial->read(); // read character from BUS
    _income += inChar;                     // add it to the inputString:
    if (inChar == '\n')                   // if the incoming character is a newline, set a flag
    {
      _strComplete = true;
    } // end if
  } //end while

 // Check, if there ist an String Complete
  if (_strComplete == true)
  {
    char copyin[100];
    char delimiter[] = ";";
    char *ptr;

    _income.toCharArray(copyin, 100);
    //Serial.print("Schreibe _income");
    //Serial.println(_income);
    ptr = strtok(copyin, delimiter);
    int i =0;

    while(ptr != NULL) {
      i++;
      switch(i)
      {
        case 1: _IncomeDevID = String(ptr).toInt();
        break;
        case 2: _IncomeState = String(ptr).toInt();
        break;
        case 3: _IncomeALV    = String(ptr).toInt();
        break;
        case 4: _IncomeValue1 = String(ptr).toInt();
        break;
        case 5: _IncomeValue2 = String(ptr).toInt();
        break;
        case 6: _IncomeValue3 = String(ptr).toInt();
        break;
        case 7: _IncomeValue4 = String(ptr).toInt();
      }
      ptr = strtok(NULL, delimiter);
    } // end while
    _strComplete = false;
    _income = "";// clear _income
  } //endif
} // end receive

int Max485::getDevID()
{
  receive();
  return _IncomeDevID;
} // end getDevID

int Max485::getState()
{
  receive();
  return _IncomeState;
} // end getState

int Max485::getALV()
{
  receive();
  return _IncomeALV;
} // end getALV

int Max485::getValue(int _IncomeValue)
{
  receive();
  switch(_IncomeValue)
  {
    case 1: return _IncomeValue1;
    break;
    case 2: return _IncomeValue2;
    break;
    case 3: return _IncomeValue3;
    break;
    case 4: return _IncomeValue4;
    break;
  } //end switch
} // end getValue

void Max485::sendOUT(int _ActState, int _sendALV, int _sendValue1, int _sendValue2, int _sendValue3, int _sendValue4)
{
  digitalWrite(_enablePin, HIGH); // aktiviere den Sender-Pin
//delay(1000);
  String _sendOut =  String(_setDevID) + ";" +
                    String(_ActState) + ";" +
                    String(_sendALV) + ";" +
                    String(_sendValue1) + ";" +
                    String(_sendValue2) + ";" +
                    String(_sendValue3) + ";" +
                    String(_sendValue4) + ";";
  _serial->flush(); // wartet, bis alles gesendet ist
  _serial->println(_sendOut);
  digitalWrite(_enablePin, LOW); // deaktiviere den Sender-Pin
} // end getValue
