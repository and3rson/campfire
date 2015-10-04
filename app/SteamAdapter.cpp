#include "SteamAdapter.h"

SteamAdapter::SteamAdapter()
{

}

bool SteamAdapter::initialize()
{
    return true;
    if (!SteamAPI_Init()) {
        cerr << "SteamAPI_Init() failed!" << endl;
        return false;
    }

    if (!SteamUser()->BLoggedOn()) {
        cerr << "Steam user is not logged in!" << endl;
        return false;
    }

    return true;
}
