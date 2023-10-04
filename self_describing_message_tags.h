// Simple object for parsing generic network messages
//
// Copyright HOLM, 2023

#pragma once

#include <boost/unordered_map.hpp>


// ================================================================================================

namespace chaos
{
    namespace network
    {
        typedef boost::unordered::unordered_map< int, std::string > SDMMap;

        // ========================================================================================
        enum
        {
            eUNKNOWN = 0,
            eSYMBOL = 1,
            eLAST = 2,
            eBID_SZ = 3,
            eBID = 4,
            eASK = 5,
            eASK_SZ = 6,
            eCURRENT_POSITION = 7,
            eINSTANCE = 8,
            eAPPLICATION = 9,
            eHOST = 10,




            eLAST_TAG = 10
        }	eSDMTags;
    }
}
