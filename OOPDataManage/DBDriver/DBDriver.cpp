#include"DBDriver.h"

QStringList DBSqlCoder::Decode(QString& text, QString delimiter)const
{
	return text.split(delimiter);
}

QString DBSqlCoder::Encode(QStringList& list, QString delimiter)const
{
	return list.join(delimiter);
}

bool DBSql::setDataBase(QSqlDatabase database)
{
	m_Sql = QSqlQuery(database);
	return true;
}

bool DBSql::exec()
{
	return m_Sql.exec();
}

bool DBSql::prepare(QString text)
{
	return m_Sql.prepare(text);
}

void DBSql::bindValue(QString name, QVariant value)
{
	m_Sql.bindValue(name, value);
}

void DBSql::bindValue(int pos, QVariant value)
{
	m_Sql.bindValue(pos, value);
}

QSqlError DBSql::lastError()
{
	return m_Sql.lastError();
}

QVariant DBSql::value(int pos)
{
	return m_Sql.value(pos);
}

QVariant DBSql::value(QString name)
{
	return m_Sql.value(name);
}

bool DBSql::next()
{
	return m_Sql.next();
}

bool DBSql::AddReference(std::shared_ptr<CGeometry> geo)
{
	//根据几何对象的类型确定表名
	QString tableName = GeometryTypeToString(geo->GetType()).c_str();

	//增加几何对象的引用计数
	QString sql = QString("UPDATE %1 SET Ref = Ref + 1 WHERE DBID = :DBID").arg(tableName);
	m_Sql.prepare(sql);
	m_Sql.bindValue(":DBID", geo->DBID);

	if (m_Sql.exec())
		return true;
	else
	{
		qDebug() << "Addreference" << m_Sql.lastError().text();
		return false;
	}
}

//绑定集合对象的属性值
void DBSql::BindAttribute(std::shared_ptr<CGeometry> geo)
{
	m_Sql.bindValue(":BoundaryStyle", geo->BoundaryStyle.ToDBText().c_str());
	m_Sql.bindValue(":BoundaryColor", geo->BoundaryColor.name());
	m_Sql.bindValue(":FillStyle", QString::number(geo->FillStyle.m_BrushStyle));
	m_Sql.bindValue(":FillColor", geo->FillColor.name());

}

//解析集合对象的属性值
void DBSql::PhraseAttribute(std::shared_ptr<CGeometry> geo)
{
	QString boundaryStyle = m_Sql.value("BoundaryStyle").toString();
	QStringList qls = m_coder.Decode(boundaryStyle,",");
	QString boundaryColor = m_Sql.value("BoundaryColor").toString().remove("#");
	QString fillStyle = m_Sql.value("FillStyle").toString();
	QString fillColor = m_Sql.value("FillColor").toString().remove("#");

	geo->BoundaryStyle.m_Width = qls[0].toInt();
	geo->BoundaryStyle.m_PenStyle = (Qt::PenStyle)qls[1].toInt();
	geo->BoundaryColor = QColor(boundaryColor);
	geo->FillStyle = (Qt::BrushStyle)fillStyle.toInt();
	geo->FillColor = QColor(fillColor);
}

int DBSql::SaveFeature(CFeature* feature)
{
	//如果存在该要素，则删除
	m_Sql.prepare("SELECT * FROM Feature WHERE DBID = :DBID");
	m_Sql.bindValue(":DBID", feature->GetID());
	m_Sql.exec();
	if (m_Sql.next())
		DeleteFeature(feature);

	//使用相同ID插入要素
	InsertFeature(feature,feature->GetID());
	return true;
}

int DBSql::InsertFeature(CFeature* feature)
{
	if (ExistFeature(feature))	//如果存在该要素，拒绝插入
		return 0;
	else
	{
		QString type = QString(GeometryTypeToString(feature->GetType()).c_str());

		QStringList qsl;
		for (CFeature::iterator iter = feature->begin(); iter != feature->end(); iter++)
		{	//遍历要素中的几何对象，插入几何对象
			int DBID = 0;
			switch (feature->GetType())
			{
			case GeometryType::Point:
				DBID = InsertPoint(std::dynamic_pointer_cast<CPoint>(*iter));
				break;
			case GeometryType::PolyLine:
				DBID = InsertPolyLine(std::dynamic_pointer_cast<CPolyLine>(*iter));
				break;
			case GeometryType::PolyGon:
				DBID = InsertPolyGon(std::dynamic_pointer_cast<CPolyGon>(*iter));
				break;
			case GeometryType::RectAngle:
				DBID = InsertRectAngle(std::dynamic_pointer_cast<CRectAngle>(*iter));
				break;
			case GeometryType::Circle:
				DBID = InsertCircle(std::dynamic_pointer_cast<CCircle>(*iter));
				break;
			case GeometryType::Section:
				DBID = InsertSection(std::dynamic_pointer_cast<CSection>(*iter));
				break;
			default:
				return 0;
			}
			qsl.append(QString::number(DBID));
		}
		//插入要素表
		m_Sql.prepare("INSERT INTO Feature (Name, Type,Geos) VALUES (:Name, :Type, :Geos)");
		m_Sql.bindValue(":Name", QString(feature->GetName()));
		m_Sql.bindValue(":Type", type);
		m_Sql.bindValue(":Geos", qsl.join(","));
	}

	if (!m_Sql.exec())
	{
		qDebug() << "InsertFeature" << m_Sql.lastError().text();
		return 0;
	}
	//获取插入的ID，赋值给要素
	int DBID = m_Sql.lastInsertId().toInt();
	feature->SetID(DBID);
	return DBID;
}

int DBSql::InsertFeature(CFeature* feature, int ID)
{
	if (ExistFeature(feature))
		return 0;
	else
	{
		QString type = QString(GeometryTypeToString(feature->GetType()).c_str());

		QStringList qsl;
		for (CFeature::iterator iter = feature->begin(); iter != feature->end(); iter++)
		{
			int DBID = 0;
			switch (feature->GetType())
			{
			case GeometryType::Point:
				DBID = InsertPoint(std::dynamic_pointer_cast<CPoint>(*iter));
				break;
			case GeometryType::PolyLine:
				DBID = InsertPolyLine(std::dynamic_pointer_cast<CPolyLine>(*iter));
				break;
			case GeometryType::PolyGon:
				DBID = InsertPolyGon(std::dynamic_pointer_cast<CPolyGon>(*iter));
				break;
			case GeometryType::RectAngle:
				DBID = InsertRectAngle(std::dynamic_pointer_cast<CRectAngle>(*iter));
				break;
			case GeometryType::Circle:
				DBID = InsertCircle(std::dynamic_pointer_cast<CCircle>(*iter));
				break;
			case GeometryType::Section:
				DBID = InsertSection(std::dynamic_pointer_cast<CSection>(*iter));
				break;
			default:
				return 0;
			}
			qsl.append(QString::number(DBID));
		}
		m_Sql.prepare("INSERT INTO Feature (DBID,Name, Type, Ref, Geos) VALUES (:DBID,:Name, :Type, :Geos)");
		m_Sql.bindValue(":DBID", ID);
		m_Sql.bindValue(":Name", QString(feature->GetName()));
		m_Sql.bindValue(":Type", type);
		m_Sql.bindValue(":Geos", qsl.join(","));
	}

	if (!m_Sql.exec())
	{
		qDebug() << "InsertFeature" << m_Sql.lastError().text();
		return 0;
	}
	int DBID = m_Sql.lastInsertId().toInt();
	feature->SetID(DBID);
	return DBID;
}

int DBSql::InsertPoint(std::shared_ptr<CPoint> point)
{

	m_Sql.prepare("INSERT INTO Point ( x, y, BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:x, :y, :BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":x", point->x());
	m_Sql.bindValue(":y", point->y());
	BindAttribute(point);
	if (!m_Sql.exec())
	{
		qDebug() << "InsertPoint" << m_Sql.lastError().text();
		return 0;
	}
	
	int DBID = m_Sql.lastInsertId().toInt();

	point->DBID = DBID;
	return DBID;
}

int DBSql::InsertPath(std::shared_ptr<CPath> path)
{
	QStringList list;
	int DBID = 0;
	//获取点的DBID，添加到path的引用中
	for (CPath::iterator iter = path->begin(); iter != path->end(); iter++)
	{
		DBID = ExistPoint(*iter);	//检查点是否已经存在
		if (!DBID)
			DBID = InsertPoint(*iter);
		else
			AddReference(*iter);
		list.append(QString::number(DBID));
	}
	
	//插入path
	m_Sql.prepare("INSERT INTO Path (Points) VALUES (:text)");
	m_Sql.bindValue(":text", m_coder.Encode(list, ","));
	
	if (!m_Sql.exec())
	{
		qDebug() <<"InsertPath" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();

	path->DBID = DBID;
	return DBID;
}

int DBSql::InsertPolyLine(std::shared_ptr<CPolyLine> polyline)
{
	QStringList list;
	int DBID = 0;
	for (CPolyLine::iterator iter = polyline->begin(); iter != polyline->end(); iter++)
	{
		DBID = ExistPath(*iter);	//检查单折线是否已经存在
		if(!DBID)
			DBID = InsertPath(*iter);
		else
			AddReference(*iter);
		list.append(QString::number(DBID));
	}

	m_Sql.prepare("INSERT INTO PolyLine (Paths,BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:text,:BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":text", m_coder.Encode(list, ","));
	BindAttribute(polyline);

	if (!m_Sql.exec())
	{
		qDebug() << "InsertPolyLine" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();

	polyline->DBID = DBID;
	return DBID;
}

int DBSql::InsertRing(std::shared_ptr<CRing> ring)
{
	QStringList list;
	int DBID = 0;
	//获取点的DBID，添加到path的引用中
	for (CRing::iterator iter = ring->begin(); iter != ring->end(); iter++)
	{
		DBID = ExistPoint(*iter);	//检查点是否已经存在
		if (!DBID)
			DBID = InsertPoint(*iter);
		else
			AddReference(*iter);
		list.append(QString::number(DBID));
	}

	//插入path
	m_Sql.prepare("INSERT INTO Ring (Points) VALUES (:text)");
	m_Sql.bindValue(":text", m_coder.Encode(list, ","));

	if (!m_Sql.exec())
	{
		qDebug() << "InsertPath" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();

	ring->DBID = DBID;
	return DBID;
}

int DBSql::InsertPolyGon(std::shared_ptr<CPolyGon> polygon)
{
	QStringList list;
	int DBID = 0;
	for (CPolyGon::iterator iter = polygon->begin(); iter != polygon->end(); iter++)
	{
		DBID = ExistRing(*iter);	//检查单折线是否已经存在
		if (!DBID)
			DBID = InsertRing(*iter);
		else
			AddReference(*iter);
		list.append(QString::number(DBID));
	}

	m_Sql.prepare("INSERT INTO PolyGon (Rings,BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:text,:BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":text", m_coder.Encode(list, ","));
	BindAttribute(polygon);

	if (!m_Sql.exec())
	{
		qDebug() << "InsertPolyLine" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();

	polygon->DBID = DBID;
	return DBID;
}

int DBSql::InsertRectAngle(std::shared_ptr<CRectAngle> rectangle)
{
	int LTID = 0,RBID=0;
	LTID = ExistPoint(rectangle->GetLT());
	RBID = ExistPoint(rectangle->GetRB());
	if(!LTID)
		LTID = InsertPoint(rectangle->GetLT());
	else
		AddReference(rectangle->GetLT());

	if (!RBID)
		RBID = InsertPoint(rectangle->GetRB());
	else
		AddReference(rectangle->GetRB());

	m_Sql.prepare("INSERT INTO RectAngle (LT,RB,BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:LT,:RB,:BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":LT", LTID);
	m_Sql.bindValue(":RB", RBID);
	BindAttribute(rectangle);

	if (!m_Sql.exec())
	{
		qDebug() << "InsertRectAngle" << m_Sql.lastError().text();
		return 0;
	}

	LTID = m_Sql.lastInsertId().toInt();

	rectangle->DBID = LTID;
	return LTID;
}

int DBSql::InsertCircle(std::shared_ptr<CCircle> circle)
{
	int DBID = 0;
	DBID = ExistPoint(circle->GetC());
	if (!DBID)
		InsertPoint(circle->GetC());
	else 
		AddReference(circle->GetC());

	m_Sql.prepare("INSERT INTO Circle (C,R,BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:C,:R,:BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":C", DBID);
	m_Sql.bindValue(":R", circle->GetR());
	BindAttribute(circle);

	if (!m_Sql.exec())
	{
		qDebug() << "InsertCircle" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();
	circle->DBID = DBID;
	return DBID;
}

int DBSql::InsertSection(std::shared_ptr<CSection> section)
{
	int DBID = 0;
	DBID = ExistPoint(section->GetC());
	if (!DBID)
		InsertPoint(section->GetC());
	else
		AddReference(section->GetC());

	m_Sql.prepare("INSERT INTO Section (C,R,StartAngle,EndAngle,BoundaryStyle, BoundaryColor, FillStyle, FillColor) VALUES (:C,:R,:StartAngle,:EndAngle,:BoundaryStyle, :BoundaryColor, :FillStyle, :FillColor)");
	m_Sql.bindValue(":C", DBID);
	m_Sql.bindValue(":R", section->GetR());
	m_Sql.bindValue(":StartAngle", section->GetSAngle());
	m_Sql.bindValue(":EndAngle", section->GetEAngle());
	BindAttribute(section);

	if (!m_Sql.exec())
	{
		qDebug() << "InsertSection" << m_Sql.lastError().text();
		return 0;
	}

	DBID = m_Sql.lastInsertId().toInt();
	section->DBID = DBID;
	return DBID;
}

//检查是否有相同值的要素
int DBSql::ExistFeature(CFeature* feature)
{
	QString type = QString(GeometryTypeToString(feature->GetType()).c_str());

	QStringList qsl;
	for (CFeature::iterator iter = feature->begin();iter!=feature->end(); iter++)
	{
		int DBID = 0;
		switch (feature->GetType())
		{
		case GeometryType::Point:
			DBID = ExistPoint(std::dynamic_pointer_cast<CPoint>(*iter));
			break;
		case GeometryType::PolyLine:
			DBID = ExistPolyLine(std::dynamic_pointer_cast<CPolyLine>(*iter));
			break;
		case GeometryType::PolyGon:
			DBID = ExistPolyGon(std::dynamic_pointer_cast<CPolyGon>(*iter));
			break;
		case GeometryType::RectAngle:
			DBID = ExistRectAngle(std::dynamic_pointer_cast<CRectAngle>(*iter));
			break;
		case GeometryType::Circle:
			DBID = ExistCircle(std::dynamic_pointer_cast<CCircle>(*iter));
			break;
		case GeometryType::Section:
			DBID = ExistSection(std::dynamic_pointer_cast<CSection>(*iter));
			break;
		default:
			break;
		}
		
		if (!DBID)
			return 0;
		qsl.append(QString::number(DBID));
	}

	m_Sql.prepare("SELECT * FROM Feature WHERE Type=:Type AND Geos=:Geos");
	m_Sql.bindValue(":Type", type);
	m_Sql.bindValue(":Geos", qsl.join(","));
	m_Sql.exec();

	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		feature->SetID(DBID);
		return DBID;
	}
	else
	{
		qDebug() << "ExistFeature" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistPoint(std::shared_ptr<CPoint> point)
{
	m_Sql.prepare("SELECT * FROM Point WHERE x=:x AND y=:y");
	m_Sql.bindValue(":x", point->x());
	m_Sql.bindValue(":y", point->y());
	m_Sql.exec();
	
	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		point->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistPoint" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistPath(std::shared_ptr<CPath> path) 
{
	QStringList list;
	for (CPath::iterator iter = path->begin(); iter != path->end(); iter++)
	{
		list.append(QString::number(ExistPoint(*iter)));
	}
	m_Sql.prepare("SELECT * FROM Path WHERE Points=:Points");
	m_Sql.bindValue(":Points", m_coder.Encode(list, ","));
	m_Sql.exec();

	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		path->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistPath" << m_Sql.lastError().text();
		return 0;
	}

}

int DBSql::ExistPolyLine(std::shared_ptr<CPolyLine> polyline)
{
	QStringList list;
	for (CPolyLine::iterator iter = polyline->begin(); iter != polyline->end(); iter++)
	{
		list.append(QString::number(ExistPath(*iter)));
	}
	m_Sql.prepare("SELECT * FROM PolyLine WHERE Paths=:Paths");
	m_Sql.bindValue(":Paths", m_coder.Encode(list, ","));
	m_Sql.exec();

	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		polyline->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistPolyLines" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistRing(std::shared_ptr<CRing> ring)
{
	QStringList list;
	for (CRing::iterator iter = ring->begin(); iter != ring->end(); iter++)
	{
		list.append(QString::number(ExistPoint(*iter)).trimmed());
		
	}
	QString str = m_coder.Encode(list, ",");
	m_Sql.prepare("SELECT * FROM Ring WHERE Points=:Points");
	m_Sql.bindValue(":Points", str);
	m_Sql.exec();

	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		ring->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistRing" << m_Sql.lastError().text();
		return 0;
	}

}

int DBSql::ExistPolyGon(std::shared_ptr<CPolyGon> polygon)
{

	QStringList list;
	for (CPolyGon::iterator iter = polygon->begin(); iter != polygon->end(); iter++)
	{
		list.append(QString::number(ExistRing(*iter)));
	}
	m_Sql.prepare("SELECT * FROM PolyGon WHERE Rings=:Rings");
	m_Sql.bindValue(":Rings", m_coder.Encode(list, ","));
	m_Sql.exec();

	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		polygon->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistPath" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistRectAngle(std::shared_ptr<CRectAngle> rectangle)
{
	int LTID= ExistPoint(rectangle->GetLT());
	int RBID= ExistPoint(rectangle->GetRB());
	m_Sql.prepare("SELECT * FROM RectAngle WHERE LTID=:LTID AND RBID=:RBID");
	m_Sql.bindValue(":LTID", LTID);
	m_Sql.bindValue(":RBID", RBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		rectangle->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistPath" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistCircle(std::shared_ptr<CCircle> circle)
{
	int CID = ExistPoint(circle->GetC());
	m_Sql.prepare("SELECT * FROM Circle WHERE C=:CID AND R=:R");
	m_Sql.bindValue(":CID", CID);
	m_Sql.bindValue(":R", circle->GetR());
	m_Sql.exec();
	
	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		circle->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistCircle" << m_Sql.lastError().text();
		return 0;
	}
}

int DBSql::ExistSection(std::shared_ptr<CSection> section)
{
	int CID = ExistPoint(section->GetC());

	m_Sql.prepare("SELECT * FROM Section WHERE StartAngle=:StartAngle AND Endangle=:Endangle AND C=:CID AND R=:R");
	m_Sql.bindValue(":StartAngle", section->GetSAngle());
	m_Sql.bindValue(":Endangle", section->GetEAngle());
	m_Sql.bindValue(":CID", CID);
	m_Sql.bindValue(":R", section->GetR());

	m_Sql.exec();
	if (m_Sql.next())
	{
		int DBID = m_Sql.value("DBID").toInt();
		section->DBID = DBID;
		return DBID;
	}
	else
	{
		qDebug() << "ExistSection" << m_Sql.lastError().text();
		return 0;
	}
}

CFeature* DBSql::ReadFeature(int DBID)
{
	m_Sql.prepare("SELECT * FROM Feature WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();

	if (m_Sql.next())
	{
		CFeatureManager& fm = CFeatureManager::GetInstance();
		CFeature* feature = fm.CreateFeature((StringToGemetryType(m_Sql.value("Type").toString().toStdString())));
		feature->SetID(DBID);
		feature->SetName(m_Sql.value("Name").toString().toStdString());

		QString text = m_Sql.value("Geos").toString();
		QStringList qsl = m_coder.Decode(text, ",");
		for (QStringList::iterator iter = qsl.begin(); iter != qsl.end(); iter++)
		{
			int DBID = iter->toInt();
			switch (feature->GetType())
			{
			case GeometryType::Point:
			{
				CREATE_GEOSHARED_PTR(CPoint, point);
				ReadPoint(point, DBID);
				feature->AppendGeometry(point);
				break;
			}
			case GeometryType::PolyLine:
			{
				CREATE_GEOSHARED_PTR(CPolyLine, polyline);
				ReadPolyLine(polyline, DBID);
				feature->AppendGeometry(polyline);
				break;
			}
			case GeometryType::PolyGon:
			{
				CREATE_GEOSHARED_PTR(CPolyGon, polygon);
				ReadPolyGon(polygon, DBID);
				feature->AppendGeometry(polygon);
				break;
			}
			case GeometryType::RectAngle:
			{
				CREATE_GEOSHARED_PTR(CRectAngle, rectangle);
				ReadRectAngle(rectangle, DBID);
				feature->AppendGeometry(rectangle);
				break;
			}
			case GeometryType::Circle:
			{
				CREATE_GEOSHARED_PTR(CCircle, circle);
				ReadCircle(circle, DBID);
				feature->AppendGeometry(circle);
				break;
			}
			case GeometryType::Section:
			{
				CREATE_GEOSHARED_PTR(CSection, section);
				ReadSection(section, DBID);
				feature->AppendGeometry(section);
				break;
			}
			default:
				return 0;
			}
		}

		return feature;
	}
	else
	{
		qDebug() << "ReadFeature" << m_Sql.lastError().text();
		return nullptr;
	}
}

bool DBSql::ReadPoint(std::shared_ptr<CPoint>& point,int DBID)
{
	m_Sql.prepare("SELECT * FROM Point WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();

	if (m_Sql.next())
	{
		point->DBID = DBID;
		point->x(m_Sql.value("x").toDouble());
		point->y(m_Sql.value("y").toDouble());
		PhraseAttribute(point);
		return true;
	}
	else
	{
		qDebug() << "ReadPoint" << m_Sql.lastError().text();
		return false;
	}

}

bool DBSql::ReadPath(std::shared_ptr<CPath>& path, int DBID)
{
	m_Sql.prepare("SELECT * FROM Path WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		path->DBID = DBID;
		QString text = m_Sql.value("Points").toString();
		QStringList qsl = m_coder.Decode(text,",");
		for(QStringList::iterator iter = qsl.begin(); iter != qsl.end(); iter++)
		{
			int DBID = iter->toInt();
			CREATE_GEOSHARED_PTR(CPoint, point);
			ReadPoint(point, DBID);
			path->AppendPoint(point);
		}
		return true;
	}
	else 
	{
	qDebug() << "ReadPath" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadPolyLine(std::shared_ptr<CPolyLine>& line, int DBID)
{
	m_Sql.prepare("SELECT * FROM PolyLine WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		line->DBID = DBID;
		PhraseAttribute(line);
		QString text = m_Sql.value("Paths").toString();
		QStringList qsl = m_coder.Decode(text, ",");
		for (QStringList::iterator iter = qsl.begin(); iter != qsl.end(); iter++)
		{
			int DBID = iter->toInt();
			CREATE_GEOSHARED_PTR(CPath,path);
			ReadPath(path, DBID);
			line->AppendPath(path);
		}
		return true;
	}
	else
	{
		qDebug() << "ReadPolyLine" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadRing(std::shared_ptr<CRing>& ring, int DBID)
{
	m_Sql.prepare("SELECT * FROM Ring WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		ring->DBID = DBID;
		QString text = m_Sql.value("Points").toString();
		QStringList qsl = m_coder.Decode(text, ",");
		for (QStringList::iterator iter = qsl.begin(); iter != qsl.end(); iter++)
		{
			int DBID = iter->toInt();
			CREATE_GEOSHARED_PTR(CPoint, point);
			ReadPoint(point, DBID);
			ring->AppendPoint(point);
		}
		return true;
	}
	else
	{
		qDebug() << "ReadRing" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadPolyGon(std::shared_ptr<CPolyGon>& Gon, int DBID)
{
	m_Sql.prepare("SELECT * FROM PolyGon WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		Gon->DBID = DBID;
		PhraseAttribute(Gon);

		QString text = m_Sql.value("Rings").toString();
		QStringList qsl = m_coder.Decode(text, ",");
		for (QStringList::iterator iter = qsl.begin(); iter != qsl.end(); iter++)
		{
			int DBID = iter->toInt();
			CREATE_GEOSHARED_PTR(CRing, ring);
			ReadRing(ring, DBID);
			Gon->AppendRing(ring);
		}
		return true;
	}
	else
	{
		qDebug() << "ReadPolyGon" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadRectAngle(std::shared_ptr<CRectAngle>& rect, int DBID)
{
	m_Sql.prepare("SELECT * FROM RectAngle WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		rect->DBID = DBID;
		int LTID = m_Sql.value("LT").toInt();
		int RBID = m_Sql.value("RB").toInt();
		PhraseAttribute(rect);

		CREATE_GEOSHARED_PTR(CPoint,LT);
		CREATE_GEOSHARED_PTR(CPoint, RB);
		ReadPoint(LT,LTID);
		ReadPoint(RB, RBID);
		rect->SetLT(LT);
		rect->SetRB(RB);
		return true;
	}
	else
	{
		qDebug() << "ReadRectAngle" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadCircle(std::shared_ptr<CCircle>& circle, int DBID)
{
	m_Sql.prepare("SELECT * FROM Circle WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		circle->DBID = DBID;
		int CID = m_Sql.value("C").toInt();
		circle->SetR(m_Sql.value("R").toDouble());
		PhraseAttribute(circle);

		CREATE_GEOSHARED_PTR(CPoint, C);
		ReadPoint(C, CID);
		circle->SetC(C);
		return true;
	}
	else
	{
		qDebug() << "ReadCircle" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::ReadSection(std::shared_ptr<CSection>& section, int DBID)
{
	m_Sql.prepare("SELECT * FROM Section WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", DBID);
	m_Sql.exec();
	if (m_Sql.next())
	{
		section->DBID = DBID;
		int CID = m_Sql.value("C").toInt();
		section->SetR(m_Sql.value("R").toDouble());
		section->SetSAngle(m_Sql.value("StartAngle").toDouble());
		section->SetEAngle(m_Sql.value("Endangle").toDouble());
		PhraseAttribute(section);

		CREATE_GEOSHARED_PTR(CPoint, C);
		ReadPoint(C, CID);
		section->SetC(C);
		return true;
	}
	else
	{
		qDebug() << "ReadSection" << m_Sql.lastError().text();
		return false;
	}
}

bool DBSql::DeleteFeature(CFeature* feature)
{
	m_Sql.prepare("DELETE FROM Feature WHERE DBID=:DBID");
	m_Sql.bindValue(":DBID", feature->GetID());
	if (m_Sql.exec())
	{
		return true;
	}
	else
	{
		qDebug() << "DeleteFeature" << m_Sql.lastError().text();
		return false;
	}
}