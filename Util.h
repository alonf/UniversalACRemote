// Util.h

#ifndef _UTIL_h
#define _UTIL_h

#include <arduino.h>
#include <algorithm>
#include <vector>

namespace Util
{
	void software_Reboot(); //rebot the board

	template <typename T, std::size_t n>
	void String2Array(const String &str, T(&arr)[n])
	{
        memset(arr, 0, n);
		memcpy(arr, str.c_str(), std::min(n - 1, str.length() + 1));
	}

    template<typename TKey, typename TValue>
    class Map
    {
    private:
        std::vector<std::pair<TKey, TValue>> _vector;

    public:
        Map() = default;
        Map(const std::initializer_list<std::pair<TKey, TValue>>& list)
        {
            for (auto &element : list)
            {
                _vector.push_back(element);
            }
        }

        TValue& at(const TKey& key)
        {
            for (unsigned int i = 0; i < _vector.size(); ++i)
            {
                if (_vector[i].first == key) //found
                    return _vector[i].second;
            }
            _vector.push_back(std::pair<TKey, TValue>(key, TValue()));
            return _vector.rbegin()->second;
        }

        const TValue& at(const TKey& key) const
        {
            for (int i = 0; i < _vector.size(); ++i)
            {
                if (_vector[i].first == key) //found
                    return _vector[i].second;
            }
            return TValue();
        }

        void clear() { _vector.clear(); }

        TValue &operator[](const TKey &key) { return at(key); }
    };

    typedef Map<String, String> StringMap;
}


#endif

