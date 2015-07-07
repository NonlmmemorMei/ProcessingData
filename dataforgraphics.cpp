#include "dataforgraphics.h"

DataForGraphics::DataForGraphics(QObject *parent)
    :QObject(parent),
    m_separator(','),
    m_commentator('#')
{}


void DataForGraphics::openFile(QFile &file)
{
    bool isOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << file.fileName();
    if(!isOpened)
    {
        qDebug() << "File" << file.fileName() << "Was not opend!";
        return;
    }
}

QStringList DataForGraphics::trimCsv(QStringList itemsList) const
{
    QString tmp = itemsList[0];
    int posFindedElement = (tmp.lastIndexOf("=")+2);
    tmp = tmp.remove(0, posFindedElement);
    itemsList.replace(0, tmp);

    return itemsList;
}

void DataForGraphics::csvReadFile(QFile &file, QVector<QStringList> &listOfValues)
{
    openFile(file);
    QStringList list;
    QString line;
    int count = 0;
    while(!file.atEnd())
    {
        count ++;
        line = file.readLine();
        list = line.split(m_separator);
        if(line.at(0) != m_commentator)
        {
            list[1] = list[1].trimmed();
            listOfValues.push_back(list);
        }
        if(count == 2)
            m_longitude = cutLongAndLat(list[0].trimmed());
        if(count == 3)
            m_latitude = cutLongAndLat(list[0].trimmed());
            else if(count == 10)
                m_listNameOfFrequencys.append(trimCsv(list));
     }
    file.close();
}

double DataForGraphics::maxValue()
{
    double max;
    max = m_vectorOfData[0][0];

    for(int i = 0; i < m_vectorOfData.size(); i++)
    {
        for(int j = 0; j < m_vectorOfData.first().size(); j++)
        {
            if(m_vectorOfData[i][j] > max)
               max = m_vectorOfData[i][j];
        }
    }
    return max;
}

double DataForGraphics::minValue()
{
    double min;
    min = m_vectorOfData[0][0];

    for(int i = 0; i < m_vectorOfData.size(); i++)
    {
        for(int j = 0; j < m_vectorOfData.first().size(); j++)
        {
            if(m_vectorOfData[i][j] < min)
                min = m_vectorOfData[i][j];
        }
    }
    return min;
}

const int &DataForGraphics::getXAxisSize(){
    m_xSize = 21;
    return m_xSize;
}

const int &DataForGraphics::getYAxisSize(){
    m_ySize = 17280;
    return m_ySize;
}

const int &DataForGraphics::getSunRiseTime(QString fileName)
{
   double time;
   time = sunRiseSunSet(true, fileName);
   return time*720;
  // return time;
}

const int &DataForGraphics::getSunSetTime(QString fileName)
{
    double time;
    time = sunRiseSunSet(false, fileName);
    return time*720;
  // return time;
}

double DataForGraphics::getMax()
{
    double min, max, max2;
    min = minValue();
    max = maxValue();
    max2 =((m_vectorOfData[0][0] - min)/(max - min));

     for(int i = 0; i < m_vectorOfData.size(); i++)
     {
         for(int j = 0; j < m_vectorOfData.first().size(); j++)
         {
             if((m_vectorOfData[i][j] - min)/(max - min) > max2)
                 max2 = (m_vectorOfData[i][j] - min)/(max - min);
         }
     }
        m_vectorOfData.clear();

        return max2;
}

const QStringList &DataForGraphics::getFrequences(){
    return m_listNameOfFrequencys;
}

QString DataForGraphics::cutLongAndLat(const QString &name)
{
    QString _ans = name;

    int posFirstFindedElement = (_ans.indexOf("="));
    _ans = _ans.remove(0, posFirstFindedElement+2);

    return _ans;
}

QString DataForGraphics::cutName(const QString &filePath)
{
    QString _ans = filePath;

    int posFirstFindedElement = (_ans.indexOf("MSCW"));
    int posLastFindetElement = (_ans.indexOf("."));
    _ans = _ans.remove(posLastFindetElement, _ans.size());
    _ans = _ans.remove(0, posFirstFindedElement+6);

    return _ans;
}

QString DataForGraphics::cutDay(const QString &filePath)
{
    QString _ans = filePath;

    int posFirstFindedElement = (_ans.indexOf("MSCW"));
    int posLastFindetElement = (_ans.indexOf("."));
    _ans = _ans.remove(posLastFindetElement, _ans.size());
    _ans = _ans.remove(0, posFirstFindedElement+21);

    return _ans;
}

QString DataForGraphics::cutMonth(const QString &filePath)
{
    QString _ans = filePath;

    int posFirstFindedElement = (_ans.indexOf("MSCW"));
    int posLastFindetElement = (_ans.indexOf("."));
    _ans = _ans.remove(posLastFindetElement-3, _ans.size());
    _ans = _ans.remove(0, posFirstFindedElement+18);

    return _ans;
}

QString DataForGraphics::cutYear(const QString &filePath)
{
    QString _ans = filePath;

    int posFirstFindedElement = (_ans.indexOf("MSCW"));
    int posLastFindetElement = (_ans.indexOf("."));
    _ans = _ans.remove(posLastFindetElement-6, _ans.size());
    _ans = _ans.remove(0, posFirstFindedElement+13);

    return _ans;
}

QString DataForGraphics::getLongitude()
{
    return m_longitude;
}

QString DataForGraphics::getLatitude()
{
    return m_latitude;
}

double DataForGraphics::sunRiseSunSet(bool select, QString &fileName)
{
    double time;
    SunRiseSunSetTime *sunRiseSunSetTime = new SunRiseSunSetTime();
    sunRiseSunSetTime->setDay(cutDay(fileName).toDouble());
    sunRiseSunSetTime->setMonth(cutMonth(fileName).toDouble());
    sunRiseSunSetTime->setYear(cutYear(fileName).toDouble());
    sunRiseSunSetTime->setLatitude(getLatitude().toDouble());
    sunRiseSunSetTime->setLongitude(getLongitude().toDouble());
    if(select == true)
       time = sunRiseSunSetTime->getSunRiseSunSetTime(true);
    if(select == false)
       time = sunRiseSunSetTime->getSunRiseSunSetTime(false);
    return time;
}







