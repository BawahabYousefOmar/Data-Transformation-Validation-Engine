#pragma once

#include <QDialog>
#include <QString>
#include "Rule.h" 

QT_BEGIN_NAMESPACE
namespace Ui { class RuleEditorDialog; }
QT_END_NAMESPACE


class RuleEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RuleEditorDialog(const QString& fieldName, const Rule& currentRule, QWidget* parent = nullptr);
    ~RuleEditorDialog();

    // Returns the newly configured rule after the user clicks Save
    Rule getUpdatedRule() const;

private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onNumericRangeToggled(bool checked);

private:
    Ui::RuleEditorDialog* ui;
    QString m_fieldName;
    Rule m_rule;

    void applyStyleSheet();
};