/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>

 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "GameTime.h"
#include "Timer.h"
#include "Util.h"

namespace GameTime
{
    time_t const StartTime = time(nullptr);

    time_t GameTime = time(nullptr);
    uint32 GameMSTime = 0;

    SystemTimePoint GameTimeSystemPoint = SystemTimePoint::min();
    TimePoint GameTimeSteadyPoint = TimePoint::min();

    tm DateTime;

    time_t GetStartTime()
    {
        return StartTime;
    }

    time_t GetGameTime()
    {
        return GameTime;
    }

    uint32 GetGameTimeMS()
    {
        return GameMSTime;
    }

    SystemTimePoint GetSystemTime()
    {
        return GameTimeSystemPoint;
    }

    TimePoint Now()
    {
        return GameTimeSteadyPoint;
    }

    template<>
    SystemTimePoint GetTime<std::chrono::system_clock>()
    {
        return GetSystemTime();
    }

    template<>
    TimePoint GetTime<std::chrono::steady_clock>()
    {
        return Now();
    }

    uint32 GetUptime()
    {
        return uint32(GameTime - StartTime);
    }

    tm const* GetDateAndTime()
    {
        return &DateTime;
    }

    void UpdateGameTimers()
    {
        GameTime = time(nullptr);
        GameMSTime = getMSTime();
        GameTimeSystemPoint = std::chrono::system_clock::now();
        GameTimeSteadyPoint = std::chrono::steady_clock::now();
        localtime_r(&GameTime, &DateTime);
    }
}
