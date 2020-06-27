#include <SPMSatRx.h>
SPMSatRx::SPMSatRx(int pin, Stream *input, int numOfChannels) : numOfChannels(numOfChannels)
{
    this->pin = pin;
    this->input = input;
}
void SPMSatRx::bind()
{
    for (char i = 0; i < NUM_OF_BIND_PULSES; i++)
    {
        // no documentation of requirements for pulse width but 200us and a
        // duty cycle of 50% was tested succesfully
        digitalWrite(this->pin, LOW);
        delayMicroseconds(100);
        digitalWrite(this->pin, HIGH);
        delayMicroseconds(100);
    }
}
float SPMSatRx::getChannel(int channelId)
{
    return (float)this->chVal[channelId];
}
bool SPMSatRx::read(void)
{
    while (input->available() >= 16)
    {
        time = millis();
        for (i = 0; i < 16; i++)
        {
            inByte = input->read();
            inData[i] = inByte;
        }
    }

    for (i = 1; i < 8; i++)
    {
        temp = inData[i * 2] * 256 + inData[i * 2 + 1];

        tempId = temp >> 11;

        tempVal = temp << 5;
        tempVal = tempVal >> 5;

        if (tempId < numOfChannels)
        {
            chVal[tempId] = tempVal - 342;
        }
        else
        {
            //error, ignore ;)
        }
    }

    return getTrans();
}

bool SPMSatRx::getTrans()
{
    if (millis() - time > 1000)
    {
        return false;
    }
    else
    {
        return true;
    }
}