#include "sms.h"

SmsSender::SmsSender(const QString &apiKey, const QString &fromNumber, QObject *parent)
    : QObject(parent), m_apiKey(apiKey), m_fromNumber(fromNumber)
{
}

void SmsSender::sendSms(const QString &toNumber, const QString &message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Infobip API URL
    QUrl url("https://api.infobip.com/sms/1/text/single");

    // Set up the request
    QNetworkRequest request(url);

    // Set up the authentication header (Basic Authentication)
    request.setRawHeader("Authorization", "App " + m_apiKey.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Set up the JSON payload
    QJsonObject json;
    json["from"] = m_fromNumber;
    json["to"] = toNumber;
    json["text"] = message;

    QJsonDocument doc(json);
    QByteArray postData = doc.toJson();

    // Send the request
    QNetworkReply *reply = manager->post(request, postData);

    // Handle the reply
    QObject::connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully!";
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
