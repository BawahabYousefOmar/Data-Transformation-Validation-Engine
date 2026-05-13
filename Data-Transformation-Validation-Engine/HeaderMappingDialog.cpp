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

void HeaderMappingDialog::applyStyleSheet()
{
    setStyleSheet(R"(
        QDialog {
            background: palette(window);
        }
        QLabel#titleLabel {
            font-size: 14px;
            font-weight: bold;
            color: palette(text);
        }
        QLabel#warningIconLabel {
            font-size: 22px;
            color: #FFB300;
        }
        QLabel#descriptionLabel {
            font-size: 12px;
            color: palette(text);
        }
        QLabel#unknownColumnKeyLabel {
            font-size: 12px;
            color: palette(mid);
        }
        QLabel#unknownColumnValueLabel {
            font-size: 13px;
            font-weight: bold;
            font-family: monospace;
            color: #FF7043;
        }
        QRadioButton {
            font-size: 12px;
        }
        QComboBox {
            font-size: 12px;
            padding: 4px 8px;
            border: 1px solid palette(mid);
            border-radius: 4px;
        }
        QPushButton#confirmButton {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 6px;
            padding: 6px 20px;
            font-weight: bold;
        }
        QPushButton#confirmButton:hover {
            background-color: #26C6DA;
        }
        QPushButton#applyToAllButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 12px;
        }
        QPushButton#applyToAllButton:hover {
            border-color: #00BCD4;
            color: #00BCD4;
        }
    )");
}