#include <Keypad.h>
#include <Wire.h>
#define DEVICE_ADDRESS 0b1010000


// setup keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//setting passwords for all rooms
char passOne[5] ;//= "12341";
char passTwo[5] ;//= "12342";
char passThree[5];// = "12343";
char managerPass[]="43215";
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
  Wire.begin(); //This function initializes the Wire library and join the I2C bus as a controller or a peripheral
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
          //get passwords from EEPROM
          Serial.println("getting passwords form eeprom...");
          getPasswords();
          Serial.println("Entering Mode, Which room?");
          addFlag=true;
          break;
    case '-':
           //get passwords from EEPROM
          Serial.println("getting passwords form eeprom...");
          getPasswords();
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
void getPasswords()
{
bool oneFlag=false;
bool twoFlag=false;
bool threeFlag=false;

if(oneFlag==false){
for(int i=0;i<5;i++)
{
 passOne[i]=getFromEEPROM(5+i); 
}
Serial.println("Pass one is set");
oneFlag=true;
}

if(twoFlag==false)
{
 for(int i=0;i<5;i++)
{
 passTwo[i]=getFromEEPROM(10+i); 
}
Serial.println("Pass two is set");
twoFlag=true; 
}

if(threeFlag==false)
{
 for(int i=0;i<5;i++)
{
 passThree[i]=getFromEEPROM(15+i); 
}
Serial.println("Pass three is set");
threeFlag=true; 
}
}


byte getFromEEPROM(byte data_addr){
  byte data=NULL;
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(DEVICE_ADDRESS,1);
  delay(1);
  if(Wire.available()){
    data=Wire.read();
  }
  return data;
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
  bool authorized = false;
  bool done = false;
  if(authorized == false)
     Serial.println("Enter managing password:");
  char password[10];
  int  passLen=0;
  bool passDone = false;
  bool passDone2 = false;
  bool passFlag = false;
  bool roomFlag = false;
  int  roomNumber=0;
  char passChange[5];
  int lenPass =0;
  
  while(!done){  
  char key = keypad.getKey();
  if(authorized==false){ //getting manager password
  if(key){
     Serial.print(key);
     switch(key)
     {
      case '=':
           passDone = true;
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
if(passDone==true)
{
    if(passLen==5)
     {
      int check=0;
      for(int i=0;i<5;i++){
         if(password[i]== managerPass[i])
           check++;
      }
      if(check==5){
       Serial.println("authorized successfully!");
       Serial.println("Which room's password do you want to change?"); 
       authorized=true;
      }
     }
     else 
     {
     Serial.println("Wrong Password!");
     done=true;
     }
}

  }
  else 
  {
    if(roomFlag==false)
    {
     if(key){
      switch(key)
      {
        case '1':
           roomNumber=1;
           roomFlag=true;
           Serial.println("Room 1");
           Serial.println("Now enter new password:");
           break;
        case '2':
           roomNumber=2;
           roomFlag=true;
           Serial.println("Room 2");
           Serial.println("Now enter new password:");                               
           break;
        case '3':
           roomNumber=3;
           Serial.println("Room 3");
           Serial.println("Now enter new password:");           
           roomFlag=true;           
           break;                      
      }
     }
    }
    else{
    if(passFlag==false)
    {
      if(key){
     Serial.print(key);
     switch(key)
     {
      case '=':
           passDone2 = true;
           break;
      case '1':
           passChange[lenPass]='1';
           lenPass++;
           break;
      case '2':
           passChange[lenPass]='2';
           lenPass++;
           break;
      case '3':
           passChange[lenPass]='3';
           lenPass++;
           break;
      case '4':
           passChange[lenPass]='4';
           lenPass++;
           break;                            
      case '5':
           passChange[lenPass]='5';
           lenPass++;
           break;
      case '6':
           passChange[lenPass]='6';
           lenPass++;
           break;           
      case '7':
           passChange[lenPass]='7';
           lenPass++;
           break;
      case '8':
           passChange[lenPass]='8';
           lenPass++;
           break;
      case '9':
           passChange[lenPass]='9';
           lenPass++;
           break;
      case '0':
           passChange[lenPass]='0';
           lenPass++;
           break;                      
     }
     }
     if(passDone2==true)
{
    if(lenPass==5)
     {
      switch(roomNumber)
      {
      case 1:
          for(int i=0;i<5;i++)
             passOne[i]=passChange[i];
          break;
      case 2:
          for(int i=0;i<5;i++)
             passTwo[i]=passChange[i];
          break;         
      case 3:
          for(int i=0;i<5;i++)
             passThree[i]=passChange[i];
          break;            
      }
          for(int i=0;i<5;i++){
          sendToEEPROM(5+i,passOne[i]);
          delay(100);
          }
          for(int i=0;i<5;i++){
          sendToEEPROM(10+i,passTwo[i]);
          delay(100);
          }
          for(int i=0;i<5;i++){
          sendToEEPROM(15+i,passThree[i]);
          delay(100);
          }                 
          Serial.println("Password is set");    
          done = true;

     }
     else
     {
      Serial.println("Wrong input!");
      roomFlag=false;
      passFlag=false;
     }
}
}
  } 
    }
  }
  Serial.println("Exiting set password");
  
}



void sendToEEPROM(byte memory_addr,byte data)
{
Wire.beginTransmission(DEVICE_ADDRESS);
Wire.write(0);
Wire.write(memory_addr);
Wire.write(data);
Wire.endTransmission();
}
