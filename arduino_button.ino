/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int16.h>

// ros::init("arduino_button");

ros::NodeHandle  nh;

int ledlist[] = {52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
int buttonlist[] =  {53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23};
std_msgs::Int16MultiArray button_state;
int i;


void updateLeds(const std_msgs::Int16& leds){
  // leds and ledlist should be the same length
  for (i=0;i<sizeof(leds);i++){
    digitalWrite(ledlist[i],leds.data);
  }
}


// ros::Subscriber<int[sizeof(ledlist)]> ledstate("ledstate", 1000, updateLeds); 
ros::Subscriber<std_msgs::Int16MultiArray> ledstate("ledstate", 1000, updateLeds); 
// nh.subscribe("ledstate", 1000, updateLeds);


// std_msgs::Int32 btn_msg;

ros::Publisher buttonstate("buttonstate",1000, &button_state);
// ros::Publisher buttonstate = nh.advertise<std_msgs::Int32>("buttonstate", 1000);

// char hello[13] = "hello world!";

void setup()
{
  for (i=0;i<sizeof(ledlist);i++){
    pinMode(i, OUTPUT);
  }
  for (i=0;i<sizeof(buttonlist);i++){
    pinMode(i, INPUT);
  }

  nh.initNode();
  nh.advertise(buttonstate);
  nh.subscribe(ledstate);
}

void loop()
{
  for (i=0;i<sizeof(buttonlist);i++){
    button_state.data[i]=digitalRead(i);
  }
  // str_msg.data = hello;
  buttonstate.publish( &button_state );
  nh.spinOnce();
  delay(500);
}
