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
        typedef boost::unordered::unordered_map< std::int32_t, std::string > SDMMap;

        // ========================================================================================
        class SDMessage
        {
        public:
            SDMessage();
            SDMessage( const std::string& payload );
            virtual ~SDMessage();

            void add_field(std::int32_t tag, const std::string& data);
            bool get_field(std::int32_t tag, std::string& data);
            void get_fields(SDMMap& map);
            void clear();

            const std::string& get_binary_payload();
            const std::string& regenerate_binary_payload();
            void set_payload( const std::string& payload ) { parse_payload(payload); }

        private:
            std::string     m_payload;
            SDMMap          m_map;

            bool parse_tag_value( const std::string& tag_value, std::string& tag, std::string& value );
            void parse( const std::string& payload );
            void parse_payload( const std::string& payload );

        };
    }
}
