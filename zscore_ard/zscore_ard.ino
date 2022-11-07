#include "Arduino.h"


#include <stdint.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define abs(x) ((x)<0 ? -(x) : (x))

float tarray[100];
float Zscore[100];
float arr[10];
const byte buttonPin = D10;
int buttonState = 0;  
float z_value =2.5;

void bubbleSort(float A[],int len)
{
  unsigned long newn;
  unsigned long n=len;
  float temp=0.0;
  do {
    newn=1;
    for(int p=1;p<len;p++){
      if(A[p-1]>A[p]){
        temp=A[p];           //swap places in array
        A[p]=A[p-1];
        A[p-1]=temp;
        newn=p;
      } //end if
    } //end for
    n=newn;
  } while(n>1);
}

float median(float samples[],int m) //calculate the median
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];   //Define and initialize sorted array.
  float temp=0.0;      //Temporary float for swapping elements
  /*Serial.println("Before:");
  for(int j=0;j<m;j++){
    Serial.println(samples[j]);
  }*/
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  /*Serial.println("After:");
  for(int i=0;i<m;i++){
    Serial.println(sorted[i]);
  }*/
  if (bitRead(m,0)==1) {  //If the last bit of a number is 1, it's odd. This is equivalent to "TRUE". Also use if m%2!=0.
    return sorted[m/2]; //If the number of data points is odd, return middle number.
  } else {    
    return (sorted[(m/2)-1]+sorted[m/2])/2; //If the number of data points is even, return avg of the middle two numbers.
  }
}

float ComputeMean( float tarray[], int size) 
{ 
   
   float mean = 0; 
   float sum = 0;
   int i;

   for  ( i = 0; i < size; ++i ){    
    sum += tarray[i];
   }

   mean= sum / size;

   return mean;
}

float ComputeStdev( float tarray[], int size, float mean) 
{ 
   float varianceSum = 0;
   float variance = 0;
   float std = 0;
   int i;

   
   for(i = 0; i < size; ++i){
    
    varianceSum += pow(tarray[i] - mean, 2);
    variance=varianceSum/size;
    
   }

   std = sqrt( variance);

   return std;
}





void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  

   buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
   if (buttonState == HIGH) 
      {
//        float tarray[100]={36.17867228, 41.25857035, 50.33008896, 30.24568113, 32.89445019, 64.57500322,
//                27.31829075, 62.73852858, 49.6590082,  47.51980455, 58.42933356, 44.48747856,
//                54.06967511, 55.71298618, 45.83535674, 61.50617378, 51.92764486, 47.08342822,
//                32.96375128, 51.84606592, 58.00010874, 33.7599418,  57.65848438, 43.45255654,
//                42.02639497, 56.83006731, 64.25095417, 43.94323857, 46.67417839, 67.82146517,
//                63.3843784,  47.72740571, 39.55332905, 51.91298937, 48.38966017, 62.70452529,
//                48.84654585, 45.13490766, 59.51819268, 49.12291417, 43.74767155, 55.37881341,
//                52.39159126, 47.28561864, 51.08585789, 40.24064115, 63.22594096, 61.01358024,
//                53.35526515, 51.93073186, 48.57886007, 35.90306064, 43.51780755, 50.57788992,
//                47.36408355, 57.59249395, 47.19929939, 66.70612289, 42.65116871, 57.72105892,
//                57.89649641, 24.00828696, 44.96712197, 65.90674436, 43.74848256, 42.19658853,
//                49.96834236, 40.49467907, 41.92971568, 53.38368625, 37.01564689, 60.98293844,
//                56.42600348, 30.71563978, 43.73840515, 61.78242276, 45.27416022, 55.57631911,
//                58.44676579, 69.35651205, 57.72775353, 51.31486383, 48.19477993, 48.90894856,
//                43.52792925, 64.36213769, 57.52320783, 53.66132325, 55.2122359,  68.99212821,
//                67.70415952, 70.39216365, 42.74284614, 30.35035048, 48.37222481, 40.99761113,
//                55.59415821, 48.28771882, 74.16107338, 46.27479268};

        float tarray[100]={47.71557423,48.25491143,53.68048177,31.02349256,50.48272661,49.10328994
                          ,75.29401167,48.66717104,43.36993518,52.04196305,45.03370332,43.94472027
                          ,32.39949818,33.48028815,42.68049499,27.89496476,45.43920498,47.55296531
                          ,47.29057241,28.40741802,38.65978168,46.10406854,61.44323675,48.97105371
                          ,50.26554728,43.29427577,50.40171097,40.56131858,35.42072687,50.27836795
                          ,58.79703033,57.09209945,53.37482702,49.93396492,52.16069433,60.26545778
                          ,35.50117148,47.12305445,63.81735661,56.17035384,32.68102412,50.6895587
                          ,44.07290179,53.14895857,47.76385041,47.69344775,38.34697132,53.59779434
                          ,50.29609,27.60065045,66.33759945,51.45144756,42.4716617,38.44413021
                          ,54.44087911,54.22252565,57.08741826,48.52893346,60.95973886,53.30949954
                          ,48.96186224,49.88986763,50.42340626,38.27239744,47.22732666,41.71930138
                          ,52.42992571,49.25452381,40.76071518,47.73708523,40.10772728,40.66501217
                          ,41.75224536,38.42855116,46.15393872,37.26217956,38.87548896,43.61134565
                          ,42.43057388,55.47612164,43.58805408,37.98987398,50.04628292,35.02087058
                          ,52.23399532,44.74363289,46.85639553,53.79256611,26.629648,50.90533031
                          ,51.16787813,21.59172339,47.09981105,71.5843143,35.27148818,54.28094494
                          ,50.8329343,33.00984194,39.11539505,71.24052149};


                




        float mean= ComputeMean(tarray, 100);
        float stdev=ComputeStdev(tarray, 100, mean);
        


        for ( int j = 0; j < 100; ++j ){ // output each array element's value {
          
          Zscore[j] = abs( ( tarray[j] - mean ) / stdev );
          Serial.print(Zscore[j]);
          Serial.print("\t");
        }

        for ( int i=0; i < 100; ++i) {
          if (Zscore[i]> z_value){
            if(i <=10){
              int k=0;
              for(int j=i; j<i+10; ++j) {
                arr[k]=tarray[j];
                k++;
              }
              tarray[i]= median(arr, 10);
              Serial.print("\n");
              Serial.print(tarray[i]);
              Serial.print("\t");
              Serial.print(i);
              
            }
            else
            {
              int k=0;
              for(int j=i-10; j < i; ++j) {
                arr[k]=tarray[j];
                k++;
              }
              tarray[i]= median(arr, 10);
              Serial.print("\n");
              Serial.print(tarray[i]);
              Serial.print("\t");
              Serial.print(i); 
            }
          }
        }
        
        Serial.print("\n");
        
        for ( int j = 0; j < 100; ++j ){ // output each array element's value {
          
          Serial.print(tarray[j]);
          Serial.print("\t");
        }
        
        Serial.print("\n");
        Serial.print(mean);
        Serial.print("\n");
        Serial.print(stdev);
        Serial.print("\n");

        
 
      }

}
