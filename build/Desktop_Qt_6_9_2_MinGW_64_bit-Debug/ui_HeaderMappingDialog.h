/********************************************************************************
** Form generated from reading UI file 'HeaderMappingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEADERMAPPINGDIALOG_H
#define UI_HEADERMAPPINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HeaderMappingDialog
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *hboxLayout;
    QLabel *warningIconLabel;
    QLabel *titleLabel;
    QSpacerItem *spacerItem;
    QLabel *descriptionLabel;
    QHBoxLayout *hboxLayout1;
    QLabel *unknownColumnKeyLabel;
    QLabel *unknownColumnValueLabel;
    QSpacerItem *spacerItem1;
    QFrame *separatorLine;
    QHBoxLayout *hboxLayout2;
    QRadioButton *mapToStandardRadio;
    QComboBox *standardFieldCombo;
    QSpacerItem *spacerItem2;
    QRadioButton *skipColumnRadio;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem3;
    QPushButton *applyToAllButton;
    QPushButton *confirmButton;

    void setupUi(QDialog *HeaderMappingDialog)
    {
        if (HeaderMappingDialog->objectName().isEmpty())
            HeaderMappingDialog->setObjectName("HeaderMappingDialog");
        HeaderMappingDialog->resize(480, 280);
        HeaderMappingDialog->setModal(true);
        HeaderMappingDialog->setMinimumSize(QSize(480, 280));
        HeaderMappingDialog->setMaximumSize(QSize(480, 280));
        mainLayout = new QVBoxLayout(HeaderMappingDialog);
        mainLayout->setSpacing(16);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(24, 24, 24, 20);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        warningIconLabel = new QLabel(HeaderMappingDialog);
        warningIconLabel->setObjectName("warningIconLabel");

        hboxLayout->addWidget(warningIconLabel);

        titleLabel = new QLabel(HeaderMappingDialog);
        titleLabel->setObjectName("titleLabel");

        hboxLayout->addWidget(titleLabel);

        spacerItem = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);


        mainLayout->addLayout(hboxLayout);

        descriptionLabel = new QLabel(HeaderMappingDialog);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setWordWrap(true);

        mainLayout->addWidget(descriptionLabel);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        unknownColumnKeyLabel = new QLabel(HeaderMappingDialog);
        unknownColumnKeyLabel->setObjectName("unknownColumnKeyLabel");

        hboxLayout1->addWidget(unknownColumnKeyLabel);

        unknownColumnValueLabel = new QLabel(HeaderMappingDialog);
        unknownColumnValueLabel->setObjectName("unknownColumnValueLabel");

        hboxLayout1->addWidget(unknownColumnValueLabel);

        spacerItem1 = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem1);


        mainLayout->addLayout(hboxLayout1);

        separatorLine = new QFrame(HeaderMappingDialog);
        separatorLine->setObjectName("separatorLine");
        separatorLine->setFrameShape(QFrame::HLine);
        separatorLine->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(separatorLine);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        mapToStandardRadio = new QRadioButton(HeaderMappingDialog);
        mapToStandardRadio->setObjectName("mapToStandardRadio");
        mapToStandardRadio->setChecked(true);

        hboxLayout2->addWidget(mapToStandardRadio);

        standardFieldCombo = new QComboBox(HeaderMappingDialog);
        standardFieldCombo->addItem(QString());
        standardFieldCombo->addItem(QString());
        standardFieldCombo->addItem(QString());
        standardFieldCombo->addItem(QString());
        standardFieldCombo->addItem(QString());
        standardFieldCombo->setObjectName("standardFieldCombo");
        standardFieldCombo->setMinimumWidth(130);

        hboxLayout2->addWidget(standardFieldCombo);

        spacerItem2 = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem2);


        mainLayout->addLayout(hboxLayout2);

        skipColumnRadio = new QRadioButton(HeaderMappingDialog);
        skipColumnRadio->setObjectName("skipColumnRadio");

        mainLayout->addWidget(skipColumnRadio);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem3);

        applyToAllButton = new QPushButton(HeaderMappingDialog);
        applyToAllButton->setObjectName("applyToAllButton");

        hboxLayout3->addWidget(applyToAllButton);

        confirmButton = new QPushButton(HeaderMappingDialog);
        confirmButton->setObjectName("confirmButton");

        hboxLayout3->addWidget(confirmButton);


        mainLayout->addLayout(hboxLayout3);


        retranslateUi(HeaderMappingDialog);

        confirmButton->setDefault(true);


        QMetaObject::connectSlotsByName(HeaderMappingDialog);
    } // setupUi

    void retranslateUi(QDialog *HeaderMappingDialog)
    {
        HeaderMappingDialog->setWindowTitle(QCoreApplication::translate("HeaderMappingDialog", "Unknown Column Detected", nullptr));
        warningIconLabel->setText(QCoreApplication::translate("HeaderMappingDialog", "\342\232\240", nullptr));
        titleLabel->setText(QCoreApplication::translate("HeaderMappingDialog", "Unknown Column Header Found", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("HeaderMappingDialog", "The column below was not found in the header mappings. Please choose how to handle it:", nullptr));
        unknownColumnKeyLabel->setText(QCoreApplication::translate("HeaderMappingDialog", "Unknown column:", nullptr));
        unknownColumnValueLabel->setText(QCoreApplication::translate("HeaderMappingDialog", "department", nullptr));
        mapToStandardRadio->setText(QCoreApplication::translate("HeaderMappingDialog", "Map to standard field:", nullptr));
        standardFieldCombo->setItemText(0, QCoreApplication::translate("HeaderMappingDialog", "ID", nullptr));
        standardFieldCombo->setItemText(1, QCoreApplication::translate("HeaderMappingDialog", "Name", nullptr));
        standardFieldCombo->setItemText(2, QCoreApplication::translate("HeaderMappingDialog", "GPA", nullptr));
        standardFieldCombo->setItemText(3, QCoreApplication::translate("HeaderMappingDialog", "Email", nullptr));
        standardFieldCombo->setItemText(4, QCoreApplication::translate("HeaderMappingDialog", "Phone", nullptr));

        skipColumnRadio->setText(QCoreApplication::translate("HeaderMappingDialog", "Skip this column entirely (ignore during validation)", nullptr));
        applyToAllButton->setText(QCoreApplication::translate("HeaderMappingDialog", "Apply to All Similar", nullptr));
        confirmButton->setText(QCoreApplication::translate("HeaderMappingDialog", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HeaderMappingDialog: public Ui_HeaderMappingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEADERMAPPINGDIALOG_H
