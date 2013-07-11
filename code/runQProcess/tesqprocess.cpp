#include "tesqprocess.h"
#include "ui_tesqprocess.h"

tesQProcess::tesQProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tesQProcess)
{
    ui->setupUi(this);
}

tesQProcess::~tesQProcess()
{
    delete ui;
}

void tesQProcess::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void tesQProcess::on_btnProcess_clicked()
{
    QString str_command;

    /* clear text report */
    ui->txtReport->clear();

    /* create string command and argument */
    str_command = ui->lineeCommand->text();

    /* create QProcess object */
    proc= new QProcess();
    proc->start("/bin/bash", (QStringList() << "-c" << QString("~/autorotate/code/./autorotate.sh " + str_command)));

    /* show output */
    connect(proc, SIGNAL(readyReadStandardOutput()),this, SLOT(rightMessage()) );
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage()) );
}

// show right message
void tesQProcess::rightMessage()
{
    QByteArray strdata = proc->readAllStandardOutput();
    ui->txtReport->setTextColor(Qt::black);
    ui->txtReport->append(strdata);
}

// show wrong message
void tesQProcess::wrongMessage()
{
    QByteArray strdata = proc->readAllStandardError();
    ui->txtReport->setTextColor(Qt::red);
    ui->txtReport->append(strdata);
}
