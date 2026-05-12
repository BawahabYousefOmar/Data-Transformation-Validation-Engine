#include "RuleEditorDialog.h"
#include "ui_RuleEditorDialog.h"

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
RuleEditorDialog::RuleEditorDialog(const QString& fieldName, const Rule& currentRule, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::RuleEditorDialog)
    , m_fieldName(fieldName)
    , m_rule(currentRule)
{
    ui->setupUi(this);
    setWindowTitle("Edit Rule: " + fieldName);

    ui->titleLabel->setText(QString("Configure Validation: %1").arg(fieldName));

    // Defaulting UI state
    ui->requiredCheckBox->setChecked(false); 
    ui->lengthSpinBox->setValue(-1);

    ui->minValSpinBox->setMinimum(-999999.0);
    ui->minValSpinBox->setMaximum(999999.0);
    ui->maxValSpinBox->setMinimum(-999999.0);
    ui->maxValSpinBox->setMaximum(999999.0);

    // Group box toggles the numeric range requirement
    ui->numericGroupBox->setChecked(false);

    applyStyleSheet();

    connect(ui->saveButton, &QPushButton::clicked, this, &RuleEditorDialog::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RuleEditorDialog::onCancelClicked);
    connect(ui->numericGroupBox, &QGroupBox::toggled, this, &RuleEditorDialog::onNumericRangeToggled);
}

RuleEditorDialog::~RuleEditorDialog()
{
    delete ui;
}


Rule RuleEditorDialog::getUpdatedRule() const
{
    return m_rule;
}

// ----------------------------------------------------------------
// Slots
// ----------------------------------------------------------------
void RuleEditorDialog::onSaveClicked()
{
    // Rebuild the rule based on UI inputs
    m_rule.setRequired(ui->requiredCheckBox->isChecked());
    m_rule.setExpectedLength(ui->lengthSpinBox->value());

    QString prefix = ui->prefixInput->text().trimmed();
    if (!prefix.isEmpty()) m_rule.setRequiredPrefix(prefix.toStdString());

    QString sub = ui->substringInput->text().trimmed();
    if (!sub.isEmpty()) m_rule.setRequiredSubstring(sub.toStdString());

    if (ui->numericGroupBox->isChecked()) {
        m_rule.setMinVal(ui->minValSpinBox->value());
        m_rule.setMaxVal(ui->maxValSpinBox->value());
    }

    accept();
}

void RuleEditorDialog::onCancelClicked()
{
    reject();
}

void RuleEditorDialog::onNumericRangeToggled(bool checked)
{
    ui->minValSpinBox->setEnabled(checked);
    ui->maxValSpinBox->setEnabled(checked);
}

// ----------------------------------------------------------------
// Styling 
// ----------------------------------------------------------------
void RuleEditorDialog::applyStyleSheet()
{
    setStyleSheet(R"(
        QDialog { background: palette(window); }
        QLabel#titleLabel {
            font-size: 16px;
            font-weight: bold;
            color: #00BCD4;
        }
        QGroupBox {
            font-weight: bold;
            border: 1px solid palette(mid);
            border-radius: 6px;
            margin-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 3px 0 3px;
        }
        QLineEdit, QDoubleSpinBox, QSpinBox {
            border: 1px solid palette(mid);
            border-radius: 4px;
            padding: 4px;
            background: palette(base);
        }
        QLineEdit:focus, QDoubleSpinBox:focus, QSpinBox:focus {
            border-color: #00BCD4;
        }
        QPushButton#saveButton {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton#saveButton:hover { background-color: #26C6DA; }
        QPushButton#cancelButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 8px 16px;
        }
        QPushButton#cancelButton:hover { border-color: #E57373; color: #E57373; }
    )");
}