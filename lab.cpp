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
bool Lab::ajouter_chahd()
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
QSqlQueryModel* Lab::afficher_chahd() { //afficher des données sous forme de table.
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LABORATOIRES");
    model->setHeaderData(0,Qt::Horizontal,QObject:: tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject:: tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject:: tr("localisation"));
    model->setHeaderData(3,Qt::Horizontal,QObject:: tr("status"));
    model->setHeaderData(4,Qt::Horizontal,QObject:: tr("contact"));

    return model;  //retourn un pointeur sur qslquery
}

bool Lab::supprimer_chahd(int id) {
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
bool Lab::modifier_chahd(int id) {
    QSqlQuery query;
    query.prepare("UPDATE LABORATOIRES SET NOM_LAB = :nom, LOCALISATION_LAB = :localisation, STATUS = :statut, CONTACT = :contact WHERE ID_LAB = :id");

    query.bindValue(":nom", nom_lab);
    query.bindValue(":localisation", localisation_lab);
    query.bindValue(":statut", status);
    query.bindValue(":contact", contact);
    query.bindValue(":id", id);

    return query.exec();
}

QMap<QString, int> Lab::getStatistiquesParstatus_chahd() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT STATUS, COUNT(*) FROM LABORATOIRES GROUP BY STATUS");

    while (query.next()) {
        QString type = query.value(0).toString(); //recupere la stat
        int count = query.value(1).toInt(); //counr le stat
        stats[type] = count; //ajout
    }

    return stats;
}


//fonctionalite de chatbot



// Fonction d'extraction d'informations sans imposer un format strict
bool extraireInfosAjoutModif(const QString &commande, int &id, QString &nom, QString &localisation, QString &status, QString &contact)
{
    QRegularExpression regex(R"(id\s+(\d+)\s+nom\s+(.+?)\s+localisation\s+(.+?)\s+status\s+(.+?)\s+contact\s+(\d+))", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(commande);

    if (match.hasMatch()) {
        id = match.captured(1).toInt();
        nom = match.captured(2).trimmed();
        localisation = match.captured(3).trimmed();
        status = match.captured(4).trimmed();
        contact = match.captured(5).trimmed();
        return true;
    }

    return false;
}

QSqlQueryModel* Lab::analyserCommande(const QString &commande)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString cmd = commande.toLower();

    // Ajout ou modification
    if (cmd.startsWith("ajouter") || cmd.startsWith("modifier")) {
        int id;
        QString nom, localisation, status, contact;

        if (!extraireInfosAjoutModif(commande, id, nom, localisation, status, contact)) {
            QMessageBox::warning(nullptr, "Erreur", "ID manquant ou invalide. Veuillez entrer :\n"
                                                    "ajouter id 1 nom BioX localisation Tunis status Actif contact 12345678");
            return model;
        }

        QSqlQuery query;
        if (cmd.startsWith("ajouter")) {
            query.prepare("INSERT INTO LABORATOIRES (ID_LAB, NOM_LAB, LOCALISATION_LAB, STATUS, CONTACT) "
                          "VALUES (:id, :nom, :localisation, :status, :contact)");
        } else {
            query.prepare("UPDATE LABORATOIRES SET "
                          "NOM_LAB = :nom, LOCALISATION_LAB = :localisation, STATUS = :status, CONTACT = :contact "
                          "WHERE ID_LAB = :id");
        }

        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":localisation", localisation);
        query.bindValue(":status", status);
        query.bindValue(":contact", contact);

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        } else {
            QMessageBox::information(nullptr, "Succès", cmd.startsWith("ajouter") ?
                                                            "Laboratoire ajouté avec succès." :
                                                            "Laboratoire modifié avec succès.");
        }

        model->setQuery("SELECT * FROM LABORATOIRES");
        return model;
    }

    // Suppression
    if (cmd.startsWith("supprimer")) {
        QStringList parts = commande.split(" ");
        if (parts.size() >= 2) {
            bool ok;
            int id = parts[1].toInt(&ok);
            if (ok) {
                QSqlQuery query;
                query.prepare("DELETE FROM LABORATOIRES WHERE ID_LAB = :id");
                query.bindValue(":id", id);
                if (!query.exec()) {
                    QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
                } else {
                    QMessageBox::information(nullptr, "Succès", "Laboratoire supprimé.");
                }
            } else {
                QMessageBox::warning(nullptr, "Erreur", "ID invalide pour suppression.");
            }
        }
        model->setQuery("SELECT * FROM LABORATOIRES");
        return model;
    }

    // Afficher tous
    if (cmd.contains("afficher tous")) {
        model->setQuery("SELECT * FROM LABORATOIRES");
        return model;
    }

    // Afficher un seul
    if (cmd.contains("afficher")) {
        QStringList parts = commande.split(" ");
        for (const QString &part : parts) {
            bool ok;
            int id = part.toInt(&ok);
            if (ok) {
                model->setQuery("SELECT * FROM LABORATOIRES WHERE ID_LAB = " + QString::number(id));
                return model;
            }
        }
    }

    afficherAide();
    return model;
}
void Lab::afficherAide() {
    QString aide =
        "Commande non reconnue.\n\n"
        "Voici quelques exemples de commandes valides :\n"
        " - Ajouter : ajouter id 1 nom BioTech localisation Tunis status Actif contact 12345678\n"
        " - Modifier : modifier id 1 nom BioX status Inactif contact 87654321\n"
        " - Supprimer : supprimer 1\n"
        " - Afficher tous : afficher tous\n"
        " - Afficher un : afficher 1\n";
    QMessageBox::warning(nullptr, "Commande non reconnue", aide);
}


// Ajout d'un laboratoire
void Lab::ajouterLaboratoire_chahd(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact)
{
    // Initialisation des attributs du laboratoire
    setId(id);
    setNom(nom);
    setLocalisation(localisation);
    setStatus(status);
    setContact(contact);

    if (ajouter_chahd()) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire ajouté avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de l'ajout du laboratoire");
    }
}

// Suppression d'un laboratoire
void Lab::supprimerLaboratoire_chahd(int id)
{
    setId(id);

    if (supprimer_chahd(id)) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire supprimé avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de la suppression du laboratoire");
    }
}

// Modification d'un laboratoire
void Lab::modifierLaboratoire_chahd(int id, const QString &nom, const QString &localisation, const QString &status, const QString &contact)
{
    setId(id);
    setNom(nom);
    setLocalisation(localisation);
    setStatus(status);
    setContact(contact);

    if (modifier_chahd(id)) {
        QMessageBox::information(nullptr, "Succès", "Laboratoire modifié avec succès");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de la modification du laboratoire");
    }
}

// Affichage de tous les laboratoires
void Lab::afficherTousLesLaboratoires_chahd()
{
    QSqlQueryModel *model = afficher_chahd();
    if (model != nullptr) {
        QMessageBox::information(nullptr, "Laboratoires", "Tous les laboratoires sont affichés");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Échec de l'affichage des laboratoires.");
    }
}

// Affichage d'un laboratoire par ID
QSqlQueryModel* Lab::afficherLaboratoireParId_chahd(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM laboratoires WHERE ID_LAB = :id");

    query.bindValue(":id", id);
    query.exec();

    auto* model = new QSqlQueryModel();
    model->setQuery(std::move(query)); // ✅ On utilise std::move ici
    return model;

}
