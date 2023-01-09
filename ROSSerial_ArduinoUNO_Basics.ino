#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#define LED 13
#define BUTTON 6


//Updated v0.1.1 fixed Button Press
ros::NodeHandle nh;

std_msgs::String button_msg;
std_msgs::UInt16 LED_msg;

void subCallback(const std_msgs::UInt16& LED_msg) {

  if (LED_msg.data == 1){
    digitalWrite(LED, HIGH);
    
  }
  else {
    digitalWrite(LED, LOW);
    
  }
}


ros::Publisher button_publisher("button_press", &button_msg);
ros::Subscriber<std_msgs::UInt16> LED_subscriber("toggle_LED", &subCallback);


void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);

  nh.initNode();
  nh.advertise(button_publisher);
  nh.subscribe(LED_subscriber);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON) == LOW){
    button_msg.data = "Pressed";
  
  }
  else {
    button_msg.data="Not Pressed";
    
  }

  button_publisher.publish(&button_msg);
  nh.spinOnce();

  delay(100);
}
