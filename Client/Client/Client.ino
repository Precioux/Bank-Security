#include <LiquidCrystal.h>
#include<string.h>

// setup LCD1
const int rs = 35, en1 = 36, d4 = 40, d5 = 41, d6 = 42, d7 =43;
// setup LCD1
const int  en2 = 37;
// setup LCD1
const int  en3 = 38;
bool doors[]={false,false,false};
int rooms[]={0,0,0};

//lcds initialization
LiquidCrystal lcd1(rs, en1, d4, d5, d6, d7);
LiquidCrystal lcd2(rs, en2, d4, d5, d6, d7);
LiquidCrystal lcd3(rs, en3, d4, d5, d6, d7);
  int flag=0;
  bool zero =false;
  bool getInput=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd1.begin(20, 4);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd2.begin(20, 4);
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd3.begin(20, 4);
  lcd3.clear();
  lcd3.setCursor(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available())                        // checking if data is received/available 
  {
           char input = Serial.read();    
           Serial.println(input);  
           if(getInput == true){
             int num = input - '0';
             switch(num){
             case 0:
               emptyAll();
               break;
             case 1:
               addRoom(1);
               break;
             case 2:
               addRoom(2);
               break;    
             case 3:
               addRoom(3);
               break;
             case 4:
               subRoom(1);
               break;
             case 5:
               subRoom(2);
               break;
             case 6:
               subRoom(3);
               break;
             case 7:
               lockRoom(1);
               break;
             case 8:
               lockRoom(2);
               break;
             case 9:
               lockRoom(3);
               break;                              
             }
             getInput=false;
           }
           if( input == '$')
              getInput = true;
  }
  }

void addRoom(int room){
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
 rooms[room-1]++;
 doors[room-1]=true;
 switch(room)
 {
  case 1:
        lcd1.print("Door is open");
        lcd1.setCursor(0, 1);
        lcd1.print(rooms[room-1]);
        lcd1.print(" person");
        break;
  case 2:
        lcd2.print("Door is open");
        lcd2.setCursor(0, 1);
        lcd2.print(rooms[room-1]);
        lcd2.print(" person");
        break;
  case 3:
        lcd3.print("Door is open");
        lcd3.setCursor(0, 1);
        lcd3.print(rooms[room-1]);
        lcd3.print(" person");
        break;  
 }
}

void subRoom(int room)
{
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
 rooms[room-1]--;
 switch(room)
 {
  case 1:
        lcd1.print("Door is open");
        lcd1.setCursor(0, 1);
        lcd1.print(rooms[room-1]);
        lcd1.print(" person");
        break;
  case 2:
        lcd2.print("Door is open");
        lcd2.setCursor(0, 1);
        lcd2.print(rooms[room-1]);
        lcd2.print(" person");
        break;
  case 3:
        lcd3.print("Door is open");
        lcd3.setCursor(0, 1);
        lcd3.print(rooms[room-1]);
        lcd3.print(" person");
        break;  
 }
}

void lockRoom(int room)
{
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  doors[room-1]=false;
 switch(room)
 {
  case 1:
        if(doors[room-1]==true){
        lcd1.print("Door is open");
        lcd1.setCursor(0, 1);
        lcd1.print(rooms[room-1]);
        lcd1.print(" person");}
        else 
          lcd1.print("Locked");
        break;
  case 2:
        if(doors[room-1]==true){
        lcd2.print("Door is open");
        lcd2.setCursor(0, 1);
        lcd2.print(rooms[room-1]);
        lcd2.print(" person");}
        else 
          lcd1.print("Locked");
        break;
  case 3:
        if(doors[room-1]==true){
        lcd3.print("Door is open");
        lcd3.setCursor(0, 1);
        lcd3.print(rooms[room-1]);
        lcd3.print(" person");}
        else 
          lcd1.print("Locked");
        break; 
 }
}
void emptyAll(){
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  rooms[0]=0;
  rooms[1]=0;
  rooms[2]=0;
  doors[0]=false;
  doors[1]=false;
  doors[2]=false;
  lcd1.print("Locked and Empty");
  lcd2.print("Locked and Empty");
  lcd3.print("Locked and Empty");
}
