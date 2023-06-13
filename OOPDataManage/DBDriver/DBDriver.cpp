#include"DBDriver.h"

bool DBSql::setDataBase(QSqlDatabase database)
{
	m_Sql = QSqlQuery(database);
	return true;
}

bool DBSql::exec()
{
	return m_Sql.exec();
}

QStringList DBSqlCoder::Decode()
{
	m_list = m_text.split(";");
	return m_list;
}

QString DBSqlCoder::Encode()
{
	m_text = m_list.join(";");
	return m_text;
}

bool DBSqlAdd::BindAttribute(CGeometry* geo)
{
	m_Sql.bindValue(":BStyle","sd")
}

bool DBSqlAdd::AddPoint(CPoint* point,int ID,int featureID)
{
	m_Sql.prepare("INSERT INTO Point (id,Feature_id ,x, y,BStyle ,BColor, FStyle,FColor) VALUES (:id,:Feature_id ,:x, :y, :BStyle, :BColor, :FStyle, :FColor)");
	m_Sql.bindValue(":id", ID);
	m_Sql.bindValue(":Feature_id", featureID);
	m_Sql.bindValue(":x", point->x());
	m_Sql.bindValue(":y", point->y());
}
