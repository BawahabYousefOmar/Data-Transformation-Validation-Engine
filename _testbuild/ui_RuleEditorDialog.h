/********************************************************************************
** Form generated from reading UI file 'RuleEditorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEEDITORDIALOG_H
#define UI_RULEEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RuleEditorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QCheckBox *requiredCheckBox;
    QFormLayout *formLayout;
    QLabel *label_length;
    QSpinBox *lengthSpinBox;
    QLabel *label_prefix;
    QLineEdit *prefixInput;
    QLabel *label_sub;
    QLineEdit *substringInput;
    QGroupBox *numericGroupBox;
    QFormLayout *formLayout_2;
    QLabel *label_min;
    QDoubleSpinBox *minValSpinBox;
    QLabel *label_max;
    QDoubleSpinBox *maxValSpinBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *saveButton;

    void setupUi(QDialog *RuleEditorDialog)
    {
        if (RuleEditorDialog->objectName().isEmpty())
            RuleEditorDialog->setObjectName("RuleEditorDialog");
        RuleEditorDialog->resize(400, 450);
        verticalLayout = new QVBoxLayout(RuleEditorDialog);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        titleLabel = new QLabel(RuleEditorDialog);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        requiredCheckBox = new QCheckBox(RuleEditorDialog);
        requiredCheckBox->setObjectName("requiredCheckBox");

        verticalLayout->addWidget(requiredCheckBox);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_length = new QLabel(RuleEditorDialog);
        label_length->setObjectName("label_length");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_length);

        lengthSpinBox = new QSpinBox(RuleEditorDialog);
        lengthSpinBox->setObjectName("lengthSpinBox");
        lengthSpinBox->setMinimum(-1);

        formLayout->setWidget(0, QFormLayout::FieldRole, lengthSpinBox);

        label_prefix = new QLabel(RuleEditorDialog);
        label_prefix->setObjectName("label_prefix");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_prefix);

        prefixInput = new QLineEdit(RuleEditorDialog);
        prefixInput->setObjectName("prefixInput");

        formLayout->setWidget(1, QFormLayout::FieldRole, prefixInput);

        label_sub = new QLabel(RuleEditorDialog);
        label_sub->setObjectName("label_sub");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_sub);

        substringInput = new QLineEdit(RuleEditorDialog);
        substringInput->setObjectName("substringInput");

        formLayout->setWidget(2, QFormLayout::FieldRole, substringInput);


        verticalLayout->addLayout(formLayout);

        numericGroupBox = new QGroupBox(RuleEditorDialog);
        numericGroupBox->setObjectName("numericGroupBox");
        numericGroupBox->setCheckable(true);
        formLayout_2 = new QFormLayout(numericGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        label_min = new QLabel(numericGroupBox);
        label_min->setObjectName("label_min");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_min);

        minValSpinBox = new QDoubleSpinBox(numericGroupBox);
        minValSpinBox->setObjectName("minValSpinBox");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, minValSpinBox);

        label_max = new QLabel(numericGroupBox);
        label_max->setObjectName("label_max");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_max);

        maxValSpinBox = new QDoubleSpinBox(numericGroupBox);
        maxValSpinBox->setObjectName("maxValSpinBox");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, maxValSpinBox);


        verticalLayout->addWidget(numericGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(RuleEditorDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        saveButton = new QPushButton(RuleEditorDialog);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RuleEditorDialog);

        QMetaObject::connectSlotsByName(RuleEditorDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleEditorDialog)
    {
        RuleEditorDialog->setWindowTitle(QCoreApplication::translate("RuleEditorDialog", "Rule Editor", nullptr));
        titleLabel->setText(QCoreApplication::translate("RuleEditorDialog", "Configure Validation", nullptr));
        requiredCheckBox->setText(QCoreApplication::translate("RuleEditorDialog", "Is Required Field", nullptr));
        label_length->setText(QCoreApplication::translate("RuleEditorDialog", "Expected Length:", nullptr));
        lengthSpinBox->setSpecialValueText(QCoreApplication::translate("RuleEditorDialog", "Any (-1)", nullptr));
        label_prefix->setText(QCoreApplication::translate("RuleEditorDialog", "Required Prefix:", nullptr));
        label_sub->setText(QCoreApplication::translate("RuleEditorDialog", "Required Substring:", nullptr));
        numericGroupBox->setTitle(QCoreApplication::translate("RuleEditorDialog", "Numeric Range Check", nullptr));
        label_min->setText(QCoreApplication::translate("RuleEditorDialog", "Minimum Value:", nullptr));
        label_max->setText(QCoreApplication::translate("RuleEditorDialog", "Maximum Value:", nullptr));
        cancelButton->setText(QCoreApplication::translate("RuleEditorDialog", "Cancel", nullptr));
        saveButton->setText(QCoreApplication::translate("RuleEditorDialog", "Save Rule", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleEditorDialog: public Ui_RuleEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEEDITORDIALOG_H
