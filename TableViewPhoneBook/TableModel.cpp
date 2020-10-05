#include <QFile>
#include <QTextStream>
#include <QtDebug>

#include "TableModel.h"

const auto testFile = "test_PhoneBook.txt"; // FIXME

TableModelPhoneBook::TableModelPhoneBook(QObject *parent)
  : QAbstractTableModel(parent)
{
  loadDataFromFile(testFile);
}

QVariant TableModelPhoneBook::headerData(int section, Qt::Orientation orientation, int role) const
{
  if ( role == Qt::DisplayRole
       && orientation == Qt::Horizontal
       && section >= 0
       && section < static_cast<int>(Header::eMaxColumnCount)
     )
     switch (static_cast<TableModelPhoneBook::Header>(section)) {
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

int TableModelPhoneBook::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return m_Data.count();
}

int TableModelPhoneBook::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return static_cast<int>(Header::eMaxColumnCount);
}

QVariant TableModelPhoneBook::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  switch (role) {
    case Qt::DisplayRole:
      if (index.row() <= m_Data.size()
          && index.column() < m_Data[index.row()].size())
        return m_Data[index.row()].at(index.column());
      else
        return QVariant();
    default:
      break;
  }

  return QVariant();
}

void TableModelPhoneBook::loadDataFromFile(const QString &fileName)
{
  QFile f(fileName);
  if (f.open(QFile::ReadOnly)) {
    QTextStream in(&f);
    QString line;
    while (in.readLineInto(&line)) {
      QStringList str_list = line.split(';'); // FIXME в таком варианте последняя 4я строка получается пустая
      m_Data.push_back(str_list);
    }
    f.close();
  }
  else
    qWarning() << "Can't open file:" << fileName;
}
