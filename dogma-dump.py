cacheIDs = {
    "cacheEosNpcToNpcStandings" :109998,
    "cacheAutAffiliates" :109997,
    "cacheAutCdkeyTypes" :109996,
    "cacheTutCategories" :200006,
    "cacheTutCriterias" :200003,
    "cacheTutTutorials" :200001,
    "cacheTutActions" :200009,
    "cacheDungeonArchetypes" :300001,
    "cacheDungeonDungeons" :300005,
    "cacheDungeonEntityGroupTypes" :300004,
    "cacheDungeonEventMessageTypes" :300017,
    "cacheDungeonEventTypes" :300015,
    "cacheDungeonSpawnpoints" :300012,
    "cacheDungeonTriggerTypes" :300013,
    "cacheInvCategories" :600001,
    "cacheInvContrabandTypes" :600008,
    "cacheInvGroups" :600002,
    "cacheInvTypes" :600004,
    "cacheInvTypeMaterials" :600005,
    "cacheInvTypeReactions" :600010,
    "cacheInvWreckUsage" :600009,
    "cacheInvMetaGroups" :600006,
    "cacheInvMetaTypes" :600007,
    "cacheDogmaAttributes" :800004,
    "cacheDogmaEffects" :800005,
    "cacheDogmaExpressionCategories" :800001,
    "cacheDogmaExpressions" :800003,
    "cacheDogmaOperands" :800002,
    "cacheDogmaTypeAttributes" :800006,
    "cacheDogmaTypeEffects" :800007,
    "cacheDogmaUnits" :800009,
    "cacheEveMessages" :1000001,
    "cacheInvBlueprintTypes" :1200001,
    "cacheNpcTypeLoots" :1600001,
    "cacheRamSkillInfo" :1809999,
    "cacheRamActivities" :1800003,
    "cacheRamAssemblyLineTypes" :1800006,
    "cacheRamAssemblyLineTypesCategory" :1800004,
    "cacheRamAssemblyLineTypesGroup" :1800005,
    "cacheRamCompletedStatuses" :1800007,
    "cacheRamInstallationTypes" :1800002,
    "cacheRamTypeRequirements" :1800001,
    "cacheReverseEngineeringTableTypes" :1800009,
    "cacheReverseEngineeringTables" :1800008,
    "cacheShipInsurancePrices" :2000007,
    "cacheShipTypes" :2000001,
    "cacheStaOperations" :2209999,
    "cacheStaServices" :2209998,
    "cacheStaOperationServices" :2209997,
    "cacheStaSIDAssemblyLineQuantity" :2209996,
    "cacheStaSIDAssemblyLineType" :2209995,
    "cacheStaSIDAssemblyLineTypeQuantity" :2209994,
    "cacheStaSIDOfficeSlots" :2209993,
    "cacheStaSIDReprocessingEfficiency" :2209992,
    "cacheStaSIDServiceMask" :2209991,
    "cacheStaStationImprovementTypes" :2209990,
    "cacheStaStationUpgradeTypes" :2209989,
    "cacheStaStations" :2209988,
    "cacheStaStationsStatic" :2209987,
    "cacheMktOrderStates" :2409999,
    "cacheMktNpcMarketData" :2400001,
    "cacheNpcSupplyDemand" :2800001,
    "cacheAgentAgents" :3009999,
    "cacheAgentCorporationActivities" :3009998,
    "cacheAgentCorporations" :3009997,
    "cacheAgentEpicMissionMessages" :3009996,
    "cacheAgentEpicMissionsBranching" :3009995,
    "cacheAgentEpicMissionsNonEnd" :3009994,
    "cacheAgtContentAgentInteractionMissions" :3009992,
    "cacheAgtContentFlowControl" :3009991,
    "cacheAgtContentTalkToAgentMissions" :3009990,
    "cacheAgtPrices" :3009989,
    "cacheAgtResearchStartupData" :3009988,
    "cacheAgtContentTemplates" :3000001,
    "cacheAgentMissionsKill" :3000006,
    "cacheAgtStorylineMissions" :3000008,
    "cacheAgtContentCourierMissions" :3000003,
    "cacheAgtContentExchangeOffers" :3000005,
    "cacheAgentEpicArcConnections" :3000013,
    "cacheAgentEpicArcMissions" :3000015,
    "cacheAgentEpicArcs" :3000012,
    "cacheAgtContentMissionExtraStandings" :3000020,
    "cacheAgtContentMissionTutorials" :3000018,
    "cacheAgtContentMissionLocationFilters" :3000021,
    "cacheAgtOfferDetails" :3000004,
    "cacheAgtOfferTableContents" :3000010,
    "cacheUserEspTagTypes" :4309999,
    "cacheFacWarCombatZoneSystems" :4500006,
    "cacheFacWarCombatZones" :4500005,
    "cacheActBillTypes" :6400004,
    "cachePetCategories" :8109999,
    "cachePetQueues" :8109998,
    "cachePetCategoriesVisible" :8109997,
    "cacheGMQueueOrder" :8109996,
    "cacheCertificates" :5100001,
    "cacheCertificateRelationships" :5100004,
    "cachePlanetSchematics" :7300004,
    "cachePlanetSchematicsTypeMap" :7300005,
    "cachePlanetSchematicsPinMap" :7300003,
    "cacheBattleStatuses" :100509999,
    "cacheBattleResults" :100509998,
    "cacheBattleServerStatuses" :100509997,
    "cacheBattleMachines" :100509996,
    "cacheBattleClusters" :100509995,
    "cacheEspCorporations" :1,
    "cacheEspAlliances" :2,
    "cacheSolarSystemObjects" :4,
    "cacheCargoContainers" :5,
    "cachePriceHistory" :6,
    "cacheTutorialVersions" :7,
    "cacheSolarSystemOffices" :8,
    "cacheResGraphics" :2001800001,
    "cacheResSounds" :2001800002,
    "cacheResIcons" :2001800004,
    "cacheEspCorporations" :1,
    "cacheEspAlliances" :2,
    "cacheEspSolarSystems" :3,
    "cacheSolarSystemObjects" :4,
    "cacheCargoContainers" :5,
    "cachePriceHistory" :6,
    "cacheTutorialVersions" :7,
    "cacheSolarSystemOffices" :8
}

cache_path = "../Crucible/bulkdata"

from reverence import blue

import sqlite3

conn = sqlite3.connect("bulkdata.db")

cache_keys = {}
cache = {}

def typer(s):
    if s == "True":
        return "bool"
    if s == "False":
        return "bool"
    try:
        float(s)
        if "." not in s:
            return "int"
        return "float"
    except ValueError:
        return "string"

def parse_dbrow_str(dbrow):
    d = []
    st = dbrow.__str__()
    st = st.split("DBRow(")[1]
    m = st.split(",")
    for x in m:
        if x == m[-1]: # Check if we're the last iteration
            d.append((x.split(":")[0],
                      typer(x.split(":")[1][:-1]),
                      x.split(":")[1][:-1] # Cut the ending paren
            ))
        else:
            d.append((x.split(":")[0],
                      typer(x.split(":")[1]),
                      x.split(":")[1]
            ))

    return d

def generate_sqlite_table(cache_name):
    c = conn.cursor()
    keys = cache_keys[cache_name]
    query = "CREATE TABLE " + cache_name + " ("
    for x in keys:
        query += " " + x[0] + " "
        if x[1] == "string":
            query += "TEXT"
        if x[1] == "int":
            query += "INTEGER"
        if x[1] == "float":
            query += "REAL"
        if x[1] == "bool":
            query += "INTEGER"
        if x != keys[-1]:
            query += ","
            
    query += " )"
    c.execute(query)

def insert_sqlite_row(cache_name, row):
    c = conn.cursor()
    keys = cache_keys[cache_name]
    query = "insert into " + cache_name + " VALUES ("
    for x in keys:
        key = str(x[0])
        if type(row[key]) == bool:
            query += " " + str(row[key]) + " "
        elif row[key] == None:
            query += " NULL "
        elif x[1] == "string":
            query += " '" + row[key].strip().replace("'","''") + "' "
        else:
            query += " " + str(row[str(x[0])]) + " "
        if x != keys[-1]:
            query += ","
            
    query += " )"

    c.execute(query.strip())

   


for k, v in cacheIDs.iteritems():
    fp = cache_path + "/" + str(v) + ".cache2"
    
    f = None
    try:
        f = open(fp, "rb")
    except Exception as e:
        continue

    d = f.read()
    d = blue.marshal.Load(d)

    cache[k] = d
    cache_keys[k] = parse_dbrow_str(d[0])

    print " > [" + k + "] Generating table"
    generate_sqlite_table(k)

    print " > [" + k + "] Inserting Data"
    for x in d:
        insert_sqlite_row(k, x)

conn.commit()
conn.close()
    
