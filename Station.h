#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <iostream> 
#include <string>
#include "Utilities.h"

namespace seneca {
	class Station {
		size_t m_id;
		std::string m_name;
		std::string m_desc;
		size_t m_serialNum;
		size_t m_quantity;
		static size_t m_widthField;
		static size_t id_generator;

	public:
		// default constructor
		Station(const std::string& theStr);

		// get the name of the resource
		const std::string& getItemName() const;

		// get the id of the resource
		size_t getNextSerialNumber();

		// get the quantity of the resource
		size_t getQuantity() const;

		// update the quantity of the resource
		void updateQuantity();

		// display the resource
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SENECA_STATION_H