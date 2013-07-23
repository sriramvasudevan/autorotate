/********************************************************************************
** Form generated from reading UI file 'tesqprocess.ui'
**
** Created: Thu Jul 11 18:20:43 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESQPROCESS_H
#define UI_TESQPROCESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_tesQProcess
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineeCommand;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnProcess, *btnProcess2;
    QTextEdit *txtReport;

    void setupUi(QDialog *tesQProcess)
    {
        if (tesQProcess->objectName().isEmpty())
            tesQProcess->setObjectName(QString::fromUtf8("tesQProcess"));
        tesQProcess->resize(595, 408);
        QPalette pal;
        pal.setColor(QPalette::Window, Qt::gray);
        tesQProcess->setPalette(pal);
        gridLayout = new QGridLayout(tesQProcess);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tesQProcess);
        label->setObjectName(QString::fromUtf8("label"));


        horizontalLayout->addWidget(label);

        lineeCommand = new QLineEdit(tesQProcess);
        lineeCommand->setObjectName(QString::fromUtf8("lineeCommand"));
        
        horizontalLayout->addWidget(lineeCommand);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnProcess = new QPushButton(tesQProcess);
        btnProcess->setObjectName(QString::fromUtf8("btnProcess"));

        horizontalLayout_3->addWidget(btnProcess);


        btnProcess2 = new QPushButton(tesQProcess);
        btnProcess2->setObjectName(QString::fromUtf8("btnProcess2"));

        horizontalLayout_3->addWidget(btnProcess2);

        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        txtReport = new QTextEdit(tesQProcess);
        txtReport->setObjectName(QString::fromUtf8("txtReport"));


        gridLayout->addWidget(txtReport, 2, 0, 1, 1);


        retranslateUi(tesQProcess);

        QMetaObject::connectSlotsByName(tesQProcess);
    } // setupUi

    void retranslateUi(QDialog *tesQProcess)
    {
        tesQProcess->setWindowTitle(QApplication::translate("tesQProcess", "Semantic Text Miner", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("tesQProcess", "Image Directory :", 0, QApplication::UnicodeUTF8));
        lineeCommand->setText(QApplication::translate("tesQProcess", "~/autorotate/all_images", 0, QApplication::UnicodeUTF8));
        btnProcess->setText(QApplication::translate("tesQProcess", "Browse", 0, QApplication::UnicodeUTF8));
        btnProcess2->setText(QApplication::translate("tesQProcess", "Autorotate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class tesQProcess: public Ui_tesQProcess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESQPROCESS_H
