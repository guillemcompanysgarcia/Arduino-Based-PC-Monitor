#include <UTFTGLUE.h>              //use GLUE class and constructor
#include <string.h>
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); //all dummy args
#define UNIT 200
#

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(115200);
  Serial.setTimeout(1);  
  myGLCD.InitLCD(0);
  myGLCD.setFont(BigFont);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, 319, 479);
  
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  
  myGLCD.print("CPU TEMP: ", LEFT, 30);
  myGLCD.print("C ",300, 30);

  myGLCD.print("CPU LOAD: ", LEFT, 30+135);
  myGLCD.print("%", 300, 30+135);
  
  myGLCD.print("GPU TEMP: ", LEFT, 30+135*2);
  myGLCD.print("C", 300, 30+135*2);
  
  myGLCD.print("GPU LOAD: ", LEFT, 30+135*3);
  myGLCD.print("%", 300, 30+135*3);
  
  myGLCD.setFont(SevenSegNumFont);
}

void loop()
{
  String x= " ";

  char str[20];
  char s[2] = ",";
  char *token;
  int aux[4], sum=0;

while (!Serial.available());
  x = Serial.readString();
  x.toCharArray(str,20);
  token = strtok(str, s);
  int i=0;
  while( token != NULL ) {
  aux[i]=atoi(token);
  i++;
  sum=sum+aux;
  token = strtok(NULL, s); 
 }
 
 
  String cputemp, cpuload, gputemp, gpuload;
  String bcputemp, bcpuload, bgputemp, bgpuload;
  bcputemp=cputemp;
  cputemp=String(aux[0]);
  if( bcputemp != cputemp){
    if(aux[0]<10){
      cputemp="0"+cputemp;
    }
    if(aux[0]==100){
      cputemp="99";
    }
    myGLCD.print(cputemp, 200, 30-10);
  }
  
  bcpuload=cpuload;
  cpuload=String(aux[1]);
  if( bcpuload != cpuload){
    if(aux[1]<10){
      cpuload="0"+cpuload;
    }
    if(aux[1]==100){
      cpuload="99";
    }
    myGLCD.print(cpuload, 200, 30+135*1-10);
  }

  bgputemp=gputemp;
  gputemp=String(aux[2]);
  if( bgputemp != gputemp){
    if(aux[2]<10){
      gputemp="0"+gputemp;
    }
    if(aux[2]==100){
      gputemp="99";
    }
    myGLCD.print(gputemp, 200, 30+135*2-10);
  }
  
  bgpuload=gpuload;
  gpuload=String(aux[3]);
  if( bgpuload != gpuload){
    if(aux[3]<10){
      gpuload="0"+gpuload;
    }
    if(aux[3]==100){
      gpuload="99";
    }
    myGLCD.print(gpuload, 200, 30+135*3-10);
  }

  
  delay (1000);
}
