#pragma once

#include <QMainWindow>
#include <QPushButton>
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

class UploadWidget;
class ReportsTableWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


// One validation run: counts, file list, and row data for the reports UI.
struct BatchRecord {
    QString batchId;
    QStringList sourceFiles;
    int totalRecords  = 0;
    int validCount    = 0;
    int invalidCount  = 0;
    QString timestamp;
    QString noteFilePath;

    QList<QMap<QString,QString>> validRecords;
    QList<QMap<QString,QString>> invalidRecords;
    QList<QStringList>           errorLogs;
};

// Main shell: navigation, upload pipeline, reports, role-based standards access.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isAdmin, const QString& username,
                        QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onRunPipeline(QStringList filePaths, QString batchName);

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

    UploadWidget*       m_uploadWidget   = nullptr;
    ReportsTableWidget* m_reportsWidget  = nullptr;

    QMap<QString, BatchRecord> m_batches;

    HeaderProcessor* m_headerProcessor = nullptr;
    RuleLoader*      m_ruleLoader      = nullptr;

    void setupWidgets();
    void setupSidebar();
    void applyStyleSheet();
    void setActivePage(int pageIndex, const QString& heading);
    void setNavButtonActive(QPushButton* btn);
    void setStatus(const QString& message);

    QString buildBatchId(const QString& batchName) const;
    BatchRecord runValidationPipeline(const QStringList& filePaths,
                                      const QString& batchId);

    static QMap<QString,QString> hashMapToQMap(const HashMap<string>& hm);
};
