#pragma once

#include <QMainWindow>
#include <QString>
#include <QStringList>

// Backend includes
#include "HeaderProcessor.h"
#include "RecordParser.h"
#include "RuleLoader.h"
#include "Validator.h"
#include "DynamicArray.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Stack.h"

// Forward declarations 
class UploadWidget;
class ReportsTableWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ============================================================
//  BatchRecord
// ============================================================
struct BatchRecord {
    QString batchId;          // e.g. "new_students_2025_05_05_12:45:17"
    QStringList sourceFiles;
    int totalRecords  = 0;
    int validCount    = 0;
    int invalidCount  = 0;
    QString timestamp;        // ISO-8601 string
    QString noteFilePath;     // path to .txt note file (may not exist yet)

    // Raw record data (kept in memory so Details window can open it)
    // valid[i] and invalid[i] are HashMaps with string keys/values
    // We store them as QList of QMap for Qt-friendliness
    QList<QMap<QString,QString>> validRecords;
    QList<QMap<QString,QString>> invalidRecords;
    QList<QStringList>           errorLogs;    // parallel to invalidRecords
};

// ============================================================
//  MainWindow
//=============================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // isAdmin controls whether the Standards Manager nav item is visible
    explicit MainWindow(bool isAdmin, const QString& username,
                        QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    // Connected to UploadWidget::filesReadyForValidation
    void onRunPipeline(QStringList filePaths, QString batchName);

    // Connected from ReportsTableWidget
    void onOpenDetails(const QString& batchId);
    void onOpenNote(const QString& batchId);

private slots:
    void onNavUpload();
    void onNavReports();
    void onNavStandards();
    void onLogout();

private:
    Ui::MainWindow* ui;

    bool    m_isAdmin;
    QString m_username;

    // Child widgets embedded into the page stack
    UploadWidget*       m_uploadWidget   = nullptr;
    ReportsTableWidget* m_reportsWidget  = nullptr;

    // In-memory store of processed batches
    QMap<QString, BatchRecord> m_batches;

    // Shared backend objects 
    HeaderProcessor* m_headerProcessor = nullptr;
    RuleLoader*      m_ruleLoader      = nullptr;

    // ── Helpers ──────────────────────────────────────────────
    void setupWidgets();
    void setupSidebar();
    void applyStyleSheet();
    void setActivePage(int pageIndex, const QString& heading);
    void setNavButtonActive(QPushButton* btn);
    void setStatus(const QString& message);

    // Pipeline helpers
    QString buildBatchId(const QString& batchName) const;
    BatchRecord runValidationPipeline(const QStringList& filePaths,
                                      const QString& batchId);

    // Convert backend types to Qt-friendly maps
    static QMap<QString,QString> hashMapToQMap(const HashMap<string>& hm);
};
