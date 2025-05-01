#ifndef SMS1_H
#define SMS1_H
#include "QString"

class sms1
{
public:
    sms1();
    void sendSMS(const QString &to, const QString &message);
};

#endif // SMS1_H
