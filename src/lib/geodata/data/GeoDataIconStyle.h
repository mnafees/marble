//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2007      Murad Tagirov <tmurad@gmail.com>
// Copyright 2007      Inge Wallin   <ingwa@kde.org>
//


#ifndef GEODATAICONSTYLE_H
#define GEODATAICONSTYLE_H


#include <QtGui/QPixmap>

#include "GeoDataColorStyle.h"
#include "GeoDataHotSpot.h"


class GeoDataIconStyle : public GeoDataColorStyle
{
  public:
    GeoDataIconStyle();
    GeoDataIconStyle( const QPixmap& icon, const QPointF &hotSpot = QPointF( 0.5, 0.5 ) );
    ~GeoDataIconStyle();

    void setIcon( const QPixmap& icon );
    QPixmap icon() const;

    void setHotSpot( const QPointF& hotSpot, GeoDataHotSpot::Units xunits, GeoDataHotSpot::Units yunits );
    const QPointF& hotSpot() const;

    void setScale( const float &scale );
    float scale() const;

    /*
     * Serializable methods
     */
    virtual void pack( QDataStream& stream ) const;
    virtual void unpack( QDataStream& stream );

  private:
    float m_scale;

    QPixmap m_icon;  // To save memory we use a pointer
    GeoDataHotSpot* m_hotSpot; // default unit is "fraction"
    mutable QPointF m_pixelHotSpot;
};

#endif // GEODATAICONSTYLE_H
