#ifndef ADAFRUIT_NEOPIXEL_MARQUEE_H
#define ADAFRUIT_NEOPIXEL_MARQUEE_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class Adafruit_NeoPixel;

class Adafruit_NeoPixel_Marquee {

    public:
        Adafruit_NeoPixel_Marquee(uint16_t numStrips, uint16_t stripLength, uint8_t startPin, uint8_t type);
        ~Adafruit_NeoPixel_Marquee();
        
        void begin();
        void show();
        void clear();
        void shiftHoriz(int16_t distance);
        void shiftVert(int16_t distance);
        void setBrightness(uint8_t brightness);
        
        void setPixelColor(uint16_t row, uint16_t n, uint8_t r, uint8_t g, uint8_t b);
        void setPixelColor(uint16_t row, uint16_t n, uint32_t c);
        uint32_t getPixelColor(uint16_t row, uint16_t n) const;

        uint16_t getNumRows() const;
        uint16_t getNumColumns() const;

    private:
        Adafruit_NeoPixel_Marquee( const Adafruit_NeoPixel_Marquee& val);
        const Adafruit_NeoPixel_Marquee& operator=(const Adafruit_NeoPixel_Marquee& val);
        
        
        Adafruit_NeoPixel ** m_marquee;
        uint16_t m_numRows;
        uint16_t m_numColumns;
        uint8_t m_startPin;
        uint8_t m_type;
};

#endif