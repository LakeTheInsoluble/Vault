#include "alustusdialogi.h"
#include "ui_alustusdialogi.h"


AlustusDialogi::AlustusDialogi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlustusDialogi)
{
    ui->setupUi(this);

    connect(ui->OK_Button, SIGNAL(clicked()),this, SLOT(accept()));
    connect(ui->Peruuta_Button, SIGNAL(clicked()),this, SLOT(reject()));
}

AlustusDialogi::~AlustusDialogi()
{
    delete ui;
}

int AlustusDialogi::exec()
{
    QDialog::exec();

    if(result() == QDialog::Accepted )
    {
        QString qs = ui->PelaajanNimi_text->text();
        std::string nimi = qs.toStdString();

        emit laheta(nimi, ui->AlustenLKM_spin->value());
    }
    return result();
}

