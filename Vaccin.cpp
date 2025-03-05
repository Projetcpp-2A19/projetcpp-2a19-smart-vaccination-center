#include "Vaccin.h"

Vaccin::Vaccin() {}

Vaccin::Vaccin(int id, QString nom, QString type, QString fabricant, QString dateFab, QString dateExp, float temp, QString pays, int stockQty)
    : id_vac(id), nom_vac(nom), type_vac(type), fabricant_vac(fabricant), date_fabrication(dateFab), date_expiration(dateExp), temperature_conservation(temp), pays_origine(pays), stock(stockQty) {}

int Vaccin::getId() const { return id_vac; }
QString Vaccin::getNom() const { return nom_vac; }
QString Vaccin::getType() const { return type_vac; }
QString Vaccin::getFabricant() const { return fabricant_vac; }
QString Vaccin::getDateFabrication() const { return date_fabrication; }
QString Vaccin::getDateExpiration() const { return date_expiration; }
float Vaccin::getTemperature() const { return temperature_conservation; }
QString Vaccin::getPaysOrigine() const { return pays_origine; }
int Vaccin::getStock() const { return stock; }

void Vaccin::setId(int id) { id_vac = id; }
void Vaccin::setNom(QString nom) { nom_vac = nom; }
void Vaccin::setType(QString type) { type_vac = type; }
void Vaccin::setFabricant(QString fabricant) { fabricant_vac = fabricant; }
void Vaccin::setDateFabrication(QString dateFab) { date_fabrication = dateFab; }
void Vaccin::setDateExpiration(QString dateExp) { date_expiration = dateExp; }
void Vaccin::setTemperature(float temp) { temperature_conservation = temp; }
void Vaccin::setPaysOrigine(QString pays) { pays_origine = pays; }
void Vaccin::setStock(int stockQty) { stock = stockQty; }

bool Vaccin::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO VACCINS (id_vac, nom_vac, type_vac, fabricant_vac, date_fabrication, date_expiration, temperature_conservation, pays_origine, stock) "
                  "VALUES (:id, :nom, :type, :fabricant, :dateFab, :dateExp, :temperature, :pays, :stock)");
    query.bindValue(":id", id_vac);
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

bool Vaccin::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE VACCINS SET nom_vac=:nom, type_vac=:type, fabricant_vac=:fabricant, date_fabrication=:dateFab, date_expiration=:dateExp, temperature_conservation=:temperature, pays_origine=:pays, stock=:stock WHERE id_vac=:id");
    query.bindValue(":id", id);
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

QSqlQueryModel* Vaccin::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VACCINS");
    return model;
}
