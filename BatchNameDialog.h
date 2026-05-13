#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class BatchNameDialog; }
QT_END_NAMESPACE

// ============================================================
//  BatchNameDialog
//
//  Simple modal dialog that collects a batch name before
//  validation starts. Called from UploadWidget::onValidateClicked().
//
// ============================================================
class BatchNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatchNameDialog(QWidget* parent = nullptr);
    ~BatchNameDialog();

    // Returns the trimmed batch name typed by the user
    QString batchName() const;

private slots:
    void onStartClicked();
    void onCancelClicked();
    void onInputChanged(const QString& text);

private:
    Ui::BatchNameDialog* ui;
    void applyStyleSheet();
};
