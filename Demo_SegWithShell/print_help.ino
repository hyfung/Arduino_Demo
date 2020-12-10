void print_help(){
  Serial.println("Instruction Format: XXFNNN");
  Serial.println("Example: 03H / 02P240");
  Serial.println("H: Set Pin to High");
  Serial.println("L: Set Pin to Low");
  Serial.println("I: Set pin to Input");
  Serial.println("O: Set pin to Output");
  Serial.println("P: Set PWM");
  Serial.println("R: Digital Read");
  Serial.println("A: Analog Read");
  Serial.println("S: Poll Pin Status");
  Serial.println("D: Delay - XXDYYY\\n");
  Serial.println("X: Reset*");
  Serial.println("?: Print Help*");
  Serial.println("T: Toggle Return Msg*");
  Serial.println("Credits: Jerry Fung");
}

void indepth_help(){
  
}

