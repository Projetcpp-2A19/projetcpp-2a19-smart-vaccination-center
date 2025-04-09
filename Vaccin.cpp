#include "Vaccin.h"
#include <QMessageBox>
#include <qsqlerror>

Vaccin::Vaccin() {}

Vaccin::Vaccin(int id, QString nom, QString type, QString fabricant, QDate dateFab, QDate dateExp, float temp, QString pays, int stockQty)
    : id_vac(id), nom_vac(nom), type_vac(type), fabricant_vac(fabricant), date_fabrication(dateFab), date_expiration(dateExp), temperature_conservation(temp), pays_origine(pays), stock(stockQty) {}

int Vaccin::getId() const { return id_vac; }
QString Vaccin::getNom() const { return nom_vac; }
QString Vaccin::getType() const { return type_vac; }
QString Vaccin::getFabricant() const { return fabricant_vac; }
QDate Vaccin::getDateFabrication() const { return date_fabrication; }
QDate Vaccin::getDateExpiration() const { return date_expiration; }
float Vaccin::getTemperature() const { return temperature_conservation; }
QString Vaccin::getPaysOrigine() const { return pays_origine; }
int Vaccin::getStock() const { return stock; }

void Vaccin::setId(int id) { id_vac = id; }
void Vaccin::setNom(QString nom) { nom_vac = nom; }
void Vaccin::setType(QString type) { type_vac = type; }
void Vaccin::setFabricant(QString fabricant) { fabricant_vac = fabricant; }
void Vaccin::setDateFabrication(QDate dateFab) { date_fabrication = dateFab; }
void Vaccin::setDateExpiration(QDate dateExp) { date_expiration = dateExp; }
void Vaccin::setTemperature(float temp) { temperature_conservation = temp; }
void Vaccin::setPaysOrigine(QString pays) { pays_origine = pays; }
void Vaccin::setStock(int stockQty) { stock = stockQty; }

bool Vaccin::ajouter() {
    QSqlQuery query;

    // Get the next available ID from a sequence
    query.prepare("SELECT NVL(MAX(id_vac), 0) + 1 FROM vaccins");
    if (!query.exec() || !query.next()) {
        return false;  // If the query fails, return false
    }

    int newId = query.value(0).toInt();  // Retrieve the new ID

    query.prepare("INSERT INTO VACCINS (id_vac, nom_vac, type_vac, fabricant_vac, date_fabrication, date_expiration, temperature_conservation, pays_origin, stock) "
                  "VALUES (:id, :nom, :type, :fabricant, :dateFab, :dateExp, :temperature, :pays, :stock)");
    query.bindValue(":id", newId);
    query.bindValue(":nom", nom_vac);
    query.bindValue(":type", type_vac);
    query.bindValue(":fabricant", fabricant_vac);
    query.bindValue(":dateFab", date_fabrication);
    query.bindValue(":dateExp", date_expiration);
    query.bindValue(":temperature", temperature_conservation);
    query.bindValue(":pays", pays_origine);
    query.bindValue(":stock", stock);
    return query.exec();
}

bool Vaccin::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM VACCINS WHERE id_vac = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Vaccin::modifier(int id, QString nom, QString type, QString fabricant, QDate date_fabrication, QDate date_expiration, float temp, QString pays, int stock) {
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE VACCINS SET nom_vac=:nom, type_vac=:type, fabricant_vac=:fabricant, date_fabrication=:dateFab, date_expiration=:dateExp, temperature_conservation=:temperature, pays_origin=:pays, stock=:stock WHERE id_vac=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":fabricant", fabricant);
    query.bindValue(":dateFab", date_fabrication);
    query.bindValue(":dateExp", date_expiration);
    query.bindValue(":temperature", temp);
    query.bindValue(":pays", pays);
    query.bindValue(":stock", stock);

    return query.exec();
}

QSqlQueryModel* Vaccin::afficher(const QString &orderBy)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Use the orderBy parameter in the SQL query
    QString queryString = QString("SELECT * FROM VACCINS ORDER BY %1").arg(orderBy);

    model->setQuery(queryString);

    return model;
}
Vaccin Vaccin::getVaccinById(int id)
{
    QSqlQuery query;
    Vaccin vac;

    query.prepare("SELECT * FROM vaccins WHERE id_vac = :id");
    query.bindValue(":id", id);

    // Exécution de la requête
    if (query.exec() && query.next())
    {
        vac.setId(query.value(0).toInt());
        vac.setNom(query.value(1).toString());
        vac.setType(query.value(2).toString());  // On ne vérifie plus ici
        vac.setFabricant(query.value(3).toString());
        vac.setDateFabrication(query.value(4).toDate());
        vac.setDateExpiration(query.value(5).toDate());
        vac.setTemperature(query.value(6).toDouble());
        vac.setPaysOrigine(query.value(7).toString());
        vac.setStock(query.value(8).toInt());
    }

    return vac;
}
bool Vaccin::checkIfIdExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id_vac FROM vaccins WHERE id_vac = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // ID exists
        return true;
    } else {
        // ID does not exist or query execution failed
        return false;
    }
}
QSqlQueryModel* Vaccin::searchByName(const QString &name) {
    QSqlQueryModel *model = new QSqlQueryModel();

    // SQL query to search by name
    QString queryString = QString("SELECT * FROM VACCINS WHERE nom_vac LIKE '%%1%' ORDER BY ID_VAC").arg(name);

    // Execute the query
    model->setQuery(queryString);

    return model;
}

