#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"
using namespace std;

namespace seneca {

	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
		fstream fileObj(file);
		if (!fileObj) throw string("Cannot open file named: [" + file + "]");
		else {
			string str{};
			while (getline(fileObj, str)) {
				if (fileObj) {
					size_t nextPos = 0;
					bool more = true;
					Utilities ut;
					string fStation = ut.extractToken(str, nextPos, more);
					string nStation = ""; 
					if(more) nStation = ut.extractToken(str, nextPos, more);
					
					Workstation* station = nullptr;
					Workstation* nextStation = nullptr;
					for_each(stations.begin(), stations.end(), [&](Workstation* st) {
						if (st->getItemName() == fStation) {
							station = st;
						}
						if (!nStation.empty() && st->getItemName() == nStation) {
							nextStation = st;
						}
						});
					if (station) {
						m_activeLine.push_back(station);
						station->setNextStation(nextStation);
					}
				}
			}
			fileObj.close();

			auto firstWorkstation = find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
				return none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* nextWs) {
					return nextWs->getNextStation() == ws;
				});
			});
			if (firstWorkstation != m_activeLine.end()) {
				m_firstWorkstation = *firstWorkstation;
			}
			else throw string("No first workstation is found");
			m_cntCustomerOrder = g_pending.size();
		}
	}

	void LineManager::reorderStations() {
		vector<Workstation*>tempStations{};
		Workstation* station = m_firstWorkstation;
		while (station) {
			tempStations.push_back(station);
			station = station->getNextStation();
		}
		m_activeLine = tempStations;
	}
	
	bool LineManager::run(ostream& os) {
		static size_t iterations = 0;
		os << "Line Manager Iteration: " << ++iterations << endl;
		if(!g_pending.empty()){
			*m_firstWorkstation += move(g_pending.front());
			g_pending.pop_front();
		}
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->fill(os);
		});
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
		});
		bool status = m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
		return status;
	}

	void LineManager::display(ostream& os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->display(os);
		});
	}

}