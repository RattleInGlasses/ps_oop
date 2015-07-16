#pragma once

bool GetVocabularyMap(char const *pVocabualryFileName, std::map<std::string, std::string> &vocabulary);
bool SaveVocabulary(std::map<std::string, std::string> const &vocabulary, char *pVocabularyFileName);