#include "StandardsManagerWidget.h"
#include "ui_StandardsManagerWidget.h"
#include "RuleEditorDialog.h"

#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>

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

    // The standard fields 
    QStringList standardFields = { "ID", "Name", "GPA", "Email", "Phone" };

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
    )");
}