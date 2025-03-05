#ifndef VACCIN_H
#define VACCIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Vaccin {
private:
    int id_vac;
    QString nom_vac;
    QString type_vac;
    QString fabricant_vac;
    QString date_fabrication;
    QString date_expiration;
    float temperature_conservation;
    QString pays_origine;
    int stock;

public:
    // Constructeurs
    Vaccin();
    Vaccin(int, QString, QString, QString, QString, QString, float, QString, int);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getType() const;
    QString getFabricant() const;
    QString getDateFabrication() const;
    QString getDateExpiration() const;
    float getTemperature() const;
    QString getPaysOrigine() const;
    int getStock() const;

    // Setters
    void setId(int);
    void setNom(QString);
    void setType(QString);
    void setFabricant(QString);
    void setDateFabrication(QString);
    void setDateExpiration(QString);
    void setTemperature(float);
    void setPaysOrigine(QString);
    void setStock(int);

    // CRUD Operations
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* afficher();
};


#endif // VACCIN_H
