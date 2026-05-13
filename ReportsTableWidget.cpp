#include "ReportsTableWidget.h"
#include "ui_ReportsTableWidget.h"
#include "MainWindow.h"

#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QWidget>

ReportsTableWidget::ReportsTableWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ReportsTableWidget)
{
    ui->setupUi(this);
    setupTable();
    applyStyleSheet();
    setEmptyStateVisible(true);

    connect(ui->searchInput, &QLineEdit::textChanged,
            this, &ReportsTableWidget::onSearchChanged);
    connect(ui->sortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ReportsTableWidget::onSortChanged);
}

ReportsTableWidget::~ReportsTableWidget()
{
    delete ui;
}

void ReportsTableWidget::addBatch(const BatchRecord& batch)
{
    m_data.insert(batch.batchId, batch);
    m_batchOrder.append(batch.batchId);

    m_totalBatches++;
    m_totalRecords  += batch.totalRecords;
    m_totalValid    += batch.validCount;
    m_totalInvalid  += batch.invalidCount;

    updateStatCards();
    insertRow(batch);
    setEmptyStateVisible(m_totalBatches == 0);
}

void ReportsTableWidget::clear()
{
    m_data.clear();
    m_batchOrder.clear();
    m_totalBatches = m_totalRecords = m_totalValid = m_totalInvalid = 0;

    ui->batchTable->setRowCount(0);
    updateStatCards();
    setEmptyStateVisible(true);
}

void ReportsTableWidget::onSearchChanged(const QString& /*text*/)
{
    rebuildTable();
}

void ReportsTableWidget::onSortChanged(int /*index*/)
{
    rebuildTable();
}

void ReportsTableWidget::setupTable()
{
    QTableWidget* t = ui->batchTable;
    t->setColumnCount(7);
    t->setHorizontalHeaderLabels({
        "Batch ID", "Timestamp", "Total", "Valid", "Invalid", "Details", "Note"
    });

    // Column sizing
    t->horizontalHeader()->setSectionResizeMode(ColId,        QHeaderView::Stretch);
    t->horizontalHeader()->setSectionResizeMode(ColTimestamp, QHeaderView::ResizeToContents);
    t->horizontalHeader()->setSectionResizeMode(ColTotal,     QHeaderView::ResizeToContents);
    t->horizontalHeader()->setSectionResizeMode(ColValid,     QHeaderView::ResizeToContents);
    t->horizontalHeader()->setSectionResizeMode(ColInvalid,   QHeaderView::ResizeToContents);
    t->horizontalHeader()->setSectionResizeMode(ColDetails,   QHeaderView::Fixed);
    t->horizontalHeader()->setSectionResizeMode(ColNote,      QHeaderView::Fixed);
    t->setColumnWidth(ColDetails, 84);
    t->setColumnWidth(ColNote,    70);

    t->verticalHeader()->setVisible(false);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ReportsTableWidget::insertRow(const BatchRecord& batch)
{
    QTableWidget* t = ui->batchTable;

    QString filter = ui->searchInput->text().trimmed().toLower();
    if (!filter.isEmpty() && !batch.batchId.toLower().contains(filter))
        return;

    int row = t->rowCount();
    t->insertRow(row);
    t->setRowHeight(row, 44);

    auto cell = [&](int col, const QString& text, Qt::Alignment align = Qt::AlignVCenter | Qt::AlignLeft) {
        auto* item = new QTableWidgetItem(text);
        item->setTextAlignment(align);
        t->setItem(row, col, item);
    };

    cell(ColId,        batch.batchId);
    cell(ColTimestamp, batch.timestamp,                             Qt::AlignVCenter | Qt::AlignLeft);
    cell(ColTotal,     QString::number(batch.totalRecords),         Qt::AlignCenter);
    cell(ColValid,     QString::number(batch.validCount),           Qt::AlignCenter);
    cell(ColInvalid,   QString::number(batch.invalidCount),         Qt::AlignCenter);

    if (batch.invalidCount > 0) {
        t->item(row, ColInvalid)->setForeground(QColor("#EF5350"));
    }

    const QString batchId = batch.batchId;

    auto makeBtn = [&](const QString& label, const QString& objName) -> QPushButton* {
        auto* btn = new QPushButton(label);
        btn->setObjectName(objName);
        btn->setFixedHeight(28);
        return btn;
    };

    QPushButton* detailsBtn = makeBtn("Details", "detailsBtn");
    connect(detailsBtn, &QPushButton::clicked, this, [this, batchId]() {
        emit detailsRequested(batchId);
    });

    QPushButton* noteBtn = makeBtn("Note", "noteBtn");
    connect(noteBtn, &QPushButton::clicked, this, [this, batchId]() {
        emit noteRequested(batchId);
    });

    auto embedBtn = [&](int col, QPushButton* btn) {
        QWidget* container = new QWidget();
        QHBoxLayout* lay = new QHBoxLayout(container);
        lay->setContentsMargins(6, 6, 6, 6);
        lay->addWidget(btn);
        t->setCellWidget(row, col, container);
    };

    embedBtn(ColDetails, detailsBtn);
    embedBtn(ColNote,    noteBtn);
}

void ReportsTableWidget::rebuildTable()
{
    ui->batchTable->setRowCount(0);

    QList<QString> sorted = m_batchOrder;
    int sortIdx = ui->sortCombo->currentIndex();

    if (sortIdx == 0) {
        std::reverse(sorted.begin(), sorted.end());
    } else if (sortIdx == 1) {
    } else if (sortIdx == 2) {
        std::sort(sorted.begin(), sorted.end(), [&](const QString& a, const QString& b) {
            return m_data[a].totalRecords > m_data[b].totalRecords;
        });
    } else if (sortIdx == 3) {
        std::sort(sorted.begin(), sorted.end(), [&](const QString& a, const QString& b) {
            double pctA = m_data[a].totalRecords > 0
                ? (double)m_data[a].invalidCount / m_data[a].totalRecords : 0.0;
            double pctB = m_data[b].totalRecords > 0
                ? (double)m_data[b].invalidCount / m_data[b].totalRecords : 0.0;
            return pctA > pctB;
        });
    }

    for (const QString& id : sorted)
        insertRow(m_data[id]);
}

void ReportsTableWidget::updateStatCards()
{
    ui->stat1ValueLabel->setText(QString::number(m_totalBatches));
    ui->stat2ValueLabel->setText(QString::number(m_totalRecords));

    double rate = m_totalRecords > 0
        ? 100.0 * m_totalValid / m_totalRecords : 0.0;
    ui->stat3ValueLabel->setText(QString::number(rate, 'f', 1) + "%");
    ui->stat4ValueLabel->setText(QString::number(m_totalInvalid));
}

void ReportsTableWidget::setEmptyStateVisible(bool v)
{
    ui->emptyStateLabel->setVisible(v);
    ui->batchTable->setVisible(!v);
}

QString ReportsTableWidget::validRateString(int valid, int total) const
{
    if (total == 0) return "—";
    return QString::number(100.0 * valid / total, 'f', 1) + "%";
}

void ReportsTableWidget::applyStyleSheet()
{
    setStyleSheet(R"(
        /* Summary stat cards */
        QFrame#statCard1, QFrame#statCard2,
        QFrame#statCard3, QFrame#statCard4 {
            background: palette(base);
            border: 1px solid palette(mid);
            border-radius: 10px;
        }

        QFrame#statCard1 QLabel[objectName="stat1ValueLabel"],
        QFrame#statCard2 QLabel[objectName="stat2ValueLabel"],
        QFrame#statCard3 QLabel[objectName="stat3ValueLabel"],
        QFrame#statCard4 QLabel[objectName="stat4ValueLabel"] {
            font-size: 28px;
            font-weight: 800;
            color: #00BCD4;
            font-family: "Segoe UI", sans-serif;
        }

        QFrame#statCard1 QLabel[objectName="stat1TitleLabel"],
        QFrame#statCard2 QLabel[objectName="stat2TitleLabel"],
        QFrame#statCard3 QLabel[objectName="stat3TitleLabel"],
        QFrame#statCard4 QLabel[objectName="stat4TitleLabel"] {
            font-size: 11px;
            color: palette(mid);
            letter-spacing: 0.5px;
        }

        /* Toolbar */
        QFrame#toolbarFrame {
            background: transparent;
        }

        QLineEdit#searchInput {
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 13px;
            background: palette(base);
        }

        QLineEdit#searchInput:focus {
            border-color: #00BCD4;
        }

        QLabel#sortLabel {
            font-size: 12px;
            color: palette(mid);
        }

        QComboBox#sortCombo {
            border: 1px solid palette(mid);
            border-radius: 6px;
            padding: 5px 10px;
            font-size: 12px;
            min-width: 160px;
        }

        /* Batch table */
        QTableWidget#batchTable {
            border: 1px solid palette(mid);
            border-radius: 8px;
            background: palette(base);
            gridline-color: transparent;
            font-size: 12px;
        }

        QTableWidget#batchTable::item {
            padding: 4px 10px;
        }

        QTableWidget#batchTable::item:selected {
            background: rgba(0,188,212,0.15);
            color: palette(text);
        }

        QHeaderView::section {
            background: palette(window);
            border: none;
            border-bottom: 1px solid palette(mid);
            padding: 6px 10px;
            font-size: 11px;
            font-weight: 600;
            color: palette(mid);
            letter-spacing: 0.8px;
            text-transform: uppercase;
        }

        /* Action buttons inside table */
        QPushButton#detailsBtn {
            background-color: #00BCD4;
            color: #000;
            border: none;
            border-radius: 5px;
            font-size: 11px;
            font-weight: 600;
            padding: 0 8px;
        }

        QPushButton#detailsBtn:hover {
            background-color: #26C6DA;
        }

        QPushButton#noteBtn {
            background: transparent;
            border: 1px solid palette(mid);
            border-radius: 5px;
            font-size: 11px;
            padding: 0 8px;
            color: palette(text);
        }

        QPushButton#noteBtn:hover {
            border-color: #00BCD4;
            color: #00BCD4;
        }

        /* Empty state */
        QLabel#emptyStateLabel {
            font-size: 14px;
            color: palette(mid);
            padding: 60px;
        }
    )");
}
