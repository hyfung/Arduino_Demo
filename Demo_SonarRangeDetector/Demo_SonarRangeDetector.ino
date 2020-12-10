// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = A0;
const int echoPin = A1;
// Variables for the duration and the distance
long duration;
int distance;
inline int calculateDistance() __attribute__((always_inline));

void setup() {
  setup_led();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
}

void loop() {
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  //Serial.print(distance); // Sends the distance value into the Serial Port
  //Serial.print("\n"); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  update_led();

  Serial.println("{\"range\": %d }", distance);
}

// Function for calculating the distance measured by the Ultrasonic sensor
inline int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2 ;// + 3;
  return distance;
}
