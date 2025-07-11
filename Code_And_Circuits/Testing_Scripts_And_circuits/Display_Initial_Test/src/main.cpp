/*****************************************************************************
 * 
/ Program for writing to NHD-C12832A1Z display Series with the ST7565R Controller.
/ This code is written for the Arduino Uno R3 using Serial Interface
/
/ Newhaven Display invests time and resources providing this open source code,
/ Please support Newhaven Display by purchasing products from Newhaven Display!

* Copyright (c) 2019, Newhaven Display International
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample code is responsible for ensuring its safe and correct operation
* and for any consequences resulting from its use.
* See the GNU General Public License for more details. 
* 
* Use Vertical Orientation when converting BMP to hex code to display custom image using LCD assistant.  
* 
*****************************************************************************/


/****************************************************
*               Pinout on Arduino Uno               *
*****************************************************/

#include <Arduino.h>

#define RES 10  //Reset signal
#define CS  9   //Chip select signal
#define RS 12   //Register select signal
#define SC 13   //Serial clock signal
#define SI 11   //Serial data signal

/****************************************************
*               Hex Table for Image Pic             *
*****************************************************/

unsigned char NHD_Logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x10, 0x90, 0x50,
0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0xF0, 0x30, 0xC0, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x50,
0x50, 0x50, 0x00, 0x00, 0x10, 0xF0, 0x00, 0xE0, 0x10, 0xC0, 0x80, 0x70, 0x00, 0x00, 0x00, 0xF0,
0x40, 0x40, 0xF0, 0x00, 0x00, 0x80, 0xE0, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x30, 0xE0, 0x00, 0xE0,
0x30, 0x00, 0x00, 0xF0, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC0, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00,
0x70, 0x50, 0x50, 0x50, 0xD0, 0x00, 0x00, 0x00, 0xF0, 0x50, 0x50, 0x70, 0x00, 0x00, 0x00, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x30, 0xE0, 0x60, 0x30, 0x00,
0x00, 0x70, 0x70, 0x60, 0x20, 0x22, 0x27, 0x27, 0x22, 0x22, 0x22, 0x12, 0x11, 0x09, 0x04, 0x02,
0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char FMRadio [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xB7, 0xB7, 0xB7, 0xF7, 0xFF, 0x07,
0xEF, 0x8F, 0xEF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xB7, 0xB7, 0xB7, 0x0F,
0xFF, 0x3F, 0xBF, 0xBF, 0xBF, 0x3F, 0xFF, 0x3F, 0xBF, 0xBF, 0xBF, 0x07, 0xFF, 0xFF, 0xBF, 0x37,
0xFF, 0xFF, 0xFF, 0x3F, 0xBF, 0xBF, 0xBF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xCF, 0x9F, 0xEF, 0x07, 0x0F, 0x7F, 0xBF, 0xBF, 0xBF,
0x7F, 0xFF, 0x3F, 0x3F, 0xBF, 0xBF, 0x3F, 0x7F, 0x7F, 0xBF, 0xBF, 0xBF, 0x3F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
0xFF, 0xFE, 0xFD, 0xFD, 0xFE, 0xFC, 0xFF, 0xCE, 0x85, 0xA5, 0xB5, 0x24, 0x6F, 0xFF, 0xBD, 0x34,
0x35, 0xFF, 0xFF, 0x3E, 0x3D, 0xBD, 0x3D, 0x3E, 0x3F, 0x3F, 0x3F, 0xBF, 0xBF, 0x3F, 0x7F, 0x3F,
0xBF, 0xBF, 0xBF, 0x3F, 0xFF, 0xFF, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0x9F, 0x9F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x87, 0x97, 0x97, 0x37, 0x77, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xF8, 0xFE, 0xFC, 0xF9, 0xF9, 0xF9,
0xFC, 0xFF, 0xF8, 0xFC, 0xFF, 0xFF, 0xF8, 0xFC, 0xFC, 0xF9, 0xF9, 0xF9, 0xFC, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xBF, 0xBF, 0xBF, 0x7F, 0xFF, 0xFF,
0x3F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xBF,
0xBF, 0xBF, 0x3F, 0xFF, 0x3F, 0xBF, 0xBF, 0xBC, 0xBD, 0x3D, 0x7D, 0xFC, 0xFE, 0xFF, 0xFD, 0xFC,
0xFC, 0xFF, 0x3F, 0xFC, 0xF4, 0xF5, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,
0xFD, 0xFD, 0xFC, 0xFC, 0xFF, 0xFF, 0xFD, 0xFC, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFD,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD, 0xFD, 0xFD, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xDF, 0xDF, 0xDF, 0xC0, 0xDF, 0xDF, 0xDF, 0xE0, 0x93, 0xD9, 0x9C, 0xDE, 0xE0, 0xFF, 0xDF,
0xDF, 0xDF, 0xC0, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xCF, 0xCF, 0xFF, 0xFF, 0xFF, 0xF8, 0xD3, 0xD3,
0xD3, 0xD3, 0xE0, 0xFF, 0xFC, 0xD3, 0xD3, 0xD3, 0xD3, 0xE0, 0xFE, 0xC0, 0xC0, 0xFC, 0xC0, 0xFC,
0xFC, 0xC1, 0xC0, 0xFC, 0xFC, 0xFC, 0xFC, 0xC1, 0xC3, 0xDD, 0xCD, 0xC5, 0xD1, 0xDD, 0xDC, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

/****************************************************
*                 Function Commands                  *
*****************************************************/

void data_write(unsigned char d) //Data Output Serial Interface
{
	unsigned int n;
	digitalWrite(CS, LOW); 
	digitalWrite(RS, HIGH); 
	for(n=0;n<8;n++){
		if((d&0x80)==0x80)
		digitalWrite(SI, HIGH);
		else
		digitalWrite(SI, LOW);
		while(0);
		d=(d<<1);
		digitalWrite(SC, LOW);
		while(0);
		digitalWrite(SC, HIGH);
		while(0);
		digitalWrite(SC, LOW);
		}
	digitalWrite(CS, HIGH);
}


void comm_write(unsigned char d) //Command Output Serial Interface
{
	unsigned int n;
	digitalWrite(CS, LOW);
	digitalWrite(RS, LOW);
	for(n=0;n<8;n++){
		if((d&0x80)==0x80)
		digitalWrite(SI, HIGH);
		else
		digitalWrite(SI, LOW);
		while(0);
		d=(d<<1);
		digitalWrite(SC, LOW);
		while(0);
		digitalWrite(SC, HIGH);
		while(0);
		digitalWrite(SC, LOW);
		}
	digitalWrite(CS, HIGH);
}


void DispPic(unsigned char *lcd_string)
{
  unsigned int i,j;
  unsigned char page = 0xB0;
  comm_write(0xAE);          //Display OFF
  comm_write(0x40);         //Display start address + 0x40
  for(i=0;i<4;i++){       //32pixel display / 8 pixels per page = 4 pages
    comm_write(page);       //send page address
    comm_write(0x10);       //column address upper 4 bits + 0x10
    comm_write(0x00);       //column address lower 4 bits + 0x00
    for(j=0;j<128;j++){     //128 columns wide
      data_write(*lcd_string);    //send picture data
      lcd_string++; 
      }
      page++;         //after 128 columns, go to next page
      }
  comm_write(0xAF);   
  
}

void ClearLCD(unsigned char *lcd_string)
{
    unsigned int i,j;
  unsigned char page = 0xB0;
  comm_write(0xAE);          //Display OFF
  comm_write(0x40);         //Display start address + 0x40
  for(i=0;i<4;i++){       //32pixel display / 8 pixels per page = 4 pages
    comm_write(page);       //send page address
    comm_write(0x10);       //column address upper 4 bits + 0x10
    comm_write(0x00);       //column address lower 4 bits + 0x00
    for(j=0;j<128;j++){     //128 columns wide
      data_write(0x00);    //send picture data
      lcd_string++; 
      }
      page++;         //after 128 columns, go to next page
      }
  comm_write(0xAF);   
}

/****************************************************
*           Initialization For controller           *
*****************************************************/

void init_LCD()  {
comm_write(0xA0);    // ADC select 
comm_write(0xAE);   // Display OFF
comm_write(0xC8);   // COM direction scan 
comm_write(0xA2);   // LCD bias set
comm_write(0x2F);   // Power Control set
comm_write(0x21);   // Resistor Ratio Set 
comm_write(0x81);   // Electronic Volume Command (set contrast) Double Btye: 1 of 2
comm_write(0x20);   // Electronic Volume value (contrast value) Double Byte: 2 of 2
comm_write(0xAF);   // Display ON
}

/*****************************************************
*           Setup Function, to run once              *
*****************************************************/

void setup() {
  //DDRD = 0xFF;          // configure PORTD as output
  pinMode(RES, OUTPUT); // configure RES as output
  pinMode(CS, OUTPUT);  // configure CS as output
  pinMode(RS, OUTPUT);  // configure RS as output
  pinMode(SC, OUTPUT);  // configure SC as output
  pinMode(SI, OUTPUT);  // configure SI as output
  digitalWrite(RES, LOW);            
  delay(100);                      
  digitalWrite(RES, HIGH);           
  delay(100); 
  init_LCD();      
}

/*****************************************************
*           Loop Function, to run repeatedly         *
*****************************************************/

void loop() {
delay(10);   
	while(1)
	{
    DispPic(NHD_Logo);
    delay(2000);
    ClearLCD(NHD_Logo);
    delay(500);

    DispPic(FMRadio);
    delay(2000);
    ClearLCD(FMRadio);
    delay(500);
		}
}