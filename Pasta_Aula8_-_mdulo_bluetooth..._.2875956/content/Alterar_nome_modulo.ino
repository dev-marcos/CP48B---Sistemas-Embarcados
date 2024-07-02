void setup() {
Serial.begin(9600);
delay(1000);
//Serial.write("AT+NAMEHC-06"); //padrao
Serial.write("AT+NAMEHC-06-MODULO6"); //
delay(1000);
}

void loop() {
delay(500);
Serial.println("teste");
}


