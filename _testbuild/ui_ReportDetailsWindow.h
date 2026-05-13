/********************************************************************************
** Form generated from reading UI file 'ReportDetailsWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDETAILSWINDOW_H
#define UI_REPORTDETAILSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportDetailsWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *batchNameLabel;
    QLabel *statsLabel;
    QTableWidget *dataTable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnExportValid;
    QPushButton *btnExportInvalid;
    QPushButton *btnExportReport;

    void setupUi(QMainWindow *ReportDetailsWindow)
    {
        if (ReportDetailsWindow->objectName().isEmpty())
            ReportDetailsWindow->setObjectName("ReportDetailsWindow");
        ReportDetailsWindow->resize(1024, 720);
        centralwidget = new QWidget(ReportDetailsWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        batchNameLabel = new QLabel(centralwidget);
        batchNameLabel->setObjectName("batchNameLabel");

        verticalLayout->addWidget(batchNameLabel);

        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName("statsLabel");

        verticalLayout->addWidget(statsLabel);

        dataTable = new QTableWidget(centralwidget);
        dataTable->setObjectName("dataTable");
        dataTable->setAlternatingRowColors(true);

        verticalLayout->addWidget(dataTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnExportValid = new QPushButton(centralwidget);
        btnExportValid->setObjectName("btnExportValid");

        horizontalLayout->addWidget(btnExportValid);

        btnExportInvalid = new QPushButton(centralwidget);
        btnExportInvalid->setObjectName("btnExportInvalid");

        horizontalLayout->addWidget(btnExportInvalid);

        btnExportReport = new QPushButton(centralwidget);
        btnExportReport->setObjectName("btnExportReport");

        horizontalLayout->addWidget(btnExportReport);


        verticalLayout->addLayout(horizontalLayout);

        ReportDetailsWindow->setCentralWidget(centralwidget);

        retranslateUi(ReportDetailsWindow);

        QMetaObject::connectSlotsByName(ReportDetailsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ReportDetailsWindow)
    {
        ReportDetailsWindow->setWindowTitle(QCoreApplication::translate("ReportDetailsWindow", "Batch Details", nullptr));
        batchNameLabel->setText(QCoreApplication::translate("ReportDetailsWindow", "Batch: unknown", nullptr));
        statsLabel->setText(QCoreApplication::translate("ReportDetailsWindow", "Total: 0  |  Valid: 0  |  Invalid: 0", nullptr));
        btnExportValid->setText(QCoreApplication::translate("ReportDetailsWindow", "\342\206\223 Export Valid (CSV)", nullptr));
        btnExportInvalid->setText(QCoreApplication::translate("ReportDetailsWindow", "\342\206\223 Export Invalid Data (CSV)", nullptr));
        btnExportReport->setText(QCoreApplication::translate("ReportDetailsWindow", "\342\232\240 Download Invalid Report w/ Errors", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReportDetailsWindow: public Ui_ReportDetailsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDETAILSWINDOW_H
