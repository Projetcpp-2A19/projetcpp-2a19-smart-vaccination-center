#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>
#include <QMap>

class Equipement {
private:
    int id_eqp;
    QString nom_eqp;
    QString type_eqp;
    QString statut_eqp;
    QDate date_maintenance_eqp;
    QString description_eqp;

public:
    // Constructeurs
    Equipement();
    Equipement(int id, QString nom, QString type, QString statut, QDate date_maintenance, QString description);

    // CRUD Functions
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(QString searchTerm);
    QString getEquipementsAsHTML();
    QMap<QString, int> getStatistiquesParType();
    bool setEnPanne(const QString &idEquipement);

    // Getters et Setters
    int getId() const;
    void setId(int id);
    QString getNom() const;
    void setNom(const QString &nom);
    QString getType() const;
    void setType(const QString &type);
    QString getStatut() const;
    void setStatut(const QString &statut);
    QDate getDateMaintenance() const;
    void setDateMaintenance(const QDate &date);
    void setDescription(const QString &description);
    QString getDescription() const;
};

#endif // EQUIPEMENTS_H
