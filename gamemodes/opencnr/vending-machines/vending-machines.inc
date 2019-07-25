// vending-machines takes care of what happens when a player uses one of the
// vending machines.

// -
// Declaration
// -

#define VENDING_MACHINE_INTERVAL    3

static const Float:vendingMachinePoints[][3] =
{
    {-14.70, 1175.36, 18.95},     {201.02, -107.62, 0.90},
    {662.43, -552.16, 15.71},     {-76.03, 1227.99, 19.13},
    {1154.73, -1460.89, 15.16},   {1277.84, 372.52, 18.95},
    {1398.84, 2222.61, 10.42},    {1520.15, 1055.27, 10.00},
    {1634.11, -2237.53, 12.89},   {1659.46, 1722.86, 10.22},
    {1729.79, -1943.05, 12.95},   {1789.21, -1369.27, 15.16},
    {1928.73, -1772.45, 12.95},   {2060.12, -1897.64, 12.93},
    {2085.77, 2071.36, 10.45},    {2139.52, -1161.48, 23.36},
    {2153.23, -1016.15, 62.23},   {2271.73, -76.46, 25.96},
    {2319.99, 2532.85, 10.22},    {2325.98, -1645.13, 14.21},
    {2352.18, -1357.16, 23.77},   {2480.86, -1959.27, 12.96},
    {2503.14, 1243.70, 10.22},    {-253.74, 2597.95, 62.24},
    {-253.74, 2599.76, 62.24},    {2647.70, 1129.66, 10.22},
    {2845.73, 1295.05, 10.79},    {-862.83, 1536.61, 21.98},
    {-1350.12, 492.29, 10.59},    {-1350.12, 493.86, 10.59},
    {-1455.12, 2591.66, 55.23},   {-1980.79, 142.66, 27.07},
    {-2005.65, -490.05, 34.73},   {-2011.14, -398.34, 34.73},
    {-2034.46, -490.05, 34.73},   {-2039.85, -398.34, 34.73},
    {-2063.27, -490.05, 34.73},   {-2068.56, -398.34, 34.73},
    {-2092.09, -490.05, 34.73},   {-2097.27, -398.34, 34.73},
    {-2118.62, -422.41, 34.73},   {-2118.97, -423.65, 34.73},
    {-2229.19, 286.41, 34.70},    {-2420.18, 985.95, 44.30},
    {-2420.22, 984.58, 44.30},    {2155.84, 1607.88, 1000.06},
    {2155.91, 1606.77, 1000.05},  {2202.45, 1617.01, 1000.06},
    {2209.24, 1621.21, 1000.06},  {2209.91, 1607.20, 1000.05},
    {2222.20, 1606.77, 1000.05},  {2222.37, 1602.64, 1000.06},
    {2225.20, -1153.42, 1025.91}, {-15.10, -140.23, 1003.63},
    {-16.12, -91.64, 1003.63},    {-16.53, -140.30, 1003.63},
    {-17.55, -91.71, 1003.63},    {-19.04, -57.84, 1003.63},
    {-32.45, -186.70, 1003.63},   {-33.88, -186.77, 1003.63},
    {330.68, 178.50, 1020.07},    {331.92, 178.50, 1020.07},
    {-35.73, -140.23, 1003.63},   {350.91, 206.09, 1008.48},
    {-36.15, -57.88, 1003.63},    {361.56, 158.62, 1008.48},
    {371.59, 178.45, 1020.07},    {373.83, -178.14, 1000.73},
    {374.89, 188.98, 1008.48},    {379.04, -178.88, 1000.73},
    {495.97, -24.32, 1000.73},    {500.56, -1.37, 1000.73},
    {501.83, -1.43, 1000.73},     {2576.70, -1284.43, 1061.09}
};

// Player variables

static playerVendingMachineLastUsage[MAX_PLAYERS];

// -
// Internal
// -

#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
    // Initializing and resetting player variables.
    playerVendingMachineLastUsage[playerid] = 0;

    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK))
    {
        if(IsPlayerNearVendingMachine(playerid))
        {
            if(playerVendingMachineLastUsage[playerid] + VENDING_MACHINE_INTERVAL < gettime())
            {
                if(GetPlayerServerMoney(playerid) >= 100)
                {
                    GivePlayerServerMoney(playerid, -100);
                    UpdatePlayerServerHealth(playerid, 10);

                    playerVendingMachineLastUsage[playerid] = gettime();
                }
            }
        }
    }

    return 1;
}

static IsPlayerNearVendingMachine(playerid)
{
    new ret;
    for(new i = 0; i < sizeof vendingMachinePoints; i++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, vendingMachinePoints[i][0], vendingMachinePoints[i][1], vendingMachinePoints[i][2]))
        {
            ret = true;
            break;
        }
    }

    return ret;
}