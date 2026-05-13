#pragma once

#include <QWidget>
#include <QStringList>
#include <QDragEnterEvent>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class UploadWidget; }
QT_END_NAMESPACE

// Drag/drop or browse for CSV/TXT files, queue them, then start validation with a batch name.
class UploadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UploadWidget(QWidget* parent = nullptr);
    ~UploadWidget();

    QStringList queuedFiles() const;

    void clearQueue();

signals:
    void filesReadyForValidation(QStringList filePaths, QString batchName);

protected:
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

    QStringList m_filePaths;

    void addFile(const QString& filePath);
    void refreshQueueUI();
    void setDropHighlight(bool active);
};
