#ifndef __BULKDATA_H__
#define __BULKDATA_H__

#include <stdint.h>

#include "sqlite3.h"

#include "cache_types.h"
#include <vector>

// @TODO: Find how to generate this, but use the enum in edit_window
enum cache_tag {
    tag_cacheShipTypes,
    tag_cacheStaOperations,
    tag_cacheRamAssemblyLineTypesCategory,
    tag_cacheInvCategories,
    tag_cacheDogmaEffects,
    tag_cacheRamCompletedStatuses,
    tag_cacheInvBlueprintTypes,
    tag_cacheRamTypeRequirements,
    tag_cacheCertificateRelationships,
    tag_cacheDogmaAttributes,
    tag_cacheRamAssemblyLineTypes,
    tag_cacheStaStationsStatic,
    tag_cacheInvGroups,
    tag_cacheInvMetaTypes,
    tag_cacheInvTypeReactions,
    tag_cacheDogmaTypeEffects,
    tag_cachePlanetSchematics,
    tag_cacheDogmaUnits,
    tag_cachePlanetSchematicsTypeMap,
    tag_cacheDogmaTypeAttributes,
    tag_cacheDogmaExpressions,
    tag_cacheRamAssemblyLineTypesGroup,
    tag_cacheResGraphics,
    tag_cacheInvTypes,
    tag_cacheResIcons,
    tag_cacheActBillTypes,
    tag_cachePlanetSchematicsPinMap,
    tag_cacheInvContrabandTypes,
    tag_cacheInvMetaGroups,
    tag_cacheCertificates,
    tag_cacheInvTypeMaterials,
    tag_cacheResSounds,
    tag_cacheRamActivities,
};

struct edit_window {
    uint32_t typeID;
    void *data;
    bool show;
    cache_tag tag;
};

struct bulkdata {
    sqlite3 *db;
};

uint32_t bulkdata_init(bulkdata *b);
uint32_t bulkdata_shutdown(bulkdata *b);

#endif
