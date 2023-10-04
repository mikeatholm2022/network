// sd_msg.cpp

#include "self_describing_message.h"
#include "self_describing_message_tags.h"

#include <iostream>
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
            m_payload = payload;
            parse(payload);
        }

        // ========================================================================================
        void SDMessage::parse( const std::string& payload )
        {
            if (!payload.empty())
            {
                std::int32_t itag = 0;
                std::string tag, value;
                for (auto const &t : boost::tokenizer{payload, boost::char_separator{"|"}} )
                {
                    if (parse_tag_value(t, tag, value))
                    {
                        itag = boost::lexical_cast<std::int32_t>(tag);
                        m_map.insert(std::make_pair(itag, value));
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        // ========================================================================================
        bool SDMessage::parse_tag_value( const std::string& tag_value, std::string& tag, std::string& value )
        {
            if (!tag_value.empty())
            {
                std::int32_t index = 0;
                for (auto const &t : boost::tokenizer{tag_value, boost::char_separator{"="}} )
                {
                    if (index == 0)
                    {
                        tag = t;
                        index++;
                    }
                    else
                    {
                        value = t;
                        return true;
                    }
                }
            }

            return false;
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
