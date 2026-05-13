/********************************************************************************
** Form generated from reading UI file 'StandardsManagerWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STANDARDSMANAGERWIDGET_H
#define UI_STANDARDSMANAGERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StandardsManagerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QVBoxLayout *titleLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *addFieldBtn;
    QPushButton *saveDiskBtn;
    QTableWidget *standardsTable;

    void setupUi(QWidget *StandardsManagerWidget)
    {
        if (StandardsManagerWidget->objectName().isEmpty())
            StandardsManagerWidget->setObjectName("StandardsManagerWidget");
        StandardsManagerWidget->resize(800, 600);
        verticalLayout = new QVBoxLayout(StandardsManagerWidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLayout = new QVBoxLayout();
        titleLayout->setObjectName("titleLayout");
        titleLabel = new QLabel(StandardsManagerWidget);
        titleLabel->setObjectName("titleLabel");

        titleLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(StandardsManagerWidget);
        subtitleLabel->setObjectName("subtitleLabel");

        titleLayout->addWidget(subtitleLabel);


        headerLayout->addLayout(titleLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        addFieldBtn = new QPushButton(StandardsManagerWidget);
        addFieldBtn->setObjectName("addFieldBtn");
        addFieldBtn->setMinimumHeight(36);

        headerLayout->addWidget(addFieldBtn);

        saveDiskBtn = new QPushButton(StandardsManagerWidget);
        saveDiskBtn->setObjectName("saveDiskBtn");
        saveDiskBtn->setMinimumHeight(36);

        headerLayout->addWidget(saveDiskBtn);


        verticalLayout->addLayout(headerLayout);

        standardsTable = new QTableWidget(StandardsManagerWidget);
        standardsTable->setObjectName("standardsTable");
        standardsTable->setShowGrid(true);
        standardsTable->setAlternatingRowColors(true);

        verticalLayout->addWidget(standardsTable);


        retranslateUi(StandardsManagerWidget);

        QMetaObject::connectSlotsByName(StandardsManagerWidget);
    } // setupUi

    void retranslateUi(QWidget *StandardsManagerWidget)
    {
        titleLabel->setText(QCoreApplication::translate("StandardsManagerWidget", "Standards & Rules Manager", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("StandardsManagerWidget", "Configure global data aliases and validation parameters.", nullptr));
        addFieldBtn->setText(QCoreApplication::translate("StandardsManagerWidget", "+ Add New Field", nullptr));
        saveDiskBtn->setText(QCoreApplication::translate("StandardsManagerWidget", "\360\237\222\276 Save to rules.txt", nullptr));
        (void)StandardsManagerWidget;
    } // retranslateUi

};

namespace Ui {
    class StandardsManagerWidget: public Ui_StandardsManagerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARDSMANAGERWIDGET_H
