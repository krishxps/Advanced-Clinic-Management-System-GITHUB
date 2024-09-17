#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <iostream>
#include <vector>
#include "Station.h"

namespace seneca {
	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{ nullptr };

		static size_t m_widthField;

	public:
		// Default constructor
		CustomerOrder();

		// Constructor with a string argument to initialize order
		CustomerOrder(const std::string& theStr);

		// Copy constructor - Not allowed
		CustomerOrder(const CustomerOrder& other);

		// Assignment operator - Not allowed
		CustomerOrder& operator=(const CustomerOrder& other) = delete;

		// Move constructor for transferring ownership of resources
		CustomerOrder(CustomerOrder&& other) noexcept;

		// Move assignment operator for transferring ownership of resources
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		// Destructor for cleaning up resources
		~CustomerOrder();

		// checks if order is filled or not
		bool isOrderFilled() const;

		// Checks if a specific item in the order is filled
		bool isItemFilled(const std::string& itemName) const;

		// Fills items from the station and outputs status to the provided stream
		void fillItem(Station& station, std::ostream& os);

		// Displays the order details to the provided stream
		void display(std::ostream& os) const;
	};
}
#endif // !SENECA_CUSTOMERORDER_H
