#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath() + "/../../task4/db.sqlite");
    bool opened = db.open();
    qDebug() << "Connection to database:" << opened << QSqlDatabase::database().databaseName();

    QSqlQuery q = QSqlQuery(QSqlDatabase::database());
    QString sql = QString("SELECT * FROM phone_book");
    q.prepare(sql);
    if (!q.exec()) {
        qDebug() << "query error: " << q.lastError().text();
    }

    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одной строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked); // NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("phone_book");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Телефон"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Фамилия"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Имя"));

    bool res = model->select();
    qDebug() << "Select from database:" << res;
    if (!res)
        qDebug() << model->lastError().text();

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);

    connect(ui->add_button, &QToolButton::clicked, [model](){
        model->insertRow(model->rowCount());
        model->submitAll();
    });

    connect(ui->delete_button, &QToolButton::clicked, [this, model]() {
        if (ui->tableView->currentIndex().row() < 0)
            return;

        if (QMessageBox::information(Q_NULLPTR, "Вопрос", "Вы действительно хотите удалить выделенную строку?\n\n"
                                     "Это действие нельзя отменить.", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            model->removeRow(ui->tableView->currentIndex().row());
            model->submitAll();
        }
    });

    connect(ui->find_lineEdit, &QLineEdit::textChanged, [this, model]() {
        if (ui->find_lineEdit->text().isEmpty())
            model->setFilter("");
        model->submitAll();
        model->setFilter(QString("(surname) LIKE '%%1%' OR "
                                 "(name) LIKE '%%1%' OR "
                                 "(tel) LIKE '%%1%'")
                         .arg(ui->find_lineEdit->text()));
    });

    connect(ui->tbSaveAllData, &QToolButton::clicked, [model](){
        //model->insertRow(model->rowCount());
        model->submitAll();
        QMessageBox::information(Q_NULLPTR, "Информация", "Ваши введённые данные сохранены в базу данных!", QMessageBox::Yes, QMessageBox::No);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent */*event*/)
{
    if (!qobject_cast<QSqlTableModel*>(ui->tableView->model())->submitAll()) {
        qDebug() << "Error submitting data";
    }
}
