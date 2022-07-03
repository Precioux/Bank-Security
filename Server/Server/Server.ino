#include <Keypad.h>
// setup keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//setting passwords for all rooms
const char passOne[] = "12341";
const char passTwo[] = "12342";
const char passThree[] = "12343";
//other initializations
bool requested = false;
bool lastRequest = false;
//rooms data
int rooms[3]={0,0,0};
bool doors[3]={false,false,false};
int room =0;
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'#','0','=', '+'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
bool addFlag = false;
bool subFlag = false;
bool managerFlag = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //find out if user wants to enter or exit or manager wants to set passwords
 char key = keypad.getKey();
 if(key!=NO_KEY){
   //Serial.println("Request detected...");
   if( subFlag==false && addFlag==false && managerFlag==false){
   switch(key)
   {
    case '+':
          Serial.println("Entering Mode, Which room?");
          addFlag=true;
          break;
    case '-':
          Serial.println("Exiting Mode, Which room?");
          subFlag=true;
          break;
    case '/':
          Serial.println("Hi manager,Enter 1 to continue:");
          managerFlag=true;
          break;    
   }
   }
   else
   {
    if(addFlag == true)
    {
      welcome(key);
      int result = -2;;
      if(requested){
      result = passCheck();
      if( result == 1 ){
     Serial.println("Entered Successfully!");
     Serial.print('$');
     switch(room){
     case 1:
        Serial.println('1');
        break;
     case 2:
        Serial.println('2');
        break;
     case 3:
        Serial.println('3');
        break;        
     } 
     //keeping door open for 5 seconds
     delay(5000);
     Serial.println("Closing door of room...");
     Serial.print('$');
     switch(room){
     case 1:
        Serial.println('7');
        break;
     case 2:
        Serial.println('8');
        break;
     case 3:
        Serial.println('9');
        break;       
      }
     doors[room-1]=false;
     requested = false;
     Serial.println("");
     
  }
  else{
    if(result == -1){
    Serial.println("Wrong Password!");
    //closing all doors and emptying all rooms
    Serial.println('$');
    Serial.print('0');
    Serial.println("");
    delay(100);
    callPolice();
    requested = false;
    }
    else{
     if(result==-3)
        Serial.println("Room is full, try again later");
        requested = false;
    }
  }
    }
    addFlag=false;
    Serial.println("Done!");
   }
   else 
   {
    if(subFlag==true)
    {
     goodBye(key);
     if(rooms[room-1]!=0){
     rooms[room-1]--;
     Serial.print('$');
     switch(room){
     case 4:
        Serial.println('4');
        break;
     case 5:
        Serial.println('5');
        break;
     case 6:
        Serial.println('6');
        break;       
      }
      requested = false;
      subFlag=false;
    }
    else
    {
      Serial.println("This room is empty!");
      requested=false;
      subFlag=false;
    }
    }
    else
    {
      if(managerFlag==true)
      {
        setPasswords();
        managerFlag=false;
      }
    }
   }
 }

}
}

void goodBye(char key){
 if(key){
     switch(key)
     {
     case '1':
         room = 1;
         Serial.println("Exiting room 1");
         requested = true;
         break;
     case '2':
         room = 2;
         Serial.println("Exiting room 2");
         requested = true;
         break;
     case '3':
         room = 3;
         Serial.println("Exiting room 3");
         requested = true;
         break;
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
         if(doors[room-1]==false)
            doors[room-1]=true;
         if(rooms[room-1]<3){
            rooms[room-1]++;
         }
         else result=-3;
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
void setPasswords(){
  Serial.println("Enter password:");
}
