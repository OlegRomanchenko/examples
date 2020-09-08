#include "TableModel.h"

#include <QFile>
#include <QTextStream>
#include <QtDebug>

const auto testFile = "test_PhoneBook.txt"; // FIXME

TableModel::TableModel(QObject *parent)
  : QAbstractTableModel(parent)
{
  loadDataFromFile(testFile);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  // FIXME: Implement me!
  if ( role == Qt::DisplayRole
       && orientation == Qt::Horizontal
       && section >= 0
       && section < static_cast<int>(Header::eMaxColumnCount)
     )
     switch (static_cast<TableModel::Header>(section)) {
       case Header::eUserID:
         return QString("User ID");
       case Header::eUserName:
         return QString("User Name");
       case Header::eUserPhone:
         return QString("User Phone");
       default:
         break;
     }
  return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return m_rowCount;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return m_columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  switch (role) {
    case Qt::DisplayRole:
      if (m_hash.contains(index.row())
          && index.column() < m_hash.value(index.row()).size())
        return m_hash.value(index.row()).at(index.column());
      else
        return QVariant();
    default:
      break;
  }

  return QVariant();
}

void TableModel::loadDataFromFile(const QString &fileName)
{
  QFile f(fileName);
  if (f.open(QFile::ReadOnly)) {
    m_columnCount = static_cast<size_t>(Header::eMaxColumnCount);
    QTextStream in(&f);
    QString line;
    while (in.readLineInto(&line)) {
      QStringList str_list = line.split(';');
      m_hash.insert(m_rowCount, str_list);
//  qDebug() << str_list;
      m_rowCount++;
    }
  }
  else
    qWarning() << "Can't open file" << testFile;
}
