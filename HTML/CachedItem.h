#pragma once

template<typename T>
class CachedItem
{
protected:
	T m_value;
	bool m_was_fetched = false;
public:

	T& value()
	{
		return m_value;
	}
	void set_value(T& value)
	{
		m_value = value;
		m_was_fetched = true;
	}
	bool was_fetched()
	{
		return m_was_fetched;
	}
};