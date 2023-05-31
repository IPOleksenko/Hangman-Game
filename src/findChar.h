#pragma once

bool FindCharInSecretWord(wchar_t letter, const wstring& secret_word)
{
    for (size_t i = 0; i < secret_word.length(); ++i) {
        if (secret_word[i] == letter) {
            return true;
        }
    }
    return false;
}