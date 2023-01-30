const int Flushecho = 4;
const int Flushtrig = 3;
const int Sink = 2;
const int Doorecho = 6;
const int Doortrig = 5;

bool event = false;
bool stinky = true;

String command;   //I smoke so much crack!!!!!!!!!!!!!!!!!!!!!!!!!

void setup() {
  pinMode(Flushtrig, OUTPUT); //Flush trig
  pinMode(Flushecho, INPUT); //Flush echo
  pinMode(Sink, INPUT); //Sink
  pinMode(Doortrig, OUTPUT); //Door trig
  pinMode(Doorecho, INPUT); //Door echo
  Serial.begin(9600);
}
                  //To do: Google "How to buy crack legally"
void loop() {
  digitalWrite(Flushtrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Flushtrig,LOW);
  
  long durationF = pulseIn(Flushecho,HIGH);
  int distanceF = (durationF/2) / 28.5;

  digitalWrite(Doortrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Doortrig,LOW);

  long durationD = pulseIn(Doorecho,HIGH);
  int distanceD = (durationD/2) / 28.5;
  
  int val = digitalRead(Sink);  
  
  if (distanceF <=5){
    event = true;
    }
  if (val == 0){
    stinky = false;
    }
  if (distanceD >= 20 && stinky == true && event == true){
    Serial.println("1");
    command = Serial.readStringUntil('\n');
    command.trim();
    event = false;
    delay(2500);
    }
  if (distanceD >= 20 && stinky == false && event == true){
    event = false;
    delay(1000);
    }
  /*Serial.print("Flush distance: ");
  Serial.println(distanceF);
  Serial.print("Door distance: ");
  Serial.println(distanceD);
  Serial.println(val);*/
}