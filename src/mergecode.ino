#include "pitches.h"

#define LED_PIN 13
#define LED_PIN1 12
#define LED_PIN2 11

#define CMD_SEND_BEGIN  "AT+CIPSEND=0"
#define CMD_SEND_END    "AT+CIPCLOSE=0"

#define STDIO_PROTOCOL_HTTP     80
#define STDIO_PROTOCOL_HTTPS    443
#define STDIO_PROTOCOL_FTP      21
#define STDIO_PROTOCOL_CURRENT  STDIO_PROTOCOL_HTTP

#define STDIO_CHAR_CR     0x0D
#define STDIO_CHAR_LF     0x0A

#define STDIO_STRING_EMPTY  ""

#define STDIO_DELAY_SEED  1000
#define STDIO_DELAY_1X    (1*STDIO_DELAY_SEED)
#define STDIO_DELAY_2X    (2*STDIO_DELAY_SEED)
#define STDIO_DELAY_3X    (3*STDIO_DELAY_SEED)
#define STDIO_DELAY_4X    (4*STDIO_DELAY_SEED)
#define STDIO_DELAY_5X    (5*STDIO_DELAY_SEED)

bool hasRequest = false;

void setup()
{
  
  delay(STDIO_DELAY_5X);
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN, LOW);
  
  pinMode(LED_PIN1, OUTPUT);
  digitalWrite(LED_PIN1, LOW);

  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN2, LOW);
  
  initESP8266();
}

void loop()
{
  while(Serial.available())
  {   
    bufferingRequest(Serial.read());
  }
  
  if(hasRequest == true) 
  {
    String htmlResponse = "<!doctype html>"
    "<html style='text-align:center'>"
      "<head>"
        "<title>Arduino & ESP8266</title>"
      "</head>"
      "<body>"
        "<h1>(^_^) Demo Remote Device [@__@]</h1>"
        "<form action='' method='GET'>"
              "<input type='radio' name='LED8' name='LED8ON' value='ON8' /> LED8 ON</>"
              "<input type='radio' name='LED8' name='LED8OFF' value='OFF8' /> LED8 OFF<br/>"
              "<input type='radio' name='LED7' name='LED7ON' value='ON7' /> LED7 ON</>"
              "<input type='radio' name='LED7' name='LED7OFF' value='OFF7' /> LED7 OFF<br/>" 
              "<input type='radio' name='LED6' name='LED6ON' value='ON6' /> LED6 ON</>"
              "<input type='radio' name='LED6' name='LED6OFF' value='OFF6' /> LED6 OFF<br/>" 
              "<input type='radio' name='Sound' name='Sound80ON' value='ON80' /> Mario</>"
              "<input type='radio' name='Sound' name='Sound90ON' value='ON90' /> Happy Birthday<br/>"
              "<input type='radio' name='Sound' name='Sound100OFF' value='OFF100' /> No Sounds<br/>"

          "<input type='submit' value='Submit' />"
        "</form>"
      "</body>"
     "</html>";
    
    String beginSendCmd = String(CMD_SEND_BEGIN) + "," + htmlResponse.length();
    deliverMessage(beginSendCmd, STDIO_DELAY_1X);
    deliverMessage(htmlResponse, STDIO_DELAY_1X);
    deliverMessage(CMD_SEND_END, STDIO_DELAY_1X);
    hasRequest = false;
  }
}

void initESP8266()
{
  deliverMessage("AT+RST", STDIO_DELAY_2X);
  deliverMessage("AT+CWMODE=2", STDIO_DELAY_3X);
  deliverMessage("AT+CWSAP=\"Tao la Ma Day!!\",\"Alo12345\",1,4", STDIO_DELAY_3X);
  deliverMessage("AT+CIFSR", STDIO_DELAY_1X);
  deliverMessage("AT+CIPMUX=1", STDIO_DELAY_1X);
  deliverMessage(String("AT+CIPSERVER=1,") + STDIO_PROTOCOL_CURRENT, STDIO_DELAY_1X);  
}

void bufferingRequest(char c)
{
  static String bufferData = STDIO_STRING_EMPTY;

  switch (c)
  {
    case STDIO_CHAR_CR:
      break;
    case STDIO_CHAR_LF:
    {
      STDIOProcedure(bufferData);
      bufferData = STDIO_STRING_EMPTY;
    }
      break;
    default:
      bufferData += c;
  }
} 

void STDIOProcedure(const String& command)
{ 
  hasRequest = command.startsWith("+IPD,");
  
    if(command.indexOf("OFF8") != -1)
  {
    digitalWrite(LED_PIN, LOW);
  }
  else if(command.indexOf("ON8") != -1)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  ////delay(DELAY_1X);
/********************************************/
  ////LED12
  
  if(command.indexOf("OFF7") != -1)
  {
    digitalWrite(LED_PIN1, LOW); 
  }
  else if(command.indexOf("ON7") != -1)
  {
    digitalWrite(LED_PIN1, HIGH);
  }
  ////LED11
  
    if(command.indexOf("OFF6") != -1)
  {
    digitalWrite(LED_PIN2, LOW); 
  }
  else if(command.indexOf("ON6") != -1)
  {
    digitalWrite(LED_PIN2, HIGH);
  }

  //Melody mario  

  if(command.indexOf("ON80") != -1)
  {
    melodyC();
  }

  //HPBD

  if(command.indexOf("ON90") != -1)
  {
    HPBD();
  }

  

}

void deliverMessage(const String& msg, int dt)
{
  Serial.println(msg);
  delay(dt);
}




void melodyA(){
//  pinMode (11, OUTPUT);
//  pinMode (12, OUTPUT);
//  pinMode (13, OUTPUT);
  Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
    int randomLight1 = random(11, 14);
    int randomLight2 = random(11, 14);
    int randomLight3 = random(11, 14);
    
      digitalWrite (randomLight1, HIGH);
      digitalWrite (randomLight2, HIGH);
      
      digitalWrite (randomLight3, LOW);
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      tone(8, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);


}
  delay(1000);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}

void melodyB(){
//  pinMode (11, OUTPUT);
//  pinMode (12, OUTPUT);
//  pinMode (13, OUTPUT);
  Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
    int randomLight1 = random(11, 14);
    int randomLight2 = random(11, 14);
    int randomLight3 = random(11, 14);
    
      digitalWrite (randomLight1, HIGH);
      digitalWrite (randomLight2, HIGH);
      
      digitalWrite (randomLight3, LOW);
    //digitalWrite (random(11, 13), LOW);
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      tone(8, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
}
  delay(1000);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}

void melodyC(){
    melodyA();
    melodyB();

}





//HPBD
void HPBD(){
//  pinMode (11, OUTPUT);
//  pinMode (12, OUTPUT);
//  pinMode (13, OUTPUT);
  Serial.println(" 'Happy Birthday'");
    int size = sizeof(hpbd_melody) / sizeof(int);
  for (int thisNote = 0 ; thisNote < size ; thisNote++) { 
    int randomLight1 = random(11, 14);
    int randomLight2 = random(11, 14);
    int randomLight3 = random(11, 14);
    
    digitalWrite (randomLight1, HIGH);
    digitalWrite (randomLight2, HIGH);
    
    digitalWrite (randomLight3, LOW);
    //digitalWrite (random(11, 14), LOW);
    
    int noteDuration = 1130/noteDurations[thisNote];
    tone (8, hpbd_melody[thisNote], noteDuration);
    
    int pause = noteDuration * 1.275;
    delay (pause);

    
  }

  delay(1000);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    
}
