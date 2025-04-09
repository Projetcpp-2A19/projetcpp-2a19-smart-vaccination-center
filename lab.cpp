#include "lab.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QString>
#include <QSqlError>
#include <QRegularExpression>
#include <QMessageBox>
#include <QRegularExpression>

// Constructeur avec paramètres
// Constructor implementation
Lab::Lab(int id, QString nom, QString localisation, QString status, QString contact)
    : id_lab(id), nom_lab(nom), localisation_lab(localisation), status(status), contact(contact)
{
}
Lab::Lab() {
    id_lab = 0;
    nom_lab = "";
    localisation_lab = "";
    status = "";
    contact = "";
}
// Or initialize members explicitly if needed
// Getters
// Implement remaining methods from lab.h
int Lab::getId() const { return id_lab; }
QString Lab::getNom() const { return nom_lab; }
QString Lab::getLocalisation() const { return localisation_lab; }
QString Lab::getStatus() const { return status; }
QString Lab::getContact() const { return contact; }

void Lab::setId(int id) { id_lab = id; }
void Lab::setNom(const QString &nom) { nom_lab = nom; }
void Lab::setLocalisation(const QString &localisation) { localisation_lab = localisation; }
void Lab::setStatus(const QString &status) { this->status = status; }
void Lab::setContact(const QString &contact) { this-> contact = contact; }


// Ajouter un laboratoire
bool Lab::ajouter()
{

    QSqlQuery query;  //class qt pour executr les reqeutte sql
    query.prepare("INSERT INTO LABORATOIRES (ID_LAB, NOM_LAB, LOCALISATION_LAB, STATUS, CONTACT) "
                  "VALUES (:id, :nom, :localisation, :status, :contact)");
    query.bindValue(":id", id_lab);
    query.bindValue(":nom", nom_lab);
    query.bindValue(":localisation", localisation_lab);
    query.bindValue(":status", status);
    query.bindValue(":contact", contact);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de l'ajout du laboratoire :" << query.lastError().text();
        return false;
    }

    return true;
}

// Afficher les laboratoires
QSqlQueryModel* Lab::afficher() { //afficher des données sous forme de table.
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LABORATOIRES");
    model->setHeaderData(0,Qt::Horizontal,QObject:: tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject:: tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject:: tr("localisation"));
    model->setHeaderData(3,Qt::Horizontal,QObject:: tr("status"));
    model->setHeaderData(4,Qt::Horizontal,QObject:: tr("contact"));

    return model;  //retourn un pointeur sur qslquery
}

bool Lab::supprimer(int id) {
    QSqlQuery query;  //class qt pour executr les reqeutte sql
    query.prepare("DELETE FROM LABORATOIRES WHERE ID_LAB = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la suppression :" << query.lastError().text();
        return false;
    }

    return true;
}

// Modifier un laboratoire
bool Lab::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE LABORATOIRES SET NOM_LAB = :nom, LOCALISATION_LAB = :localisation, STATUS = :statut, CONTACT = :contact WHERE ID_LAB = :id");

    query.bindValue(":nom", nom_lab);
    query.bindValue(":localisation", localisation_lab);
    query.bindValue(":statut", status);
    query.bindValue(":contact", contact);
    query.bindValue(":id", id);

    return query.exec();
}

QMap<QString, int> Lab::getStatistiquesParstatus() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT STATUS, COUNT(*) FROM LABORATOIRES GROUP BY STATUS");

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[type] = count;
    }

    return stats;
}


//fonctionalite de chatbot



// Fonction d'extraction d'informations sans imposer un format strict
bool extraireInfosAjoutModif(const QString &commande, int &id, QString &nom, QString &localisation, QString &status, QString &contact) {
    QRegularExpression regexId(R"((?:id|numéro|n°)\s*(\d+))", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression regexNom(R"((?:nom|appellation|titre)\s*[:=]?\s*([\w\s]+))", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression regexLoc(R"((?:localisation|ville|basé à|lieu)\s*[:=]?\s*([\w\s]+))", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression regexStat(R"((?:status|statut|état)\s*[:=]?\s*([\w\s]+))", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression regexContact(R"((?:contact|tél|tel|numéro de téléphone)\s*[:=]?\s*(\d{8,15}))", QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch matchId = regexId.match(commande);
    QRegularExpressionMatch matchNom = regexNom.match(commande);
    QRegularExpressionMatch matchLoc = regexLoc.match(commande);
    QRegularExpressionMatch matchStat = regexStat.match(commande);
    QRegularExpressionMatch matchContact = regexContact.match(commande);

    if (matchId.hasMatch() && matchNom.hasMatch() && matchLoc.hasMatch() && matchStat.hasMatch() && matchContact.hasMatch()) {
        id = matchId.captured(1).toInt();
        nom = matchNom.captured(1).trimmed();
        localisation = matchLoc.captured(1).trimmed();
        status = matchStat.captured(1).trimmed();
        contact = matchContact.captured(1).trimmed();
        return true;
    }
    return false;
}

void Lab::analyserCommande(const QString &commande) {
    QString lowerCmd = commande.toLower();
    int id;
    QString nom, localisation, status, contact;

    if (lowerCmd.contains("ajoute") || lowerCmd.contains("ajouter")) {
        if (extraireInfosAjoutModif(commande, id, nom, localisation, status, contact)) {
            ajouterLaboratoire(id, nom, localisation, status, contact);
        } else {
            QMessageBox::warning(nullptr, "Format incorrect", "Merci de préciser l'ID, le nom, la localisation, le statut et le contact.");
        }
    }
    else if (lowerCmd.contains("modifie") || lowerCmd.contains("modifier") || lowerCmd.contains("change")) {
        if (extraireInfosAjoutModif(commande, id, nom, localisation, status, contact)) {
            modifierLaboratoire(id, nom, localisation, status, contact);
        } else {
            QMessageBox::warning(nullptr, "Format incorrect", "Merci de préciser l'ID, le nom, la localisation, le statut et le contact.");
        }
    }
    else if (lowerCmd.contains("supprime") || lowerCmd.contains("enlever") || lowerCmd.contains("delete")) {
        QRegularExpression regexSupp(R"((\d+))");
        QRegularExpressionMatch match = regexSupp.match(commande);
        if (match.hasMatch()) {
            supprimerLaboratoire(match.captured(1).toInt());
        } else {
            QMessageBox::warning(nullptr, "Commande invalide", "Spécifiez un ID pour supprimer.");
        }
    }
    else if (lowerCmd.contains("affiche") || lowerCmd.contains("voir") || lowerCmd.contains("montre")) {
        if (lowerCmd.contains("tous")) {
            afficherTousLesLaboratoires();
        } else {
            QRegularExpression regexId(R"((\d+))");
            QRegularExpressionMatch match = regexId.match(commande);
            if (match.hasMatch()) {
                afficherLaboratoireParId(match.captured(1).toInt());
            } else {
                QMessageBox::warning(nullptr, "Commande invalide", "Spécifiez un ID valide.");
            }
        }
    }
    else {
        QMessageBox::warning(nullptr, "Commande non reconnue", "Essayez une commande valide comme 'ajoute', 'supprime', 'modifie' ou 'affiche'.");
    }
}
// Ajout d'un laboratoire
void Lab::ajouterLaboratoire(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact)
{
    // Initialisation des attributs du laboratoire
    setId(id);
    setNom(nom);
    setLocalisation(localisation);
    setStatus(status);
    setContact(contact);

    if (ajouter()) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire ajouté avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de l'ajout du laboratoire");
    }
}

// Suppression d'un laboratoire
void Lab::supprimerLaboratoire(int id)
{
    setId(id);

    if (supprimer(id)) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire supprimé avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de la suppression du laboratoire");
    }
}

// Modification d'un laboratoire
void Lab::modifierLaboratoire(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact)
{
    setId(id);
    setNom(nom);
    setLocalisation(localisation);
    setStatus(status);
    setContact(contact);

    if (modifier(id)) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire modifié avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de la modification du laboratoire");
    }
}

// Affichage de tous les laboratoires
void Lab::afficherTousLesLaboratoires()
{
    QSqlQueryModel *model = afficher();
    if (model != nullptr) {
        QMessageBox::information(nullptr, "Laboratoires", "Tous les laboratoires sont affichés");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de l'affichage des laboratoires.");
    }
}

// Affichage d'un laboratoire par ID
QSqlQueryModel* Lab::afficherLaboratoireParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM laboratoires WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Erreur lors de l'exécution de la requête.");
        delete model;
        return nullptr;
    }

    return model;
}
