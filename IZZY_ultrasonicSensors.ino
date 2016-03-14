
#include <Ultrasonic.h>
#include <Wire.h>

byte warning;
int trigPinFrontLeft =27;
int echoPinFrontLeft = 26;
int trigPinFrontMid = 30;
int echoPinFrontMid = 30;
int trigPinFrontRight = 35;
int echoPinFrontRight = 34;
int trigPinDownLeft = 50;
int echoPinDownLeft = 51; 
int trigPinDownRight = 46;
int echoPinDownRight = 47;  
float distanceAvg;



Ultrasonic ultrasonicFrontLeft(trigPinFrontLeft,echoPinFrontLeft);
Ultrasonic ultrasonicFrontRight(trigPinFrontRight,echoPinFrontRight);
Ultrasonic ultrasonicFrontMid(trigPinFrontMid,echoPinFrontMid);
Ultrasonic ultrasonicDownLeft(trigPinDownLeft,echoPinDownLeft);
Ultrasonic ultrasonicDownRight(trigPinDownRight,echoPinDownRight);


          
void setup()
{

        float distanceDownLeft;
        float distanceDownRight;
        
        long microsecDownLeft = ultrasonicDownLeft.timing();
        long microsecDownRight = ultrasonicDownRight.timing();
        
        Serial.begin(9600);
	Wire.begin(3);
        Wire.onRequest(getWarning);
          
        distanceAvg = ultrasonicDownLeft.CalcDistance(microsecDownLeft,Ultrasonic::IN) + ultrasonicDownLeft.CalcDistance(microsecDownLeft,Ultrasonic::IN)+ ultrasonicDownLeft.CalcDistance(microsecDownLeft,Ultrasonic::IN)+ ultrasonicDownRight.CalcDistance(microsecDownRight,Ultrasonic::IN)+ ultrasonicDownRight.CalcDistance(microsecDownRight,Ultrasonic::IN);
        distanceAvg = distanceAvg / 5;
        
}
void loop()
{
  delay(1000);
        
	float distanceFrontLeft;
        float distanceFrontMid;
        float distanceFrontRight;
        float distanceDownLeft;
        float distanceDownRight;
        float distanceDownAvg;
   
        warning = 0;
        
	long microsecFrontLeft = ultrasonicFrontLeft.timing();
        long microsecFrontMid = ultrasonicFrontMid.timing();
        long microsecFrontRight = ultrasonicFrontRight.timing();
        long microsecDownLeft = ultrasonicDownLeft.timing();
        long microsecDownRight = ultrasonicDownRight.timing();

	distanceFrontLeft = ultrasonicFrontLeft.CalcDistance(microsecFrontLeft,Ultrasonic::IN);
	distanceFrontMid = ultrasonicFrontMid.CalcDistance(microsecFrontMid,Ultrasonic::IN);
        distanceFrontRight = ultrasonicFrontRight.CalcDistance(microsecFrontRight,Ultrasonic::IN);
	distanceDownLeft = ultrasonicDownLeft.CalcDistance(microsecDownLeft,Ultrasonic::IN);
        distanceDownRight = ultrasonicDownRight.CalcDistance(microsecDownRight,Ultrasonic::IN);

        
         

        if (distanceDownLeft > (distanceAvg + 6) || distanceDownRight > (distanceAvg + 6))
        {
        
          warning = warning << 1 | 1;
          warning = warning << 1 | 1;
        }else if (distanceFrontLeft < 35 || distanceFrontRight < 35 || distanceFrontMid < 35)
        {
        
                    
          warning = warning << 1 | 1;
          warning = warning << 1 | 0;
        }
        //Serial.println(warning,BIN);
}

void getWarning(){
  Wire.write(warning);
}
