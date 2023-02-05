#include <UTFTGLUE.h>
#include <string.h>

#define UPDATE_INTERVAL 1000
#define SLEEP_INTERVAL 10000
#define UPPER_TEMP_TH 80
#define LOWER_TEMP_TH 50


#define GLCD_RS  0
#define GLCD_WR  A2
#define GLCD_CS  A1
#define GLCD_RST A3
#define GLCD_D0  A4
#define GLCD_D1  A0

UTFTGLUE myGLCD(GLCD_RS, GLCD_WR, GLCD_CS, GLCD_RST, GLCD_D0, GLCD_D1);

int maxCpuTemp = 0;
int maxGpuTemp = 0;

unsigned long lastDataReceived = millis();

bool display = false;


void updateDisplay(){
  myGLCD.InitLCD(0);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, 319, 479);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);


  char *texts[] = {"CPU TEMP: ", "C", "CPU LOAD: ", "%", "GPU TEMP: ", "C", "GPU LOAD: ", "%"};
  int x = LEFT, y = 30;

  for (int i = 0; i < 8; i += 2) {
    myGLCD.print(texts[i], x, y);
    myGLCD.print(texts[i + 1], 300, y);
    y += 135;
  }

  myGLCD.setFont(SevenSegNumFont);

}
void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  Serial.setTimeout(1);
  
  updateDisplay();
}

void loop() {
  String x = "";
  char str[20];
  char s[2] = ",";
  char *token;
  int aux[4];

  while (!Serial.available()) {
    unsigned long currentTime = millis();
    if (currentTime - lastDataReceived >= SLEEP_INTERVAL) {
      myGLCD.clrScr();
      display = true;

      maxCpuTemp = 0;
      maxGpuTemp = 0;

      return;
    }
  }
  if (display) {
    updateDisplay();
    display = false;
  }
  x = Serial.readString();
  x.toCharArray(str, 20);
  token = strtok(str, s);
  int i = 0;
  while (token != NULL) {
    aux[i] = atoi(token);
    i++;
    token = strtok(NULL, s);
  }

  for (int j = 0; j < 4; j++) {
    int value = aux[j];
    if (j == 0) {
      if (value > maxCpuTemp) {
        maxCpuTemp = value;
        myGLCD.setFont(BigFont);
        myGLCD.setColor(0, 0, 0); // Black
        myGLCD.print("Max CPU Temp: ", LEFT, 30 +(2 * j + 1)* 67);
        myGLCD.print(String(maxCpuTemp), 200 + 16, 30 +(2 * j + 1)* 67);
        myGLCD.setFont(SevenSegNumFont);

      }
      int color = (value >= LOWER_TEMP_TH) ? 255 : (value <= LOWER_TEMP_TH) ? 0 : map(value, LOWER_TEMP_TH, LOWER_TEMP_TH, 0, 255);
      myGLCD.setColor(color, 255 - color, 0);
    } else if (j == 2) {
      if (value > maxGpuTemp) {
        maxGpuTemp = value;
        myGLCD.setFont(BigFont);
        myGLCD.setColor(0, 0, 0); // Black
        myGLCD.print("Max GPU Temp: ", LEFT, 30 +(2 * j + 1)* 67);
        myGLCD.print(String(maxGpuTemp), 200 + 16, 30 +(2 * j + 1)* 67);
        myGLCD.setFont(SevenSegNumFont);
      }
      int color = (value >= LOWER_TEMP_TH) ? 255 : (value <= LOWER_TEMP_TH) ? 0 : map(value, LOWER_TEMP_TH, LOWER_TEMP_TH, 0, 255);
      myGLCD.setColor(color, 255 - color, 0);
    } else {
      myGLCD.setColor(0,0,0); 
    }
    String text = value == 100 ? "99" : value < 10 ? "0" + String(value) : String(value).substring(0, 2);
    myGLCD.print(text, 200, 30 + j * 135 - 10);
}
  lastDataReceived = millis();
  delay(UPDATE_INTERVAL);
}
