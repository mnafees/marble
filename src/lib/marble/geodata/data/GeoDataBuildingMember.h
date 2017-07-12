//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2017      Mohammed Nafees <nafees.technocool@gmail.com>
//

#ifndef MARBLE_GEODATABUILDINGCHILD_H
#define MARBLE_GEODATABUILDINGCHILD_H

#include "osm/OsmPlacemarkData.h"
#include "GeoDataGeometry.h"

#include <QColor>

#include "geodata_export.h"

namespace Marble {
class GeoDataBuildingMemberPrivate;

class GEODATA_EXPORT GeoDataBuildingMember : public GeoDataGeometry
{
public:
    explicit GeoDataBuildingMember();
    explicit GeoDataBuildingMember(const GeoDataGeometry& other);
    explicit GeoDataBuildingMember(const GeoDataBuildingMember& other);

    enum RoofShape {
        Undefined,
        Flat,
        Skillion,
        Gabled,
        Half_hipped,
        Hipped,
        Pyramidal,
        Gambrel,
        Mansard,
        Dome,
        Onion,
        Round,
        Saltbox
    };

    enum RoofOrientation {
        Along,
        Across
    };

    ~GeoDataBuildingMember() override;

    GeoDataBuildingMember& operator=(const GeoDataBuildingMember &other);

    const char *nodeType() const override;

    EnumGeometryId geometryId() const override;

    GeoDataGeometry *copy() const override;

    const GeoDataLatLonAltBox& latLonAltBox() const override;

    void setOsmData(const OsmPlacemarkData &osmData);

    OsmPlacemarkData& osmData() const;

    void setGeometry(GeoDataGeometry* geometry);

    GeoDataGeometry* geometry() const;

    // Convenience functions

    double height() const;

    double roofHeight() const;

    QColor buildingColour() const;

    QColor roofColour() const;

    RoofShape roofShape() const;

    RoofOrientation roofOrientation() const;

private:
    GeoDataBuildingMemberPrivate* const d;
};

}

#endif
