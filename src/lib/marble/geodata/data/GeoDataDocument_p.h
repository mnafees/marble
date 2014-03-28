//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Patrick Spendrin <ps_ml@gmx.de>
//

#ifndef MARBLE_GEODATADOCUMENTPRIVATE_H
#define MARBLE_GEODATADOCUMENTPRIVATE_H

#include "GeoDataStyle.h"
#include "GeoDataNetworkLinkControl.h"
#include "GeoDataStyleMap.h"
#include "GeoDataSchema.h"
#include "GeoDataContainer_p.h"

#include "GeoDataTypes.h"

namespace Marble
{

class GeoDataDocumentPrivate : public GeoDataContainerPrivate
{
  public:
    GeoDataDocumentPrivate()
    :  m_documentRole( UnknownDocument )
    {
    }
    
    virtual GeoDataFeaturePrivate* copy()
    { 
        GeoDataDocumentPrivate* copy = new GeoDataDocumentPrivate;
        *copy = *this;
        return copy;
    }

    virtual const char* nodeType() const
    {
        return GeoDataTypes::GeoDataDocumentType;
    }

    virtual EnumFeatureId featureId() const
    {
        return GeoDataDocumentId;
    }

    mutable QMap<QString, GeoDataStyle> m_styleHash;
    mutable QMap<QString, GeoDataStyleMap> m_styleMapHash;
    QMap<QString, GeoDataSchema> m_schemaHash;
    QString m_filename;
    QString m_baseUri;
    GeoDataNetworkLinkControl m_networkLinkControl;
    QString m_property;
    DocumentRole m_documentRole;
};

} // namespace Marble

#endif
