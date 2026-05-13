#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "UploadWidget.h"
#include "ReportsTableWidget.h"
#include "NoteDialog.h"
#include "HeaderMappingDialog.h"

// #include "StandardsManagerWidget.h"

#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <fstream>
#include <string>

using namespace std;

namespace {

QString pathToBundledFile(const QString& fileName)
{
    const QString roots[] = {
        QCoreApplication::applicationDirPath(),
        QDir::currentPath(),
    };
    for (const QString& root : roots) {
        QDir dir(root);
        for (int i = 0; i < 12; ++i) {
            const QString candidate = dir.filePath(fileName);
            if (QFileInfo::exists(candidate))
                return QFileInfo(candidate).absoluteFilePath();
            if (!dir.cdUp())
                break;
        }
    }
    return {};
}

} // namespace

MainWindow::MainWindow(bool isAdmin, const QString& username, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_isAdmin(isAdmin)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("DataValve — Data Validation Engine");
    resize(1280, 800);

    m_headerProcessor = new HeaderProcessor();
    const QString headersPath = pathToBundledFile(QStringLiteral("headers.txt"));
    const std::string headersStd = headersPath.isEmpty()
        ? std::string("headers.txt")
        : std::string(QFile::encodeName(headersPath).constData());
    if (!m_headerProcessor->loadFromFile(headersStd)) {
        QMessageBox::critical(this, "Startup Error",
            "Could not load headers.txt.\nMake sure it is in the working directory.");
    }

    m_ruleLoader = new RuleLoader();
    const QString rulesPath = pathToBundledFile(QStringLiteral("rules.txt"));
    const std::string rulesStd = rulesPath.isEmpty()
        ? std::string("rules.txt")
        : std::string(QFile::encodeName(rulesPath).constData());
    if (!m_ruleLoader->loadFromFile(rulesStd)) {
        QMessageBox::critical(this, "Startup Error",
            "Could not load rules.txt.\nMake sure it is in the working directory.");
    }

    setupWidgets();
    setupSidebar();
    applyStyleSheet();

    onNavUpload();
}

MainWindow::~MainWindow()
{
    delete m_headerProcessor;
    delete m_ruleLoader;
    delete ui;
}

// Runs validation after the user picks files and a batch name on the upload page.
void MainWindow::onRunPipeline(QStringList filePaths, QString batchName)
{
    if (filePaths.isEmpty()) return;

    setStatus("Running pipeline for batch: " + batchName + " …");
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString batchId = buildBatchId(batchName);

    BatchRecord result = runValidationPipeline(filePaths, batchId);

    m_batches.insert(batchId, result);

    if (m_reportsWidget)
        m_reportsWidget->addBatch(result);

    QApplication::restoreOverrideCursor();
    setStatus(QString("Batch '%1' complete — %2 valid, %3 invalid.")
              .arg(batchName)
              .arg(result.validCount)
              .arg(result.invalidCount));

    onNavReports();
}

void MainWindow::onOpenDetails(const QString& batchId)
{
    if (!m_batches.contains(batchId)) return;

    QMessageBox::information(this, "Details",
        QString("Batch details view is not implemented yet.\n\nBatch: %1").arg(batchId));
}

void MainWindow::onOpenNote(const QString& batchId)
{
    if (!m_batches.contains(batchId)) return;

    BatchRecord& batch = m_batches[batchId];
    NoteDialog dlg(batch.batchId, batch.noteFilePath, this);
    if (dlg.exec() == QDialog::Accepted) {
        batch.noteFilePath = dlg.noteFilePath();
    }
}

void MainWindow::onNavUpload()
{
    setActivePage(0, "Upload & Validate");
    setNavButtonActive(ui->navUploadBtn);
}

void MainWindow::onNavReports()
{
    setActivePage(1, "Reports");
    setNavButtonActive(ui->navReportsBtn);
}

void MainWindow::onNavStandards()
{
    if (!m_isAdmin) {
        QMessageBox::warning(this, "Access Denied",
            "Only Admins can access the Standards Manager.");
        return;
    }
    setActivePage(2, "Standards Manager");
    setNavButtonActive(ui->navStandardsBtn);
}

void MainWindow::onLogout()
{
    close();
}

void MainWindow::setupWidgets()
{
    m_uploadWidget = new UploadWidget(this);
    QLayout* uploadLayout = ui->pageUpload->layout();
    delete uploadLayout->takeAt(0)->widget();
    uploadLayout->addWidget(m_uploadWidget);

    connect(m_uploadWidget, &UploadWidget::filesReadyForValidation,
            this, &MainWindow::onRunPipeline);

    m_reportsWidget = new ReportsTableWidget(this);
    QLayout* reportsLayout = ui->pageReports->layout();
    delete reportsLayout->takeAt(0)->widget();
    reportsLayout->addWidget(m_reportsWidget);

    connect(m_reportsWidget, &ReportsTableWidget::detailsRequested,
            this, &MainWindow::onOpenDetails);
    connect(m_reportsWidget, &ReportsTableWidget::noteRequested,
            this, &MainWindow::onOpenNote);
}

void MainWindow::setupSidebar()
{
    ui->userNameLabel->setText(m_username);
    ui->userRoleLabel->setText(m_isAdmin ? "Admin" : "Worker");

    if (!m_isAdmin) {
        ui->sectionAdminLabel->setVisible(false);
        ui->navStandardsBtn->setVisible(false);
    }

    connect(ui->navUploadBtn,    &QPushButton::clicked, this, &MainWindow::onNavUpload);
    connect(ui->navReportsBtn,   &QPushButton::clicked, this, &MainWindow::onNavReports);
    connect(ui->navStandardsBtn, &QPushButton::clicked, this, &MainWindow::onNavStandards);
    connect(ui->logoutButton,    &QPushButton::clicked, this, &MainWindow::onLogout);
}

void MainWindow::setActivePage(int pageIndex, const QString& heading)
{
    ui->pageStack->setCurrentIndex(pageIndex);
    ui->pageHeadingLabel->setText(heading);
}

void MainWindow::setNavButtonActive(QPushButton* activeBtn)
{
    for (QPushButton* btn : {ui->navUploadBtn, ui->navReportsBtn, ui->navStandardsBtn}) {
        btn->setChecked(btn == activeBtn);
    }
}

void MainWindow::setStatus(const QString& message)
{
    ui->statusBarLabel->setText(message);
}

QString MainWindow::buildBatchId(const QString& batchName) const
{
    QString ts = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh:mm:ss");
    return batchName + "_" + ts;
}

BatchRecord MainWindow::runValidationPipeline(const QStringList& filePaths,
                                               const QString& batchId)
{
    BatchRecord result;
    result.batchId    = batchId;
    result.sourceFiles = filePaths;
    result.timestamp  = QDateTime::currentDateTime().toString(Qt::ISODate);
    result.noteFilePath = "note_" + batchId + ".txt";

    RecordParser parser(*m_headerProcessor);

    parser.setUnknownHeaderCallback([this](const string& rawCol) -> string {
        HeaderMappingDialog dlg(QString::fromStdString(rawCol), this);
        if (dlg.exec() != QDialog::Accepted) return "";
        if (dlg.shouldSkip()) return "";
        return dlg.mappedKey().toStdString();
    });

    for (const QString& path : filePaths) {
        std::ifstream file(path.toStdString());
        if (!file.is_open()) {
            setStatus("Warning: could not open " + path);
            continue;
        }
        std::string line;
        if (std::getline(file, line))
            parser.setHeader(line);
        while (std::getline(file, line))
            parser.parseLine(line);
        file.close();
    }

    const DynamicArray<HashMap<string>>& allRecords = parser.getRecords();
    result.totalRecords = allRecords.getSize();

    Validator validator;
    HashSet<string> seenIds;
    const HashMap<Rule>& rules = m_ruleLoader->getRulesMap();

    for (int i = 0; i < allRecords.getSize(); i++) {
        HashMap<string> rec = allRecords.get(i);
        Stack<string> errors = validator.validateRecord(rec, rules, seenIds);

        QMap<QString,QString> qrec = hashMapToQMap(rec);

        if (errors.isEmpty()) {
            result.validRecords.append(qrec);
            result.validCount++;
        } else {
            result.invalidRecords.append(qrec);
            result.invalidCount++;

            QStringList errList;
            while (!errors.isEmpty())
                errList.prepend(QString::fromStdString(errors.pop()));
            result.errorLogs.append(errList);
        }
    }

    return result;
}

QMap<QString,QString> MainWindow::hashMapToQMap(const HashMap<string>& hm)
{
    QMap<QString,QString> out;
    DynamicArray<string> keys = hm.getKeys();
    for (int i = 0; i < keys.getSize(); i++) {
        string val;
        hm.get(keys.get(i), val);
        out.insert(QString::fromStdString(keys.get(i)),
                   QString::fromStdString(val));
    }
    return out;
}

void MainWindow::applyStyleSheet()
{
    setStyleSheet(R"(
        /* Main window */
        QMainWindow, QWidget#centralWidget {
            background: palette(window);
        }

        /* Sidebar */
        QFrame#sidebar {
            background-color: #0D1117;
            border-right: 1px solid #1E2A35;
        }

        QFrame#sidebarBrandFrame {
            background: transparent;
        }

        QLabel#sidebarLogoLabel {
            font-size: 22px;
            color: #00BCD4;
        }

        QLabel#sidebarAppNameLabel {
            font-size: 16px;
            font-weight: 800;
            color: #FFFFFF;
            font-family: "Segoe UI", sans-serif;
            letter-spacing: -0.5px;
        }

        /* User badge */
        QFrame#userBadgeFrame {
            background-color: rgba(0,188,212,0.07);
            border: 1px solid rgba(0,188,212,0.15);
            border-radius: 8px;
            margin: 4px 0px;
        }

        QLabel#userAvatarLabel {
            font-size: 16px;
        }

        QLabel#userNameLabel {
            font-size: 12px;
            font-weight: 600;
            color: #FFFFFF;
        }

        QLabel#userRoleLabel {
            font-size: 10px;
            color: #00BCD4;
            letter-spacing: 1px;
            text-transform: uppercase;
        }

        /* Dividers */
        QFrame#sidebarDivider1, QFrame#sidebarDivider2 {
            color: #1E2A35;
            background: #1E2A35;
            max-height: 1px;
            margin: 6px 0px;
        }

        /* Section labels */
        QLabel#sectionMainLabel, QLabel#sectionAdminLabel {
            font-size: 9px;
            font-weight: 700;
            color: #3D5060;
            letter-spacing: 2px;
            padding: 6px 8px 2px 8px;
            font-family: "Courier New", monospace;
        }

        /* Nav buttons — default (unchecked) */
        QPushButton#navUploadBtn,
        QPushButton#navReportsBtn,
        QPushButton#navStandardsBtn {
            text-align: left;
            font-size: 13px;
            color: #8BA5B8;
            background: transparent;
            border: none;
            border-radius: 6px;
            padding: 9px 12px;
            font-family: "Segoe UI", sans-serif;
        }

        QPushButton#navUploadBtn:hover,
        QPushButton#navReportsBtn:hover,
        QPushButton#navStandardsBtn:hover {
            background-color: rgba(255,255,255,0.05);
            color: #FFFFFF;
        }

        /* Nav button — active (checked) */
        QPushButton#navUploadBtn:checked,
        QPushButton#navReportsBtn:checked,
        QPushButton#navStandardsBtn:checked {
            background-color: rgba(0,188,212,0.15);
            color: #00BCD4;
            font-weight: 600;
        }

        /* Logout */
        QPushButton#logoutButton {
            text-align: left;
            font-size: 12px;
            color: #3D5060;
            background: transparent;
            border: none;
            border-radius: 6px;
            padding: 8px 12px;
        }

        QPushButton#logoutButton:hover {
            color: #EF5350;
            background-color: rgba(239, 83, 80, 0.08);
        }

        /* Top bar */
        QFrame#topBar {
            background: palette(window);
            border-bottom: 1px solid palette(mid);
        }

        QLabel#pageHeadingLabel {
            font-size: 18px;
            font-weight: 700;
            color: palette(text);
            font-family: "Segoe UI", sans-serif;
        }

        QLabel#statusIndicatorLabel {
            font-size: 11px;
            color: #4CAF50;
            font-family: "Courier New", monospace;
        }

        /* Status bar */
        QFrame#statusBar {
            background: palette(window);
            border-top: 1px solid palette(mid);
        }

        QLabel#statusBarLabel {
            font-size: 11px;
            color: palette(mid);
        }

        QLabel#versionLabel {
            font-size: 10px;
            color: palette(mid);
            font-family: "Courier New", monospace;
        }

        /* Page stack */
        QStackedWidget#pageStack {
            background: palette(window);
        }

        /* Labels replaced at runtime when pages get their real widgets */
        QLabel#uploadPlaceholderLabel,
        QLabel#reportsPlaceholderLabel,
        QLabel#standardsPlaceholderLabel {
            color: palette(mid);
            font-size: 14px;
        }
    )");
}
