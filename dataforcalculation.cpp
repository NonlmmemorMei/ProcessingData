#include "dataforcalculation.h"

DataForCalculation::DataForCalculation(QObject *parent)
    :QObject(parent),
    m_separator(','),
    m_commentator('#')
{}

QStringList DataForCalculation::trimCsv(QStringList itemsList) const
{
    QString tmp = itemsList[0];
    int posFindedElement = (tmp.lastIndexOf("=")+2);
    tmp = tmp.remove(0, posFindedElement);
    itemsList.replace(0, tmp);

    return itemsList;
}

QVector<QString> DataForCalculation::calcTime()
{
    QTime time(00, 00, 00);
    QString str;
    for(int i = 0; ; i++)
    {
        QTime time2;
        time2 = time.addSecs(5*i);
        str = time2.toString("hh:mm:ss");
        m_times.push_back(m_date1 + " " + str +",");

        if((time2.hour() == 23) && (time2.minute() == 59) && (time2.second() == 55))
            break;
    }
    return m_times;
}

QString DataForCalculation::cutOutputFileName(const QString &filePath)
{
    QString _ans = filePath;
    int posFindedElement = (_ans.lastIndexOf("/"));
    _ans = _ans.remove(0, posFindedElement);

    return _ans;
}

QString DataForCalculation::cuttedName(const QString &filePath)
{
    QString _ans = filePath;

    int posFirstFindedElement = (_ans.indexOf("MSCW"));
    int posLastFindetElement = (_ans.indexOf("."));
    _ans = _ans.remove(posLastFindetElement, _ans.size());
    _ans = _ans.remove(0, posFirstFindedElement+6);

    return _ans;
}

QString DataForCalculation::cutDate(const QString &filePath)
{
    QString _date = filePath;
    int posFindedElement = (_date.lastIndexOf("."));
    _date = _date.remove(posFindedElement, _date.size());
    _date = _date.remove(0, _date.size()-10);

    return _date;
}

int DataForCalculation::min(int a, int b)
{
    return (a > b) ? b : a;
}

void DataForCalculation::openFile(QFile &file)
{
    bool isOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << file.fileName();
    if(!isOpened)
    {
        qDebug() << "File" << file.fileName() << "Was not opend!";
        return;
    }
}

void DataForCalculation::csvReadCuttedFile(QFile &file, QVector<QStringList> &listOfValues)
{
    openFile(file);
    QStringList list;
    QString line;
    int count = 0;
    while(!file.atEnd()){
        count ++;
        line = file.readLine();
        list = line.split(m_separator);
        if(line.at(0) != m_commentator){
            list[1] = list[1].trimmed();
            listOfValues.push_back(list);
        }
            else if(count == 10){
                m_listNameOfFrequencys.append(trimCsv(list));
            }
                else if(line.at(0) == m_commentator)
                        m_listHead.push_back(list);
     }
     file.close();
}

void DataForCalculation::csvReadNotCuttedFile(QFile &file, QVector<QStringList> &listOfValues)
{
    openFile(file);
    QStringList list;
    QString line;
    int count = 0;
    while(!file.atEnd()){
        line = file.readLine();
        list = line.split(m_separator);
        for(int i = 0; i < list.size(); i++)
            list[i] = list[i].trimmed();
        count++;
        if(count == 7){
            m_date1 = line;
            int posFindedElement = (m_date1.indexOf("=", 0)+2);
            m_date1 = m_date1.mid(posFindedElement, m_date1.size());
            m_date1 = m_date1.mid(0, m_date1.size()-11);
         }
            else if(count == 9){
                m_listNameOfStations = list;
                m_listNameOfStations = trimCsv(m_listNameOfStations);
            }
                else if(count == 10){
                    m_listNameOfFrequencys = list;
                    m_listNameOfFrequencys = trimCsv(m_listNameOfFrequencys);
                }
                    else if(count > 10)
                            listOfValues.push_back(list);
     }
     file.close();
}


