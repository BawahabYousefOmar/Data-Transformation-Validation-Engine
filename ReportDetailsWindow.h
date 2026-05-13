#pragma once

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QMap>

// Include Amro's header to get the BatchRecord definition
#include "MainWindow.h" 

QT_BEGIN_NAMESPACE
namespace Ui { class ReportDetailsWindow; }
QT_END_NAMESPACE


class ReportDetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportDetailsWindow(const BatchRecord& batch, QWidget* parent = nullptr);
    ~ReportDetailsWindow();

private slots:
    void onExportValidClicked();
    void onExportInvalidClicked();
    void onExportReportClicked();

private:
    Ui::ReportDetailsWindow* ui;
    BatchRecord m_batch;
    QStringList m_standardKeys; // ID, Name, GPA, Email, Phone

    void setupTable();
    void populateTable();
    void applyStyleSheet();

    // Reusable helper to write out CSV files
    void exportToCsv(const QList<QMap<QString, QString>>& records,
        const QString& defaultFileName,
        const QList<QStringList>* errors = nullptr);
};