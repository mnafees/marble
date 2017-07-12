//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2015      Dennis Nienhüser <nienhueser@kde.org>
//

#ifndef MARBLE_OSMRELATION
#define MARBLE_OSMRELATION

#include "OsmNode.h"
#include "OsmWay.h"
#include <osm/OsmPlacemarkData.h>
#include <GeoDataLinearRing.h>

#include <QString>
#include <QXmlStreamAttributes>
#include <QSet>

namespace Marble {

class GeoDataDocument;

class OsmRelation
{
public:
    OsmPlacemarkData & osmData();
    void parseMember(const QXmlStreamAttributes &attributes);
    void addMember(qint64 reference, const QString &role, const QString &type);
    void createBuilding(GeoDataDocument* document, OsmWays &ways, const OsmNodes &nodes, QSet<qint64> &usedNodes, QSet<qint64> &usedWays) const;
    void createMultipolygon(GeoDataDocument* document, OsmWays &ways, const OsmNodes &nodes, QSet<qint64> &usedNodes, QSet<qint64> &usedWays) const;
    void createRelation(GeoDataDocument* document, const QHash<qint64, GeoDataPlacemark*>& wayPlacemarks) const;

    const OsmPlacemarkData & osmData() const;

private:
    typedef QPair<GeoDataLinearRing, OsmPlacemarkData> OsmRing;
    typedef QVector<OsmRing> OsmRings;

    struct OsmMember
    {
        QString type;
        QString role;
        qint64 reference;

        OsmMember();
    };

    OsmRings rings(const QStringList &roles, const OsmWays &ways, const OsmNodes &nodes, QSet<qint64> &usedNodes, QSet<qint64> &usedWays) const;

    OsmPlacemarkData m_osmData;
    QVector<OsmMember> m_members;

    qint64 fetchWayId(qint64 reference, const OsmWays &ways) const;
};

typedef QHash<qint64,OsmRelation> OsmRelations;

}

#endif
