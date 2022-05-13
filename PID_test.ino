
#define Kp 30
#define Ki 100
#define Kd 0.3
#define target 2.5

#define AA

float duty = 0;
#ifdef AA
float duty2 = 0;
float duty3 = 0;
float duty4 = 0;
#endif
void Duty_control();

void setup()
{
    Serial.begin(9600); // initialize Serial communication
    pinMode(3, OUTPUT);
#ifdef AA
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
#endif
}

void loop()
{
    Duty_control();
}

void Duty_control()
{
    static float vol = 0;
    static unsigned long preTime = 0;
    static float preP = 0;
    double dt;
    float P, I, D;
#ifdef AA
    static float vol2 = 0;
    static unsigned long preTime2 = 0;
    static float preP2 = 0;
    float P2, I2, D2;

    static float vol3 = 0;
    static unsigned long preTime3 = 0;
    static float preP3 = 0;
    float P3, I3, D3;

    static float vol4 = 0;
    static unsigned long preTime4 = 0;
    static float preP4 = 0;
    float P4, I4, D4;
#endif

    analogWrite(3, duty);
#ifdef AA
    analogWrite(9, duty2);
    analogWrite(10, duty3);
    analogWrite(11, duty4);
#endif

    for (int i = 0; i < 1000; i++)
    {
        vol += analogRead(A0);
    }
    vol = (vol / 1000.0f) * 5.0f / 1024.0f;
    dt = (micros() - preTime) / (double)1000000;
    preTime = micros();

    P = target - vol;
    //  I += P * dt;
    //  D  = (P - preP) / dt;
    preP = P;
    duty += Kp * P;

#ifdef AA
    for (int i = 0; i < 1000; i++)
    {
        vol2 += analogRead(A1);
    }
    vol2 = (vol2 / 1000.0f) * 5.0f / 1024.0f;
    dt = (micros() - preTime2) / (double)1000000;
    preTime2 = micros();

    P2 = target - vol2;
    I2 += P2 * dt;
    //  D2  = (P2 - preP2) / dt;
    //  preP2 = P2;
    duty2 += Kp * P2 + Ki * I2;

    for (int i = 0; i < 1000; i++)
    {
        vol3 += analogRead(A3);
    }
    vol3 = (vol3 / 1000.0f) * 5.0f / 1024.0f;
    dt = (micros() - preTime3) / (double)1000000;
    preTime3 = micros();

    P3 = target - vol3;
    //  I3 += P3 * dt;
    D3 = (P3 - preP3) / dt;
    preP3 = P3;
    duty3 += Kp * P3 + Kd * D3;

    for (int i = 0; i < 1000; i++)
    {
        vol4 += analogRead(A5);
    }
    vol4 = (vol4 / 1000.0f) * 5.0f / 1024.0f;
    dt = (micros() - preTime4) / (double)1000000;
    preTime4 = micros();

    P4 = target - vol4;
    I4 += P4 * dt;
    D4 = (P4 - preP4) / dt;
    preP4 = P4;
    duty4 += Kp * P4 + Ki * I4 + Kd * D4;

#endif

    Serial.print(target);
    Serial.print(",");
    Serial.print(vol);
#ifdef AA
    Serial.print(",");
    Serial.print(vol2);
    Serial.print(",");
    Serial.print(vol3);
    Serial.print(",");
    Serial.println(vol4);
#endif
}
