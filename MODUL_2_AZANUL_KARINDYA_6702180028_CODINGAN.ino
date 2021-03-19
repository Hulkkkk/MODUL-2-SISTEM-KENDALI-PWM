// Modul Pratikum 2 - Sistem Kendali PWM
// Nama Tim : Hulkkkk
// Nama Anggota 1 : Azanul Karindya
// Versi Program : 1.0

//pin buat sensor analog
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//pin buat enable
int pinEnable =4;//Harus Diset HIGH apabila akan Diaktifkan
int pinEnable2 = 2;//Harus Diset HIGH apabila akan Diaktifkan

//pin buat motor kiri
int motor_kiri1 = 5;//Input motor Driver 1 L293D
int motor_kiri2 = 6;//Input motor Driver 2 L293D

//pin buat motor kanan
int motor_kanan1 = 3;//Input motor Driver 3 L293D
int motor_kanan2 = 11;//Input motor Driver 4 L293D

//Variable Bantuan
int x; 
int LastError = 0;

void setup(){
  //Pin Mode Input Sensor
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
   
  //Pin Mode Output Sensor
  pinMode(pinEnable, OUTPUT);
  pinMode(pinEnable2, OUTPUT);
  pinMode(motor_kiri1, OUTPUT);
  pinMode(motor_kiri2, OUTPUT);
  pinMode(motor_kanan1, OUTPUT);
  pinMode(motor_kanan2, OUTPUT);
  
  //Inisialiasai Komunikasi Serial
  Serial.begin(9600);  //Baud Rate Standar 9600
}

void readsensor() { 
  baca_sensor[0] = analogRead(sensor1);
  baca_sensor[1] = analogRead(sensor2);
  baca_sensor[2] = analogRead(sensor3);
  baca_sensor[3] = analogRead(sensor4);
  baca_sensor[4] = analogRead(sensor5);
  baca_sensor[5] = analogRead(sensor6);
  
  delay(1000);
  
  //Menampilkan data sensor ke serial Monitor
  //Data Sensor 1-6
  //Formatting Tampilan Data Sensor
  for(x=0; x<=5; x++){
    Serial.print("Sensor ");
    Serial.print(x+1);
    Serial.print(": ");
    Serial.println(baca_sensor[x]);
    Serial.print("\n");}
}

void loop(){
    
    readsensor();
    Serial.print("Nilai Last Error: ");
    Serial.println(LastError);
  
    //Sensor 1 dan 2 mendeteksi gelap, sisanya terang -->Duty cycle 0% motor kiri, 50% motor kanan
    if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
    }
    //Sensor 2 dan 3 mendeteksi gelap, sisanya terang --> Duty cycle 20% motor kiri, 50% motor kanan
    else if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
             baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
        
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.2*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
    }
    //Sensor 3 dan 4 mendeteksi gelap, sisanya terang  Duty cycle 60% pada kedua motor
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
        
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.6*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.6*255);
        analogWrite(motor_kanan2, 0);
    }
    //Sensor 4 dan 5 mendeteksi gelap, sisanya terang  Duty cycle 50% motor kiri, 20% motor kanan
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
             baca_sensor[4] < 34 && baca_sensor[5] > 34){
        //STOP CONDITION
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.2*255);
        analogWrite(motor_kanan2, 0);
    }
    //Sensor 5 dan 6 mendeteksi gelap, sisanya terang  Duty cycle 50% motor kiri, 0% motor kanan
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] < 34 && baca_sensor[5] < 34){
        //STOP CONDITION
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0);
        analogWrite(motor_kanan2, 0);
    }
    //Sensor 4 dan 5 mendeteksi gelap, sisanya terang  Duty cycle 50% motor kiri, 20% motor kanan
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
             baca_sensor[4] < 34 && baca_sensor[5] > 34){
        
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.2*255);
        analogWrite(motor_kanan2, 0);
    }
    //Semua sensor mendeteksi terang  Duty cycle kedua motor 0%
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0);
        analogWrite(motor_kanan2, 0);
    }
    //Error Sensor 1
     if (baca_sensor[0] < 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = -2");
       LastError = -2;
    }
    //Error Sensor 2
     if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.2*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = -1");
       LastError = -1;
    }
    //Error Sensor 3
     if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] < 34 || baca_sensor[3] < 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.6*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.6*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 0");
       LastError = 0;
    }
    //Error Sensor 4
     if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] > 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 1");
       LastError = 1;
    }
    //Error Sensor 5
     if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] < 34){
     
        digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.2*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 2");
       LastError = 2;
    }
}
