/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
// #include "/home/luc/catkin_ws/pacof_whack_a_mole/devel/include/wham/ledlist.h"
#include <wham/ledlist.h>
#include <wham/buttonlist.h>

#include <std_msgs/Empty.h>

ros::NodeHandle  nh;
int ledpins[16] = {52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
int buttonpins[16] =  {53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23};

void updateLeds(wham::ledlist* leds){
  // leds and ledlist should be the same length
  for (int i=0;i<16;i++){
    digitalWrite(ledpins[i],bool(leds->leds[i]));
    
  }
}
ros::Subscriber<wham::ledlist> ledstate("/ledstate", updateLeds); 

wham::buttonlist button_state;
ros::Publisher button_pub("/buttonstate", &button_state);

void setup()
{
  for (int i=0;i<16;i++){
    pinMode(ledpins[i], OUTPUT);
  }
  for (int i=0;i<16;i++){
    pinMode(buttonpins[i], INPUT_PULLUP);
  }

  nh.initNode();
  
  nh.advertise(button_pub);
 
  nh.subscribe(ledstate);
  nh.negotiateTopics();
  
}

void loop()
{
  for (int i=0;i<16;i++){
    button_state.buttons[i]= digitalRead(buttonpins[i])?0:1;
  }
  button_pub.publish(&button_state); // publish the adress of button_state..?
  nh.spinOnce();
  delay(5);
}
