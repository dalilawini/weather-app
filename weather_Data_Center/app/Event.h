#ifndef Event_H
#define Event_H

typedef void (*SensorCallback)(float temp, float hum);

class Event {

public:
    static void subscribe(SensorCallback cb);
    static void publish(float temp, float hum);

private:
    static SensorCallback subscribers[5];
    static int count;
};

#endif