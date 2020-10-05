#ifndef TABLEMODEL_PHONE_BOOK_H
#define TABLEMODEL_PHONE_BOOK_H

#include <QAbstractTableModel>
#include <qqml.h>

class TableModelPhoneBook : public QAbstractTableModel
{
  Q_OBJECT
  QML_ELEMENT

public:
  explicit TableModelPhoneBook(QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override
  {
      return { {Qt::DisplayRole, "display"} };
  }

  // Load data from file:
  Q_INVOKABLE void loadDataFromFile(const QString &fileName);

private:
	enum class Header{ eUserID = 0, eUserName, eUserPhone, eMaxColumnCount};
	QVector<QStringList> m_Data;
};

#endif // TABLEMODEL_PHONE_BOOK_H
