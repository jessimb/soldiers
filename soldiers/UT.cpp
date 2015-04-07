//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "UT.h"
#include <QtCore/QDateTime>

UT* UT::_instance = NULL ;
QFile UT::m_Debugfile("log.log");

UT* UT::getInstance()
{
    if(UT::_instance == NULL)
    {
        UT::_instance = new UT();
    }
    return _instance;
}
 
UT::UT()
{
	//manager	= new QNetworkAccessManager(); 
	AppConfig.unique_id = 0;
}
/* 
QNetworkAccessManager* UT::getQNAManager()
{
	return manager;
}
*/


void UT::ConvertTimeStampToDateTime(const QString& timeStamp,QString& dateTime)
{
    bool ok;
    QDateTime timestamp;
    if(timeStamp.length() > 0)
    { 
        uint unixTime = timeStamp.toUInt(&ok,10);
        timestamp.setTime_t(unixTime);
        dateTime = timestamp.toString(Qt::SystemLocaleShortDate);
    }

}


QString UT::GetFromDateTimeAsSecounds(const QDate& date,const QTime& time)
{
	 return QString::number(QDateTime(date,time).toTime_t());	
}

QString UT::GetCurrentDateTimeAsSecounds()
{
	
	return QString::number(QDateTime(QDate::currentDate(),QTime::currentTime()).toTime_t());	
}
QString UT::GetCurrentDateTimeAsMiliSecounds()
{
	QDateTime setTime = QDateTime::fromString (QString("1970-07-18T14:15:09"), Qt::ISODate);
	QDateTime current = QDateTime::currentDateTime();

	uint timestame = current.toTime_t();
	 
	 
	 
	return  QString::number(timestame);
}


bool UT::GetMD5String(const QString& toAPISignature,QString& APIMD5Signature)
{
    QByteArray hashedApiData= QCryptographicHash::hash(toAPISignature.toLatin1(),
													   QCryptographicHash::Md5);
	APIMD5Signature.append(hashedApiData.toHex());
	if(APIMD5Signature.length() < 1)
		return false;

	return true;
}

 
QString UT::GetCurrentTime()
{
	QTime time = QTime::currentTime();
	QString timeString = time.toString();
	return timeString;
}	

QString UT::GetCurrentDate()
{
	QDate date = QDate::currentDate();
	QString dateString = date.toString();
	return dateString;
}	

QString UT::GetCurrentDateTime()
{
	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString();
	return dateTimeString;
}	




void UT::LogToFile(QString data)
{
	QString printData;
	printData.append("FBApi " + GetCurrentDateTime()+"  "+data);
	
	if ( UT::m_Debugfile.open( IO_WriteOnly | IO_Append  ) )
	{
		QTextStream stream( &UT::m_Debugfile );
		//stream.setAutoDetectUnicode(true);
		stream.setCodec("UTF-8");
		stream << printData << endl;
		UT::m_Debugfile.close();
	} 
	else 
	{
		QTextStream stream( &UT::m_Debugfile );
		//stream.setAutoDetectUnicode(true);
		stream.setCodec("UTF-8");
		stream << printData << endl;
		UT::m_Debugfile.close();
	}

}



void UT::SetResultMapWithSets(QList<QMap<QString,QString > >& fql_result_set,
							  QScriptValueIterator& resultSetIter)
{
	int i = 1;
	while (resultSetIter.hasNext()) {
	    QMap<QString,QString> fql_result_set_map;
		resultSetIter.next();
		UT::getInstance()->LogToFile("# "+(i++));
	    QScriptValueIterator it3(resultSetIter.value());
		while (it3.hasNext()) {
			it3.next();
			UT::getInstance()->LogToFile(it3.name() +": " + it3.value().toString());
			fql_result_set_map.insert(it3.name(),it3.value().toString());
		}
		fql_result_set.append(fql_result_set_map);	
	}


}

int UT::GetAppConfigUniqueId()
{
    return AppConfig.unique_id;
}

void UT::IncreaseByOneUniqueId()
{
    AppConfig.unique_id++;
}
int UT::CreateAppConfigUniqueId()
{
    IncreaseByOneUniqueId();
    return AppConfig.unique_id;
}
