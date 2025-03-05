#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QDate>
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class RendezVous {
private:
    int id_rdv;
    QDate date_rdv;
    QDate heure_rdv;
    QString priorite_rdv;
    QString status;
    int id_pat;

public:
    // Constructeurs
    RendezVous();
    RendezVous(int id, QDate date, QDate heure, QString priorite, QString stat, int idp);

    // Accesseurs (getters)
    int getIdRdv() const;
    QDate getDateRdv() const;
    QDate getHeureRdv() const;
    QString getPrioriteRdv() const;
    QString getStatus() const;
    int getIdpat() const;

    // Mutateurs (setters)
    void setIdRdv(int id);
    void setDateRdv(QDate date);
    void setHeureRdv(QDate heure);
    void setPrioriteRdv(QString priorite);
    void setStatus(QString stat);
    void setIdpat(int idp);

    // CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
};

#endif // RENDEZVOUS_H
