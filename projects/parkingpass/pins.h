// esp8266 https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

#define GPIO16 16  // 	no interrupt	no PWM or I2C support	HIGH at boot used to wake up from deep sleep
#define GPIO5  5   //OK	OK	often used as SCL (I2C)
#define GPIO4  4   //OK	OK	often used as SDA (I2C)
#define GPIO0  0   //pulled up	OK	connected to FLASH button, boot fails if pulled LOW
#define GPIO2  2   //pulled up	OK	HIGH at boot connected to on-board LED, boot fails if pulled LOW
#define GPIO14 14  //OK	OK	SPI (SCLK)
#define GPIO12 12  //OK	OK	SPI (MISO)
#define GPIO13 13  //OK	OK	SPI (MOSI)
#define GPIO15 15  //pulled to GND	OK	SPI (CS) Boot fails if pulled HIGH
#define D0 GPIO16  // 	no interrupt	no PWM or I2C support	HIGH at boot used to wake up from deep sleep
#define D1 GPIO5   //OK	OK	often used as SCL (I2C)
#define D2 GPIO4   //OK	OK	often used as SDA (I2C)
#define D3 GPIO0   //pulled up	OK	connected to FLASH button, boot fails if pulled LOW
#define D4 GPIO2   //pulled up	OK	HIGH at boot connected to on-board LED, boot fails if pulled LOW
#define D5 GPIO14  //OK	OK	SPI (SCLK)
#define D6 GPIO12  //OK	OK	SPI (MISO)
#define D7 GPIO13  //OK	OK	SPI (MOSI)
#define D8 GPIO15  //pulled to GND	OK	SPI (CS) Boot fails if pulled HIGH

/*
// RX	GPIO3 //OK	RX pin	HIGH at boot
// TX	GPIO1 //TX pin	OK	HIGH at boot debug output at boot, boot fails if pulled LOW
// A0	ADC0
*/
