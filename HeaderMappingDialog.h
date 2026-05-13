#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class HeaderMappingDialog; }
QT_END_NAMESPACE

// Shown when a CSV column is not in headers.txt: map it to a standard field or skip it.
class HeaderMappingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HeaderMappingDialog(const QString& unknownColumn,
                                 QWidget* parent = nullptr);
    ~HeaderMappingDialog();

    bool shouldSkip() const;
    QString mappedKey() const;
    bool applyToAll() const;

private slots:
    void onMapToStandardToggled(bool checked);
    void onApplyToAllClicked();
    void onConfirmClicked();

private:
    Ui::HeaderMappingDialog* ui;
    bool m_applyToAll = false;

    void applyStyleSheet();
};
