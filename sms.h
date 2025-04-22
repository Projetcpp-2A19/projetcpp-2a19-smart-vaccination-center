#ifndef SMS_H
#define SMS_H
#include <QtCore>
#include <QtNetwork>

class SmsSender : public QObject
{
    Q_OBJECT

public:
    explicit SmsSender(const QString &apiKey, const QString &fromNumber, QObject *parent = nullptr);
    void sendSms(const QString &toNumber, const QString &message);

private:
    QString m_apiKey;
    QString m_fromNumber;
};
#endif // SMS_H
