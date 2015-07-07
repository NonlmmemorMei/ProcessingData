#include "letter.h"

Letter::Letter(QStringList freq, int xSize)
{
    m_frequency = freq;
    m_xSize = xSize;
}

Letter::~Letter(){}

Scale *Letter::clone() const
{
   return new Letter(m_frequency, m_xSize);
}

QString Letter::ticLabel(unsigned int idx) const
{
    if (idx < majors_p.size() && idx < m_xSize)
       return QString(m_frequency[idx]);
    return QString("-");
}
