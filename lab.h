#ifndef LAB_H
#define LAB_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QMap>

class Lab
{
private:
    int id_lab;
    QString nom_lab;
    QString localisation_lab;
    QString status;

    QString contact;


public:
    Lab();
    Lab(int id ,QString nom, QString localisation, QString status,  QString contact);

    int getId() const;
    QString getLocalisation() const;
    QString getStatus() const;
    QString getNom() const;
    QString getContact() const;


    void setId(int id);
    void setLocalisation(const QString &localisation);
    void setStatus(const QString &status);
    void setNom(const QString &nom);
    void setContact(const QString &contact);
    //fonctionnalite de db
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);  //supp
    bool modifier(int id); //modif
    QMap<QString, int> getStatistiquesParstatus();

    // Fonctionnalité pour le chatbot (CRUD)
    QSqlQueryModel* analyserCommande(const QString &commande);
    void ajouterLaboratoire(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact);
    void supprimerLaboratoire(int id);
    void modifierLaboratoire(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact);
    void afficherAide();
    // Méthodes d'affichage
    void afficherTousLesLaboratoires();
    QSqlQueryModel* afficherLaboratoireParId(int id);



};

#endif // LAB_H
