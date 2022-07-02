#include <Keypad.h>

// setup keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const char passOne[] = "12341";
const char passTwo[] = "12342";
const char passThree[] = "12343";
bool requested = false;
bool lastRequest = false;
int rooms[3]={0,0,0};
bool doors[3]={false,false,false};

char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'#','0','=', '+'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int room =0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 char key = keypad.getKey();
 if(key!=NO_KEY){
   Serial.println("Request detected...");
 Serial.println(key);
 welcome(key);
  int result = -2;;
  if(requested){
     result = passCheck();
  if( result == 1 ){
     Serial.println("Entered Successfully!");
     requested = false;
     doors[room-1]=true;
  }
  else{
    Serial.println("Wrong Password!");
    callPolice();
    requested = false;
  }
}
}
}


void welcome(char key){
 if(key){
     switch(key)
     {
     case '1':
         room = 1;
         Serial.println("Entering room 1");
         requested = true;
         break;
     case '2':
         room = 2;
         Serial.println("Entering room 2");
         requested = true;
         break;
     case '3':
         room = 3;
         Serial.println("Entering room 3");
         requested = true;
         break;
     }
 }
}

int passCheck(){
  int result = -1;
  char password[10];
  int  passLen=0;
  bool done = false;
  Serial.println("Please Enter Room's Password: ");
  Serial.println("(enter pass and = to finish)");
  while(!done){
  char key = keypad.getKey();
  if(key){
     Serial.print(key);
     switch(key)
     {
      case '=':
           done = true;
           break;
      case '1':
           password[passLen]='1';
           passLen++;
           break;
      case '2':
           password[passLen]='2';
           passLen++;
           break;
      case '3':
           password[passLen]='3';
           passLen++;
           break;
      case '4':
           password[passLen]='4';
           passLen++;
           break;                            
      case '5':
           password[passLen]='5';
           passLen++;
           break;
      case '6':
           password[passLen]='6';
           passLen++;
           break;           
      case '7':
           password[passLen]='7';
           passLen++;
           break;
      case '8':
           password[passLen]='8';
           passLen++;
           break;
      case '9':
           password[passLen]='9';
           passLen++;
           break;
      case '0':
           password[passLen]='0';
           passLen++;
           break;                      
     }
}
  }
  Serial.println("");
  Serial.println(passLen);
  Serial.println(password);
  if(passLen==5)
     {
      int check=0;
      if(room == 1){
      for(int i=0;i<5;i++){
         if(password[i]== passOne[i])
           check++;
      }
      }
      if(room == 2){
      for(int i=0;i<5;i++){
         if(password[i]== passTwo[i])
           check++;
      }
      }
      if(room == 3){
      for(int i=0;i<5;i++){
         if(password[i]== passThree[i])
           check++;
      }
      }
      if(check==5){
         result = 1;
         rooms[room-1]++;
      }
     }
     return result;
}
void callPolice(){
 Serial.println("Emptying all rooms...");
 rooms[0]=0;
 rooms[1]=0;
 rooms[2]=0;
 Serial.println("Closing all doors..");
 doors[0]=false;
 doors[1]=false;
 doors[2]=false;
}
