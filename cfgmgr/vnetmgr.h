
#ifndef __VNETMGRMGR__
#define __VNETMGRMGR__

#include "dbconnector.h"
#include "producerstatetable.h"
#include "orch.h"

#include <map>
#include <vector>
#include <memory>
#include <string>
#include <utility>

namespace swss {
class VNetMgr : public Orch
{
public:
    VNetMgr(DBConnector *db, const std::vector<TableConnector> &tables);
    using Orch::doTask;

    typedef struct VnetInfo
    {
        std::string m_vxlanTunnel;
        std::string m_sourceIp;
        std::string m_vnet;
        std::string m_vni;
        std::string m_macAddress;
    } VnetInfo;

    typedef struct TunCache
    {
        std::vector<FieldValueTuple> fvt;
        std::string m_sourceIp;
        uint32_t vlan_vni_refcnt;
    } TunCache;

    typedef struct VxlanRouteTunnelInfo
    {
        std::string m_routeName;
        std::string m_macAddress;
        std::string m_endpoint;
        std::string m_vni;
        std::string m_vnet;
        std::string m_prefix;
        std::bool m_installOnKernel;
    } VxlanRouteTunnelInfo;

    typedef struct VxlanKernelRouteInfo
    {
        std::string m_routeName;
        std::string m_dstMac;
        std::string m_dstIp;
        std::string m_srcIp;
        std::string m_srcMac;
        std::string m_vni;
        std::string m_vnet;
        std::string m_prefix;
        std::string m_vxlanDevName;
    } VxlanKernelRouteInfo;

private:
    void doTask(Consumer &consumer);

    Table m_cfgVxlanTunnelTable,m_cfgVnetTable,m_stateVrfTable,m_stateVxlanTable, m_stateVxlanTunnelTable;
    ProducerStateTable m_vnet_tunnelTable;

    DBConnector *m_app_db;

    std::map<std::string, std::string> m_vxlanNetDevices;
    std::map<std::string, TunCache > m_vxlanTunnelCache;
    std::map<std::string, VnetInfo> m_vnetCache;
    std::map<std::string, VxlanRouteTunnelInfo> m_vnetRouteTunnelCache;
    std::map<std::string, VxlanKernelRouteInfo> m_kernelRouteTunnelCache;
};
} // namespace swss

#endif