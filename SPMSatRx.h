#ifndef SMP_SAT_RX_H
#define SPM_SAT_RX_H
#include <Arduino.h>
#define NUM_OF_BIND_PULSES 9
class SPMSatRx
{
public:
    SPMSatRx(int pin, Stream *input, int numOfChannels);
    void bind();
    bool read();
    float getChannel(int channelId);
    const int numOfChannels;

private:
    int pin;
    Stream *input;

    bool getTrans();
    short inData[16];
    short i;
    short inByte;

    short chVal[9];
    unsigned short tempData;
    unsigned short temp;
    unsigned short tempId;
    unsigned short tempVal;
    unsigned long time;
};
#endif