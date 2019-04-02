// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "AndroidAP5B11";
const char* password = "rykr8399";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// LED pins
const int greenLED = 15;
const int yellowLED = 2;
// Button pins
const int requestBtn1 = 4;
const int cancelBtn1 = 13;
const int requestBtn2;
const int cancelBtn2;

int index, maxNum, oldPlace;
boolean allZero;

String text[6] = {"", "", "", "", "", ""};

/* array stores and changes the order that each student has pressed request.
 * 0 means that the student hasn't pressed the button. The higher the number
 * the later they pressed the button in relation to everything else. index 0
 * is student 1.*/
int order[6] = {0, 0, 0, 0, 0, 0};

/* array stores the number of times the student has pressed the help button whether
 * or not they had cancelled the request or not. Inded 0 represents student 1*/
int counter[6] = {0, 0, 0, 0, 0, 0};

void helpPressed(int studentNum);
void cancelPressed(int studentNum);
void reorder(int studentNum);

void setup() {
   Serial.begin(115200);
  
  //GREEN LED - request sent
  pinMode(greenLED, OUTPUT);
  
  //YELLOW LED - cancel light (teacher cancels request / student cancels request
  pinMode(yellowLED, OUTPUT);

  //CANCEL BUTTON
  pinMode(cancelBtn, INPUT);
  pinMode(cancelBtn2, INPUT);

  //REQUEST BUTTON
  pinMode(requestBtn, INPUT);
  pinMode(requestBtn2, INPUT);

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  
  // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      Serial.write(c);                    // print it out the serial monitor
      header += c;
      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
                 
          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta http-equiv=\"refresh\" content=\"1.5\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          
          // CSS to style the page
          client.println("<style>");
          client.println("body{ background-color: lightblue; color: black}");
          client.println("h1 { text-align: center; text-decoration: underline; border-style: outset;}");
          client.println("#title { color:black;}");
          client.println("table { text-align: center; border: solid 10px;}");
          client.println("th { border: solid 1px; border-collapse: collapse; padding: 2px;}");
          client.println("td { border: solid 1px;}");
          client.println("#cancel { width: fit-content;}");
          client.println("</style>");

          client.println("</head>");

          //JavaScript
          /*enter code here for JavaScript*/
          
          // Web Page Heading
          client.println("<body>");
          client.println("<h1>Welcome Back!</h1>");
          
          client.println("<p style=\"text-align:center;\">Below is a chart that includes your student's names and their requests.</p>");

          client.println("<table style=\"width:100%\">");
            
          client.println("<tr id=\"title\">");
          client.println("<th>Student</th>");
          client.println("<th>Help Requested</th>");
          client.println("<th>Order of Requests</th>");
          client.println("<th>Times requested</th>");
          client.println("<th>Request Canceled</th>");
          client.println("<th>Cancel Request</th>");
          client.println("</tr>");

          //~~~~~~~~USER 1 (Index number 0)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          client.println("<tr>");
          client.println("<td id=\"01\">01</td>");//student
          //help requested
            client.println("<td>");
            if(text.equals("")){
              if(digitalRead(requestBtn1)){
                digitalWrite(greenLED, HIGH);
                helpPressed(1);
                client.println(text[0]);
                reorder(1);
                counter[0]++;
                while(digitalRead(requestBtn1)){
                  //keep in loop until button is released
                }
              }else{
                client.println(text[0]);
              }
            }else{
              client.println(text[0]);
            }
            client.println("</td>");
            //order of requests
            client.println("<td>");
            client.println(order[0]);
            client.println("</td>");            
            //times requested
            client.println("<td class = \"count\">");
            client.println(counter[0]);
            client.println("</td>");                     
            //request cancelled
            client.println("<td>");
            if(digitalRead(cancelBtn1)){
              reorder(1);
              digitalWrite(yellowLED, HIGH);
              digitalWrite(greenLED, LOW);
              client.println("REQUEST CANCELED");
              cancelPressed(1); 
              delay(5000);
              while(digitalRead(cancelBtn1)){
                //remain in loop until button is released
              } 
              digitalWrite(yellowLED, LOW);                                
            }
            client.println("</td>");
            client.println("<td><button id=\"cancel\">Cancel</button></td>");//cancel request
            client.println("</th>");
            client.println("</table>");

          //~~~~~~~~USER 2 (Index number 1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          client.println("<tr>");
          client.println("<td id=\"01\">01</td>");//student
          //help requested
          client.println("<td>");
          if(text.equals("")){
            if(digitalRead(requestBtn2)){
              digitalWrite(greenLED, HIGH);
              helpPressed();
              client.println(text[1]);
              reorder(2);
              counter[1]++;
              while(digitalRead(requestBtn2)){
                //keep in loop until button is released
              }
            }else{
              client.println(text[1]);
            }
          }else{
            client.println(text[1]);
          }
          client.println("</td>");
          //order of requests
          client.println("<td>");
          client.println(order[1]);
          client.println("</td>");            
          //times requested
          client.println("<td class = \"count\">");
          client.println(counter[1]);
          client.println("</td>");                     
          //request cancelled
          client.println("<td>");
          if(digitalRead(cancelBtn2)){
            reorder(2);
            digitalWrite(yellowLED, HIGH);
            digitalWrite(greenLED, LOW);
            client.println("REQUEST CANCELED");
            cancelPressed(2); 
            delay(5000);
            while(digitalRead(cancelBtn2)){
              //remain in loop until button is released
            }
            digitalWrite(yellowLED, LOW);                                 
          }
          client.println("</td>");
          client.println("<td><button id=\"cancel\">Cancel</button></td>");//cancel request
          client.println("</th>");
          client.println("</table>");
          client.println("</body>");
          client.println("</html>");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loop
          break;
        } else { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }
    }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("Refresh: 4;URL='//192.168.43.208/'>");
  }
}

void helpPressed(int studentNum){
  text[studentNum--] = "HELP REQUESTED";
}
void cancelPressed(int studentNum){
  text[studentNum--] = "";
}
void reorder(int studentNum){
  index = studentNum - 1;
  maxNum = 0;

  if(order[index]) == 0){
    for(int x : order){
      if(maxNum < x){
        maxNum = x;
      }
    }
    order[index] = ++max;
  } else{
    for(int x = 0; x<order.length; x++){
      if(order[x] > order[index}){
        order[x]--;
      }
      order[index] = 0;
  }
}
