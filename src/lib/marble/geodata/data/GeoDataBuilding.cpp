//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2017      Mohammed Nafees <nafees.technocool@gmail.com>
//

#include "GeoDataBuilding.h"
#include "GeoDataBuilding_p.h"
#include "GeoDataTypes.h"
#include "OsmPlacemarkData.h"

namespace Marble {

QSet<StyleBuilder::OsmTag> GeoDataBuilding::s_buildingTags;

GeoDataBuilding::GeoDataBuilding()
    : GeoDataGeometry(new GeoDataBuildingPrivate),
      d(new GeoDataBuildingPrivate)
{
}

GeoDataBuilding::GeoDataBuilding(const GeoDataGeometry &other)
    : GeoDataGeometry(other),
      d(new GeoDataBuildingPrivate)
{
}

GeoDataBuilding::GeoDataBuilding(const GeoDataBuilding &other)
    : GeoDataGeometry(other),
      d(new GeoDataBuildingPrivate(*other.d))
{
}

GeoDataBuilding::~GeoDataBuilding()
{
    delete d;
}

GeoDataBuilding& GeoDataBuilding::operator=(const GeoDataBuilding& other)
{
    GeoDataGeometry::operator=(other);
    *d = *other.d;
    return *this;
}

const char *GeoDataBuilding::nodeType() const
{
    return GeoDataTypes::GeoDataBuildingType;
}

EnumGeometryId GeoDataBuilding::geometryId() const
{
    return GeoDataBuildingId;
}

GeoDataGeometry *GeoDataBuilding::copy() const
{
    return new GeoDataBuilding(*this);
}

int GeoDataBuilding::minLevel() const
{
    return d->m_minLevel;
}

void GeoDataBuilding::setMinLevel(int minLevel)
{
    d->m_minLevel = minLevel;
}

int GeoDataBuilding::maxLevel() const
{
    return d->m_maxLevel;
}

void GeoDataBuilding::setMaxLevel(int maxLevel)
{
    d->m_maxLevel = maxLevel;
}

QVector<int> GeoDataBuilding::nonExistentLevels() const
{
    return d->m_nonExistentLevels;
}

void GeoDataBuilding::setNonExistentLevels(const QVector<int> &nonExistentLevels)
{
    d->m_nonExistentLevels = nonExistentLevels;
}

const GeoDataLatLonAltBox &GeoDataBuilding::latLonAltBox() const
{
    return d->m_multiGeometry.latLonAltBox();
}

QString GeoDataBuilding::name() const
{
    return d->m_name;
}

void GeoDataBuilding::setName(const QString& name)
{
    d->m_name = name;
}

QVector<GeoDataBuilding::NamedEntry> GeoDataBuilding::entries() const
{
    return d->m_entries;
}

void GeoDataBuilding::setEntries(const QVector<GeoDataBuilding::NamedEntry> &entries)
{
    d->m_entries = entries;
}

double GeoDataBuilding::parseBuildingHeight(const QString& buildingHeight)
{
    double height = 8.0;

    // check first for unitless value
    bool converted;
    double extractedHeight = buildingHeight.toDouble(&converted);
    if (converted) {
        return extractedHeight;
    }

    if (buildingHeight.endsWith(QChar('m')) ||
        buildingHeight.endsWith(QLatin1String("meter")) ||
        buildingHeight.endsWith(QLatin1String("meters")) ||
        buildingHeight.endsWith(QLatin1String("metre")) ||
        buildingHeight.endsWith(QLatin1String("metres"))) {
        QString const heightValue = QString(buildingHeight).remove(QStringLiteral("meters"))
                .remove(QStringLiteral("meter")).remove(QStringLiteral("metres"))
                .remove(QStringLiteral("metre")).remove(QChar('m')).trimmed();
        bool extracted;
        double extractedHeight = heightValue.toDouble(&extracted);
        if (extracted) {
            height = extractedHeight;
        }
    } else { // feet and inches
        double extractedHeight = 0.0; // in inches, converted to meters in the end
        if (buildingHeight.contains(QChar('\''))) {
            double heightInches = 0.0;
            QStringList const feetInches = buildingHeight.split(QChar('\''));
            bool okFeet;
            double feet = feetInches[0].trimmed().toDouble(&okFeet);
            if (okFeet) {
                heightInches = feet * FT2IN;
            }
            if (!feetInches[1].isEmpty()) { // has inches as unit as well
                bool okInches;
                double inches = QString(feetInches[1]).remove(QChar('\"')).trimmed().toDouble(&okInches);
                if (okInches) {
                    heightInches += inches;
                }
            }
            extractedHeight = heightInches;
        } else if (buildingHeight.endsWith(QLatin1String("feet"))) {
            bool ok;
            double feet = QString(buildingHeight).remove(QStringLiteral("feet")).trimmed().toDouble(&ok);
            if (ok) {
                extractedHeight = feet * FT2IN;
            }
        }
        if (extractedHeight > 0.0) {
            height = extractedHeight * IN2M; // convert inches to meters
        }
    }

    return height;
}

bool GeoDataBuilding::isBuilding(const OsmPlacemarkData &osmData)
{
    for (auto iter = osmData.tagsBegin(), end=osmData.tagsEnd(); iter != end; ++iter) {
        const auto tag = StyleBuilder::OsmTag(iter.key(), iter.value());
        if (isBuildingTag(tag)) {
            return true;
        }
    }

    return false;
}

bool GeoDataBuilding::isBuildingTag(const StyleBuilder::OsmTag &keyValue)
{
    if (s_buildingTags.isEmpty()) {
        for (auto const & tag: StyleBuilder::buildingTags()) {
            s_buildingTags.insert(tag);
        }
    }

    return s_buildingTags.contains(keyValue);
}

QString GeoDataBuilding::extractName(const OsmPlacemarkData &osmData)
{
    auto tagIter = osmData.findTag(QStringLiteral("addr:housename"));
    if (tagIter != osmData.tagsEnd()) {
        return tagIter.value();
    }

    tagIter = osmData.findTag(QStringLiteral("addr:housenumber"));
    if (tagIter != osmData.tagsEnd()) {
        return tagIter.value();
    }

    return QString();
}

double GeoDataBuilding::extractHeight(const OsmPlacemarkData &osmData)
{
    double height = 0.0;

    QHash<QString, QString>::const_iterator tagIter;
    if ((tagIter = osmData.findTag(QStringLiteral("height"))) != osmData.tagsEnd()) {
        height = parseBuildingHeight(tagIter.value());
    } else if ((tagIter = osmData.findTag(QStringLiteral("building:levels"))) != osmData.tagsEnd()) {
        int const levels = tagIter.value().toInt();
        int const skipLevels = osmData.tagValue(QStringLiteral("building:min_level")).toInt();
        /** @todo Is 35 as an upper bound for the number of levels sane? */
        height = 3.0 * qBound(1, 1+levels-skipLevels, 35);
    }

    return qBound(1.0, height, 1000.0);
}

QVector<GeoDataBuilding::NamedEntry> &GeoDataBuilding::extractNamedEntries(const OsmPlacemarkData &osmData)
{
    QVector<GeoDataBuilding::NamedEntry> entries;

    const auto end = osmData.nodeReferencesEnd();
    for (auto iter = osmData.nodeReferencesBegin(); iter != end; ++iter) {
        const auto tagIter = iter.value().findTag(QStringLiteral("addr:housenumber"));
        if (tagIter != iter.value().tagsEnd()) {
            GeoDataBuilding::NamedEntry entry;
            entry.point = iter.key();
            entry.label = tagIter.value();
            entries.push_back(entry);
        }
    }

    return entries;
}

GeoDataMultiGeometry *GeoDataBuilding::multiGeometry() const
{
    return &d->m_multiGeometry;
}

}
