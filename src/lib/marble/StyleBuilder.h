//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2016      Dennis Nienhüser <nienhueser@kde.org>
//

#ifndef MARBLE_STYLEBUILDER_H
#define MARBLE_STYLEBUILDER_H

#include <QSharedPointer>

#include <GeoDataStyle.h>
#include <GeoDataFeature.h>

namespace Marble {

class StyleParameters
{
public:
    explicit StyleParameters(const GeoDataFeature* feature=nullptr, int tileLevel=0);

    const GeoDataFeature* feature;
    int tileLevel;
};

class StyleBuilder
{
public:
    typedef QSharedPointer<StyleBuilder> Ptr;

    StyleBuilder();
    ~StyleBuilder();

    GeoDataStyle::ConstPtr createStyle(const StyleParameters &parameters) const;
    GeoDataStyle::ConstPtr presetStyle(GeoDataFeature::GeoDataVisualCategory visualCategory) const;

    void reset();

private:
    Q_DISABLE_COPY(StyleBuilder)

    class Private;
    Private * const d;
};

}

#endif