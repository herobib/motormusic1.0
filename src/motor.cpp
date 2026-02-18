#include <Arduino.h>

class Nema17{
    private:
        int stepPin;
        int dirPin;
        int enablePin;

        long duration;
        int frequency;

        unsigned long startTime;
        unsigned long lastStep;

        bool free = true;
    public:
        Nema17(int dirPin, int stepPin, int enablePin){
            this->stepPin = stepPin;
            this->dirPin = dirPin;
            this->enablePin = enablePin;
            duration = 0;
            pinMode(stepPin, OUTPUT);
            pinMode(dirPin, OUTPUT);
            pinMode(enablePin, OUTPUT);
            digitalWrite(enablePin, HIGH);
        }
        
        bool getFree(){
            return free;
        }
        void setNote(int frequency, long duration){
            this->duration = duration;
            this->frequency = frequency;

            startTime = micros();
            free = false;
        }
        
        void playNote(){
        unsigned long now = micros();
        if (now - startTime >= duration) {
            digitalWrite(enablePin, HIGH);
            free = true;
            return;
        }
        if (now - lastStep >= frequency) {
            digitalWrite(enablePin, LOW);
            digitalWrite(stepPin, HIGH);
            digitalWrite(stepPin, LOW);
            lastStep = now;
        }
    }
};
