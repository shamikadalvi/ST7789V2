
#include <SPI.h>


#define ST_CMD_DELAY 0x80 // special signifier for command lists

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00



#define TFT_WIDTH  240
#define TFT_HEIGHT 320

 #define SCK        13
 #define MOSI        11
 #define MISO        12
 

  #define SS        10
  #define RESET        9 // Or set to -1 and connect to Arduino RESET pin
  #define DC         8


uint16_t _width=240;
uint16_t _height=320;

uint16_t  _xstart=0;
uint16_t  _ystart=0;

uint8_t _colstart = 0;   ///< Some displays need this changed to offset
uint8_t  _rowstart = 0;
uint8_t _rowstart2=0;
uint8_t _colstart2=0;

uint16_t rotation=0;



void setup() {
	
	 pinMode(SS,OUTPUT);
     pinMode(MOSI,OUTPUT);
     pinMode(MISO,INPUT);
     pinMode(SCK,OUTPUT);
	 pinMode(DC,OUTPUT);
     pinMode(RESET,OUTPUT);
	
	
	

  
  displayInit();
 
 
  fillScreen();
  
}

void loop() {
  // Draw a pixel at coordinates (120, 160) with color red
  //tft.drawPixel(120, 160, ST77XX_YELLOW);
    drawthePixel(80, 100, ST77XX_YELLOW);

  // Wait for a while
  delay(1000);
}







void drawthePixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= _height) || (y < 0) || (y >= _height)) {
    return;  // Skip if coordinates are outside the display area
  }

  writecommand(ST77XX_CASET);         // Set column address
  writedata(x >> 8);                  // Start column high byte
  writedata(x & 0xFF);                // Start column low byte
  writedata((x + 1) >> 8);            // End column high byte
  writedata((x + 1) & 0xFF);          // End column low byte

  writecommand(ST77XX_RASET);         // Set row address
  writedata(y >> 8);                  // Start row high byte
  writedata(y & 0xFF);                // Start row low byte
  
  writecommand(ST77XX_RAMWR);         // Memory write command
  
  // Send pixel data
  digitalWrite(DC, HIGH);        // Set DC pin high to send data
  digitalWrite(SS, LOW);         // Set CS pin low to select the display
  spiwrite(color >> 8);
  spiwrite(color);           // Send 16-bit color data
  digitalWrite(SS, HIGH);        // Set CS pin high to deselect the display
}




void spiwrite(uint8_t c) 
{

 
      SPI.transfer(c);

}


void fillScreen(void)
  {
  
      for(int i=0;i<240;i++)
       {
        for(int j=0;j<320;j++)
           {
           drawthePixel(i, j, ST77XX_BLACK);  

      
           }

    
         }
  
  }



  void writecommand(uint8_t c) {

     digitalWrite(DC,LOW);// DC_LOW();
     digitalWrite(SS, LOW);               // CS_LOW();
     SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0)); // SPI Settings 100 kHz, MSB first, Mode 0              //SPI_BEGIN_TRANSACTION();

     SPI.transfer(c);

   digitalWrite(SS, HIGH);//CS_HIGH();
    SPI.endTransaction();
}

void writedata(uint8_t c) {
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0)); // SPI Settings 100 kHz, MSB first, Mode 0              //SPI_BEGIN_TRANSACTION();
 digitalWrite(DC,HIGH);// DC_HIGH();
  digitalWrite(SS, LOW);//CS_LOW();
    
  SPI.transfer(c);

    digitalWrite(SS, HIGH); //CS_HIGH();
   SPI.endTransaction();
}







void displayInit(void)
{

  digitalWrite(RESET, HIGH); // Set RST pin high
  delay(5);
  digitalWrite(RESET, LOW);  // Set RST pin low
  delay(20);
  digitalWrite(RESET, HIGH); // Set RST pin high
  delay(150);
    _rowstart = _rowstart2 = (int)((320 - _height) / 2);
    _colstart = _colstart2 = (int)((240 - _width) / 2);

  
writecommand(ST77XX_SWRESET); // 1: Software reset
delay(150);   // 150 ms delay

writecommand(ST77XX_SLPOUT); // 2: Out of sleep mode
delay(500);   // 500 ms delay  

writecommand(ST77XX_COLMOD); // 3: Set color mode
delay(500);   // 500 ms delay  
writedata(0x55);
delay(10);   // 10 ms delay  


writecommand(ST77XX_MADCTL); // 4: Memory access ctrl
writedata(0x08);


writecommand(ST77XX_CASET); // // 5: Column addr set
writedata(0x00);
writedata(0);
writedata(0);
writedata(240);


writecommand(ST77XX_RASET); // 6: Row addr set
writedata(0x00);
writedata(0);
writedata((320) >> 8);
writedata((320) & 0xFF);

 



writecommand(ST77XX_INVON); // 7: Inversion ON
delay(10);   // 10 ms delay 

writecommand(ST77XX_NORON); // 8: Normal display on
delay(10);   // 10 ms delay 

writecommand(ST77XX_DISPON); // 9: Main screen turn on
  delay(500);   // 10 ms delay 
  
  

writecommand(ST77XX_MADCTL); 
  
writedata(ST77XX_MADCTL_RGB);

 _xstart = _colstart2;
 _ystart = _rowstart2;

delay(500); 
}



void displayRotation(uint8_t m) {

  writecommand(ST77XX_MADCTL);
  rotation = m % 4; // can't be higher than 3
  switch (rotation) {
  case 0:
     writedata(ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB);

     _xstart = _colstart;
     _ystart = 80;//_rowstart;
     break;
  case 1:
     writedata(ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB);

     _ystart = _colstart;
     _xstart = 80;//_rowstart;
     break;
  case 2:
     writedata(ST77XX_MADCTL_RGB);
 
     _xstart = _colstart;
     _ystart = _rowstart;
     break;

   case 3:
     writedata(ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB);

     _ystart = _colstart;
     _xstart = _rowstart;
     break;
  }
}
