#include <iostream>

bool compareAirLineStrings(const std::string &str1, const std::string &str2) {
    char lettersCount {0};
    auto it1 = str1.cbegin(), it2 = str2.cbegin();
    // Считаем количество букв в первых трёх символах, чтобы определить длину кода авиакомпании
    for(int i = 0; i < 3 && it1 != str1.cend(); i++) {
        if(std::isalpha(*(it1+i))) {
            lettersCount++;
        }
    }

    {
        // Если в коде авиакомпании только 1 буква,  то код состоит только из двух символов
        // Иначе длина кода равна количеству букв
        const unsigned char codeLength = (lettersCount == 1) ? 2 : lettersCount;

        //! Данная проверка не нужна, так как невозможен выход за пределы строки,
        //! если входные строки полностью соответствуют описанному в задаче формату.
        //! Если код авиакомпании отсутствует, то codeLength равно 0 и сдвига не происходит.
        //! Если же код есть, то строка состоит минимум из трёх символов (Код - 2 символа, Номер - 1 символ).
        /* if(str1.size() < codeLength || str2.size() < codeLength) {
            return false;
        }*/

        it1 += codeLength;
        it2 += codeLength;
    }
    // Закрываем область видимости, чтобы освободить память, выделенную для codeLength

    // Сравниваем код авиакомпании
    if(!std::equal(str1.cbegin(), it1, str2.cbegin())) {
        return false;
    }

    // Пропускаем пробел и незначащие нули
    if(std::isspace(*it1)) it1++;
    if(std::isspace(*it2)) it2++;
    while(it1 < str1.cend() && *it1 == '0') it1++;
    while(it2 < str2.cend() && *it2 == '0') it2++;

    //Сравниваем номер рейса
    for(; it1 < str1.cend() && it2 < str2.cend(); it1++, it2++) {
        if(*it1 != *it2) {
            return false;
        }
    }
    if(it1 != str1.cend() || it2 != str2.cend()) {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    std::cout << compareAirLineStrings("AFL1", "AFL001") << std::endl;
    std::cout << compareAirLineStrings("D2 25", "D225") << std::endl;
    std::cout << compareAirLineStrings("D225", "D2025") << std::endl;
    std::cout << compareAirLineStrings("D2 25", "D2025") << std::endl;
    std::cout << compareAirLineStrings("0F 213", "00F 213") << std::endl;
    std::cout << compareAirLineStrings("0F 213", "1F 213") << std::endl;
    std::cout << compareAirLineStrings("1", "000001") << std::endl;
    std::cout << compareAirLineStrings("A12222", "A1 02222") << std::endl;
    std::cout << compareAirLineStrings("D00001", "D01") << std::endl;
    std::cout << compareAirLineStrings("125", "1000025") << std::endl;
    std::cout << compareAirLineStrings("D25", "D000025") << std::endl;
    std::cout << compareAirLineStrings("D325", "D3000025") << std::endl;
    std::cout << compareAirLineStrings("D3125", "D31000025") << std::endl;
    std::cout << compareAirLineStrings("SU 0123", "SU000123") << std::endl;
    std::cout << compareAirLineStrings("D", "D11") << std::endl;
    std::cout << compareAirLineStrings("D12", "D") << std::endl;
    std::cout << compareAirLineStrings("DSF23", "D") << std::endl;
    std::cout << compareAirLineStrings("DSF23", "") << std::endl;

    return 0;
}
