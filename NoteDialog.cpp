#include "NoteDialog.h"
#include "ui_NoteDialog.h"

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QMessageBox>
#include <QFileInfo>

NoteDialog::NoteDialog(const QString& batchId,
                       const QString& noteFilePath,
                       QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::NoteDialog)
    , m_batchId(batchId)
    , m_noteFilePath(noteFilePath)
{
    ui->setupUi(this);
    setWindowTitle("Note — " + batchId);
    resize(560, 440);

    ui->noteSubtitleLabel->setText(batchId);

    if (!noteFilePath.isEmpty() && QFile::exists(noteFilePath)) {
        loadFromFile(noteFilePath);
        ui->fileStatusLabel->setText("Loaded from file");
    } else {
        ui->fileStatusLabel->setText("New note");
        m_noteFilePath = "note_" + batchId + ".txt";
    }

    setDirty(false);
    applyStyleSheet();

    connect(ui->saveButton,   &QPushButton::clicked,
            this, &NoteDialog::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &NoteDialog::onCancelClicked);
    connect(ui->clearButton,  &QPushButton::clicked,
            this, &NoteDialog::onClearClicked);
    connect(ui->noteEditor,   &QPlainTextEdit::textChanged,
            this, &NoteDialog::onTextChanged);
}

NoteDialog::~NoteDialog()
{
    delete ui;
}

QString NoteDialog::noteFilePath() const
{
    return m_noteFilePath;
}

void NoteDialog::onSaveClicked()
{
    if (saveToFile(m_noteFilePath)) {
        ui->fileStatusLabel->setText("Saved ✓");
        setDirty(false);
        accept();
    } else {
        QMessageBox::critical(this, "Save Failed",
            "Could not write note to:\n" + m_noteFilePath +
            "\n\nCheck write permissions and try again.");
    }
}

void NoteDialog::onCancelClicked()
{
    if (m_dirty) {
        auto btn = QMessageBox::question(
            this, "Discard Changes?",
            "You have unsaved changes.\nDiscard them and close?",
            QMessageBox::Discard | QMessageBox::Cancel,
            QMessageBox::Cancel);
        if (btn != QMessageBox::Discard)
            return;
    }
    reject();
}

void NoteDialog::onClearClicked()
{
    if (ui->noteEditor->document()->isEmpty()) return;

    auto btn = QMessageBox::question(
        this, "Clear Note",
        "Are you sure you want to clear all note content?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (btn == QMessageBox::Yes)
        ui->noteEditor->clear();
}

void NoteDialog::onTextChanged()
{
    updateWordCount();
    setDirty(true);
}

bool NoteDialog::loadFromFile(const QString& path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&f);
    ui->noteEditor->setPlainText(in.readAll());
    f.close();
    return true;
}

bool NoteDialog::saveToFile(const QString& path)
{
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&f);
    out << ui->noteEditor->toPlainText();
    f.close();
    return true;
}

void NoteDialog::updateWordCount()
{
    QString text = ui->noteEditor->toPlainText().trimmed();
    int words = text.isEmpty() ? 0 : text.split(QRegularExpression("\\s+")).count();
    ui->wordCountLabel->setText(QString::number(words) + (words == 1 ? " word" : " words"));
}

void NoteDialog::setDirty(bool dirty)
{
    m_dirty = dirty;
    ui->unsavedLabel->setText(dirty ? "● Unsaved" : "");
}

void NoteDialog::applyStyleSheet()
{
    setStyleSheet(R"(
        QDialog {
            background: palette(window);
        }

        QLabel#noteIconLabel {
            font-size: 24px;
        }

        QLabel#noteTitleLabel {
            font-size: 16px;
            font-weight: 700;
            color: palette(text);
            font-family: "Segoe UI", sans-serif;
        }

        QLabel#noteSubtitleLabel {
            font-size: 10px;
            color: palette(mid);
            font-family: "Courier New", monospace;
        }

        QLabel#fileStatusLabel {
            font-size: 10px;
            color: #4CAF50;
        }

        QFrame#noteDivider {
            color: palette(mid);
            background: palette(mid);
            max-height: 1px;
        }

        QPlainTextEdit#noteEditor {
            border: 1.5px solid palette(mid);
            border-radius: 8px;
            padding: 10px;
            font-size: 13px;
            font-family: "Cascadia Code", "Fira Mono", "Courier New", monospace;
            background: palette(base);
            color: palette(text);
            line-height: 1.6;
        }

        QPlainTextEdit#noteEditor:focus {
            border-color: #00BCD4;
        }

        QLabel#wordCountLabel {
            font-size: 10px;
            color: palette(mid);
            font-family: "Courier New", monospace;
        }

        QLabel#unsavedLabel {
            font-size: 10px;
            color: #FFB300;
        }

        /* Buttons */
        QPushButton#saveButton {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 6px;
            padding: 8px 20px;
            font-size: 13px;
            font-weight: 700;
        }

        QPushButton#saveButton:hover {
            background-color: #26C6DA;
        }

        QPushButton#clearButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 8px 14px;
            font-size: 12px;
            color: palette(text);
        }

        QPushButton#clearButton:hover {
            border-color: #FFB300;
            color: #FFB300;
        }

        QPushButton#cancelButton {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 8px 14px;
            font-size: 12px;
            color: palette(mid);
        }

        QPushButton#cancelButton:hover {
            border-color: #EF5350;
            color: #EF5350;
        }
    )");
}
