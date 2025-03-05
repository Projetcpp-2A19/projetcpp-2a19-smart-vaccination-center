#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

class Equipement {
private:
    int id_eqp;
    QString nom_eqp;
    QString type_eqp;
    QString statut_eqp;
    QDate date_maintenance_eqp;

public:
    // Constructeurs
    Equipement();
    Equipement(int id, QString nom, QString type, QString statut, QDate date_maintenance);

    // CRUD Functions
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* afficher();

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
};

#endif // EQUIPEMENTS_H
