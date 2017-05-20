// https://leetcode.com/problems/permutation-in-string/#/description
// 567. Permutation in String

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
       
    auto mapItemUpdater = [](bool insertItem, char item, std::map<char, short>& m) // insert or remove item
	{
		if (insertItem)
		{
			auto insertRes = m.insert(std::make_pair(item, 1));
			if (!insertRes.second) 
				++insertRes.first->second;
		}
		else // Remove item
		{
			auto removeIt = m.find(item);
			if (--removeIt->second <= 0)
			m.erase(removeIt);
		}
	};

	map<char, short> STRING_TO_SEARCH_OCCURENCE_MAP;
	for (auto c : s1)
		mapItemUpdater(true, c, STRING_TO_SEARCH_OCCURENCE_MAP);

	map<char, short> currentSubStrEntriesMap;
	size_t startIndex = 0;
	size_t endIndex = startIndex + s1.size() - 1;
	for (size_t i = startIndex; i<=endIndex; ++i)
		mapItemUpdater(true, s2[i], currentSubStrEntriesMap);

	while (endIndex < s2.size())
	{
		if (std::equal(currentSubStrEntriesMap.begin(), currentSubStrEntriesMap.end(), STRING_TO_SEARCH_OCCURENCE_MAP.begin()))
			return true;

		mapItemUpdater(false, s2[startIndex++], currentSubStrEntriesMap);
		if (++endIndex < s2.size())
			mapItemUpdater(true, s2[endIndex], currentSubStrEntriesMap);
	}

	return false;
    }
};