#ifndef MEDECIN_H
#define MEDECIN_H
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <string>

class Medecin {
private:
    int id_med;
    std::string nom_med;
    std::string prenom_med;
    std::string specialite_med;
    std::string contact_med;

public:

    // Constructeur
    Medecin(int id, const std::string& nom, const std::string& prenom,
            const std::string& specialite, const std::string& contact);

    // Getters
    int getId() const;
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getSpecialite() const;
    std::string getContact() const;

    bool ajouter();
    static QSqlQueryModel* afficher(); // Récupérer la liste des médecins

};

#endif // MEDECIN_H
