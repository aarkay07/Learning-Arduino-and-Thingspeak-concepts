#include <mysql_connection.h>
/*
#include <mysql.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
*/
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  char host[] = "localhost";
  char user[] = "root";
  char pass[] = "";
  char db[] = "arduino";
  int isconnected = mysql_connect(host, user, pass, db);
  if(isconnected)
  {
    Serial.print("Connected to ");
    Serial.println(host);
  }
  else
  {
    Serial.println("Connection failed. ");
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  mysql_close();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&isconnected);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  cur_mem->execute("inserti into ultra values distance");

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  
}

