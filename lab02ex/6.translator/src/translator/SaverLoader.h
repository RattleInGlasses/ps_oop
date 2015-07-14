#pragma once

std::map<std::string, std::string> GetVocabularyMap(char const *pVocabualryFileName);
void SaveVocabulary(std::map<std::string, std::string> const &vocabulary);