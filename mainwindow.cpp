#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "Vaccin.h"
#include <QMessageBox>
#include <QDate>
#include<QStandardPaths>
#include<QDesktopServices>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


void logToFile(const QString &event, const QString &details) {
    QFile file("app_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss] ");
        out << timestamp << event << ": " << details << "\n";
        file.close();
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::applyFilter);
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSortChanged);
    /*connect(ui->pdfButton, &QPushButton::clicked, this, &MainWindow::on_pdfButton_clicked);
    connect(ui->emailButton, &QPushButton::clicked, this, &MainWindow::on_emailButton_clicked);
    connect(ui->sms, &QPushButton::clicked, this, &MainWindow::on_sms_clicked);*/



    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->setModel(vac.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnmedecin_clicked()
{
    ui->sqs->setCurrentIndex(0);
}

void MainWindow::on_btnpatient_clicked()
{
    ui->sqs->setCurrentIndex(1);
}

void MainWindow::on_btnlabo_clicked()
{
    ui->sqs->setCurrentIndex(2);
}

void MainWindow::on_btnequiprmrnt_clicked()
{
    ui->sqs->setCurrentIndex(3);
}

void MainWindow::on_btnvaccins_clicked()
{
    ui->sqs->setCurrentIndex(4);
}

void MainWindow::on_btnrendezv_clicked()
{
    ui->sqs->setCurrentIndex(5);
}

void MainWindow::on_btnuser_clicked()
{
    ui->sqs->setCurrentIndex(6);
}

void MainWindow::on_btnlabo2_clicked()
{
    ui->sqs->setCurrentIndex(7);
}

void MainWindow::on_btnlabo3_clicked()
{
    ui->sqs->setCurrentIndex(8);
}

void MainWindow::on_btnlabo4_clicked()
{
    ui->sqs->setCurrentIndex(9);
}

void MainWindow::on_btnmedecin2_clicked()
{
    ui->sqs->setCurrentIndex(10);
}

void MainWindow::on_btnpatient2_clicked()
{
    ui->sqs->setCurrentIndex(11);
}

void MainWindow::on_btnequiprmrnt2_clicked()
{
    ui->sqs->setCurrentIndex(12);
}

void MainWindow::on_btnequiprmrnt3_clicked()
{
    ui->sqs->setCurrentIndex(13);
}

void MainWindow::on_btnvaccins2_clicked()
{
    showStockPieChart();
    //ui->sqs->setCurrentIndex(14);
}

void MainWindow::on_btnrendezv2_clicked()
{
    ui->sqs->setCurrentIndex(15);
}

void MainWindow::on_btnrendezv3_clicked()
{
    ui->sqs->setCurrentIndex(16);
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
            logToFile("Vaccine added", nom + ", " + type + ", " + paysOrigine);
            checkLowStockAndNotify(); // 🚨 Add this line
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
        Vaccin vacToDelete = vac.getVaccinById(id);
        Vaccin r;
        if (r.supprimer(id)) {
            logToFile("Vaccine deleted", vacToDelete.getNom() + ", " + vacToDelete.getType() + ", " + vacToDelete.getPaysOrigine()); // 📝 Log it
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
                logToFile("Vaccine modified", nom + ", " + type + ", " + paysOrigine);
                checkLowStockAndNotify(); // 🚨 Add this line
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
void MainWindow::applyFilter(const QString &text)
{
    // Call the searchByName method from Vaccin class and update the model
    ui->sortComboBox->setCurrentIndex(0);
    ui->tableau5->setModel(vac.searchByName(text));
}
void MainWindow::onSortChanged(int index)
{
    ui->searchLineEdit->clear();

    QString orderBy;

    // Check the current index of the combo box and set the sorting column accordingly
    if (index == 0) {
        // "Default" selected - order by id_vac
        orderBy = "id_vac";
    } else if (index == 1) {
        // "Date de fabrication" selected - order by date_fabrication
        ui->sortComboBox->setCurrentIndex(1);
        orderBy = "date_fabrication";
    }

    // Update the model with the appropriate sorted query
    ui->tableau5->setModel(vac.afficher(orderBy));  // Call afficher with the orderBy column
}
void MainWindow::on_pdfButton_clicked()
{
    // Open save dialog
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save PDF"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/vaccins.pdf",
        tr("PDF Files (*.pdf)")
        );
    if (filePath.isEmpty()) {
        return;
    }

    // Create PDF writer
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);
    writer.setTitle(tr("Vaccin Report"));
    writer.setCreator("VAX Nest");

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to create PDF."));
        return;
    }

    // Set fonts
    QFont headerFont = painter.font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);

    QFont dataFont = painter.font();
    dataFont.setPointSize(9);

    // Layout parameters
    const int margin = 40;
    int yPos = margin;
    const int baseRowHeight = 50; // Minimum row height
    const int lineHeight = 20;
    const int cellPadding = 5;

    // Column widths (adjust according to your data)
    QVector<int> columnWidths = {120, 300, 300, 300, 300, 300, 300, 300, 300}; // ID, Name, Type, etc.

    // Get model data
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableau5->model());
    if (!model) {
        QMessageBox::critical(this, tr("Error"), tr("No data to export."));
        return;
    }

    // Draw title
    painter.setFont(headerFont);
    painter.drawText(margin, yPos, tr("Vaccination Report"));
    yPos += lineHeight * 2;

    // Draw current date
    painter.drawText(margin, yPos, tr("Generated on: ") + QDate::currentDate().toString(Qt::ISODate));
    yPos += lineHeight * 2;

    // Calculate total table width
    int tableWidth = std::accumulate(columnWidths.begin(), columnWidths.end(), 0);

    // Draw headers with background
    painter.setFont(headerFont);
    painter.setBrush(QBrush(Qt::lightGray));
    painter.setPen(Qt::NoPen);
    painter.drawRect(margin, yPos, tableWidth, baseRowHeight);

    painter.setPen(Qt::black);
    int xPos = margin;
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(QRect(xPos, yPos, columnWidths[col], baseRowHeight),
                         Qt::AlignCenter, header);
        xPos += columnWidths[col];
    }
    yPos += baseRowHeight;

    // Draw data rows with dynamic height
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        // First pass: calculate required row height
        int requiredRowHeight = baseRowHeight;

        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            // Special formatting for dates
            if (col == 4 || col == 5) { // Date columns
                QDate date = QDate::fromString(data, Qt::ISODate);
                if (date.isValid()) {
                    data = date.toString("dd/MM/yyyy");
                }
            }

            QRect textRect(0, 0, columnWidths[col] - 2*cellPadding, 0);
            QFontMetrics fm(dataFont);
            QRect boundingRect = fm.boundingRect(textRect, Qt::TextWordWrap, data);

            // Calculate how many lines we need
            int linesNeeded = ceil((double)boundingRect.height() / lineHeight);
            int cellHeight = linesNeeded * lineHeight;

            if (cellHeight > requiredRowHeight) {
                requiredRowHeight = cellHeight;
            }
        }

        // Check for page break before drawing row
        if (yPos + requiredRowHeight > writer.height() - margin) {
            writer.newPage();
            yPos = margin;

            // Redraw headers on new page
            painter.setFont(headerFont);
            painter.setBrush(QBrush(Qt::lightGray));
            painter.setPen(Qt::NoPen);
            painter.drawRect(margin, yPos, tableWidth, baseRowHeight);

            painter.setPen(Qt::black);
            xPos = margin;
            for (int col = 0; col < model->columnCount(); ++col) {
                QString header = model->headerData(col, Qt::Horizontal).toString();
                painter.drawText(QRect(xPos, yPos, columnWidths[col], baseRowHeight),
                                 Qt::AlignCenter, header);
                xPos += columnWidths[col];
            }
            yPos += baseRowHeight;

            painter.setFont(dataFont);
        }

        // Draw row background (alternating colors)
        painter.setBrush(QBrush(row % 2 ? Qt::white : QColor(240, 240, 240)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(margin, yPos, tableWidth, requiredRowHeight);
        painter.setPen(Qt::black);

        // Draw cell contents with text wrapping
        xPos = margin;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            // Format dates
            if (col == 4 || col == 5) { // Date columns
                QDate date = QDate::fromString(data, Qt::ISODate);
                if (date.isValid()) {
                    data = date.toString("dd/MM/yyyy");
                }
            }

            QRect cellRect(xPos + cellPadding, yPos + cellPadding,
                           columnWidths[col] - 2*cellPadding, requiredRowHeight - 2*cellPadding);

            painter.drawText(cellRect, Qt::TextWordWrap | Qt::AlignVCenter, data);
            xPos += columnWidths[col];
        }

        yPos += requiredRowHeight;
    }

    painter.end();


    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::on_emailButton_clicked()
{

    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);


    smtp.connectToHost();
    if (smtp.waitForReadyConnected()) {
        qDebug() << "Connected to the SMTP server!";


        smtp.login("3abedelsmadGathafi@gmail.com", "qbap zjeo obxj ixse", SmtpClient::AuthLogin);

        if (smtp.waitForAuthenticated()) {
            qDebug() << "Logged in successfully!";


            MimeMessage message;
            EmailAddress sender("3abedelsmadGathafi@gmail.com", "VAX NEST");
            message.setSender(sender);

            EmailAddress recipient("allanimohammed73@gmail.com", "Mohamed");
            message.addRecipient(recipient);

            message.setSubject("Stock Alert: Low Levels");

            MimeText *text = new MimeText();
            text->setText("Dear Admin,\n\nSome stock levels are getting low. Please review.\n\nBest regards,\nYour Application");
            message.addPart(text);


            smtp.sendMail(message);


            if (smtp.waitForMailSent()) {
                QMessageBox::information(this, "Email Sent", "Stock alert email has been sent successfully.");
            } else {
                QMessageBox::critical(this, "Mail Sending Error", "Failed to send the email.");
            }


            smtp.quit();
        } else {
            qDebug() << "Failed to log in to the SMTP server.";
            QMessageBox::critical(this, "Login Error", "Failed to log in to the SMTP server.");
        }
    } else {
        qDebug() << "Failed to connect to the SMTP server.";
        QMessageBox::critical(this, "Connection Error", "Failed to connect to the email server.");
    }
}



void MainWindow::on_sms_clicked()
{
    SmsSender sender("b7e5a19e50227693c9f5a908a1382769-dbfcdd8b-0e1d-4392-bd72-7c50d3600a4f", "447491163443");
    sender.sendSms("+21646598646", "Hello from Qt!");
    QMessageBox::critical(this, "Connection Error", "hi");

}


void MainWindow::sendStockAlertEmail(const QString &nom, const QString &type, const QString &pays, int stock) {
    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);
    smtp.connectToHost();
    if (smtp.waitForReadyConnected()) {
        smtp.login("3abedelsmadGathafi@gmail.com", "qbap zjeo obxj ixse", SmtpClient::AuthLogin);
        if (smtp.waitForAuthenticated()) {
            MimeMessage message;
            EmailAddress sender("3abedelsmadGathafi@gmail.com", "AUTO VAX NEST");
            message.setSender(sender);

            EmailAddress recipient("allanimohammed73@gmail.com", "Mohamed");
            message.addRecipient(recipient);

            message.setSubject("Low Vaccine Stock Alert");

            QString content = QString("Dear Admin,\n\nStock for vaccine %1 (%2 - %3) is low.\nCurrent stock: %4 units.\n\nPlease restock soon.")
                                  .arg(nom, type, pays).arg(stock);

            MimeText *text = new MimeText();
            text->setText(content);
            message.addPart(text);

            qDebug() << "📤 Trying to send email...";
            smtp.sendMail(message);
            qDebug() << "✅ sendMail() called.";

            if (smtp.waitForMailSent()) {
                qDebug() << "📬 Email successfully sent.";
            } else {
                qDebug() << "❌ Failed to send email after calling sendMail.";
            }

            smtp.quit();
        } else {
            qDebug() << "❌ Failed to authenticate.";
        }
    } else {
        qDebug() << "❌ Failed to connect.";
    }
}



void MainWindow::checkLowStockAndNotify() {
    QSqlQuery query;
    query.prepare("SELECT nom_vac, type_vac, pays_origin, stock FROM vaccins WHERE stock <= 10");

    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value(0).toString();
            QString type = query.value(1).toString();
            QString pays = query.value(2).toString();
            int stock = query.value(3).toInt();

            // Compose message
            QString details = QString("Vaccine %1 (%2 - %3) stock is low: %4 units left.")
                                  .arg(nom, type, pays).arg(stock);

            // Log and send
            logToFile("Stock alert", details);
            sendStockAlertEmail(nom, type, pays, stock);
        }
    }
}

void MainWindow::showStockPieChart() {
    QPieSeries *series = new QPieSeries();

    QSqlQuery query;
    query.prepare("SELECT type_vac, SUM(stock) FROM vaccins GROUP BY type_vac");
    if (query.exec()) {
        while (query.next()) {
            QString type = query.value(0).toString();
            int stock = query.value(1).toInt();
            series->append(type, stock);
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Stock Distribution by Vaccine Type");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistics - Pie Chart");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setLayout(layout);
    dialog->resize(600, 400);
    dialog->exec();
}
