#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSignalBlocker>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QProcess>
#include <QDate>



//------------------------------------------------------------------------------------------------------------------MAIN
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);


    ui->lineEdit_54->setPlaceholderText("Recherche");  // Set search hint
    connect(ui->lineEdit_54, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_54_textChanged);
    ui->tableauEquipements->setModel(equipement.afficher()); // or trier("Par défaut")
    ui->tableauEquipements->setSortingEnabled(true);
    ui->tableauEquipements->sortByColumn(0, Qt::AscendingOrder); // optional default sort


    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableauEquipements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    updateTableView();

    ui->dateEdit_6->clear();             // Clear the date field (remains empty)
    ui->dateEdit_6->setEnabled(false);     // Disable user interaction
    ui->dateEdit_6->setVisible(false);
    ui->label_209->setVisible(false);


    int ret = A.connect_arduino();
    switch (ret) {
    case 0: qDebug() << "Arduino connecté sur :" << A.getarduino_port_name(); break;
    case 1: qDebug() << "Arduino détecté mais non connecté !"; break;
    case -1: qDebug() << "Arduino non disponible !"; break;
    }
    connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_fridge_status()));
    ui->tableau5->setModel(vac.afficher());


}

MainWindow::~MainWindow(){delete ui;}
void MainWindow::on_btnmedecin_clicked(){ui->sqs->setCurrentIndex(0);}
void MainWindow::on_btnpatient_clicked(){ui->sqs->setCurrentIndex(1);}
void MainWindow::on_btnlabo_clicked(){ui->sqs->setCurrentIndex(2);}
void MainWindow::on_btnequiprmrnt_clicked(){ui->sqs->setCurrentIndex(3);}
void MainWindow::on_btnvaccins_clicked(){ui->sqs->setCurrentIndex(4);}
void MainWindow::on_btnrendezv_clicked(){ui->sqs->setCurrentIndex(5);}
void MainWindow::on_btnuser_clicked(){ui->sqs->setCurrentIndex(6);}
void MainWindow::on_btnlabo2_clicked(){ui->sqs->setCurrentIndex(7);}
void MainWindow::on_btnlabo3_clicked(){ui->sqs->setCurrentIndex(8);}
void MainWindow::on_btnlabo4_clicked(){ui->sqs->setCurrentIndex(9);}
void MainWindow::on_btnmedecin2_clicked(){ui->sqs->setCurrentIndex(10);}
void MainWindow::on_btnpatient2_clicked(){ui->sqs->setCurrentIndex(11);}
void MainWindow::on_btnequiprmrnt2_clicked(){showStatistiques(); ui->sqs->setCurrentIndex(12);}
void MainWindow::on_btnvaccins2_clicked(){ui->sqs->setCurrentIndex(14);}
void MainWindow::on_btnrendezv2_clicked(){ui->sqs->setCurrentIndex(15);}
void MainWindow::on_btnrendezv3_clicked(){ui->sqs->setCurrentIndex(16);}









//------------------------------------------------------------------------------------------------------------------CRUD

void MainWindow::updateTableView() {
    QSqlQueryModel* model = equipement.afficher();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableauEquipements->setModel(proxyModel);
    ui->tableauEquipements->setSortingEnabled(true);
    ui->tableauEquipements->sortByColumn(0, Qt::AscendingOrder);  // Optional: Default sort by ID
}

void MainWindow::on_btnequipementAjouter_clicked() {
    QSqlQuery query;
    query.prepare("SELECT MAX(id_eqp) FROM EQUIPEMENTS");  // Get max ID
    query.exec();

    int id = 1;  // Default ID if the table is empty

    if (query.next() && !query.value(0).isNull()) {
        id = query.value(0).toInt() + 1;  // Assign max ID + 1
    }

    // Récupérer les valeurs de l'UI
    QString nom = ui->lineEdit_51->text();
    QString type = ui->comboBox_11->currentText();
    QString statut = ui->comboBox_13->currentText();
    QString description = ui->inputvoice->text();

    // Obtenir la date actuelle
    QDate dateMaintenance ;

    // Vérifier si le nom est vide
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom ne peut pas être vide !");
        return;
    }

    if (nom.length() > 30) {
        QMessageBox::warning(this, "Erreur", "Le nom ne doit pas dépasser 30 caractères !");
        return;
    }

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La description ne peut pas être vide !");
        return;
    }

    if (description.length() > 100) {
        QMessageBox::warning(this, "Erreur", "La description ne doit pas dépasser 100 caractères !");
        return;
    }

    // Vérifier si le nom existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE nom_eqp = :nom");
    checkQuery.bindValue(":nom", nom);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Un équipement avec ce nom existe déjà !");
        return;
    }

    // Créer l'objet Equipement avec le bon ID
    Equipement equip(id, nom, type, statut, dateMaintenance, description);

    // Ajouter dans la base de données
    if (equip.ajouter()) {
        QMessageBox::information(this, "Succès", "Équipement ajouté avec succès !");
        afficherEquipements();  // Refresh table after adding
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'équipement a échoué !");
    }
}

void MainWindow::afficherEquipements(){
    QSqlQueryModel* model = equipement.afficher();
    ui->tableauEquipements->setModel(model);  // Assign model to QTableView
}

void MainWindow::on_btnSupprimer_clicked() {
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 0)).toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Equipement equip;
        if (equip.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableView();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}

void MainWindow::on_btnModifier_clicked() {

    ui->dateEdit_6->setEnabled(true);
    ui->dateEdit_6->setVisible(true);
    ui->label_209->setVisible(true);

    // Retrieve the selected row
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un élément à modifier."));
        return;
    }

    // Get the record values from the table.
    currentId = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 0)).toInt();
    originalNom = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 1)).toString();
    originalType = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 2)).toString();
    originalStatut = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 3)).toString();
    originalDescription = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 5)).toString();

    QString dateStr = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 4)).toString();

    QDate maintenanceDate = QDate::fromString(dateStr, "dd-MM-yyyy");
    originalDate = maintenanceDate;

    if (maintenanceDate.isValid()) {
        ui->dateEdit_6->setDate(maintenanceDate);
        ui->dateEdit_6->setDisplayFormat("dd/MM/yyyy");
    } else {
        ui->dateEdit_6->clear();  // fallback if parsing fails
    }

    // Populate the other fields
    ui->lineEdit_51->setText(originalNom);

    // Set comboBox_11 (Type)
    if (originalType == "Machine")
        ui->comboBox_11->setCurrentIndex(0);
    else if (originalType == "Outil")
        ui->comboBox_11->setCurrentIndex(1);
    else if (originalType == "Stockage")
        ui->comboBox_11->setCurrentIndex(0);
    else
        ui->comboBox_11->setCurrentIndex(3);

    // Set comboBox_13 (Statut)
    if (originalStatut == "Inactif")
        ui->comboBox_13->setCurrentIndex(1);
    else
        ui->comboBox_13->setCurrentIndex(0);

    ui->inputvoice->setText(originalDescription);

    modificationInProgress = true; // Set the flag when modification starts
}

void MainWindow::on_btnConfirmerModifier_clicked() {
    // Ensure user clicked "Modifier" before confirming
    if (!modificationInProgress) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un équipement à modifier en cliquant sur 'Modifier'."));
        return;
    }

    // Retrieve new values from groupbox fields
    QString newNom = ui->lineEdit_51->text();
    QString newType = ui->comboBox_11->currentText();
    QString newStatut = ui->comboBox_13->currentText();
    QString newDescription = ui->inputvoice->text();

    // Here, we use the text of the dateEdit_6:
    QString dateText = ui->dateEdit_6->text().trimmed();
    QDate newDate;
    if (dateText.isEmpty()) {
        // If the field is empty, set newDate to an invalid date
        newDate = QDate();
    } else {
        newDate = ui->dateEdit_6->date();
    }

    // Check if no change was made
    if (newNom == originalNom && newType == originalType && newStatut == originalStatut && newDescription == originalDescription && newDate == originalDate) {
        QMessageBox::information(this, tr("Modification"), tr("Aucune modification apportée."));
        return;
    }

    // Validate the new name
    if (newNom.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne peut pas être vide !"));
        return;
    }
    if (newNom.length() > 30) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne doit pas dépasser 30 caractères !"));
        return;
    }

    // Check if the new name already exists in the database
    if (newNom != originalNom) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE nom_eqp = :nom");
        query.bindValue(":nom", newNom);
        if(query.exec() && query.next() && query.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Erreur"), tr("Un équipement avec ce nom existe déjà !"));
            return;
        }
    }

    if (newDescription.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La description ne peut pas être vide !");
        return;
    }

    if (newDescription.length() > 100) {
        QMessageBox::warning(this, "Erreur", "La description ne doit pas dépasser 100 caractères !");
        return;
    }

    Equipement equip(currentId, newNom, newType, newStatut, newDate, newDescription);
    if (equip.modifier(currentId)) {
        QMessageBox::information(this, tr("Modification"), tr("Modification réussie."));
        updateTableView();  // Refresh the table

        modificationInProgress = false; // Reset the flag after modification
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }

    ui->dateEdit_6->clear();             // Clear the date field (remains empty)
    ui->dateEdit_6->setEnabled(false);     // Disable user interaction
    ui->dateEdit_6->setVisible(false);
    ui->label_209->setVisible(false);
    ui->comboBox_11->setCurrentIndex(0);
    ui->comboBox_13->setCurrentIndex(0);
    ui->inputvoice->clear();
    ui->lineEdit_51->clear();
}



//------------------------------------------------------------------------------------------------------------------RECHERCHER

void MainWindow::on_lineEdit_54_textChanged(const QString &searchTerm) {
    if (searchTerm.trimmed().isEmpty()) {
        // If the search field is empty, show all equipment
        ui->tableauEquipements->setModel(equipement.afficher());
    } else {
        // Otherwise, filter based on search input
        ui->tableauEquipements->setModel(equipement.rechercher(searchTerm));
    }
}

//------------------------------------------------------------------------------------------------------------------PDF

void MainWindow::on_btnequiprmrnt4_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(equipement.getEquipementsAsHTML()); // Call the function from Equipement class
    doc.print(&printer);

    QMessageBox::information(this, "Succès", "PDF généré avec succès !");
}

//------------------------------------------------------------------------------------------------------------------STAT

void MainWindow::showStatistiques() {
    // Clear existing layout content
    if (ui->chartContainerType->layout()) {
        QLayout *layout = ui->chartContainerType->layout();
        while (QLayoutItem *item = layout->takeAt(0)) {
            if (QWidget *widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    } else {
        ui->chartContainerType->setLayout(new QVBoxLayout());
    }

    // 📊 Pie Chart (Type Distribution)
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = equipement.getStatistiquesParType();

    int total = 0;
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        total += it.value();  // Calculate total count of all equipment
    }

    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for equipment types!";
    } else {
        for (auto it = statsType.begin(); it != statsType.end(); ++it) {
            double percentage = (total > 0) ? (it.value() * 100.0 / total) : 0;  // Calculate percentage

            QPieSlice *slice = pieSeries->append(it.key(), it.value());

            // Set label format to show percentage
            slice->setLabel(QString("%1: %2%").arg(it.key()).arg(percentage, 0, 'f', 1));

            slice->setLabelVisible(true);  // Ensure label is visible

            // Add hover effect
            connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
                slice->setExploded(hovered);
                slice->setLabelFont(QFont("Arial", hovered ? 12 : 10, hovered ? QFont::Bold : QFont::Normal));
            });
        }
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);

    // Set Background Color 🎨
    pieChart->setBackgroundBrush(QBrush(QColor(234, 251, 255)));

    QChartView *chartView = new QChartView(pieChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartContainerType->layout()->addWidget(chartView);
}



//------------------------------------------------------------------------------------------------------------------Alert

void MainWindow::on_panneButton_clicked() {
    // Get the selected row from QTableView
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Aucune sélection"), tr("Veuillez sélectionner un équipement."));
        return;
    }

    // Get the model to extract data from the selected row
    QAbstractItemModel *model = ui->tableauEquipements->model();
    int row = index.row();

    // Get the equipment ID and name
    QString equipementID = model->data(model->index(row, 0)).toString();  // Column 1 = id_eqp
    QString equipementNom = model->data(model->index(row, 1)).toString(); // Column 2 = nom_eqp

    // Call the function to update the database
    Equipement equip;
    if (equip.setEnPanne(equipementID)) {
        QMessageBox::information(this, tr("Mise en panne"), tr("L'équipement a été marqué en panne."));
        updateTableView();  // Refresh the table from the database
        showPanneNotification(equipementNom);  // Show scrolling alert message
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de modifier le statut en panne."));
    }
}

void MainWindow::showPanneNotification(const QString &equipementNom) {
    QString alertText = equipementNom + " est en panne. 🚨";

    // Set text style (red text only)
    ui->labelAlert->setStyleSheet("color: red; font-size: 18px; font-weight: bold;");
    ui->labelAlert->setAlignment(Qt::AlignVCenter);
    ui->labelAlert->setText(alertText);

    // Setup media player with audio output
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("C:/Users/sadekk/Documents/sadek/siren.wav"));
    audioOutput->setVolume(50); // 50% volume
    player->setLoops(QMediaPlayer::Infinite);

    // Faster animation (3 seconds per cycle)
    int animationDuration = 6000;
    int totalDuration = 15000;

    QPropertyAnimation *animation = new QPropertyAnimation(ui->labelAlert, "pos", this);
    animation->setDuration(animationDuration);
    animation->setStartValue(QPoint(-ui->labelAlert->width(), ui->labelAlert->y()));
    animation->setEndValue(QPoint(width(), ui->labelAlert->y()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setLoopCount(totalDuration / animationDuration);

    // Start both sound and animation
    player->play();
    animation->start();

    // Cleanup after 15 seconds
    QTimer::singleShot(totalDuration, [=]() {
        player->stop();
        animation->stop();
        ui->labelAlert->clear();
        player->deleteLater();
        audioOutput->deleteLater();
        animation->deleteLater();
    });
}

//------------------------------------------------------------------------------------------------------------------Voice to chat

void MainWindow::on_btnvoice_clicked() {
    QProcess process;
    QString pythonPath = "python";  // Or the full path if needed
    QString scriptPath = "C:/Users/sadekk/Documents/sadek/voice_module/run_transcription.py";

    // Start the Python process
    process.start(pythonPath, QStringList() << scriptPath);
    process.waitForFinished(-1);  // Wait for the script to finish

    // 🔹 Capture standard output (transcribed text)
    QString output = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    ui->inputvoice->setText(output);

    // 🔹 Capture and print standard error (for debugging)
    QString errors = QString::fromUtf8(process.readAllStandardError());
}

//------------------------------------------------------------------------------------------------------------------Arduino

void MainWindow::update_fridge_status() {
    qDebug() << "💡 SLOT appelé !";

    static QByteArray buffer;
    buffer += A.read_from_arduino();

    int endIndex;
    while ((endIndex = buffer.indexOf('\n')) != -1) {
        QByteArray line = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        QString text = QString::fromUtf8(line);
        qDebug() << "📨 Donnée brute reçue :" << text;

        int tempIndex = text.indexOf("TEMP:");
        if (tempIndex != -1) {
            QString tempStr = text.mid(tempIndex + 5);
            qDebug() << "🌡️ Temp extraite :" << tempStr;

            bool ok;
            float currentTemp = tempStr.toFloat(&ok);
            if (!ok) {
                qDebug() << "❌ Temp reçue invalide (non float) : " << tempStr;
                return;
            }

            QSqlQuery tempQuery;
            tempQuery.prepare("SELECT temperature_conservation FROM VACCINS WHERE id_vac = 1");

            float conservationTemp = 0.0;
            if (tempQuery.exec() && tempQuery.next()) {
                QString conservationStr = tempQuery.value(0).toString();
                qDebug() << "📦 Température de conservation (brute BDD) :" << conservationStr;

                conservationTemp = conservationStr.toFloat(&ok);
                if (!ok) {
                    qDebug() << "❌ Erreur de conversion (varchar2->float): " << conservationStr;
                    return;
                }
            } else {
                qDebug() << "❌ Erreur SQL : vaccin non trouvé ou requête invalide";
                return;
            }

            qDebug() << "✅ Comparaison : Temp mesurée =" << currentTemp
                     << "/ Temp conservation =" << conservationTemp;

            if (qAbs(currentTemp - conservationTemp) > 0.5) {
                qDebug() << "🚨 Écart détecté → Alerte déclenchée !";

                QSqlQuery update;
                update.prepare("UPDATE EQUIPEMENTS SET statut_eqp = 'En panne' WHERE nom_eqp = 'Réfrigérateur'");
                if (update.exec()) {
                    qDebug() << "✅ Base mise à jour : statut = En panne";
                } else {
                    qDebug() << "❌ Erreur SQL UPDATE :" << update.lastError().text();
                }

                A.write_to_arduino("ALERTE\n");
                qDebug() << "📤 ALERTE envoyée à Arduino";

                updateTableView();
                showPanneNotification("Réfrigérateur");
            } else {
                qDebug() << "✅ Température correcte. Aucun changement.";
            }
        } else {
            qDebug() << "❌ Format inattendu (pas de 'TEMP:') → " << text;
        }
    }
}











































































void MainWindow::on_submit_clicked()
{
    /*QDate currentDate = QDate::currentDate();
    ui->d2->setDate(QDate::currentDate());*/

    QString nom = ui->nom->text();
    QString type = ui->type->currentText();
    QString fabricant = ui->fab->text();
    QDate dateFabrication = ui->d1->date();
    QDate dateExpiration = ui->d2->date();
    double temperature = ui->temp->text().toDouble();
    QString paysOrigine = ui->pays->text();
    int stock = ui->stock->text().toInt();


    if (nom.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le nom ne peut pas être vide !");
    } else if (type.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le type ne peut pas être vide !");
    } else if (fabricant.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le fabricant ne peut pas être vide !");
    } else if (dateFabrication > dateExpiration) {
        QMessageBox::critical(this, "Erreur", "La date d'expiration doit être après la date de fabrication !");
    } else if (temperature < -100 || temperature > 100) {
        QMessageBox::critical(this, "Erreur", "Température invalide !");
        ui->temp->clear();
    } else if (paysOrigine.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le pays d'origine ne peut pas être vide !");
    } else if (stock < 0) {
        QMessageBox::critical(this, "Erreur", "Le stock ne peut pas être négatif !");
        ui->stock->clear();
    } else {
        Vaccin V (0, nom, type, fabricant, dateFabrication, dateExpiration, temperature, paysOrigine, stock);
        bool test = V.ajouter();

        if (test) {
            ui->tableau5->setModel(V.afficher());
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                                     QObject::tr("Ajout effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
            ui->nom->clear();
            ui->fab->clear();
            ui->d1->clear();
            ui->d2->clear();
            ui->temp->clear();
            ui->pays->clear();
            ui->stock->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Échec"),
                                  QObject::tr("Ajout non effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
        }
    }


}


void MainWindow::on_del_clicked()
{
    // Récupérer l'ID sélectionné
    QModelIndex index = ui->tableau5->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau5->model()->data(ui->tableau5->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Vaccin r;
        if (r.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            ui->tableau5->setModel(vac.afficher());


        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }

}


void MainWindow::on_pushButton_159_clicked()
{
    if(mod==0){
        // Récupérer l'ID sélectionné
        QModelIndex index = ui->tableau5->selectionModel()->currentIndex();
        if (!index.isValid()) {
            QMessageBox::warning(this, tr("Modifier"), tr("Veuillez sélectionner un élément à Modifier."));
            return;
        }

        int id = ui->tableau5->model()->data(ui->tableau5->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne
        Vaccin v=vac.getVaccinById(id);
        ui->id->setText(QString::number(v.getId()));
        ui->nom->setText(v.getNom());
        ui->type->setCurrentText(v.getType());
        ui->fab->setText(v.getFabricant());
        ui->d1->setDate(v.getDateFabrication());
        ui->d2->setDate(v.getDateExpiration());
        ui->temp->setText(QString::number(v.getTemperature()));
        ui->pays->setText(v.getPaysOrigine());
        ui->stock->setText(QString::number(v.getStock()));
        mod=1;
    }
    else{
        int id = ui->id->text().toInt();
        QString nom = ui->nom->text();
        QString type = ui->type->currentText();
        QString fabricant = ui->fab->text();
        QDate dateFabrication = ui->d1->date();
        QDate dateExpiration = ui->d2->date();
        double temperature = ui->temp->text().toDouble();
        QString paysOrigine = ui->pays->text();
        int stock = ui->stock->text().toInt();
        if (nom.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Le nom ne peut pas être vide !");
        } else if (type.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Le type ne peut pas être vide !");
        } else if (fabricant.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Le fabricant ne peut pas être vide !");
        } else if (dateFabrication > dateExpiration) {
            QMessageBox::critical(this, "Erreur", "La date d'expiration doit être après la date de fabrication !");
        } else if (temperature < -100 || temperature > 100) {
            QMessageBox::critical(this, "Erreur", "Température invalide !");
            ui->temp->clear();
        } else if (paysOrigine.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Le pays d'origine ne peut pas être vide !");
        } else if (stock < 0) {
            QMessageBox::critical(this, "Erreur", "Le stock ne peut pas être négatif !");
            ui->stock->clear();
        } else {
            bool test = vac.modifier(id,nom,type,fabricant,dateFabrication,dateExpiration,temperature,paysOrigine,stock);
            if (test) {
                ui->tableau5->setModel(vac.afficher());
                QMessageBox::information(nullptr, QObject::tr("Succès"),
                                         QObject::tr("Modification effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
                ui->nom->clear();
                ui->fab->clear();
                ui->d1->clear();
                ui->d2->clear();
                ui->temp->clear();
                ui->pays->clear();
                ui->stock->clear();
                ui->id->clear();
                mod=0;
            } else {
                mod=0;
                QMessageBox::critical(nullptr, QObject::tr("Échec"),
                                      QObject::tr("Modification non effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
            }
        }
    }
}

