#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Mac do Arduino
byte ip[] = { 192, 168, 0, 10 }; //IP do Arduino

EthernetServer server(80); //Selecionar porta de saída
Servo Garagem; //Declara como garagem o servo motor
Servo Porta; // Declara como porta o servo motor
Servo Varal; // Declara como varal o servo motor

int led1 = 2;    //Cozinha
int led2 = 3;   //Copa


String readString = String(30);
String statusLed;

void setup() {
  Ethernet.begin(mac, ip);
  pinMode(led1, OUTPUT); //define led1 como saída
  pinMode(led2, OUTPUT); //define led2 como saída
 
  Garagem.attach(4); //Define a porta 4 a saída do servo da garagem.
  Porta.attach(5);//Mesma coisa
  Varal.attach(6);//mesma coisa
}

void loop() {
  EthernetClient client = server.available();
 
  if(client){
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        if(readString.length() < 30) {
          readString += (c);
        }    
       
        if(c == '\n'){
          if(readString.indexOf("led1") >= 0) {
            digitalWrite(led1,!digitalRead(led1));
          }
         
          if(readString.indexOf("led2") >= 0) {
            digitalWrite(led2,!digitalRead(led2));
          }
         
         

          if(readString.indexOf("garagemUP") >= 0) {
           Garagem.write(180);
          }

          if(readString.indexOf("garagemDOWN") >= 0) {
            Garagem.write(0);
          }

              if(readString.indexOf("portaOPEN") >= 0) {
            Porta.write(180);
          }

          if(readString.indexOf("portaCLOSE") >= 0) {
            Porta.write(0);
          }      


           if(readString.indexOf("varalOPEN") >= 0) {
            Varal.write(180);
          }

          if(readString.indexOf("varalCLOSE") >= 0) {
            Varal.write(0);
          }      

         

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!doctype html>");
         
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Carmine SmartHome</title>");
          client.println("<meta name=\"viewport\" content=\"width=320\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width\">");
          client.println("<meta charset=\"utf-8\">");
          client.println("<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">");
          client.println("</head>");
          client.println("<body>");
          client.println("<center>");
         
          client.println("<font size=\"10\" face=\"verdana\" color=\"blue\">Carmine</font>");
          client.println("<font size=\"10\" face=\"verdana\" color=\"black\">SmartHome</font><br />");
         
          if(digitalRead(led1)){
            statusLed = "Ligado";
          }

          else{
            statusLed = "Desligado";
          }
         
          client.println("<td> <form action=\"led1\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">COZINHA - "+statusLed+"</button>");
          client.println("</form> <br /></td>");
         
          if(digitalRead(led2)) {
            statusLed = "Ligado";
          }
         
          else{
            statusLed = "Desligado";
          }

          client.println("<td> <form action=\"led2\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">COPA - "+statusLed+"</button>");
          client.println("</form> <br /></td>");

         

          client.println("Abrir");
          client.println("<td> <form action=\"garagemUP\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">GARAGEM" "</button>");
          client.println("</form> <br /></td>");

          client.println("Fechar");
          client.println("<td> <form action=\"garagemDOWN\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">GARAGEM" "</button>");
          client.println("</form> <br /></td>");

          client.println("Abrir");
          client.println("<td> <form action=\"portaOPEN\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">Porta" "</button>");
          client.println("</form> <br /></td>");

          client.println("Fechar");
          client.println("<td> <form action=\"portaCLOSE\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">Porta" "</button>");
          client.println("</form> <br /></td>");

          client.println("Abrir");
          client.println("<td> <form action=\"varalOPEN\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">Varal" "</button>");
          client.println("</form> <br /></td>");

          client.println("Fechar");
          client.println("<td> <form action=\"varalCLOSE\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">Varal" "</button>");
          client.println("</form> <br /></td>");

          client.println("</center>");  
          client.println("</body>");
          client.println("</html>");  
          readString = "";
          client.stop();
        }
      }
    }
  }
}
