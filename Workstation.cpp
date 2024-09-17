#include <iostream>
#include <deque>
#include <string>
#include <iomanip>
#include <algorithm>
#include <utility>
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"
using namespace std;

namespace seneca {

	deque<CustomerOrder> g_pending{};
	deque<CustomerOrder> g_completed{};
	deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const string& str) : Station(str) {}
	
	void Workstation::fill(ostream& os) {
		if (!m_orders.empty()) m_orders.front().fillItem(*this, os);
	}

	bool Workstation::attemptToMoveOrder() {
		bool isMoved = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					m_pNextStation->m_orders.push_back(move(this->m_orders.front()));
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(move(m_orders.front()));
					}
				}
				m_orders.pop_front();
				isMoved = true;
			}
		}
		return isMoved;
	}

	void Workstation::setNextStation(Workstation* station = nullptr) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const {
		os << getItemName() << " --> ";
		if (m_pNextStation) os << m_pNextStation->getItemName() << "\n";
		else os << "End of Line\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(move(newOrder));
		return *this;
	}

}