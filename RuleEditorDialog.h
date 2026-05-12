#pragma once

#include <QDialog>
#include <QString>
#include "Rule.h" // Your backend rule class

QT_BEGIN_NAMESPACE
namespace Ui { class RuleEditorDialog; }
QT_END_NAMESPACE

// ============================================================
//  RuleEditorDialog
//  Owner: Yousef
//
//  Modal dialog that takes an existing Rule object, populates
//  a form for the Admin to edit, and returns the modified Rule.
// ============================================================
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