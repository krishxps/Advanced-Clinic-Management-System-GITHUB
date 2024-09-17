#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <string>
#include "Workstation.h"

namespace seneca {

	class LineManager {
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{ 0 };
		Workstation* m_firstWorkstation{ nullptr };
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& station);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}


#endif // !SENECA_LINEMANAGER_H
