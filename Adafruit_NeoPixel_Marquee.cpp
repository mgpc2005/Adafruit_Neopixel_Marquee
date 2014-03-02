#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoPixel_Marquee.h>


Adafruit_NeoPixel_Marquee::Adafruit_NeoPixel_Marquee(uint16_t numStrips, uint16_t stripLength, uint8_t startPin=6, uint8_t type=NEO_GRB + NEO_KHZ800)
{
    m_numRows = numStrips;
    m_numColumns = stripLength;
    m_marquee = new Adafruit_NeoPixel* [numStrips];
    
    for(int i = 0; i < m_numRows; i++)
    {
        m_marquee[i] = new Adafruit_NeoPixel(m_numColumns, startPin+i, type);
    }
}
 
Adafruit_NeoPixel_Marquee::~Adafruit_NeoPixel_Marquee()
{
    for(int i = 0; i < m_numRows; i++)
    {   
        delete m_marquee[i];
    }
    
    delete[] m_marquee;
}
 

void Adafruit_NeoPixel_Marquee::begin()
{
    for(int i = 0; i < m_numRows; i++)
    {
        m_marquee[i]->begin();
    }
}
 
void Adafruit_NeoPixel_Marquee::show()
{
    for(int i = 0; i < m_numRows; i++)
    {
        m_marquee[i]->show();
    }
}
        
void Adafruit_NeoPixel_Marquee::clear()
 {
    shiftHoriz(m_numColumns);
 }

void Adafruit_NeoPixel_Marquee::shiftRegionHoriz(int16_t start, int16_t end, int16_t distance)
{
    for(int i = 0; i < m_numRows; i++)
    { 
        m_marquee[i]->shiftRegion(start, end, distance);
    }
    
    show();
}
 
 
void Adafruit_NeoPixel_Marquee::shiftHoriz(int16_t distance)
{
    for(int i = 0; i < m_numRows; i++)
    { 
        m_marquee[i]->shift(distance);
    }
    
    show();
}

void Adafruit_NeoPixel_Marquee::shiftVert(int16_t distance)
{
    // Too lazy to implement ATM
}

void Adafruit_NeoPixel_Marquee::setBrightness(uint8_t brightness)
{
    for(int i = 0; i < m_numRows; i++)
    { 
        m_marquee[i]->setBrightness(brightness);
    }
}

void Adafruit_NeoPixel_Marquee::setPixelColor(uint16_t row, uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
    if (row >= getNumRows())
    {
        row = getNumRows() - 1;
    }

    m_marquee[row]->setPixelColor(n, r, g, b);
}

void Adafruit_NeoPixel_Marquee::setPixelColor(uint16_t row, uint16_t n, uint32_t c)
{
    if (row >= getNumRows())
    {
        row = getNumRows() - 1;
    }
    
    m_marquee[row]->setPixelColor(n, c);
}

void Adafruit_NeoPixel_Marquee::setColumn(uint16_t n, uint32_t* col)
{
    for(int i=0; i < m_numRows; i++)
    {
        setPixelColor(i, n, col[i]);
    }
    
    delete[] col;
	show();
}


uint32_t Adafruit_NeoPixel_Marquee::getPixelColor(uint16_t row, uint16_t n) const
{
    if (row >= getNumRows())
    {
        row = getNumRows() - 1;
    }
    
    return m_marquee[row]->getPixelColor(n);
}

uint16_t Adafruit_NeoPixel_Marquee::getNumRows() const
{
    return m_numRows;
}

uint16_t Adafruit_NeoPixel_Marquee::getNumColumns() const
{
    return m_numColumns;
}