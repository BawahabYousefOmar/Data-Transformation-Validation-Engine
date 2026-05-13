#include "BatchNameDialog.h"
#include "ui_BatchNameDialog.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
BatchNameDialog::BatchNameDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BatchNameDialog)
{
    ui->setupUi(this);

    // Only allow alphanumeric + underscore + hyphen (no spaces)
    QRegularExpression rx("[A-Za-z0-9_\\-]+");
    ui->batchNameInput->setValidator(new QRegularExpressionValidator(rx, this));

    // Start button disabled until there's text
    ui->startButton->setEnabled(false);

    applyStyleSheet();

    connect(ui->startButton, &QPushButton::clicked,
        this, &BatchNameDialog::onStartClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
        this, &BatchNameDialog::onCancelClicked);
    connect(ui->batchNameInput, &QLineEdit::textChanged,
        this, &BatchNameDialog::onInputChanged);
}

// ----------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------
BatchNameDialog::~BatchNameDialog()
{
    delete ui;
}

// ----------------------------------------------------------------
// Public API
// ----------------------------------------------------------------
QString BatchNameDialog::batchName() const
{
    return ui->batchNameInput->text().trimmed();
}

// ----------------------------------------------------------------
// Slots
// ----------------------------------------------------------------
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
