/********************************************************************************
** Form generated from reading UI file 'BatchNameDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHNAMEDIALOG_H
#define UI_BATCHNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BatchNameDialog
{
public:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *hintLabel;
    QLineEdit *batchNameInput;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *cancelButton;
    QPushButton *startButton;

    void setupUi(QDialog *BatchNameDialog)
    {
        if (BatchNameDialog->objectName().isEmpty())
            BatchNameDialog->setObjectName("BatchNameDialog");
        BatchNameDialog->resize(400, 180);
        BatchNameDialog->setModal(true);
        BatchNameDialog->setMinimumSize(QSize(400, 180));
        BatchNameDialog->setMaximumSize(QSize(400, 180));
        mainLayout = new QVBoxLayout(BatchNameDialog);
        mainLayout->setSpacing(14);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(24, 24, 24, 20);
        titleLabel = new QLabel(BatchNameDialog);
        titleLabel->setObjectName("titleLabel");

        mainLayout->addWidget(titleLabel);

        hintLabel = new QLabel(BatchNameDialog);
        hintLabel->setObjectName("hintLabel");
        hintLabel->setWordWrap(true);

        mainLayout->addWidget(hintLabel);

        batchNameInput = new QLineEdit(BatchNameDialog);
        batchNameInput->setObjectName("batchNameInput");
        batchNameInput->setMinimumHeight(36);

        mainLayout->addWidget(batchNameInput);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        cancelButton = new QPushButton(BatchNameDialog);
        cancelButton->setObjectName("cancelButton");

        hboxLayout->addWidget(cancelButton);

        startButton = new QPushButton(BatchNameDialog);
        startButton->setObjectName("startButton");

        hboxLayout->addWidget(startButton);


        mainLayout->addLayout(hboxLayout);


        retranslateUi(BatchNameDialog);

        startButton->setDefault(true);


        QMetaObject::connectSlotsByName(BatchNameDialog);
    } // setupUi

    void retranslateUi(QDialog *BatchNameDialog)
    {
        BatchNameDialog->setWindowTitle(QCoreApplication::translate("BatchNameDialog", "Name This Batch", nullptr));
        titleLabel->setText(QCoreApplication::translate("BatchNameDialog", "Enter a name for this validation batch", nullptr));
        hintLabel->setText(QCoreApplication::translate("BatchNameDialog", "e.g. \"new_students\" or \"grad_files_2025\". No spaces; underscores are fine.", nullptr));
        batchNameInput->setPlaceholderText(QCoreApplication::translate("BatchNameDialog", "batch_name", nullptr));
        cancelButton->setText(QCoreApplication::translate("BatchNameDialog", "Cancel", nullptr));
        startButton->setText(QCoreApplication::translate("BatchNameDialog", "Start Validation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BatchNameDialog: public Ui_BatchNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHNAMEDIALOG_H
