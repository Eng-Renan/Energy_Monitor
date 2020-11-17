#include <OneWire.h>
#include <SPI.h>
#include <Ethernet.h>  // Biblioteca utilizada para comunicação com o Arduino

//===================================================================================LEITURA DOS RELÉS E ENTRADAS=============================================================================================

int leitura_2; //(eletropaulo)
int leitura_3; //(grupo gerador)
int leitura_5; // (nobreak)
int leitura_8; // (rack)
//int leitura_8; // (futuro rele)

//===================================================================================================================================================================================
// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa de rede. 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 192, 168,0, 115 };  // Define o endereço IP.
    
EthernetServer server(80);  // Porta onde estará aberta para comunicação Internet e Arduino.
 
String readString;

int elp = 2; //
int gg = 3; //
int nb = 5; //
int rck = 8; //
//int Pin = 9;  //  Pino digital onde será ligado e desligado o LED.
//int led = 8; //  Pino digital onde será ligado e desligado o LED.
float temp;
int tempPin = A0;

void setup(){
 
  //==================================================================================AJUSTE LCD =====================================================================================
//lcd.begin(16,2); // Inicio comunicação LCD
//  pinMode(8,OUTPUT);
  //=================================================================================================================================================================================
 
  pinMode(elp, INPUT);
  pinMode(gg, INPUT);
  pinMode(nb, INPUT);
  pinMode(rck, INPUT);
//  pinMode(Pin, OUTPUT);  // Define o Pino 9 como saída.
  Ethernet.begin(mac, ip);  // Chama o MAC e o endereço IP da placa Ethernet.
  server.begin();  //  Inicia o servidor que esta inserido junto a placa Ethernet.
  //sensors.begin();
}
 
void loop()

{

leitura_2 = digitalRead(2);
leitura_3 = digitalRead(3);
leitura_5 = digitalRead(5);
leitura_8 = digitalRead(8);

//leitura_8 = digitalRead(8);

//---------------------------------------------------------------------------COMANDOS ETHERNET SHIELD--------------------------------------------------------------------------------------  
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
 
        if (readString.length() < 100) 
        {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          //client.println (F("<META HTTP-EQUIV=REFRESH CONTENT=5;>"));
          client.println();
    
           // A partir daqui começa os códigos html.
    
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1><title>Telemetria Jaragua</title></H1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<p>");
          client.println("<p>");
          client.println("<center><img src=http://tvcultura.com.br/_img/tvcultura/programas_abertura_TV.jpg weight=300 height=100></center>");
          client.println("<p>");
          client.println("<p>");
          client.println("<font size=+4><center><B>Telemetria Jaragua</B><BR><font size=+3>");
          client.println("<p>");
          //client.println("<a href=\"/facacomarduino/LedOn\"\">Ascender led</a><font size=+2>");
          //client.println("<a href=\"/facacomarduino/LedOff\"\">Apagar led</a><br /><font size=+2>");   
          //client.println("<a href=\"/arduino/led_liga\"\">Ascender liga</a><font size=+2>");
          //client.println("<a href=\"/arduino/led_des\"\">Apagar desliga</a><br /><font size=+2>");   
          client.println("</BODY>");
          client.println("</HTML>");
//==================================================================================================================================================================================          
             temp = analogRead(tempPin);
             temp = temp * 0.48828125;
             client.println("Temperatura = <font size=+2>");
             client.println(temp);
             client.println("*C <font size=+2><p>");
             client.println();
             client.println (F("<META HTTP-EQUIV=REFRESH CONTENT=0.5;>"));
//==================================================================================================================================================================================          
            //leitura_8 = digitalRead(8);
             
            
           if (leitura_2 == 1)          
            {
              client.println(" ELETROPAULO ON <font size=+2><p>");
            }
            
            if (leitura_2 == 0)
            {
              client.println(" ELETROPAULO OFF <font size=+2><p>");
            }
           
           if (leitura_3 == 1)          
            {
              client.println(" GRUPO GERADOR ON <font size=+2><p>");
            }
            
            if (leitura_3 == 0)
            {
              client.println(" GRUPO GERADOR OFF <font size=+2><p>");
            }
           
           if (leitura_5 == 1)          
            {
              client.println(" NOBREAK ON <font size=+2><p>");
            }
            
            if (leitura_5 == 0)
            {
              client.println(" NOBREAK OFF <font size=+2><p>");
            }
           
           if (leitura_8 == 1)          
            {
              client.println(" RACK ON <font size=+2><p>");
            }
            
            if (leitura_8 == 0)
            {
              client.println(" RACK OFF <font size=+2><p>");
            }
            
            /*if (leitura_8 == 1)          
            {
              client.println(" RELE ON <font size=+2><p>");
            }
            
            if (leitura_8 == 0)
            {
              client.println(" RELE OFF <font size=+2><p>");
            }*/
             
          delay(1);
          client.stop();
          
          /*
          if(readString.indexOf("facacomarduino/LedOn") > 0)
          {
            digitalWrite(Pin, HIGH);  // Liga LED.
          }
          else {
            if(readString.indexOf("facacomarduino/LedOff") > 0)
            {
              digitalWrite(Pin, LOW);  // Desliga LED.
            }
          } 
          
           if(readString.indexOf("arduino/led_liga") > 0)
          {
            digitalWrite(led, HIGH);  // Liga LED.
          }
          else {
            if(readString.indexOf("arduino/led_des") > 0)
            {
              digitalWrite(led, LOW);  // Desliga LED.
            }
          } */
          
          readString="";    
        }
      }
    }
  }
}
