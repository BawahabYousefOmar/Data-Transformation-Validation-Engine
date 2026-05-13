#include "HeaderMappingDialog.h"
#include "ui_HeaderMappingDialog.h"

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
HeaderMappingDialog::HeaderMappingDialog(const QString& unknownColumn,
    QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::HeaderMappingDialog)
    , m_applyToAll(false)
    , m_unknownColumn(unknownColumn)
{
    ui->setupUi(this);

    // Display the unknown column name
    ui->unknownColumnValueLabel->setText(
        QString("  \"%1\"").arg(unknownColumn)
    );

    // Default: "Map to standard" radio is checked → combo is enabled
    ui->standardFieldCombo->setEnabled(true);

    applyStyleSheet();

    // Connect
    connect(ui->mapToStandardRadio, &QRadioButton::toggled,
        this, &HeaderMappingDialog::onMapToStandardToggled);
    connect(ui->applyToAllButton, &QPushButton::clicked,
        this, &HeaderMappingDialog::onApplyToAllClicked);
    connect(ui->confirmButton, &QPushButton::clicked,
        this, &HeaderMappingDialog::onConfirmClicked);
}

// ----------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------
HeaderMappingDialog::~HeaderMappingDialog()
{
    delete ui;
}

// ----------------------------------------------------------------
// Public Query Methods
// ----------------------------------------------------------------
bool HeaderMappingDialog::shouldSkip() const
{
    return ui->skipColumnRadio->isChecked();
}

QString HeaderMappingDialog::mappedKey() const
{
    if (shouldSkip()) return QString();
    return ui->standardFieldCombo->currentText();
}

bool HeaderMappingDialog::applyToAll() const
{
    return m_applyToAll;
}

// ----------------------------------------------------------------
// Private Slots
// ----------------------------------------------------------------
void HeaderMappingDialog::onMapToStandardToggled(bool checked)
{
    // Enable/disable the combo box based on which radio is active
    ui->standardFieldCombo->setEnabled(checked);
}

void HeaderMappingDialog::onApplyToAllClicked()
{
    m_applyToAll = true;
    accept(); // treat as confirmation with "apply to all" flag set
}

void HeaderMappingDialog::onConfirmClicked()
{
    accept();
}