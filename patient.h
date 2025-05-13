#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QTableWidget>
#include <QSqlQueryModel>

class Patient
{
public:
    // Constructeurs
    Patient();
    Patient(int id, QString nom, QString prenom, QDate dateNaissance, QString email,
            QString genre, QString adresse, QString groupSanguin, int tel);

    // Getters & Setters
    int getId() const;
    void setId(int id);
    QString getNom() const;
    void setNom(const QString &nom);
    QString getPrenom() const;
    void setPrenom(const QString &prenom);
    QDate getDateNaissance() const;
    void setDateNaissance(const QDate &dateNaissance);
    QString getEmail() const;
    void setEmail(const QString &email);
    QString getGenre() const;
    void setGenre(const QString &genre);
    QString getAdresse() const;
    void setAdresse(const QString &adresse);
    QString getGroupSanguin() const;
    void setGroupSanguin(const QString &groupSanguin);


    // CRUD Operations
    bool ajouter();
    void afficher(QTableWidget* tableWidget);
    void afficherSpecifique(QTableWidget* tableWidget, const QString& filtreNom);
    bool supprimerPatient(int row);
    bool modifierPatient(int id, const QString& nom, const QString& prenom, const QDate& dateNaiss, const QString& email, const QString& genre, const QString& adresse, const QString& groupeSanguin,int tel);
    void afficherTrieParAnneeNaissance(QTableWidget* tableWidget, bool croissant);
private:
    int id;
    QString nom;
    QString prenom;
    QDate dateNaissance;
    QString email;
    QString genre;
    QString adresse;
    QString groupSanguin;
    int tel;
};

#endif // PATIENT_H
