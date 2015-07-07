#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>
#include <QChar>

#include <sunrisesunsettime.h>

class DataForCalculation : public QObject
{
    Q_OBJECT
public:
    explicit DataForCalculation(QObject *parent = 0);
    ~DataForCalculation() {}
    
    QStringList                 trimCsv(QStringList itemsList) const;
    QVector <QString>           calcTime();
    QString                     cutOutputFileName(const QString &filePath);
    QString                     cuttedName(const QString &filePath);
    QString                     cutDate(const QString &filePath);
    int                         min(int a, int b);
    void                        openFile(QFile &file);
    void                        csvReadCuttedFile(QFile &file, QVector<QStringList> &listOfValues);
    void                        csvReadNotCuttedFile(QFile &file, QVector<QStringList> &listOfValues);
    virtual void                createResult() = 0;
    virtual void                process() = 0;

protected:
    const QChar                 m_separator;
    const QChar                 m_commentator;
    QString                     m_date1;
    QStringList                 m_listNameOfStations;
    QStringList                 m_listNameOfFrequencys;
    QVector <QString>           m_times;
    QVector<QStringList>        m_listHead;

private:

};

#endif // DATA_H
