#pragma once

#include <QWidget>
#include <QString>
#include "HeaderProcessor.h"
#include "RuleLoader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StandardsManagerWidget; }
QT_END_NAMESPACE

// ============================================================
//  StandardsManagerWidget
//  Owner: Yousef
//
//  Admin-only panel to view standard fields, their mapped 
//  aliases from headers.txt, and edit validation rules.
// ============================================================
class StandardsManagerWidget : public QWidget
{
    Q_OBJECT

public:
    // Takes pointers to the global processors owned by MainWindow
    explicit StandardsManagerWidget(bool isAdmin,
        HeaderProcessor* headerProc,
        RuleLoader* ruleLoader,
        QWidget* parent = nullptr);
    ~StandardsManagerWidget();

private slots:
    void openRuleEditor(const QString& fieldName);

private:
    Ui::StandardsManagerWidget* ui;
    bool m_isAdmin;

    HeaderProcessor* m_headerProc;
    RuleLoader* m_ruleLoader;

    void setupTable();
    void populateTable();
    void applyStyleSheet();

    // Helper to format rule parameters into a readable string
    QString buildRuleSummary(const QString& fieldName) const;
};