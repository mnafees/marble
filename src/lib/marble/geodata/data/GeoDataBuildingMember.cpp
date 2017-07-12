//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2017      Mohammed Nafees <nafees.technocool@gmail.com>
//

#include "GeoDataBuildingMember.h"
#include "GeoDataBuildingMember_p.h"
#include "GeoDataTypes.h"
#include "GeoDataBuilding.h"

namespace Marble {

GeoDataBuildingMember::GeoDataBuildingMember()
    : GeoDataGeometry(new GeoDataBuildingMemberPrivate),
      d(new GeoDataBuildingMemberPrivate)
{
}

GeoDataBuildingMember::GeoDataBuildingMember(const GeoDataGeometry &other)
    : GeoDataGeometry(other),
      d(new GeoDataBuildingMemberPrivate)
{
}

GeoDataBuildingMember::GeoDataBuildingMember(const GeoDataBuildingMember &other)
    : GeoDataGeometry(other),
      d(new GeoDataBuildingMemberPrivate(*other.d))
{
}

GeoDataBuildingMember::~GeoDataBuildingMember()
{
    delete d;
}

GeoDataBuildingMember& GeoDataBuildingMember::operator=(const GeoDataBuildingMember& other)
{
    GeoDataGeometry::operator=(other);
    *d = *other.d;
    return *this;
}

const char *GeoDataBuildingMember::nodeType() const
{
    return GeoDataTypes::GeoDataBuildingMemberType;
}

EnumGeometryId GeoDataBuildingMember::geometryId() const
{
    return GeoDataBuildingMemberId;
}

GeoDataGeometry *GeoDataBuildingMember::copy() const
{
    return new GeoDataBuildingMember(*this);
}

void GeoDataBuildingMember::setOsmData(const OsmPlacemarkData &osmData)
{
    d->m_osmData = osmData;
}

OsmPlacemarkData& GeoDataBuildingMember::osmData() const
{
    return d->m_osmData;
}

double GeoDataBuildingMember::height() const
{
    return GeoDataBuilding::extractHeight(d->m_osmData);
}

void GeoDataBuildingMember::setGeometry(GeoDataGeometry *geometry)
{
    d->m_geometry = geometry;
}

GeoDataGeometry *GeoDataBuildingMember::geometry() const
{
    return d->m_geometry;
}

const GeoDataLatLonAltBox &GeoDataBuildingMember::latLonAltBox() const
{
    return d->m_geometry->latLonAltBox();
}

double GeoDataBuildingMember::roofHeight() const
{
    return d->m_osmData.tagValue(QStringLiteral("roof:height")).toDouble();
}

QColor GeoDataBuildingMember::buildingColour() const
{
    return QColor(d->m_osmData.tagValue(QStringLiteral("building:colour")));
}

QColor GeoDataBuildingMember::roofColour() const
{
    return QColor(d->m_osmData.tagValue(QStringLiteral("roof:colour")));
}

GeoDataBuildingMember::RoofShape GeoDataBuildingMember::roofShape() const
{
    QString const shape = d->m_osmData.tagValue(QStringLiteral("roof:shape"));
    if (shape.isEmpty()) {
        return Undefined;
    }

    if (shape == QLatin1String("flat")) {
        return Flat;
    } else if (shape == QLatin1String("skillion")) {
        return Skillion;
    } else if (shape == QLatin1String("gabled")) {
        return Gabled;
    } else if (shape == QLatin1String("half-hipped")) {
        return Half_hipped;
    } else if (shape == QLatin1String("hipped")) {
        return Hipped;
    } else if (shape == QLatin1String("pyramidal")) {
        return Pyramidal;
    } else if (shape == QLatin1String("gambrel")) {
        return Gambrel;
    } else if (shape == QLatin1String("mansard")) {
        return Mansard;
    } else if (shape == QLatin1String("dome")) {
        return Dome;
    } else if (shape == QLatin1String("onion")) {
        return Onion;
    } else if (shape == QLatin1String("round")) {
        return Round;
    } else if (shape == QLatin1String("saltbox")) {
        return Saltbox;
    }

    return Undefined;
}

GeoDataBuildingMember::RoofOrientation GeoDataBuildingMember::roofOrientation() const
{
    QString const orientation = d->m_osmData.tagValue(QStringLiteral("roof:orientation"));
    if (orientation.isEmpty()) {
        return Along;
    }

    if (orientation == QLatin1String("across")) {
        return Across;
    }

    return Along;
}


}
