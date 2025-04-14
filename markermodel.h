#ifndef MARKERMODEL_H
#define MARKERMODEL_H

#include <QAbstractListModel>
#include <QGeoCoordinate>

class MarkerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MarkerRoles {
        CoordinateRole = Qt::UserRole + 1
    };

    MarkerModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadFromJson();
   Q_INVOKABLE void addLocation(const QString &localisation, double lat, double lon);

   // Q_INVOKABLE void geocodeAndAddLocation(const QString &localisation);
    Q_INVOKABLE void removeLocation(const QString &localisation);
    Q_INVOKABLE void addMarker(const QGeoCoordinate &coord);


private:
    QList<QGeoCoordinate> m_coordinates;

};

#endif // MARKERMODEL_H
