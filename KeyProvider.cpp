#include "KeyProvider.h"
#include <cctype>
#include <cassert>
#include <string>
std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
	std::string result;
	for (char c : aString) {
		if (std::isalpha(c)) {
			result += std::toupper(c);
		}
	}
	return result;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept
	:fKeys(""), fIndex(0) {
	std::string processedkeyword = preprocessString(aKeyword);
	std::string processedsource = preprocessString(aSource);
	size_t sourcelength = processedsource.length();
	size_t keywordlength = processedkeyword.length();
	
	for (size_t i = 0; i < sourcelength; ++i) {
		char keywordchar = processedkeyword[i % keywordlength];
		fKeys += keywordchar;
	}
	assert(fKeys.length() == sourcelength);
}
char KeyProvider::operator*() const noexcept {
	return fKeys[fIndex];

}
KeyProvider& KeyProvider:: operator++() noexcept {
	++fIndex;
	return *this;
}
KeyProvider KeyProvider:: operator++(int) noexcept {
	KeyProvider temp = *this;
	++(*this);
	return temp;
}
bool KeyProvider:: operator==(const KeyProvider& aOther) const noexcept {
	return fKeys == aOther.fKeys && fIndex == aOther.fIndex;
}
bool KeyProvider:: operator!=(const KeyProvider& aOther) const noexcept {
	return !(*this == aOther);
}
KeyProvider KeyProvider::begin() const noexcept {
	KeyProvider copy = *this;
	copy.fIndex = 0;
	return copy;
}
KeyProvider KeyProvider::end() const noexcept {
	KeyProvider copy = *this;
	copy.fIndex = fKeys.size();
	return copy;
}