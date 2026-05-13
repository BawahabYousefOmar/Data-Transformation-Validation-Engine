/********************************************************************************
** Form generated from reading UI file 'ReportsTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTSTABLEWIDGET_H
#define UI_REPORTSTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportsTableWidget
{
public:
    QVBoxLayout *rootLayout;
    QFrame *summaryRow;
    QHBoxLayout *summaryRowLayout;
    QFrame *statCard1;
    QVBoxLayout *vboxLayout;
    QLabel *stat1ValueLabel;
    QLabel *stat1TitleLabel;
    QFrame *statCard2;
    QVBoxLayout *vboxLayout1;
    QLabel *stat2ValueLabel;
    QLabel *stat2TitleLabel;
    QFrame *statCard3;
    QVBoxLayout *vboxLayout2;
    QLabel *stat3ValueLabel;
    QLabel *stat3TitleLabel;
    QFrame *statCard4;
    QVBoxLayout *vboxLayout3;
    QLabel *stat4ValueLabel;
    QLabel *stat4TitleLabel;
    QFrame *toolbarFrame;
    QHBoxLayout *toolbarLayout;
    QLineEdit *searchInput;
    QLabel *sortLabel;
    QComboBox *sortCombo;
    QTableWidget *batchTable;
    QLabel *emptyStateLabel;

    void setupUi(QWidget *ReportsTableWidget)
    {
        if (ReportsTableWidget->objectName().isEmpty())
            ReportsTableWidget->setObjectName("ReportsTableWidget");
        ReportsTableWidget->resize(960, 700);
        rootLayout = new QVBoxLayout(ReportsTableWidget);
        rootLayout->setSpacing(16);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(0, 0, 0, 0);
        summaryRow = new QFrame(ReportsTableWidget);
        summaryRow->setObjectName("summaryRow");
        summaryRow->setMaximumHeight(88);
        summaryRowLayout = new QHBoxLayout(summaryRow);
        summaryRowLayout->setSpacing(12);
        summaryRowLayout->setObjectName("summaryRowLayout");
        summaryRowLayout->setContentsMargins(0, 0, 0, 0);
        statCard1 = new QFrame(summaryRow);
        statCard1->setObjectName("statCard1");
        vboxLayout = new QVBoxLayout(statCard1);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(16, 12, 16, 12);
        stat1ValueLabel = new QLabel(statCard1);
        stat1ValueLabel->setObjectName("stat1ValueLabel");

        vboxLayout->addWidget(stat1ValueLabel);

        stat1TitleLabel = new QLabel(statCard1);
        stat1TitleLabel->setObjectName("stat1TitleLabel");

        vboxLayout->addWidget(stat1TitleLabel);


        summaryRowLayout->addWidget(statCard1);

        statCard2 = new QFrame(summaryRow);
        statCard2->setObjectName("statCard2");
        vboxLayout1 = new QVBoxLayout(statCard2);
        vboxLayout1->setObjectName("vboxLayout1");
        vboxLayout1->setContentsMargins(16, 12, 16, 12);
        stat2ValueLabel = new QLabel(statCard2);
        stat2ValueLabel->setObjectName("stat2ValueLabel");

        vboxLayout1->addWidget(stat2ValueLabel);

        stat2TitleLabel = new QLabel(statCard2);
        stat2TitleLabel->setObjectName("stat2TitleLabel");

        vboxLayout1->addWidget(stat2TitleLabel);


        summaryRowLayout->addWidget(statCard2);

        statCard3 = new QFrame(summaryRow);
        statCard3->setObjectName("statCard3");
        vboxLayout2 = new QVBoxLayout(statCard3);
        vboxLayout2->setObjectName("vboxLayout2");
        vboxLayout2->setContentsMargins(16, 12, 16, 12);
        stat3ValueLabel = new QLabel(statCard3);
        stat3ValueLabel->setObjectName("stat3ValueLabel");

        vboxLayout2->addWidget(stat3ValueLabel);

        stat3TitleLabel = new QLabel(statCard3);
        stat3TitleLabel->setObjectName("stat3TitleLabel");

        vboxLayout2->addWidget(stat3TitleLabel);


        summaryRowLayout->addWidget(statCard3);

        statCard4 = new QFrame(summaryRow);
        statCard4->setObjectName("statCard4");
        vboxLayout3 = new QVBoxLayout(statCard4);
        vboxLayout3->setObjectName("vboxLayout3");
        vboxLayout3->setContentsMargins(16, 12, 16, 12);
        stat4ValueLabel = new QLabel(statCard4);
        stat4ValueLabel->setObjectName("stat4ValueLabel");

        vboxLayout3->addWidget(stat4ValueLabel);

        stat4TitleLabel = new QLabel(statCard4);
        stat4TitleLabel->setObjectName("stat4TitleLabel");

        vboxLayout3->addWidget(stat4TitleLabel);


        summaryRowLayout->addWidget(statCard4);


        rootLayout->addWidget(summaryRow);

        toolbarFrame = new QFrame(ReportsTableWidget);
        toolbarFrame->setObjectName("toolbarFrame");
        toolbarFrame->setMaximumHeight(44);
        toolbarLayout = new QHBoxLayout(toolbarFrame);
        toolbarLayout->setSpacing(10);
        toolbarLayout->setObjectName("toolbarLayout");
        toolbarLayout->setContentsMargins(0, 0, 0, 0);
        searchInput = new QLineEdit(toolbarFrame);
        searchInput->setObjectName("searchInput");

        toolbarLayout->addWidget(searchInput);

        sortLabel = new QLabel(toolbarFrame);
        sortLabel->setObjectName("sortLabel");

        toolbarLayout->addWidget(sortLabel);

        sortCombo = new QComboBox(toolbarFrame);
        sortCombo->addItem(QString());
        sortCombo->addItem(QString());
        sortCombo->addItem(QString());
        sortCombo->addItem(QString());
        sortCombo->setObjectName("sortCombo");

        toolbarLayout->addWidget(sortCombo);


        rootLayout->addWidget(toolbarFrame);

        batchTable = new QTableWidget(ReportsTableWidget);
        batchTable->setObjectName("batchTable");
        batchTable->setColumnCount(7);
        batchTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        batchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        batchTable->setAlternatingRowColors(true);
        batchTable->setShowGrid(false);
        batchTable->setSortingEnabled(false);
        batchTable->setWordWrap(false);
        batchTable->horizontalHeader()->setStretchLastSection(true);

        rootLayout->addWidget(batchTable);

        emptyStateLabel = new QLabel(ReportsTableWidget);
        emptyStateLabel->setObjectName("emptyStateLabel");
        emptyStateLabel->setAlignment(Qt::AlignCenter);
        emptyStateLabel->setVisible(false);

        rootLayout->addWidget(emptyStateLabel);


        retranslateUi(ReportsTableWidget);

        QMetaObject::connectSlotsByName(ReportsTableWidget);
    } // setupUi

    void retranslateUi(QWidget *ReportsTableWidget)
    {
        stat1ValueLabel->setText(QCoreApplication::translate("ReportsTableWidget", "0", nullptr));
        stat1TitleLabel->setText(QCoreApplication::translate("ReportsTableWidget", "Total Batches", nullptr));
        stat2ValueLabel->setText(QCoreApplication::translate("ReportsTableWidget", "0", nullptr));
        stat2TitleLabel->setText(QCoreApplication::translate("ReportsTableWidget", "Records Processed", nullptr));
        stat3ValueLabel->setText(QCoreApplication::translate("ReportsTableWidget", "0%", nullptr));
        stat3TitleLabel->setText(QCoreApplication::translate("ReportsTableWidget", "Overall Valid Rate", nullptr));
        stat4ValueLabel->setText(QCoreApplication::translate("ReportsTableWidget", "0", nullptr));
        stat4TitleLabel->setText(QCoreApplication::translate("ReportsTableWidget", "Total Invalid", nullptr));
        searchInput->setPlaceholderText(QCoreApplication::translate("ReportsTableWidget", "\360\237\224\215  Search batches\342\200\246", nullptr));
        sortLabel->setText(QCoreApplication::translate("ReportsTableWidget", "Sort:", nullptr));
        sortCombo->setItemText(0, QCoreApplication::translate("ReportsTableWidget", "Newest first", nullptr));
        sortCombo->setItemText(1, QCoreApplication::translate("ReportsTableWidget", "Oldest first", nullptr));
        sortCombo->setItemText(2, QCoreApplication::translate("ReportsTableWidget", "Most records", nullptr));
        sortCombo->setItemText(3, QCoreApplication::translate("ReportsTableWidget", "Highest invalid %", nullptr));

        emptyStateLabel->setText(QCoreApplication::translate("ReportsTableWidget", "No batches processed yet.<br/>Upload a CSV file and run validation to see results here.", nullptr));
        (void)ReportsTableWidget;
    } // retranslateUi

};

namespace Ui {
    class ReportsTableWidget: public Ui_ReportsTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTSTABLEWIDGET_H
