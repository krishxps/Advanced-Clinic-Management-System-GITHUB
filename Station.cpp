
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"

namespace seneca {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& theStr) {
        Utilities util{};
        bool more = true;
        size_t next_pos = 0;

        m_name = util.extractToken(theStr, next_pos, more);
        std::string serialStr = util.extractToken(theStr, next_pos, more);
        
        m_serialNum = std::stoul(serialStr);
        std::string quantityStr = util.extractToken(theStr, next_pos, more);
        
        m_quantity = std::stoul(quantityStr);


        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }

        m_desc = util.extractToken(theStr, next_pos, more);
        m_id = ++id_generator;
    }


    const std::string& Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNum++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ')
            << " | " << std::setw(m_widthField) << std::left << m_name
            << " | " << std::setw(6) << std::setfill('0') << std::right
            << m_serialNum << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | " << std::left << m_desc;
        }

        os << "\n";
    }
}
