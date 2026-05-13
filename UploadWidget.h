#pragma once

#include <QWidget>
#include <QStringList>
#include <QDragEnterEvent>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class UploadWidget; }
QT_END_NAMESPACE

// ============================================================
//    - Provides a drag-and-drop zone for CSV/TXT files
//    - Maintains an ordered queue (QListWidget) of pending files
//    - On "Validate Batch" click → shows BatchNameDialog,
//      then emits filesReadyForValidation() for the pipeline
// ============================================================
class UploadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UploadWidget(QWidget* parent = nullptr);
    ~UploadWidget();

    // Returns the current list of queued file paths
    QStringList queuedFiles() const;

    // Clears the queue (also called after a batch starts processing)
    void clearQueue();

signals:

    void filesReadyForValidation(QStringList filePaths, QString batchName);

protected:
    // Drag & Drop event overrides
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onBrowseClicked();
    void onClearQueueClicked();
    void onValidateClicked();
    void onQueueSelectionChanged();

private:
    Ui::UploadWidget* ui;

    QStringList m_filePaths;   // parallel list to the QListWidget items

    // Adds a file to the queue if it's not already present and has .csv/.txt extension
    void addFile(const QString& filePath);

    // Updates the file count label and validate button enabled state
    void refreshQueueUI();

    // Applies stylesheet for drop zone highlight / normal state
    void setDropHighlight(bool active);

    void applyStyleSheet(); 
};
