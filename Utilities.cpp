#include <iostream>
#include "Utilities.h"
namespace seneca
{
	char Utilities::m_delimiter = ',';

	void Utilities::setDelimiter(char delimiter)
	{
		m_delimiter = delimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

	void Utilities::setFieldWidth(size_t width)
	{
		m_fieldWidth = width;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_fieldWidth;
	}

	//std::string Utilities::trim(std::string str)
	//{
	//	size_t last = str.find_last_not_of(' ');
	//	size_t first = str.find_first_not_of(' ');
	//	if (first == std::string::npos)
	//	{
	//		return str;
	//	}
	//	return str.substr(first, (last - first + 1));
	//}

	std::string Utilities::trim(std::string& s) {
		std::string temp{};

		size_t p = s.find_first_not_of(" \t");
		s.erase(0, p);

		p = s.find_last_not_of(" \t");
		if (std::string::npos != p) {
			temp = s.erase(p + 1);
		}
		return temp;
	}


	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token{}, restStr{};
		size_t n{};

		if (more) {
			n = str.find(m_delimiter, next_pos);

			if (n != std::string::npos) {
				if (n == next_pos) {
					more = false;
					throw "Error! A delimiter is found at next_pos";
				}
				else {
					token = str.substr(next_pos, (n - next_pos));
					token = trim(token);

					next_pos = n + 1;
					str[n] == '\n' ? more = false : more = true;
				}
			}
			else {
				more = false;
				token = str.substr(next_pos);
				token = trim(token);
			}

			if (m_fieldWidth < token.length()) {
				m_fieldWidth = token.length();
			}
		}
		return token;
	}

}