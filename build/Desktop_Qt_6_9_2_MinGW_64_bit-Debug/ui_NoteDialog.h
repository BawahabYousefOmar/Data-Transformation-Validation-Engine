/********************************************************************************
** Form generated from reading UI file 'NoteDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEDIALOG_H
#define UI_NOTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NoteDialog
{
public:
    QVBoxLayout *rootLayout;
    QHBoxLayout *hboxLayout;
    QLabel *noteIconLabel;
    QVBoxLayout *vboxLayout;
    QLabel *noteTitleLabel;
    QLabel *noteSubtitleLabel;
    QSpacerItem *spacerItem;
    QLabel *fileStatusLabel;
    QFrame *noteDivider;
    QPlainTextEdit *noteEditor;
    QHBoxLayout *hboxLayout1;
    QLabel *wordCountLabel;
    QSpacerItem *spacerItem1;
    QLabel *unsavedLabel;
    QHBoxLayout *hboxLayout2;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem2;
    QPushButton *clearButton;
    QPushButton *saveButton;

    void setupUi(QDialog *NoteDialog)
    {
        if (NoteDialog->objectName().isEmpty())
            NoteDialog->setObjectName("NoteDialog");
        NoteDialog->resize(560, 440);
        rootLayout = new QVBoxLayout(NoteDialog);
        rootLayout->setSpacing(12);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(24, 24, 24, 20);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        noteIconLabel = new QLabel(NoteDialog);
        noteIconLabel->setObjectName("noteIconLabel");

        hboxLayout->addWidget(noteIconLabel);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(2);
        vboxLayout->setObjectName("vboxLayout");
        noteTitleLabel = new QLabel(NoteDialog);
        noteTitleLabel->setObjectName("noteTitleLabel");

        vboxLayout->addWidget(noteTitleLabel);

        noteSubtitleLabel = new QLabel(NoteDialog);
        noteSubtitleLabel->setObjectName("noteSubtitleLabel");

        vboxLayout->addWidget(noteSubtitleLabel);


        hboxLayout->addLayout(vboxLayout);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        fileStatusLabel = new QLabel(NoteDialog);
        fileStatusLabel->setObjectName("fileStatusLabel");

        hboxLayout->addWidget(fileStatusLabel);


        rootLayout->addLayout(hboxLayout);

        noteDivider = new QFrame(NoteDialog);
        noteDivider->setObjectName("noteDivider");
        noteDivider->setFrameShape(QFrame::HLine);
        noteDivider->setFrameShadow(QFrame::Plain);

        rootLayout->addWidget(noteDivider);

        noteEditor = new QPlainTextEdit(NoteDialog);
        noteEditor->setObjectName("noteEditor");
        noteEditor->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        rootLayout->addWidget(noteEditor);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        wordCountLabel = new QLabel(NoteDialog);
        wordCountLabel->setObjectName("wordCountLabel");

        hboxLayout1->addWidget(wordCountLabel);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        unsavedLabel = new QLabel(NoteDialog);
        unsavedLabel->setObjectName("unsavedLabel");

        hboxLayout1->addWidget(unsavedLabel);


        rootLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        cancelButton = new QPushButton(NoteDialog);
        cancelButton->setObjectName("cancelButton");

        hboxLayout2->addWidget(cancelButton);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem2);

        clearButton = new QPushButton(NoteDialog);
        clearButton->setObjectName("clearButton");

        hboxLayout2->addWidget(clearButton);

        saveButton = new QPushButton(NoteDialog);
        saveButton->setObjectName("saveButton");

        hboxLayout2->addWidget(saveButton);


        rootLayout->addLayout(hboxLayout2);


        retranslateUi(NoteDialog);

        QMetaObject::connectSlotsByName(NoteDialog);
    } // setupUi

    void retranslateUi(QDialog *NoteDialog)
    {
        NoteDialog->setWindowTitle(QCoreApplication::translate("NoteDialog", "Batch Note", nullptr));
        noteIconLabel->setText(QCoreApplication::translate("NoteDialog", "\360\237\223\235", nullptr));
        noteTitleLabel->setText(QCoreApplication::translate("NoteDialog", "Batch Note", nullptr));
        noteSubtitleLabel->setText(QCoreApplication::translate("NoteDialog", "\342\200\224", nullptr));
        fileStatusLabel->setText(QCoreApplication::translate("NoteDialog", "No file", nullptr));
        noteEditor->setPlaceholderText(QCoreApplication::translate("NoteDialog", "Write your observations, comments, or follow-up actions here\342\200\246", nullptr));
        wordCountLabel->setText(QCoreApplication::translate("NoteDialog", "0 words", nullptr));
        unsavedLabel->setText(QString());
        cancelButton->setText(QCoreApplication::translate("NoteDialog", "Cancel", nullptr));
        clearButton->setText(QCoreApplication::translate("NoteDialog", "Clear", nullptr));
        saveButton->setText(QCoreApplication::translate("NoteDialog", "Save Note", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoteDialog: public Ui_NoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEDIALOG_H
