#include "StandardsManagerWidget.h"
#include "ui_StandardsManagerWidget.h"
#include "RuleEditorDialog.h"

#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
StandardsManagerWidget::StandardsManagerWidget(bool isAdmin, HeaderProcessor* headerProc, RuleLoader* ruleLoader, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::StandardsManagerWidget)
    , m_isAdmin(isAdmin)
    , m_headerProc(headerProc)
    , m_ruleLoader(ruleLoader)
{
    ui->setupUi(this);

    // Security check, Disable UI if not admin 
    if (!m_isAdmin) {
        ui->standardsTable->setEnabled(false);
    }

    setupTable();
    populateTable();
    connect(ui->addFieldBtn, &QPushButton::clicked, this, &StandardsManagerWidget::onAddNewFieldClicked);
    connect(ui->saveDiskBtn, &QPushButton::clicked, this, &StandardsManagerWidget::onSaveToDiskClicked);
    applyStyleSheet();
}

StandardsManagerWidget::~StandardsManagerWidget()
{
    delete ui;
}

// ----------------------------------------------------------------
// Setup & Population
// ----------------------------------------------------------------
void StandardsManagerWidget::setupTable()
{
    ui->standardsTable->setColumnCount(4);
    ui->standardsTable->setHorizontalHeaderLabels({
        "Standard Field", "Mapped Aliases", "Active Rules", "Actions"
        });

    ui->standardsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->standardsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->standardsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->standardsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->standardsTable->setColumnWidth(3, 120);

    ui->standardsTable->verticalHeader()->setVisible(false);
    ui->standardsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->standardsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StandardsManagerWidget::populateTable()
{
    ui->standardsTable->setRowCount(0);
    //get rules names
    DynamicArray<string> backendKeys = m_ruleLoader->getRulesMap().getKeys();

    // append to the QStringList
    QStringList standardFields;
    for (int i = 0; i < backendKeys.getSize(); i++) {
        standardFields.append(QString::fromStdString(backendKeys.get(i)));
    }

    for (const QString& field : standardFields) {
        int row = ui->standardsTable->rowCount();
        ui->standardsTable->insertRow(row);
        ui->standardsTable->setRowHeight(row, 50);

        // Field Name
        auto* nameItem = new QTableWidgetItem(field);
        nameItem->setTextAlignment(Qt::AlignCenter);
        ui->standardsTable->setItem(row, 0, nameItem);

        auto* aliasItem = new QTableWidgetItem("Click to view/edit aliases");
        aliasItem->setForeground(QBrush(QColor("#8BA5B8")));
        ui->standardsTable->setItem(row, 1, aliasItem);

        // Rule Summary
        auto* ruleItem = new QTableWidgetItem(buildRuleSummary(field));
        ui->standardsTable->setItem(row, 2, ruleItem);

        // Action Button
        QPushButton* editBtn = new QPushButton("Edit Rules");
        editBtn->setObjectName("editRuleBtn");
        editBtn->setCursor(Qt::PointingHandCursor);

        connect(editBtn, &QPushButton::clicked, this, [this, field]() {
            openRuleEditor(field);
            });

        QWidget* btnContainer = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(btnContainer);
        layout->setContentsMargins(10, 5, 10, 5);
        layout->addWidget(editBtn);
        ui->standardsTable->setCellWidget(row, 3, btnContainer);
    }
}

// ----------------------------------------------------------------
// Slots
// ----------------------------------------------------------------
void StandardsManagerWidget::openRuleEditor(const QString& fieldName)
{
    // Retrieve the current rule from the backend
    Rule currentRule;
    m_ruleLoader->getRulesMap().get(fieldName.toStdString(), currentRule);

    // Open your modal dialog
    RuleEditorDialog dlg(fieldName, currentRule, this);
    if (dlg.exec() == QDialog::Accepted) {
        Rule updatedRule = dlg.getUpdatedRule();

        // Update the map in memory
        m_ruleLoader->updateRule(fieldName.toStdString(), updatedRule);

        // Refresh the table to show the new summary
        populateTable();


    }
}

// ----------------------------------------------------------------
// Helpers & Styling
// ----------------------------------------------------------------
QString StandardsManagerWidget::buildRuleSummary(const QString& fieldName) const
{
    Rule r;
    if (!m_ruleLoader->getRulesMap().get(fieldName.toStdString(), r)) {
        return "None";
    }

    QStringList conditions;
    if (r.getIsRequired()) conditions << "Required";
    if (r.getExpectedLength() != -1) conditions << QString("Length: %1").arg(r.getExpectedLength());
    if (r.getCheckNumericRange()) conditions << QString("Range: [%1 - %2]").arg(r.getMinVal()).arg(r.getMaxVal());
    if (!r.getRequiredPrefix().empty()) conditions << QString("Prefix: '%1'").arg(QString::fromStdString(r.getRequiredPrefix()));
    if (!r.getRequiredSubstring().empty()) conditions << QString("Contains: '%1'").arg(QString::fromStdString(r.getRequiredSubstring()));

    return conditions.isEmpty() ? "None" : conditions.join(" | ");
}

void StandardsManagerWidget::onAddNewFieldClicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Add New Standard Field",
        "Enter the name of the new field (e.g. Department, Age):",
        QLineEdit::Normal, "", &ok);

    if (ok && !text.trimmed().isEmpty()) {
        QString field = text.trimmed();

        // Create a blank rule and add it to the backend
        Rule newRule;
        m_ruleLoader->updateRule(field.toStdString(), newRule);

        // Refresh the table so it shows up immediately
        populateTable();

        // Automatically open the editor
        openRuleEditor(field);
    }
}

void StandardsManagerWidget::onSaveToDiskClicked()
{
    // Call the new backend function we just wrote
    if (m_ruleLoader->saveToFile("rules.txt")) {
        QMessageBox::information(this, "Success", "All rules have been successfully saved to rules.txt!");
    }
    else {
        QMessageBox::critical(this, "Error", "Failed to save to rules.txt. Check file permissions.");
    }
}
void StandardsManagerWidget::applyStyleSheet()
{
    setStyleSheet(R"(
        QWidget { background: palette(window); }
        QLabel#titleLabel {
            font-size: 20px;
            font-weight: 800;
            color: palette(text);
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#subtitleLabel {
            font-size: 12px;
            color: palette(mid);
        }
        QTableWidget#standardsTable {
            border: 1px solid palette(mid);
            border-radius: 8px;
            background: palette(base);
            gridline-color: rgba(255, 255, 255, 0.05);
            font-size: 13px;
        }
        QHeaderView::section {
            background: rgba(0, 188, 212, 0.1);
            border: none;
            border-bottom: 1px solid palette(mid);
            padding: 8px;
            font-weight: bold;
            color: #00BCD4;
            text-transform: uppercase;
            font-size: 11px;
        }
        QPushButton#editRuleBtn {
            background-color: transparent;
            color: #00BCD4;
            border: 1px solid #00BCD4;
            border-radius: 4px;
            font-weight: bold;
            font-size: 11px;
        }
        QPushButton#editRuleBtn:hover {
            background-color: #00BCD4;
            color: #000;
        }
        
        /* --- NEW BUTTON STYLES --- */
        
        /* Secondary Button Style */
        QPushButton#addFieldBtn {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 0px 16px;
            font-size: 12px;
            font-weight: bold;
            color: palette(text);
        }
        QPushButton#addFieldBtn:hover {
            border-color: #00BCD4;
            color: #00BCD4;
        }
        
        /* Primary Action Button Style */
        QPushButton#saveDiskBtn {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 6px;
            padding: 0px 16px;
            font-weight: bold;
            font-size: 12px;
        }
        QPushButton#saveDiskBtn:hover {
            background-color: #26C6DA;
        }
    )");
}