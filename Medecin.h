#ifndef MEDECIN_H
#define MEDECIN_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <regex>
#include <string>

class Medecin {
private:
    int id_med;
    std::string nom_med;
    std::string prenom_med;
    std::string specialite_med;
    std::string contact_med;

public:
    Medecin(); // Constructeur par défaut

    // Constructeur
    Medecin(int id, const std::string& nom, const std::string& prenom,
            const std::string& specialite, const std::string& contact);

    // Getters
    int getId() const;
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getSpecialite() const;
    std::string getContact() const;
    void setId(int id);
    void setNom(const std::string& nom);
    void setPrenom(const std::string& prenom);
    void setSpecialite(const std::string& specialite);
    void setContact(const std::string& contact);


    bool ajouter();
    static QSqlQueryModel* afficher(); // Récupérer la liste des médecins
    bool supprimer(int id);
    bool modifier();

    static bool verifierChamps(int id, const std::string& nom, const std::string& prenom,
                               const std::string& specialite, const std::string& contact);
};

#endif // MEDECIN_H
