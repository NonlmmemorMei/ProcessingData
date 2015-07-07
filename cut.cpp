#include "cut.h"

Cut::Cut(const QString &_fileName, const QString &_dirForResult)
    :DataForCalculation()
{
    m_fileName     = _fileName;
    m_dirForResult = _dirForResult;
}

void Cut::createResult()
{
    QVector <QString> _times;
    _times = calcTime();

    for(int i = 0; i < m_listNameOfStations.size(); i++)
    {
        QString name = m_listNameOfStations.at(i).trimmed();
        QString outputFileName = ("/MSCW2_" + name + "_" + m_date1 + ".dat");
        QFile outputFile(m_dirForResult + outputFileName);
        outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&outputFile);
        out << "# Site = MSCW2" << endl;
        out << "# Longitude = 37.28" << endl;
        out << "# Latitude = 55.40"<<  endl;
        out << "#" << endl;
        out << "# UTC_Offset = 4" << endl;
        out << "# TimeZone = Moscow Time (MSK)" << endl;
        out << "#" << endl;
        out << "# UTC_StartTime = " + m_date1 + " 00:00:00" << endl;
        out << "# StationID = " << m_listNameOfStations.at(i) << endl;
        out << "# Frequency = " << m_listNameOfFrequencys.at(i) << endl;
        out << "# MonitorID = 0423" << endl;
        out << "# SampleRate =  5" << endl;

        for(int j = 0; j < m_listOfValues.size(); j++)
        {
            QString result;
            result = _times[j] + " " + m_listOfValues.at(j)[i];
            out << result << endl;
        }
        outputFile.close();
    }
}

void Cut::process()
{
    m_file.setFileName(m_fileName);
    csvReadNotCuttedFile(m_file, m_listOfValues);
    createResult();
}
