#include "knx/platform.h"
#ifdef SOFT_SERIAL
#include <SoftwareSerialE1.h>
#endif

#include "Arduino.h"

#ifndef KNX_DEBUG_SERIAL
#define KNX_DEBUG_SERIAL Serial
#endif

class ArduinoPlatform : public Platform
{
  public:
    ArduinoPlatform();
#ifdef SOFT_SERIAL
    ArduinoPlatform(SoftwareSerialE1* knxSerial);
#else
    ArduinoPlatform(HardwareSerial* knxSerial);
#endif
    
    // basic stuff
    void fatalError();

    //uart
#ifdef SOFT_SERIAL
    virtual void knxUart( SoftwareSerialE1* serial);
    virtual SoftwareSerialE1* knxUart();
#else
    virtual void knxUart( HardwareSerial* serial);
    virtual HardwareSerial* knxUart();
#endif
    virtual void setupUart();
    virtual void closeUart();
    virtual int uartAvailable();
    virtual size_t writeUart(const uint8_t data);
    virtual size_t writeUart(const uint8_t* buffer, size_t size);
    virtual int readUart();
    virtual size_t readBytesUart(uint8_t* buffer, size_t length);

    //spi
#ifndef KNX_NO_SPI
    void setupSpi() override;
    void closeSpi() override;
    int readWriteSpi (uint8_t *data, size_t len) override;
#endif
#ifndef KNX_NO_PRINT
    static Stream* SerialDebug;
#endif

  protected:
#ifdef SOFT_SERIAL
    SoftwareSerialE1* _knxSerial;
#else
    HardwareSerial* _knxSerial;
#endif
};
