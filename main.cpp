/* EXAMPLE */
#include "mbed.h"
#include "hcsr04.h"

//D12 TRIGGER D11 ECHO
HCSR04 sensor(D12, D11);



#include "MQTTmbed.h"

#include <MQTTClientMbedOs.h>

#include <cstdio>


#include "mbed.h"
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x4E, 16, 2);
 

int main(int argc, char *argv[])
 {
   
   /* EXAMPLE */
 long distance = sensor.distance();   
      printf("distance  %d  \n",distance);
    // initialize the LCD
    lcd.begin();
     
      
    // initialize the LCD
    lcd.begin();

    // Turn on the blacklight and print a message.
    lcd.backlight();
    lcd.print("Hello, world!");
    
    
    
//lcd.printf("Hi mbed World!\n");

 printf("Starting IBM MQTT demo:\n");

 

 TCPSocket socket;

 NetworkInterface *net = NetworkInterface::get_default_instance();

 if (!net) {

   printf("Error! No network inteface found.\n");

   return 0;

 }

 printf("Connecting to the network...\r\n");

 

 nsapi_size_or_error_t rc = net->connect();

 if (rc != 0) {

   printf("Error! _net->connect() returned: %d\r\n", rc);

   return -1;

 }

 

 rc = socket.open(net);

 if (rc != 0) {

   printf("Error! _socket.open() returned: %d\r\n", rc);

   return -1;

 }

 

 SocketAddress address;

 net->gethostbyname("thingsboard.myitacademy.ru",

                    &address);

 address.set_port(1883);

 

 printf("Opening connection to remote %s port %d\r\n",

        address.get_ip_address(), address.get_port());

 rc = socket.connect(address);

 if (rc != 0) {

   printf("Error! _socket.connect() returned: %d\r\n", rc);

   return -1;

 }

 printf("Connected socket\n");

 

 MQTTClient client(&socket);

 MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

 data.MQTTVersion = 3;

 data.clientID.cstring = "vali_client_id";

 data.username.cstring = "vali_user_name";

 data.password.cstring = "fkQiW3AJFcM38ED";

 if ((rc = client.connect(data)) != 0)

   printf("rc from MQTT connect is %d\r\n", rc);

 
 
 
 
    //{clientId:"vali_client_id",userName:"vali_user_name",password:"fkQiW3AJFcM38ED"}
 
 
  
 

 MQTT::Message message;

 char *topic = "v1/devices/me/telemetry";

 char buf[100];

 int temp = 1;

 int press = 2;

 int hum = 3;

 //sprintf(buf,

 //        "{\"d\":{\"ST\":\"Nucleo-IoT-mbed\",\"Temp\":%d,\"Pressure\":"

//         "%d,\"Humidity\":%d}}", temp, press, hum);

 sprintf(buf,

         "{\"temperature\":  %d}", temp);
         sprintf(buf,

         "{\"distance\":  %d}", distance);



 printf("Sending message: \n%s\n", buf);

 message.qos = MQTT::QOS0;

 message.retained = false;

 message.dup = false;

 message.payload = (void *)buf;

 message.payloadlen = strlen(buf);

 rc = client.publish(topic, message);

 printf("Message sent\n");

 printf("Demo concluded successfully \r\n");

 

 return 0;
}