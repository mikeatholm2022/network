// sd_msg.cpp

#include "self_describing_message.h"
#include "self_describing_message_tags.h"

#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

namespace chaos
{
    namespace network
    {
        // ========================================================================================
        SDMessage::SDMessage()
        {
        }

        /// =======================================================================================
        SDMessage::SDMessage( const std::string& payload )
        {
            parse_payload(payload);
        }

        // ========================================================================================
        SDMessage::~SDMessage()
        {
            m_map.clear();
        }

        // ========================================================================================
        void SDMessage::clear()
        {
            m_map.clear();
            m_payload = "";
        }

        // ========================================================================================
        void SDMessage::add_field( std::int32_t tag, const std::string& data )
        {
            m_map.insert( std::make_pair(tag, data) );
        }

        // ========================================================================================
        bool SDMessage::get_field(std::int32_t tag, std::string& data )
        {
            bool bRet = false;
            auto it = m_map.find(tag);
            if (it != m_map.end())
            {
                data = it->second;
                bRet = true;
            }

            return bRet;
        }

        // ========================================================================================
        void SDMessage::get_fields( SDMMap& map )
        {
            map = m_map;
        }

        // ========================================================================================
        void SDMessage::parse_payload( const std::string& payload )
        {
            clear();
            parse(payload);
        }

        // ========================================================================================
        void SDMessage::parse( const std::string& payload )
        {
            typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
            boost::char_separator<char> sep{ "=", "|" };
            tokenizer tok{ payload, sep };

            std::int32_t index = 0, tag = 0;
            for (const auto& t : tok)
            {
                if (index == 0)
                {
                    tag = boost::lexical_cast<std::int32_t>(t);
                    index++;
                }
                else
                {
                    m_map.insert(std::make_pair(tag, t));
                    index = 0;
                }
            }
        }

        // ========================================================================================
        const std::string& SDMessage::get_binary_payload()
        {
            // If the payload is empty then lets parse it again
            if (m_payload.empty())
            {
                std::stringstream ss;
                for (auto& it : m_map)
                    ss << it.first << "=" << it.second << "|";

                m_payload = ss.str();
            }

            return m_payload;
        }

        // ========================================================================================
        const std::string& SDMessage::regenerate_binary_payload()
        {
            m_payload = "";
            return get_binary_payload();
        }
    }
}
