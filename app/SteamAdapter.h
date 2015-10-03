#ifndef STEAMADAPTER_H
#define STEAMADAPTER_H

#include <steam_api.h>
#include <iostream>

using namespace std;


class SteamAdapter
{
public:
    SteamAdapter();

    bool initialize();
};

#endif // STEAMADAPTER_H
