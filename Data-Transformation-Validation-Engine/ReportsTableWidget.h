#pragma once

#include <QWidget>
#include <QMap>
#include <QString>

struct BatchRecord;

QT_BEGIN_NAMESPACE
namespace Ui { class ReportsTableWidget; }
QT_END_NAMESPACE

// Table of past batches: search, sort, Details and Note buttons
class ReportsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsTableWidget(QWidget* parent = nullptr);
    ~ReportsTableWidget();

    void addBatch(const BatchRecord& batch);

    void clear();

signals:
    void detailsRequested(QString batchId);
    void noteRequested(QString batchId);

private slots:
    void onSearchChanged(const QString& text);
    void onSortChanged(int index);

private:
    Ui::ReportsTableWidget* ui;

    QList<QString> m_batchOrder;
    QMap<QString, BatchRecord> m_data;

    int m_totalBatches   = 0;
    int m_totalRecords   = 0;
    int m_totalValid     = 0;
    int m_totalInvalid   = 0;

    enum Col { ColId=0, ColTimestamp, ColTotal, ColValid, ColInvalid, ColDetails, ColNote };

    void setupTable();
    void insertRow(const BatchRecord& batch);
    void rebuildTable();
    void updateStatCards();
    void setEmptyStateVisible(bool v);
    QString validRateString(int valid, int total) const;

    void applyStyleSheet();
};
