#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class BatchNameDialog; }
QT_END_NAMESPACE

// Asks for a batch name before validation runs.
class BatchNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatchNameDialog(QWidget* parent = nullptr);
    ~BatchNameDialog();

    QString batchName() const;

private slots:
    void onStartClicked();
    void onCancelClicked();
    void onInputChanged(const QString& text);

private:
    Ui::BatchNameDialog* ui;
    void applyStyleSheet();
};
