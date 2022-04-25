#include <Adafruit_GFX.h>    //核心图形库
#include <Adafruit_ST7735.h> //为ST7735硬件专用库
#include <Adafruit_ST7789.h> //为ST7789硬件专用库
#include <SPI.h>

#define TFT_CS        7 // Hallowing显示控制引脚：芯片选择
#define TFT_RST       10 //显示复位
#define TFT_DC        6 //显示数据/命令选择
#define TFT_BACKLIGHT  7 //显示屏背光销
#define TFT_MOSI  3 //MOSI
#define TFT_SCLK  2 //SCLK

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, 3, 2, TFT_RST);
float p = 3.1415926;
void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.initR(INITR_MINI160x80); //初始化ST7735S芯片，黑色标签
  Serial.println(F("Initialized"));
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  delay(500);
  
  //大块文字
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("123456", ST77XX_WHITE);  //其中WHITE，定义字体为白色
  delay(1000);
  // tft打印功能！
  tftPrintTest();
  delay(4000);
  //一个像素

  tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN); //就只是在，屏幕正中间画了一个点
  delay(500);
  //线条绘制测试
  testlines(ST77XX_YELLOW);
  delay(500);
  //优化的线条
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);
  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);

  Serial.println("完成");
  delay(1000);
}

void loop() {
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < tft.height(); y += radius * 2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0 ; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);  //设置字体包裹，是否打开
  tft.fillScreen(ST77XX_BLACK);  //填充背景颜色（必须填充，否则之前的图像，将不会消失）
  tft.setCursor(0, 30); //设置游标初始位置,x轴为0，Y轴为30
  tft.setTextColor(ST77XX_RED);  //设置字体为红色
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);//设置光标的起始位置
  tft.fillScreen(ST77XX_BLACK);//填充屏幕，为黑色（必须填充，否则之前的图像，将不会消失）
  tft.setTextColor(ST77XX_WHITE);//设置字体颜色，为白色
  tft.setTextSize(0);  //设置字体大小为，0
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6); //显示，p这个变量，第6位以后，不再显示
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(10, 10, 60, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(27, 20, 27, 60, 60, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(10, 90, 60, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(20, 100, 15, 40, 5, ST77XX_GREEN);
  tft.fillRoundRect(45, 100, 15, 40, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(27, 20, 27, 60, 60, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(20, 100, 15, 40, 5, ST77XX_RED);
  tft.fillRoundRect(45, 100, 15, 40, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(27, 20, 27, 60, 60, 40, ST77XX_GREEN);
}
