
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


 uint16_t Rose[] = 
 {
 4226,4226,4226,4226,4226,4226,4226,2210,6307,47172,59392,53248,63489,63489,63555,22789,10403,18563,2210,2210,4258,4258,4226,4258,4258,4258,4258,4258,4258,4258,
 4226,4226,4226,4226,4226,4226,4226,130,35078,55297,63489,55296,57344,61440,61441,55331,51203,49155,45092,10403,2210,4258,4258,4258,4258,4226,4226,4258,4258,4258,
  4226,4226,4226,4226,4226,4226,97,26885,53315,61440,61441,51201,51200,51234,51201,51201,43011,36867,43011,59395,14467,129,4226,4226,4226,4226,4226,4226,4226,4258,
  4226,4226,4226,4226,4226,130,28966,53381,57344,63489,59393,47106,38946,53249,53248,51202,43010,28672,38913,47105,63524,22886,6339,97,97,2178,4226,4226,4226,4258,
  4226,4226,4226,4226,4226,130,51366,55297,61440,63488,53249,32770,53282,55297,51202,47172,32770,26624,30720,43009,55296,59525,51430,41352,16677,8419,4291,2210,4226,4258,
  4226,4258,4226,4226,4226,130,47173,61440,63488,59522,55460,59492,57345,47106,43009,55330,34817,22528,24576,32768,47105,61441,53248,55299,55462,49448,47334,43043,4258,4258,
  4226,4258,4258,4258,4258,4194,51300,61473,59588,63555,61506,55329,55362,49219,30721,24576,53250,40995,45123,36897,38913,61441,45057,49152,51200,51200,57345,53250,20579,2210,
  4226,4226,4258,4226,4258,16482,51331,61507,63586,63554,49185,59393,51202,53249,57345,40993,24576,51201,16384,38914,51234,45122,40993,40961,45057,53248,59392,59394,22627,162,
  4226,4226,4226,4226,18499,20481,49186,63490,63521,47105,45057,61442,45188,32769,32768,51201,43042,40994,32768,20480,38913,55362,57378,30753,38913,47105,59392,59393,32770,162,
  4226,4226,2178,53803,39174,10240,63555,63490,63522,22528,59394,59460,61507,51235,24576,22528,38913,36865,49186,32768,24576,36865,59459,57442,26689,36865,51200,49218,43334,8323,
  4226,2210,12418,14563,32900,8192,63523,63490,38946,26624,59492,51525,34882,34882,26657,32802,24576,28672,28672,38945,34816,28672,38914,45057,55394,32802,45057,47105,51201,18531,
  2178,14499,28673,18529,10369,14337,63489,61604,18465,28672,63879,41188,30818,16384,32802,30721,38945,24608,43008,30720,30720,38912,34816,32769,53248,53379,36865,49153,57345,18563,
  6306,41124,20545,24576,12385,16384,63489,59523,8224,32769,45349,8224,20513,32899,6241,32,20480,36897,20480,38912,36898,38912,36864,24576,38913,55297,51331,49152,63489,14467,
  18531,49153,16384,16384,20480,22561,59394,61538,2113,40961,28770,20480,30819,24609,16417,10272,10240,38913,4096,34817,28705,49218,32768,20480,28672,45057,57345,53314,61441,8355,
  24675,51201,14336,14336,14368,53314,49153,63522,6241,45057,43139,30720,26658,38912,26658,24674,8224,34816,4128,34882,20480,45123,38946,26658,22528,38913,49152,57410,55363,2243,
  162,51525,22561,12288,10240,57377,49153,63554,14401,45057,55395,38912,14401,40993,24576,28770,32,14336,20513,12353,26624,34849,38978,61540,30720,30720,45057,53248,45285,130,
  12386,55298,28705,8192,10240,55297,51201,63522,24609,49186,49186,32833,38978,28705,38977,24609,4128,14401,30818,32,30721,43042,32801,61474,45089,26624,43009,57344,39011,130,
  20675,55297,24576,10240,6144,53249,51201,53250,51233,32834,16449,53315,10240,39010,39009,26657,18497,28673,26787,6144,43075,30720,30753,63555,45122,22528,43010,55297,47171,130,
  26850,55296,20480,14336,6144,51201,63521,30753,63490,4096,53412,34817,34946,12288,28737,41188,35076,43333,20512,34817,26625,12385,34817,63586,45186,32802,49153,53249,16483,98,
  28833,49152,18432,16384,8192,45057,63489,32931,43009,10240,26658,32963,63555,18497,28672,45058,47138,36898,18465,41027,51461,34946,32769,63554,51428,45090,53248,59426,8323,2146,
  22722,43009,20480,18432,12288,40962,63488,61538,12386,26624,16384,38978,49187,53509,10337,10305,16546,22723,59588,61572,26657,4096,36897,63554,53476,51200,55296,55395,10370,2146,
  16578,34817,22528,20480,16384,16384,57345,63488,59523,6144,12288,26624,32768,51267,49348,47203,49154,45057,28672,6144,32,22528,41027,63554,55458,55296,53379,45057,14498,2146,
  4353,26625,22528,22528,18432,22528,28673,61441,63489,43009,4096,20512,26624,24576,40961,55297,55297,55363,63684,53541,12385,28672,47235,63554,57473,53314,39043,47105,16547,98,
  2304,16513,26624,22528,20480,22528,22528,36865,63489,63489,38913,32,40961,38912,36864,43009,49283,32769,30753,8224,12288,36898,51364,63489,55427,39076,38913,47105,16579,97,
  6369,4418,24577,22528,20480,20480,24576,18432,38913,63489,63489,51202,2080,34818,57346,63489,63522,63748,24771,16579,41188,49477,55330,63522,32996,32802,38913,49154,12451,2146,
  6338,6465,10499,26624,20480,30753,30720,20480,16384,34882,61441,63489,53249,4128,10272,40962,53250,61441,63521,63619,59620,53250,61440,63555,24835,36931,43009,45090,6274,2146,
  4258,6401,4417,14498,22528,38913,63489,28672,18432,4096,12321,53282,63488,55296,4096,32,20480,45058,55297,61440,63489,51200,53347,35044,32963,40961,47105,35044,97,4194,
  4194,6370,6401,2305,8385,26690,57345,63488,43008,16384,6144,32,30786,51298,49314,14498,2177,2048,30721,47106,45057,47268,29093,33125,38913,45057,47236,162,2145,4194,
  4226,4258,6401,6369,2304,14787,45059,57345,63488,53248,16384,8192,0,4128,28738,45188,41091,34915,16384,20480,30787,37092,39043,40962,45057,43139,12515,65,2145,4194,
  4226,4194,6338,4321,8482,12966,26689,47171,53248,63488,45056,12288,12288,10240,4096,18432,38914,45057,45057,43009,45057,43009,43009,40961,33028,161,65,4193,4194,4194

 };


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

  drawPic();
  
}

void loop() {
  // Draw a pixel at coordinates (120, 160) with color red
  //tft.drawPixel(120, 160, ST77XX_YELLOW);
    //drawthePixel(80, 100, ST77XX_YELLOW);

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



  void drawPic(void)
  {
     int kk=0;
      for(int i=50;i<80;i++)
       {
        for(int j=50;j<80;j++)
           {
           drawthePixel(i, j, Rose[kk]);  
             kk++;
      
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
