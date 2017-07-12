//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011      Konstantin Oblaukhov <oblaukhov.konstantin@gmail.com>
//

#ifndef MARBLE_GEOPOLYGONGRAPHICSITEM_H
#define MARBLE_GEOPOLYGONGRAPHICSITEM_H

#include <src/lib/marble/geodata/data/GeoDataGeometry.h>
#include "AbstractGeoPolygonGraphicsItem.h"

namespace Marble
{

class GeoDataLinearRing;
class GeoDataPolygon;
class GeoDataBuilding;
class GeoDataBuildingMember;

class MARBLE_EXPORT GeoPolygonGraphicsItem : public AbstractGeoPolygonGraphicsItem
{
public:
    static AbstractGeoPolygonGraphicsItem *createGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataPolygon *polygon);
    static AbstractGeoPolygonGraphicsItem *createGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataLinearRing *ring);
    static AbstractGeoPolygonGraphicsItem *createGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataBuilding *building,
                                                              GeoDataBuildingMember* child);

    explicit GeoPolygonGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataPolygon *polygon);
    explicit GeoPolygonGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataLinearRing *ring);
};

}

#endif
