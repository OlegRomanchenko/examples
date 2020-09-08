#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QHash>

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit TableModel(QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  // Load data from file:
  void loadDataFromFile(const QString &fileName);
private:
	enum class Header{ eUserID = 0, eUserName, eUserPhone, eMaxColumnCount};
	size_t m_columnCount = 0;
	size_t m_rowCount = 0;
	QHash<size_t, QStringList> m_hash;
};

#endif // TABLEMODEL_H
