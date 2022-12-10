#include<SoftwareSerial.h>

SoftwareSerial esp(7, 8);

String task[2];  //{"id","task"}
String wrong;   //Wrong respons buffer


void setup()
{
  esp.begin(9600);
  Serial.begin(9600);   //start the serial port
  
  String arg[]={"WifiSSID","WIFIPASSWD"}; //create a String array for arguments
  wifi(1,arg);    //connect to a network
}

void loop()
{
  if (esp.available())
    Serial.println(op_read());  //if esp available then read datas
}

String op_read()
{
  String buff = esp.readStringUntil(char(244));   //read datas to the "buff" until the character ¶ character (An arbitrary character)
  buff.replace(String(char(244)),""); //delet this char from buffer 
  byte id=byte(buff.charAt(0)); //get the id from the first char of buffer
  buff.remove(0,1); //remove the first char. we don't need any more
  if ((byte(task[0].charAt(0)) + id) == 255)  //if the task id and response id are inverts
  {
    task[0]="";task[1]="";
    return buff;    //return
  }
  else
  {
    Serial.println("Old datas:\n");   //else this are old datas. Read to wrong
    wrong=buff.substring(1);
    Serial.println(wrong);
  }
  return "-1";  //this can not happen
}

void wifi(byte id,String data[])  //function wifi with arguments
{
  String output=String(char(id)); //add the converted id to output
  task[0]=output;
  for(int k=0;k<sizeof(data);k++)   //devide arguments with a "\t" char
    output+=data[k]+"\t";
  task[1]=output.substring(1);  
  esp.println(output);  //send datas to esp
}
void wifi(byte id)    //This is the same as the previous one, without arguments
{
  String output=String(char(id));
  task[0]=output;
  esp.println(output);
}
