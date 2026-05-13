#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class HeaderMappingDialog; }
QT_END_NAMESPACE

// ============================================================
//  HeaderMappingDialog
//
//  Shown whenever RecordParser encounters a column name that
//  does not exist in headers.txt.
//
//  The user can either:
//    (a) Map the unknown column to one of the five standard fields
//    (b) Skip the column entirely
//
//  If "Apply to All Similar" is clicked, the same decision is
//  remembered by the caller for the rest of this file's headers.
//
// 
// ============================================================
class HeaderMappingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HeaderMappingDialog(const QString& unknownColumn,
        QWidget* parent = nullptr);
    ~HeaderMappingDialog();

    // --- Query results after exec() returns Accepted ---

    // True  user chose "Skip this column"
    // False user chose "Map to standard field"
    bool shouldSkip() const;

    // Returns the chosen standard key (e.g. "ID", "GPA")
    // Only meaningful when shouldSkip() == false
    QString mappedKey() const;

    // True user clicked "Apply to All Similar"
    // Caller should remember this decision for remaining unknowns
    bool applyToAll() const;

    QString getUnknownColumnName() const { return m_unknownColumn; }

private slots:
    void onMapToStandardToggled(bool checked);
    void onApplyToAllClicked();
    void onConfirmClicked();

private:
    Ui::HeaderMappingDialog* ui;
    bool m_applyToAll = false;

    QString m_unknownColumn;

    void applyStyleSheet();
};
