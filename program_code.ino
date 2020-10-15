/ **
      * Faculty of Mechanical Engineering, Computing and Electrical Engineering, University of Mostar
      * Final thesis - Control of DC motor speed using Arduino computer platform - Marcel Bandić
      * Code for Arduino Uno with ATmega328 microcontroller
      * Applied to H bridge
     ** /

#define Aulaz1 14      
#define Dulaz1 2      
#define Aulaz2 15    
#define Izlaz1a 3  
#define Izlaz1b 5    
#define Izlaz2a 6   
#define Izlaz2b 9    

// period in microseconds
#define T   1000    

// PID controller parameters
double Kp = 1;      
double Ki = 0.02;
double Kd = 0.005;

// tachogenerator parameters
double Kt = 1.8;


void setup() {
    
    // input variables
    pinMode(Aulaz1, INPUT);          
    pinMode(Dulaz1, INPUT);         
    pinMode(Dulaz1, INPUT_PULLUP);   
    pinMode(Aulaz2, INPUT);

    // variables pwm output
    pinMode(Izlaz1a, OUTPUT);       
    digitalWrite(Izlaz1a, LOW);    
    pinMode(Izlaz1b, OUTPUT);       
    digitalWrite(Izlaz1b, LOW);     
    pinMode(Izlaz2a, OUTPUT);      
    digitalWrite(Izlaz2a, LOW);     
    pinMode(Izlaz2b, OUTPUT);       
    digitalWrite(Izlaz2b, LOW);     

   // for serial communication with PC
   // Serial.begin(57600);
}

void loop() {
    unsigned int pg = Pot_get();
    unsigned int tg = Taho_get();
    unsigned int pidg = PID_gen(pg, tg);
    PWM_gen(pidg);
    // sending data to a PC
    // S_plot(pg, tg, pidg) ;
}

unsigned int Pot_get () {
    unsigned int a = analogRead(Aulaz1);     
    a = map(a, 0, 1023, 0, T);           
    return a;
}   


unsigned int Taho_get () {
    int b = analogRead(Aulaz2);
    if (b >=500 && b<=530)
      b=0;
    else {
      b -= 512;
      if (b < 0) 
        b *= -1;
      b *= 2;
      b *= Kt;
      if (b >= 1024)
        b = 1023;
    }
    b = map(b, 0, 1023, 0, T);
    return b; 
}   

double PID_gen(unsigned int a, unsigned int b){     

    unsigned long Time;
    double rTime, dGreska;
    int greska;
    static unsigned long pTime;
    static int pGreska;
    static double iGreska;

    Time = millis();                                
    rTime = (double)(Time - pTime);                
    greska = a - b;                                 
    iGreska += greska * rTime;                      
    dGreska = (greska - pGreska)/rTime;           
    double x = Kp*greska + Ki*iGreska + Kd*dGreska;   
    pGreska = greska;
    pTime = Time; 
    if (x >= T ) x = T;
    else if (x <= 0 ) x = 0;
    return x;
}  

void PWM_gen(unsigned int t1) {
    if (digitalRead(Dulaz1) == LOW) {    
        digitalWrite(Izlaz1a, HIGH);  
        digitalWrite(Izlaz2b, HIGH);          
        delayMicroseconds(t1);      
        digitalWrite(Izlaz1a, LOW);     
        digitalWrite(Izlaz2b, LOW);        
        delayMicroseconds(T - t1); 
    }

    else {
        digitalWrite(Izlaz2a, HIGH);  
        digitalWrite(Izlaz1b, HIGH);          
        delayMicroseconds(t1);      
        digitalWrite(Izlaz2a, LOW);    
        digitalWrite(Izlaz1b, LOW);        
        delayMicroseconds(T - t1); 
    }
}  
/*
// PC data sending function
void S_plot(unsigned int a, unsigned int b, unsigned int c) {
  Serial.print(a);
  Serial.print(" "); 
  Serial.print(b);
  Serial.print(" "); 
  Serial.println(c);
}
*/

