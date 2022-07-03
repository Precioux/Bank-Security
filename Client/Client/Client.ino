#include <LiquidCrystal.h>
#include<string.h>

// setup LCD1
const int rs = 35, en1 = 36, d4 = 40, d5 = 41, d6 = 42, d7 =43;
// setup LCD2
const int  en2 = 37;
// setup LCD3
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
 rooms[room-1]++;
 doors[room-1]=true;
 showStatus();
}

void subRoom(int room)
{
 rooms[room-1]--;
 showStatus();
}

void lockRoom(int room)
{
  doors[room-1]=false;
  showStatus();  
}
void emptyAll(){
  rooms[0]=0;
  rooms[1]=0;
  rooms[2]=0;
  doors[0]=false;
  doors[1]=false;
  doors[2]=false;
  showStatus();
}
void showStatus()
{
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  if(doors[0]==true)
  {
        lcd1.print("Door is open");
        lcd1.setCursor(0, 1);
        lcd1.print(rooms[0]);
        lcd1.print(" person");
  }
  else  lcd1.print("Locked");
  if(doors[1]==true)
  {
        lcd2.print("Door is open");
        lcd2.setCursor(0, 1);
        lcd2.print(rooms[1]);
        lcd2.print(" person");
  }
  else  lcd2.print("Locked");
  if(doors[2]==true)
  {
        lcd3.print("Door is open");
        lcd3.setCursor(0, 1);
        lcd3.print(rooms[2]);
        lcd3.print(" person");
  }
  else  lcd3.print("Locked");  
}
