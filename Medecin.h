#ifndef MEDECIN_H
#define MEDECIN_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <regex>
#include <string>
#include <map>  // Pour utiliser std::map

class Medecin {
private:
    int id_med;
    std::string nom_med;
    std::string prenom_med;
    std::string specialite_med;
    std::string contact_med;
    std::string login_med;
    std::string mdp;
    std::string question;
    std::string reponse;

public:
    Medecin(); // Constructeur par défaut

    // Constructeur
    Medecin(int id, const std::string& nom, const std::string& prenom,
            const std::string& specialite, const std::string& contact,
            const std::string& mdp,const std::string& question, const std::string& reponse);

    // Getters
    int getId() const;
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getSpecialite() const;
    std::string getContact() const;
    std::string getMdp() const;
    std::string getQuestion() const;
    std::string getReponse() const;

    void setId(int id);
    void setNom(const std::string& nom);
    void setPrenom(const std::string& prenom);
    void setSpecialite(const std::string& specialite);
    void setContact(const std::string& contact);
    void setLogin(const std::string& login);
    void setMdp(const std::string& mdp);
    void setQuestion(const std::string& question);
    void setReponse(const std::string& reponse);


    bool ajouter();
    static QSqlQueryModel* afficher(); // Récupérer la liste des médecins
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel *tri_id();
    QSqlQueryModel *tri_nom();
    QSqlQueryModel *tri_prenom();
    QSqlQueryModel *chercher(int id_chercher);
    //static std::map<std::string, int> statistiquesParSpecialite();
    static std::map<std::string, int> statistiquesParSpecialite();

    static bool verifierChamps(int id, const std::string& nom, const std::string& prenom,
                               const std::string& specialite, const std::string& contact);
};

#endif // MEDECIN_H
