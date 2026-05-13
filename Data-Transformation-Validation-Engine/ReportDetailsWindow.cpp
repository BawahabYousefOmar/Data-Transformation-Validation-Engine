#include "ReportDetailsWindow.h"
#include "ui_ReportDetailsWindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
ReportDetailsWindow::ReportDetailsWindow(const BatchRecord& batch, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ReportDetailsWindow)
    , m_batch(batch)
{
    ui->setupUi(this);

    // Set up standard window properties
    setWindowTitle("Batch Details: " + batch.batchId);
    setAttribute(Qt::WA_DeleteOnClose); // Free memory when closed so we can open many
    resize(1024, 720);

    // Set UI labels
    ui->batchNameLabel->setText("Batch: " + batch.batchId);
    ui->statsLabel->setText(QString("Total: %1  |  Valid: %2  |  Invalid: %3")
        .arg(batch.totalRecords)
        .arg(batch.validCount)
        .arg(batch.invalidCount));

    m_standardKeys = { "ID", "Name", "GPA", "Email", "Phone" };

    setupTable();
    populateTable();
    applyStyleSheet();

    // Connect export buttons
    connect(ui->btnExportValid, &QPushButton::clicked, this, &ReportDetailsWindow::onExportValidClicked);
    connect(ui->btnExportInvalid, &QPushButton::clicked, this, &ReportDetailsWindow::onExportInvalidClicked);
    connect(ui->btnExportReport, &QPushButton::clicked, this, &ReportDetailsWindow::onExportReportClicked);

    // Disable export buttons if there is no corresponding data
    ui->btnExportValid->setEnabled(m_batch.validCount > 0);
    ui->btnExportInvalid->setEnabled(m_batch.invalidCount > 0);
    ui->btnExportReport->setEnabled(m_batch.invalidCount > 0);
}

ReportDetailsWindow::~ReportDetailsWindow()
{
    delete ui;
}

// ----------------------------------------------------------------
// Table Setup
// ----------------------------------------------------------------
void ReportDetailsWindow::setupTable()
{
    QStringList headers = m_standardKeys;
    headers << "Status" << "Error Details";

    ui->dataTable->setColumnCount(headers.size());
    ui->dataTable->setHorizontalHeaderLabels(headers);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(headers.size() - 1, QHeaderView::ResizeToContents);
    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ReportDetailsWindow::populateTable()
{
    ui->dataTable->setRowCount(0);

    // 1. Populate Valid Records
    for (const auto& recordMap : m_batch.validRecords) {
        int row = ui->dataTable->rowCount();
        ui->dataTable->insertRow(row);

        for (int col = 0; col < m_standardKeys.size(); col++) {
            ui->dataTable->setItem(row, col, new QTableWidgetItem(recordMap.value(m_standardKeys[col], "")));
        }

        auto* statusItem = new QTableWidgetItem("Valid");
        statusItem->setForeground(QBrush(QColor("#4CAF50"))); // Green
        ui->dataTable->setItem(row, m_standardKeys.size(), statusItem);
        ui->dataTable->setItem(row, m_standardKeys.size() + 1, new QTableWidgetItem("—"));
    }

    // 2. Populate Invalid Records
    for (int i = 0; i < m_batch.invalidRecords.size(); i++) {
        const auto& recordMap = m_batch.invalidRecords[i];
        int row = ui->dataTable->rowCount();
        ui->dataTable->insertRow(row);

        for (int col = 0; col < m_standardKeys.size(); col++) {
            auto* item = new QTableWidgetItem(recordMap.value(m_standardKeys[col], ""));
            item->setForeground(QBrush(QColor("#EF5350"))); // Red text
            ui->dataTable->setItem(row, col, item);
        }

        auto* statusItem = new QTableWidgetItem("Invalid");
        statusItem->setForeground(QBrush(QColor("#EF5350")));
        ui->dataTable->setItem(row, m_standardKeys.size(), statusItem);

        // Join the errors from the stack into a single string for the table
        QString errorStr = m_batch.errorLogs[i].join(" | ");
        auto* errorItem = new QTableWidgetItem(errorStr);
        errorItem->setForeground(QBrush(QColor("#EF5350")));
        ui->dataTable->setItem(row, m_standardKeys.size() + 1, errorItem);
    }
}

// ----------------------------------------------------------------
// Export Slots
// ----------------------------------------------------------------
void ReportDetailsWindow::onExportValidClicked()
{
    exportToCsv(m_batch.validRecords, m_batch.batchId + "_valid.csv");
}

void ReportDetailsWindow::onExportInvalidClicked()
{
    exportToCsv(m_batch.invalidRecords, m_batch.batchId + "_invalid_raw.csv");
}

void ReportDetailsWindow::onExportReportClicked()
{
    // Pass the error logs so they get appended as an extra column
    exportToCsv(m_batch.invalidRecords, m_batch.batchId + "_invalid_report.csv", &m_batch.errorLogs);
}

// ----------------------------------------------------------------
// Helper: Export to CSV
// ----------------------------------------------------------------
void ReportDetailsWindow::exportToCsv(const QList<QMap<QString, QString>>& records,
    const QString& defaultFileName,
    const QList<QStringList>* errors)
{
    QString filePath = QFileDialog::getSaveFileName(this, "Export CSV", defaultFileName, "CSV Files (*.csv)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Export Error", "Could not open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write Header Row
    QStringList headerRow = m_standardKeys;
    if (errors != nullptr) {
        headerRow << "Validation_Errors";
    }
    out << headerRow.join(",") << "\n";

    // Write Data Rows
    for (int i = 0; i < records.size(); i++) {
        QStringList rowData;
        for (const QString& key : m_standardKeys) {
            // Basic CSV escaping for fields that might contain commas
            QString val = records[i].value(key, "");
            if (val.contains(",")) val = "\"" + val + "\"";
            rowData << val;
        }

        if (errors != nullptr && i < errors->size()) {
            QString errStr = errors->at(i).join(" | ");
            if (errStr.contains(",")) errStr = "\"" + errStr + "\"";
            rowData << errStr;
        }

        out << rowData.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export Successful", "Data exported to:\n" + filePath);
}

// ----------------------------------------------------------------
// Style
// ----------------------------------------------------------------
void ReportDetailsWindow::applyStyleSheet()
{
    setStyleSheet(R"(
        QMainWindow { background: palette(window); }
        QLabel#batchNameLabel {
            font-size: 20px;
            font-weight: 800;
            color: #00BCD4;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel#statsLabel {
            font-size: 13px;
            color: palette(mid);
            font-family: monospace;
            padding-bottom: 10px;
        }
        QTableWidget#dataTable {
            border: 1px solid palette(mid);
            background: palette(base);
            font-family: monospace;
            font-size: 12px;
        }
        QHeaderView::section {
            background: rgba(0, 188, 212, 0.1);
            border: none;
            border-bottom: 1px solid palette(mid);
            padding: 8px;
            font-weight: bold;
            color: palette(text);
        }
        QPushButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
            color: palette(text);
        }
        QPushButton:hover {
            border-color: #00BCD4;
            color: #00BCD4;
        }
        QPushButton:disabled {
            color: palette(dark);
            border-color: palette(dark);
        }
        QPushButton#btnExportReport {
            background-color: rgba(239, 83, 80, 0.1);
            border-color: #EF5350;
            color: #EF5350;
        }
        QPushButton#btnExportReport:hover {
            background-color: #EF5350;
            color: #000;
        }
    )");
}