#ifndef VACCIN_H
#define VACCIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Vaccin {
    private:
        int id_vac;
        QString nom_vac;
        QString type_vac;
        QString fabricant_vac;
        QDate date_fabrication;
        QDate date_expiration;
        float temperature_conservation;
        QString pays_origine;
        int stock;

    public:
        // Constructeurs
        Vaccin();
        Vaccin(int, QString, QString, QString, QDate, QDate, float, QString, int);

        // Getters
        int getId() const;
        QString getNom() const;
        QString getType() const;
        QString getFabricant() const;
        QDate getDateFabrication() const;
        QDate getDateExpiration() const;
        float getTemperature() const;
        QString getPaysOrigine() const;
        int getStock() const;

        // Setters
        void setId(int);
        void setNom(QString);
        void setType(QString);
        void setFabricant(QString);
        void setDateFabrication(QDate);
        void setDateExpiration(QDate);
        void setTemperature(float);
        void setPaysOrigine(QString);
        void setStock(int);

        // CRUD Operations
        bool ajouter();
        bool supprimer(int);
        bool modifier(int, QString, QString, QString, QDate, QDate, float, QString, int);
        QSqlQueryModel* afficher(const QString &orderBy = "id_vac");
        Vaccin getVaccinById(int id);
        bool checkIfIdExists(int id);
        QSqlQueryModel* searchByName(const QString &name);
};


#endif // VACCIN_H
