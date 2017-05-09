

#include <Ethernet.h>

EthernetClient client;

//pino de saida LM25
int pinoSensor = 2;
int valorLido = 0;
float temperatura = 0;



void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x06};
  Ethernet.begin(mac);

  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());


   //pin led
    pinMode (3, OUTPUT);

  
}

void loop() {

  
      Serial.println("Client connect");

      if (client.connect(IPAddress(192,168,1,101),5000))
      //if (client.connect(IPAddress(10,0,1,30),5000))
        {
          Serial.println("Client connected");
          //client.println("DATA from Client");

          int temp = 0;
          char ledOP;
          
         

          while(1){
      valorLido = analogRead(pinoSensor);
      temperatura = (valorLido * 0.00488);
      temperatura = temperatura * 100;
      temp = (int)temperatura;


            
          if(client.available() == 0)
            {

              
             
              client.write(temp);
              Serial.print("Enviou Temperatura: ");
              Serial.println(temperatura);
            
            
            }


             if (client.available()) {

              ledOP = client.read();
              Serial.println("Recebeu ledOP:");
              Serial.println(ledOP);

             }


                if(ledOP == '1'){
                  digitalWrite(3, HIGH);
                  Serial.println("LED ON");
                  
                }
                if(ledOP == '0'){
                  digitalWrite(3, LOW);
                  Serial.println("LED OFF");
                  
                }

          
               delay(5000);
             }
             


        
          }
        
}
