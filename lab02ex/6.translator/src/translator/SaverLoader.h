#pragma once

boost::optional<std::map<std::string, std::string>> GetVocabularyMap(char const *pVocabularyFileName);
bool SaveVocabulary(std::map<std::string, std::string> const &vocabulary, char *pVocabularyFileName);