#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class NoteDialog; }
QT_END_NAMESPACE

// Editor for a plain-text note saved as note_<batchId>.txt next to the app or chosen path
class NoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteDialog(const QString& batchId,
                        const QString& noteFilePath,
                        QWidget* parent = nullptr);
    ~NoteDialog();

    QString noteFilePath() const;

private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onClearClicked();
    void onTextChanged();

private:
    Ui::NoteDialog* ui;
    QString m_batchId;
    QString m_noteFilePath;
    bool    m_dirty = false;

    bool loadFromFile(const QString& path);
    bool saveToFile(const QString& path);
    void updateWordCount();
    void setDirty(bool dirty);
    void applyStyleSheet();
};
