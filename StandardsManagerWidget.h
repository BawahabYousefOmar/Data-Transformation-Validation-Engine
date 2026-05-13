#pragma once

#include <QWidget>
#include <QString>
#include "HeaderProcessor.h"
#include "RuleLoader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StandardsManagerWidget; }
QT_END_NAMESPACE

class StandardsManagerWidget : public QWidget
{
    Q_OBJECT

public:
    // Takes pointers to the global processors that by MainWindow
    explicit StandardsManagerWidget(bool isAdmin,
        HeaderProcessor* headerProc,
        RuleLoader* ruleLoader,
        QWidget* parent = nullptr);
    ~StandardsManagerWidget();

private slots:
    void openRuleEditor(const QString& fieldName);
    void onAddNewFieldClicked(); 
    void onSaveToDiskClicked();
private:
    Ui::StandardsManagerWidget* ui;
    bool m_isAdmin;

    HeaderProcessor* m_headerProc;
    RuleLoader* m_ruleLoader;

    void setupTable();
    void populateTable();
    void applyStyleSheet();

    // Helper to format rule parameters 
    QString buildRuleSummary(const QString& fieldName) const;
};