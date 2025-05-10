#include <iostream>
#include <fstream>
#include <thread>
#include <unordered_set>

bool normalizeAirlineStr(const std::string &str, std::string &resultStr) {
    //! Проверка на корректность размера строки.
    //! Если на вход всегда поступает корректная строка, то проверка не нужна
    if(str.empty() || str.size() > 7) {
        return false;
    }

    resultStr.clear();
    char lettersCount {0};
    auto iter = str.cbegin();
    // Считаем количество букв в первых трёх символах, чтобы определить длину кода авиакомпании
    for(int i = 0; i < 3 && iter != str.cend(); i++) {
        if(std::isalpha(*(iter+i))) {
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
        if(str.size() < codeLength) {
            return false;
        }

        iter += codeLength;
        resultStr += str.substr(0, codeLength);
    }
    // Закрываем область видимости, чтобы освободить память, выделенную для codeLength

    // Пропускаем пробел, если он есть
    if(std::isspace(*iter)) iter++;

    {
        //! Проверка на корректность размера номера рейса.
        //! Если на вход всегда поступает корректная строка, то проверка не нужна
        const auto numLength = str.cend() - iter;
        if(numLength < 1 || 5 < numLength) {
            return false;
        }
    }
    // Закрываем область видимости, чтобы освободить память, выделенную для numLength

    // Пропускаем незначащие нули, если они есть
    while(iter < str.cend() && *iter == '0') iter++;

    for(; iter < str.cend(); iter++) {
        //! Проверка на то, что номер рейса состоит только из цифр.
        //! Если на вход всегда поступает корректная строка, то проверка не нужна
        if(!std::isdigit(*iter)) {
            return false;
        }
        resultStr += *iter;
    }
    return true;
};

void processFile(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);
    std::ofstream output(outputPath);

    std::unordered_set<std::string> uniqueFlights;
    std::string line;
    while (std::getline(input, line)) {
        std::string normalizedStr;
        // Если строка не проходит согласно правилам грамматики, то эту строку не записываем в выходной файл
        if(!normalizeAirlineStr(line, normalizedStr)) {
            continue;
        }
        if(uniqueFlights.count(normalizedStr)) {
            continue;
        }
        uniqueFlights.insert(normalizedStr);
        output << line << "\n";
    }
}

int main(int argc, char *argv[])
{
   std::thread t1(processFile, "1_in.txt", "1_out.txt");
   std::thread t2(processFile, "2_in.txt", "2_out.txt");

   t1.join();
   t2.join();
   return 0;
}
