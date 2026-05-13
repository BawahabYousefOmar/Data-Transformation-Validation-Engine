#include "UploadWidget.h"
#include "ui_UploadWidget.h"
#include "BatchNameDialog.h"

#include <QFileDialog>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QMessageBox>

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
UploadWidget::UploadWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::UploadWidget)
{
    ui->setupUi(this);

    // Enable drop events on this widget
    setAcceptDrops(true);




    connect(ui->browseButton, &QPushButton::clicked, this, &UploadWidget::onBrowseClicked);
    connect(ui->clearQueueButton, &QPushButton::clicked, this, &UploadWidget::onClearQueueClicked);
    connect(ui->validateButton, &QPushButton::clicked, this, &UploadWidget::onValidateClicked);
    connect(ui->fileQueueList, &QListWidget::itemSelectionChanged,
        this, &UploadWidget::onQueueSelectionChanged);

    refreshQueueUI();
}

// ----------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------
UploadWidget::~UploadWidget()
{
    delete ui;
}

// ----------------------------------------------------------------
// Public API
// ----------------------------------------------------------------
QStringList UploadWidget::queuedFiles() const
{
    return m_filePaths;
}

void UploadWidget::clearQueue()
{
    m_filePaths.clear();
    ui->fileQueueList->clear();
    refreshQueueUI();
}

// ----------------------------------------------------------------
// Drag & Drop Events
// ----------------------------------------------------------------
void UploadWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        setDropHighlight(true);
    }
}

void UploadWidget::dragLeaveEvent(QDragLeaveEvent* /*event*/)
{
    setDropHighlight(false);
}

void UploadWidget::dropEvent(QDropEvent* event)
{
    setDropHighlight(false);
    const QList<QUrl> urls = event->mimeData()->urls();
    for (const QUrl& url : urls) {
        addFile(url.toLocalFile());
    }
    event->acceptProposedAction();
}

// ----------------------------------------------------------------
// Private Slots
// ----------------------------------------------------------------
void UploadWidget::onBrowseClicked()
{
    QStringList paths = QFileDialog::getOpenFileNames(
        this,
        tr("Select Student Data Files"),
        QString(),
        tr("Data Files (*.csv *.txt);;CSV Files (*.csv);;Text Files (*.txt);;All Files (*)")
    );
    for (const QString& path : paths) {
        addFile(path);
    }
}

void UploadWidget::onClearQueueClicked()
{
    clearQueue();
}

void UploadWidget::onValidateClicked()
{
    if (m_filePaths.isEmpty()) return;

    // Show the batch naming dialog
    BatchNameDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;

    QString batchName = dlg.batchName();
    if (batchName.trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Invalid Name"),
            tr("Please enter a valid batch name."));
        return;
    }

    //  MainWindow pipeline picks this up
    emit filesReadyForValidation(m_filePaths, batchName.trimmed());

    // Clear queue after dispatching
    clearQueue();
}

void UploadWidget::onQueueSelectionChanged()
{
    // Reserved for future: allow removing a specific item via keyboard
}

// ----------------------------------------------------------------
// Private Helpers
// ----------------------------------------------------------------
void UploadWidget::addFile(const QString& filePath)
{
    if (filePath.isEmpty()) return;

    QFileInfo info(filePath);
    QString ext = info.suffix().toLower();

    // Only accept .csv and .txt
    if (ext != "csv" && ext != "txt") {
        QMessageBox::warning(this, tr("Unsupported File"),
            tr("Only .csv and .txt files are accepted.\n\n'%1' was skipped.").arg(info.fileName()));
        return;
    }

    // Prevent duplicates
    if (m_filePaths.contains(filePath)) return;

    m_filePaths.append(filePath);

    // Add a list item showing only the file name; store full path as UserRole
    QListWidgetItem* item = new QListWidgetItem(
        QString("  %1  ·  %2").arg(info.fileName()).arg(
            info.size() < 1024 ? QString("%1 B").arg(info.size())
            : QString("%1 KB").arg(info.size() / 1024))
    );
    item->setData(Qt::UserRole, filePath);
    item->setToolTip(filePath);
    ui->fileQueueList->addItem(item);

    refreshQueueUI();
}

void UploadWidget::refreshQueueUI()
{
    int count = m_filePaths.size();
    ui->fileCountLabel->setText(tr("%1 file(s) queued").arg(count));
    ui->validateButton->setEnabled(count > 0);
}

void UploadWidget::setDropHighlight(bool active)
{
    // Use a dynamic property + stylesheet rule so Qt re-evaluates the style
    ui->dropZoneFrame->setProperty("dropActive", active);
    ui->dropZoneFrame->style()->unpolish(ui->dropZoneFrame);
    ui->dropZoneFrame->style()->polish(ui->dropZoneFrame);
    ui->dropZoneFrame->update();
}

void UploadWidget::applyStyleSheet()
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