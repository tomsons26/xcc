// sql_query.cpp: implementation of the Csql_query class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sql_query.h"

#include "database.h"
#include "string_conversion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Csql_query::Csql_query(Cdatabase& database):
	m_database(database)
{
}

Csql_result Csql_query::execute() const
{
	return m_database.query(read());
}

string Csql_query::read() const
{
	string r;
	r.reserve(m_data.length());
	t_list::const_iterator l = m_list.begin();
	for (int i = 0; i < m_data.length(); i++)
	{
		if (m_data[i] == '%')
		{
			i++;
			if (i < m_data.length())
			{
				switch (m_data[i])
				{
				case 's':
					assert(l != m_list.end());
					r += *l++;
					break;
				default:
					r += m_data[i];
				}
			}
		}
		else
			r += m_data[i];
	}
	assert(l == m_list.end());
	return r;
}

void Csql_query::write(const string& v)
{
	m_data = v;
	m_list.clear();
}

void Csql_query::p(const string& v)
{
	m_list.push_back(v);
}

void Csql_query::p(int v)
{
	p(n(v));
}

void Csql_query::pe(const string& v)
{
	char* r = new char[2 * v.length() + 3];
	r[0] = '\"';
	// mysql_real_escape_string(&m_handle, r, v.c_str(), v.length());
	mysql_escape_string(r + 1, v.c_str(), v.length());
	strcat(r, "\"");
	p(r);
	delete[] r;
}

void Csql_query::pe(const Cvirtual_binary v)
{
	char* r = new char[2 * v.size() + 3];
	r[0] = '\"';
	// mysql_real_escape_string(&m_handle, r, v.c_str(), v.length());
	mysql_escape_string(r + 1, reinterpret_cast<const char*>(v.data()), v.size());
	strcat(r, "\"");
	p(r);
	delete[] r;
}