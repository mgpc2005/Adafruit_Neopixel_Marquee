#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoPixel_Marquee.h>

Adafruit_NeoPixel_Marquee::Adafruit_NeoPixel_Marquee(uint16_t numStrips, uint16_t stripLength, uint8_t startPin=6, uint8_t layout=SERIAL_LAYOUT, uint8_t type=NEO_GRB + NEO_KHZ800)
{
    m_numRows = numStrips;
    m_numColumns = stripLength;
    m_layout = layout;
    
    uint8_t arrayLen = getArrayLen();
    
    m_marquee = new Adafruit_NeoPixel* [arrayLen];
    
    uint16_t pixelsPerArrayItem = 0;
    
    if(m_layout == SERIAL_LAYOUT)
    {
        pixelsPerArrayItem = m_numRows * m_numColumns;
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        pixelsPerArrayItem = m_numColumns;
    }
    
    for(int i = 0; i < arrayLen; i++)
    {
        m_marquee[i] = new Adafruit_NeoPixel(pixelsPerArrayItem, startPin+i, type);
    }
}
 
Adafruit_NeoPixel_Marquee::~Adafruit_NeoPixel_Marquee()
{
    uint8_t arrayLen = getArrayLen();

    for(int i = 0; i < arrayLen; i++)
    {   
        delete m_marquee[i];
    }
    
    delete[] m_marquee;
}
 
uint8_t Adafruit_NeoPixel_Marquee::getArrayLen()
{
    uint8_t rv = 0;
    
    if(m_layout == SERIAL_LAYOUT)
    {
        rv = 1;
    }
    else if (m_layout == PARALLEL_LAYOUT)
    {
        rv = m_numRows;
    }
    
    return rv;
}
 
 
void Adafruit_NeoPixel_Marquee::begin()
{
    uint8_t arrayLen = getArrayLen();
    
    for(int i = 0; i < arrayLen; i++)
    {
        m_marquee[i]->begin();
    }
}
 
void Adafruit_NeoPixel_Marquee::show()
{
    uint8_t arrayLen = getArrayLen();
    
    for(int i = 0; i < arrayLen; i++)
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
    if(m_layout == SERIAL_LAYOUT)
    {
        for(int16_t i = 0; i < m_numRows; i++)
        { 
            int16_t ledStart = (m_numColumns*i) + start;
            int16_t ledEnd = ledStart + m_numColumns - 1 - end;
            
            m_marquee[0]->shiftRegion(ledStart, ledEnd, (i%2 == 0)? distance : (-1 * distance));
        }
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        for(int16_t i = 0; i < m_numRows; i++)
        { 
            m_marquee[i]->shiftRegion(start, end, distance);
        }
    }
    
    show();
}

void Adafruit_NeoPixel_Marquee::shiftHoriz(int16_t distance)
{
    if(m_layout == SERIAL_LAYOUT)
    {
        for(int16_t i = 0; i < m_numRows; i++)
        { 
            int16_t start = (m_numColumns*i);
            int16_t end = start + m_numColumns - 1;
            
            m_marquee[0]->shiftRegion(start, end, (i%2 == 0)? distance : (-1 * distance));
        }
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        for(int16_t i = 0; i < m_numRows; i++)
        { 
            m_marquee[i]->shift(distance);
        }
    }
    
    show();
}

void Adafruit_NeoPixel_Marquee::shiftVert(int16_t distance)
{
    // Too lazy to implement ATM
}

void Adafruit_NeoPixel_Marquee::setBrightness(uint8_t brightness)
{
    uint8_t arrayLen = getArrayLen();
    
    for(int i = 0; i < arrayLen; i++)
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

    if(m_layout == SERIAL_LAYOUT)
    {
        int16_t ledPos = 0;

        if(row%2 == 0)
        {
            ledPos = (row*m_numColumns) + n;
        }
        else
        {
            ledPos = (row*m_numColumns) + ((m_numColumns-1) - n);
        }

        m_marquee[0]->setPixelColor(ledPos, r, g, b);
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        m_marquee[row]->setPixelColor(n, r, g, b);
    }
}

void Adafruit_NeoPixel_Marquee::setPixelColor(uint16_t row, uint16_t n, uint32_t c)
{
    if (row >= getNumRows())
    {
        row = getNumRows() - 1;
    }

    if(m_layout == SERIAL_LAYOUT)
    {
        int16_t ledPos = 0;

        if(row%2 == 0)
        {
            ledPos = (row*m_numColumns) + n;
        }
        else
        {
            ledPos = (((row+1)*m_numColumns) - n - 1);
        }

        m_marquee[0]->setPixelColor(ledPos,c);
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        m_marquee[row]->setPixelColor(n, c);
    }
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
    
    if(m_layout == SERIAL_LAYOUT)
    {
        int16_t ledPos = 0;

        if(row%2 == 0)
        {
            ledPos = (row*m_numColumns) + n;
        }
        else
        {
            ledPos = (row*m_numColumns) + ((m_numColumns-1) - n);
        }
        
        m_marquee[0]->getPixelColor(ledPos);
    }
    else if(m_layout == PARALLEL_LAYOUT)
    {
        return m_marquee[row]->getPixelColor(n);
    }
}

uint16_t Adafruit_NeoPixel_Marquee::getNumRows() const
{
    return m_numRows;
}

uint16_t Adafruit_NeoPixel_Marquee::getNumColumns() const
{
    return m_numColumns;
}