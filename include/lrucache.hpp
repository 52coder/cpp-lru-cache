/* 
 * File:   lrucache.hpp
 * Author: Alexander Ponomarev
 * Modify by: 52coder
 * Created on Nov 29, 2019, 23:15 PM
 */

#ifndef _LRUCACHE_HPP_INCLUDED_
#define	_LRUCACHE_HPP_INCLUDED_

#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>

namespace cache 
{

template<typename key_t, typename value_t>
class lru_cache 
{
public:
	typedef typename std::pair<key_t, value_t> key_value_pair_t;
	typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

	lru_cache(size_t max_size) :m_max_size(max_size) {}
	
	void put(const key_t& key, const value_t& value) 
	{
		auto it = m_cache_items_map.find(key);
		m_cache_items_list.push_front(key_value_pair_t(key, value));
		
		if (it != m_cache_items_map.end()) 
		{
			m_cache_items_list.erase(it->second);
			m_cache_items_map.erase(it);
		}

		m_cache_items_map[key] = m_cache_items_list.begin();
		
		if (m_cache_items_map.size() > m_max_size) 
		{
			auto last_node = m_cache_items_list.rbegin();
			m_cache_items_map.erase(last_node->first);
			m_cache_items_list.pop_back();
		}
	}
	
	bool get(const key_t& key,value_t& value) 
	{
		auto it = m_cache_items_map.find(key);
		if (it == m_cache_items_map.end()) 
		{
			return false;
		} 
		else 
		{
			//将访问到的这个节点放在最前面
			m_cache_items_list.splice(m_cache_items_list.begin(), m_cache_items_list, it->second);
			value = it->second->second;
			return true;
		}
	}
	//判断key是否存在
	bool exists(const key_t& key) const 
	{
		return m_cache_items_map.find(key) != m_cache_items_map.end();
	}
	
	size_t size() const 
	{
		return m_cache_items_map.size();
	}
	
private:
	std::list<key_value_pair_t> m_cache_items_list;
	std::unordered_map<key_t, list_iterator_t> m_cache_items_map;
	size_t m_max_size;
};

} // namespace cache

#endif	/* _LRUCACHE_HPP_INCLUDED_ */

