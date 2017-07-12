//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2017      Mohammed Nafees <nafees.technocool@gmail.com>
//

#ifndef MARBLE_GEODATABUILDINGCHILD_P_H
#define MARBLE_GEODATABUILDINGCHILD_P_H

#include "GeoDataGeometry_p.h"
#include "OsmPlacemarkData.h"

namespace Marble {

class GeoDataBuildingMemberPrivate : public GeoDataGeometryPrivate
{
public:
    GeoDataBuildingMemberPrivate()
    {
    }

    GeoDataGeometryPrivate *copy() const override
    {
        GeoDataBuildingMemberPrivate* copy = new GeoDataBuildingMemberPrivate;
        *copy = *this;
        return copy;
    }

    OsmPlacemarkData m_osmData;
    GeoDataGeometry* m_geometry;
};

}

#endif
