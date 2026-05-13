#include "BatchNameDialog.h"
#include "ui_BatchNameDialog.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

BatchNameDialog::BatchNameDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BatchNameDialog)
{
    ui->setupUi(this);

    QRegularExpression rx("[A-Za-z0-9_\\-]+");
    ui->batchNameInput->setValidator(new QRegularExpressionValidator(rx, this));

    ui->startButton->setEnabled(false);

    applyStyleSheet();

    connect(ui->startButton,    &QPushButton::clicked,
            this, &BatchNameDialog::onStartClicked);
    connect(ui->cancelButton,   &QPushButton::clicked,
            this, &BatchNameDialog::onCancelClicked);
    connect(ui->batchNameInput, &QLineEdit::textChanged,
            this, &BatchNameDialog::onInputChanged);
}

BatchNameDialog::~BatchNameDialog()
{
    delete ui;
}

QString BatchNameDialog::batchName() const
{
    return ui->batchNameInput->text().trimmed();
}

void BatchNameDialog::onStartClicked()
{
    accept();
}

void BatchNameDialog::onCancelClicked()
{
    reject();
}

void BatchNameDialog::onInputChanged(const QString& text)
{
    ui->startButton->setEnabled(!text.trimmed().isEmpty());
}

void BatchNameDialog::applyStyleSheet()
{
    setStyleSheet(R"(
        QDialog { background: palette(window); }
        QLabel#titleLabel {
            font-size: 14px;
            font-weight: bold;
        }
        QLabel#hintLabel {
            font-size: 11px;
            color: palette(mid);
        }
        QLineEdit#batchNameInput {
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 6px 10px;
            font-size: 13px;
            font-family: monospace;
        }
        QLineEdit#batchNameInput:focus {
            border-color: #00BCD4;
        }
        QPushButton#startButton {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 6px;
            padding: 7px 20px;
            font-weight: bold;
        }
        QPushButton#startButton:hover  { background-color: #26C6DA; }
        QPushButton#startButton:disabled {
            background-color: palette(mid);
            color: palette(dark);
        }
        QPushButton#cancelButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 7px 16px;
        }
        QPushButton#cancelButton:hover { border-color: #E57373; color: #E57373; }
    )");
}
