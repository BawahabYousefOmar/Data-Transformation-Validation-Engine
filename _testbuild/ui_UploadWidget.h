/********************************************************************************
** Form generated from reading UI file 'UploadWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADWIDGET_H
#define UI_UPLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UploadWidget
{
public:
    QHBoxLayout *mainLayout;
    QFrame *dropZoneFrame;
    QVBoxLayout *dropZoneLayout;
    QSpacerItem *topSpacer;
    QLabel *dropIconLabel;
    QLabel *dropMainLabel;
    QLabel *dropSubLabel;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLabel *orDividerLabel;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *browseButton;
    QSpacerItem *spacerItem3;
    QSpacerItem *bottomSpacer;
    QFrame *queueFrame;
    QVBoxLayout *queueLayout;
    QHBoxLayout *hboxLayout2;
    QLabel *queueTitleLabel;
    QSpacerItem *spacerItem4;
    QPushButton *clearQueueButton;
    QFrame *queueDivider;
    QListWidget *fileQueueList;
    QLabel *fileCountLabel;
    QPushButton *validateButton;

    void setupUi(QWidget *UploadWidget)
    {
        if (UploadWidget->objectName().isEmpty())
            UploadWidget->setObjectName("UploadWidget");
        UploadWidget->resize(820, 600);
        mainLayout = new QHBoxLayout(UploadWidget);
        mainLayout->setSpacing(16);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(20, 20, 20, 20);
        dropZoneFrame = new QFrame(UploadWidget);
        dropZoneFrame->setObjectName("dropZoneFrame");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dropZoneFrame->sizePolicy().hasHeightForWidth());
        dropZoneFrame->setSizePolicy(sizePolicy);
        dropZoneFrame->setFrameShape(QFrame::StyledPanel);
        dropZoneLayout = new QVBoxLayout(dropZoneFrame);
        dropZoneLayout->setSpacing(12);
        dropZoneLayout->setObjectName("dropZoneLayout");
        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        dropZoneLayout->addItem(topSpacer);

        dropIconLabel = new QLabel(dropZoneFrame);
        dropIconLabel->setObjectName("dropIconLabel");
        dropIconLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        dropZoneLayout->addWidget(dropIconLabel);

        dropMainLabel = new QLabel(dropZoneFrame);
        dropMainLabel->setObjectName("dropMainLabel");
        dropMainLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        dropZoneLayout->addWidget(dropMainLabel);

        dropSubLabel = new QLabel(dropZoneFrame);
        dropSubLabel->setObjectName("dropSubLabel");
        dropSubLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        dropZoneLayout->addWidget(dropSubLabel);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        orDividerLabel = new QLabel(dropZoneFrame);
        orDividerLabel->setObjectName("orDividerLabel");
        orDividerLabel->setAlignment(Qt::AlignHCenter);

        hboxLayout->addWidget(orDividerLabel);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        dropZoneLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        browseButton = new QPushButton(dropZoneFrame);
        browseButton->setObjectName("browseButton");
        browseButton->setMinimumSize(QSize(140, 38));

        hboxLayout1->addWidget(browseButton);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);


        dropZoneLayout->addLayout(hboxLayout1);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        dropZoneLayout->addItem(bottomSpacer);


        mainLayout->addWidget(dropZoneFrame);

        queueFrame = new QFrame(UploadWidget);
        queueFrame->setObjectName("queueFrame");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(queueFrame->sizePolicy().hasHeightForWidth());
        queueFrame->setSizePolicy(sizePolicy1);
        queueFrame->setMinimumWidth(240);
        queueFrame->setFrameShape(QFrame::StyledPanel);
        queueLayout = new QVBoxLayout(queueFrame);
        queueLayout->setSpacing(10);
        queueLayout->setObjectName("queueLayout");
        queueLayout->setContentsMargins(12, 16, 12, 16);
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        queueTitleLabel = new QLabel(queueFrame);
        queueTitleLabel->setObjectName("queueTitleLabel");

        hboxLayout2->addWidget(queueTitleLabel);

        spacerItem4 = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem4);

        clearQueueButton = new QPushButton(queueFrame);
        clearQueueButton->setObjectName("clearQueueButton");
        clearQueueButton->setMaximumWidth(60);

        hboxLayout2->addWidget(clearQueueButton);


        queueLayout->addLayout(hboxLayout2);

        queueDivider = new QFrame(queueFrame);
        queueDivider->setObjectName("queueDivider");
        queueDivider->setFrameShape(QFrame::HLine);
        queueDivider->setFrameShadow(QFrame::Sunken);

        queueLayout->addWidget(queueDivider);

        fileQueueList = new QListWidget(queueFrame);
        fileQueueList->setObjectName("fileQueueList");
        fileQueueList->setSelectionMode(QAbstractItemView::SingleSelection);
        fileQueueList->setAlternatingRowColors(true);

        queueLayout->addWidget(fileQueueList);

        fileCountLabel = new QLabel(queueFrame);
        fileCountLabel->setObjectName("fileCountLabel");
        fileCountLabel->setAlignment(Qt::AlignRight);

        queueLayout->addWidget(fileCountLabel);

        validateButton = new QPushButton(queueFrame);
        validateButton->setObjectName("validateButton");
        validateButton->setMinimumHeight(44);
        validateButton->setEnabled(false);

        queueLayout->addWidget(validateButton);


        mainLayout->addWidget(queueFrame);


        retranslateUi(UploadWidget);

        QMetaObject::connectSlotsByName(UploadWidget);
    } // setupUi

    void retranslateUi(QWidget *UploadWidget)
    {
        UploadWidget->setWindowTitle(QCoreApplication::translate("UploadWidget", "File Upload", nullptr));
        dropIconLabel->setText(QCoreApplication::translate("UploadWidget", "\342\254\206", nullptr));
        dropMainLabel->setText(QCoreApplication::translate("UploadWidget", "Drag & Drop Files Here", nullptr));
        dropSubLabel->setText(QCoreApplication::translate("UploadWidget", "Accepts .csv and .txt files", nullptr));
        orDividerLabel->setText(QCoreApplication::translate("UploadWidget", "\342\200\224 or \342\200\224", nullptr));
        browseButton->setText(QCoreApplication::translate("UploadWidget", "Browse Files", nullptr));
        queueTitleLabel->setText(QCoreApplication::translate("UploadWidget", "Upload Queue", nullptr));
        clearQueueButton->setText(QCoreApplication::translate("UploadWidget", "Clear", nullptr));
        fileCountLabel->setText(QCoreApplication::translate("UploadWidget", "0 file(s) queued", nullptr));
        validateButton->setText(QCoreApplication::translate("UploadWidget", "\342\226\266  Validate Batch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UploadWidget: public Ui_UploadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADWIDGET_H
