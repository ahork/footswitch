/*Press button to scan, serial monitor will print information*/

#include  <M5Atom.h>
#include <BleKeyboard.h>

String AltGrazerty="~#{[|`\\^@#]}";
String shiftazerty="QBCDEFGHIJKL?NOPARSTUVZXYW1234567890 Q+QQQQM%Q./Q>";
String azerty="qbcdefghijkl,noparstuvzxyw&q\"'(-q_qq )=q$q*mqq;:!<";
const byte scancode[] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,44,45,46,47,48,49,50,51,52,53,54,55,56,100};

const boolean AZERTY = true;

BleKeyboard bleKeyboard;

const int tempo=10;
 
void Keyfr(const String &Texte){
  int j = -1;
 
  for (unsigned int i=0; i< Texte.length(); i++){
    delay(tempo);
    
    char c = Texte.charAt(i);
    
    if (c=='\t'){
      bleKeyboard.write(KEY_TAB);
    }
   
    int index = azerty.indexOf(c);
    if (index>-1){
      j = scancode[index]+136;
      bleKeyboard.write(j);
    } else{
      index = shiftazerty.indexOf(c);
      if (index>-1){
        j = scancode[index]+136;
        bleKeyboard.press(KEY_LEFT_SHIFT);
        bleKeyboard.press(j);
        bleKeyboard.releaseAll();
      }else {
        index = AltGrazerty.indexOf(c);
        if (index>-1){
          j = scancode[index+27]+136;
          bleKeyboard.press(KEY_LEFT_CTRL);
          bleKeyboard.press(KEY_LEFT_ALT);
          bleKeyboard.write(j);
          bleKeyboard.releaseAll(); 
          if (index==0 || index==7){
            // Traitement spécial pour ce caractère ~ et ^ qui sont des deads keys
            // ce qui n'est pas le cas sur les clavier qwerty
            // on le tape une seconde fois puis on fait un Retour Arrière.
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press(KEY_LEFT_ALT);
            bleKeyboard.write(j);
            bleKeyboard.releaseAll();
            bleKeyboard.write(KEY_BACKSPACE);
          }
        }
      }   
    }
  }
}

void Keyfrln(const String &Texte){
  Keyfr(Texte);
  bleKeyboard.write(KEY_RETURN);
}

void setup() {
  pinMode(21,INPUT_PULLUP);
  pinMode(25,INPUT_PULLUP);
  
  M5.begin(true, false, true);
  delay(500);
  bleKeyboard.begin();
  delay(500);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 22, 19);
  M5.dis.drawpix(0, 0x00f000);
  
}
int clic = 0;
int clicd = 0;

void loop() {
  
     if(bleKeyboard.isConnected()) 
      {        
       if (digitalRead(21) == LOW && clic == 0) {
       
         //Keyfr(phrase);
         bleKeyboard.press(KEY_DOWN_ARROW);
         Serial.println("D");
         delay(500);
        clic = 1;
      }
      
      if (digitalRead(21) == HIGH && clic == 1) {
          
        //Keyfr(phrase);
         bleKeyboard.press(KEY_DOWN_ARROW);
         Serial.println("D");
         delay(500);
         clic = 0;
        }        
       

      
       if (digitalRead(25) == LOW && clicd == 0) {
       
         //Keyfr(phrase);
         bleKeyboard.press(KEY_DOWN_ARROW);
         Serial.println("M");
         delay(500);
        clicd = 1;
      }
      
      if (digitalRead(25) == HIGH && clicd == 1) {
          
        //Keyfr(phrase);
         bleKeyboard.press(KEY_DOWN_ARROW);
         Serial.println("M");
         delay(500);
         clicd = 0;
        }        
     
    }
    delay(500);
    M5.update();
    
  }
