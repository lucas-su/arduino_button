/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
// #include <std_msgs/Bool.h>


ros::NodeHandle  nh;

int ledlist[] = {52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
int buttonlist[] =  {53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23};
bool button_state[sizeof(buttonlist)];
int i;
bool[sizeof(ledlist)]& leds;

void updateLeds(leds){
  // leds and ledlist should be the same length
  
  for (i=0;i<sizeof(leds);i++){
    digitalWrite(ledlist[i],leds[i].value;
  }
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );



std_msgs::String str_msg;
ros::Publisher buttonstate("buttonstate");

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
    button_state[i]=digitalRead(i);
  }
  // str_msg.data = hello;
  buttonstate.publish( &button_state );
  nh.spinOnce();
  delay(500);
}
