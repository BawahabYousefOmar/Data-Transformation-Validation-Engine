#include "UploadWidget.h"
#include "ui_UploadWidget.h"
#include "BatchNameDialog.h"

#include <QFileDialog>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QMessageBox>

UploadWidget::UploadWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::UploadWidget)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    setStyleSheet(R"(
        QFrame#dropZoneFrame {
            border: 2px dashed palette(mid);
            border-radius: 12px;
            background: palette(base);
        }
        QFrame#dropZoneFrame[dropActive="true"] {
            border: 2px dashed #00BCD4;
            background: rgba(0, 188, 212, 0.07);
        }
        QLabel#dropIconLabel {
            font-size: 48px;
            color: palette(mid);
        }
        QLabel#dropMainLabel {
            font-size: 16px;
            font-weight: bold;
            color: palette(text);
        }
        QLabel#dropSubLabel {
            font-size: 12px;
            color: palette(mid);
        }
        QLabel#orDividerLabel {
            font-size: 12px;
            color: palette(mid);
        }
        QPushButton#browseButton {
            background-color: palette(button);
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 6px 18px;
            font-size: 13px;
        }
        QPushButton#browseButton:hover {
            background-color: #00BCD4;
            color: #000;
            border-color: #00BCD4;
        }
        QFrame#queueFrame {
            border: 1px solid palette(mid);
            border-radius: 10px;
            background: palette(window);
        }
        QLabel#queueTitleLabel {
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton#clearQueueButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 4px;
            padding: 2px 8px;
            font-size: 11px;
            color: palette(mid);
        }
        QPushButton#clearQueueButton:hover {
            color: #E57373;
            border-color: #E57373;
        }
        QListWidget#fileQueueList {
            border: 1px solid palette(mid);
            border-radius: 6px;
            background: palette(base);
            font-size: 12px;
        }
        QLabel#fileCountLabel {
            font-size: 11px;
            color: palette(mid);
        }
        QPushButton#validateButton {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 8px;
            font-size: 14px;
            font-weight: bold;
            padding: 8px 0;
        }
        QPushButton#validateButton:hover {
            background-color: #26C6DA;
        }
        QPushButton#validateButton:disabled {
            background-color: palette(mid);
            color: palette(dark);
        }
    )");

    connect(ui->browseButton,     &QPushButton::clicked, this, &UploadWidget::onBrowseClicked);
    connect(ui->clearQueueButton, &QPushButton::clicked, this, &UploadWidget::onClearQueueClicked);
    connect(ui->validateButton,   &QPushButton::clicked, this, &UploadWidget::onValidateClicked);
    connect(ui->fileQueueList,    &QListWidget::itemSelectionChanged,
            this, &UploadWidget::onQueueSelectionChanged);

    refreshQueueUI();
}

UploadWidget::~UploadWidget()
{
    delete ui;
}

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

void UploadWidget::onBrowseClicked()
{
    QStringList paths = QFileDialog::getOpenFileNames(
        this,
        tr("Select data files"),
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

    BatchNameDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;

    QString batchName = dlg.batchName();
    if (batchName.trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Invalid Name"),
                             tr("Please enter a valid batch name."));
        return;
    }

    emit filesReadyForValidation(m_filePaths, batchName.trimmed());

    clearQueue();
}

void UploadWidget::onQueueSelectionChanged()
{
}

void UploadWidget::addFile(const QString& filePath)
{
    if (filePath.isEmpty()) return;

    QFileInfo info(filePath);
    QString ext = info.suffix().toLower();

    if (ext != "csv" && ext != "txt") {
        QMessageBox::warning(this, tr("Unsupported File"),
            tr("Only .csv and .txt files are accepted.\n\n'%1' was skipped.").arg(info.fileName()));
        return;
    }

    if (m_filePaths.contains(filePath)) return;

    m_filePaths.append(filePath);

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
    ui->dropZoneFrame->setProperty("dropActive", active);
    ui->dropZoneFrame->style()->unpolish(ui->dropZoneFrame);
    ui->dropZoneFrame->style()->polish(ui->dropZoneFrame);
    ui->dropZoneFrame->update();
}
