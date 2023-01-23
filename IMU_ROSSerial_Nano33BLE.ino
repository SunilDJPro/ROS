//This code gets the IMU 9 Axis data from the on-board IMU of Arduino Nano 33 BLE and proces them into single line String format within the MCU, 
//Then sends the String type data to the ROS core system via ROSSerial by creating a topic.
//The data can be accessed via echoing the topic using rostopic.
//!Needs a processing node in the ROS Core to convert the single line string into parameter or int/float type data to further work with Rviz or other nodes.!

#include <Arduino_LSM9DS1.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>





int led1 = LEDR;
int led2 = LEDG;
int led3 = LEDB;

ros::NodeHandle nh;

std_msgs::String imu_msg;

ros::Publisher imu_publisher("imu_data", &imu_msg);

void setup() {
  // put your setup code here, to run once:

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  nh.initNode();
  nh.advertise(imu_publisher);
  
  

  if (!IMU.begin()) {
    //IMU Failed to init!
    while (1);
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:
  float ax, ay, az, gx, gy, gz, mx, my, mz;
  String AX, AY, AZ, GX, GY, GZ, MX, MY, MZ;
  
  if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(ax, ay, az);
      AX = String(ax);
      AY = String(ay);
      AZ = String(az);
      digitalWrite(led1, HIGH);
      delay(100);
      
    
  }
  digitalWrite(led1, LOW);

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
    GX = String(gx);
    GY = String(gy);
    GZ = String(gz);
    digitalWrite(led2, HIGH);
    delay(100);
    

    
  }
  digitalWrite(led2, LOW);

  if (IMU. magneticFieldAvailable()){

      IMU.readMagneticField(mx, my, mz);
      MX = String(mx);
      MY = String(my);
      MZ = String(mz);
      digitalWrite(led3, HIGH);
      delay(100);
      
      
      
     
  }
  digitalWrite(led3, LOW);

  String IMU_data = "A"+AX+"B"+AY+"C"+AZ+"D"+GX+"E"+GY+"F"+GZ+"G"+MX+"H"+MY+"I"+MZ+"J" ;
  int length = IMU_data.indexOf("J")+2;
  char data_final[length+1];
  IMU_data.toCharArray(data_final, length+1);
  
  imu_msg.data = data_final;
  imu_publisher.publish(&imu_msg);
  nh.spinOnce();

  delay(100);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

}
