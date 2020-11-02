#include <vector>
#include <string>
#include <stack>


struct Union {

    std::vector<std::vector<bool> > substrings;
    std::vector<std::vector<bool> > prefixes;
    size_t length;
    int maxCommonPrefix;
    bool voidWord;

    Union(std::string &s, char symbol) {

        length = s.size();
        substrings.assign(length, std::vector<bool>(length, false));
        prefixes.assign(length, std::vector<bool>(length, false));

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == symbol) {
                substrings[i][i] = true;
                prefixes[i][i] = true;
            }
        }

        voidWord = (symbol == '1');
        maxCommonPrefix = s[0] == symbol ? 1 : 0;
    }

    explicit Union(size_t myLength) : length(myLength),
                                      substrings(myLength, std::vector<bool>(myLength, false)),
                                      prefixes(myLength, std::vector<bool>(myLength, false)),
                                      voidWord(false),
                                      maxCommonPrefix(0) {};

    Union &operator=(const Union &other) {
        voidWord = other.voidWord;
        length = other.length;
        maxCommonPrefix = other.maxCommonPrefix;
        substrings.assign(length, std::vector<bool>(length, false));
        prefixes.assign(length, std::vector<bool>(length, false));

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                substrings[i][j] = other.substrings[i][j];
                prefixes[i][j] = other.prefixes[i][j];
            }
        }
        return *this;
    }

    Union operator+(const Union &other) const {

        Union mySum(length);

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                mySum.substrings[i][j] = substrings[i][j] | other.substrings[i][j];
                mySum.prefixes[i][j] = prefixes[i][j] | other.prefixes[i][j];
            }
        }

        mySum.voidWord = voidWord | other.voidWord;
        mySum.maxCommonPrefix = std::max(maxCommonPrefix, other.maxCommonPrefix);

        return mySum;
    }

    Union operator*(const Union &other) const {

        Union mult(length);

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length - 1; ++j) {
                for (int k = 0; k < length; ++k) {
                    if (substrings[i][j] && other.substrings[j + 1][k]) mult.substrings[i][k] = true;
                    if (substrings[i][j] && other.prefixes[j + 1][k]) mult.prefixes[i][k] = true;
                }
            }
        }

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {

                mult.prefixes[i][j] = (mult.prefixes[i][j] || prefixes[i][j]);
                mult.prefixes[i][j] = (mult.prefixes[i][j] || (voidWord && other.prefixes[i][j]));

                if ((substrings[i][j] && other.voidWord) || (other.substrings[i][j] && voidWord))
                    mult.substrings[i][j] = true;
            }
        }

        mult.voidWord = voidWord && other.voidWord;

        mult.maxCommonPrefix = maxCommonPrefix;

        for (int i = 0; i < length; ++i) {
            if (mult.substrings[0][i]) mult.maxCommonPrefix = std::max(mult.maxCommonPrefix, i + 1);
            if (mult.prefixes[0][i]) mult.maxCommonPrefix = std::max(mult.maxCommonPrefix, i + 1);
        }

        return mult;
    }

    Union star() const {

        Union result = *this;

        for (int k = 0; k < length; ++k) {
            for (int i = 0; i < length; ++i) {
                for (int j = 0; j < length; ++j) {

                    if (k != 0) {
                        if (result.substrings[i][k - 1] && result.substrings[k][j]) result.substrings[i][j] = true;
                    }

                    if (k + 1 != length) {
                        if (result.substrings[i][k] && result.substrings[k + 1][j]) result.substrings[i][j] = true;
                    }

                }
            }
        }

        for (int i = 0; i < length; ++i) {
            for (int j = i; j < length - 1; ++j) {
                for (int k = j + 1; k < length; ++k) {
                    if (result.substrings[i][j] && result.prefixes[j + 1][k]) result.prefixes[i][k] = true;
                }
            }
        }

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                if (result.substrings[i][j]) result.prefixes[i][j] = true;
            }
        }

        result.voidWord = true;

        for (int i = 0; i < length; ++i) {
            if (result.substrings[0][i]) result.maxCommonPrefix = std::max(result.maxCommonPrefix, i + 1);
            if (result.prefixes[0][i]) result.maxCommonPrefix = std::max(result.maxCommonPrefix, i + 1);
        }

        return result;
    }
};

int solveTask(std::string &regularExpression, std::string &targetString) {

    std::stack<Union> subExpressions;
    size_t expressionLength = regularExpression.size();

    for (int i = 0; i < expressionLength; ++i) {

        char myChar = regularExpression[i];

        if (myChar == 'a' || myChar == 'b' || myChar == 'c' || myChar == '1') {

            subExpressions.push(Union(targetString, myChar));

            continue;

        }

        if ((myChar == '*' && subExpressions.empty()) || (myChar != '*' && subExpressions.size() < 2)) {

            return -1;

        }

        if (myChar == '*') {

            Union myUnion = subExpressions.top();

            subExpressions.pop();
            subExpressions.push(myUnion.star());

            continue;

        }

        Union secondValue = subExpressions.top();
        subExpressions.pop();

        Union firstValue = subExpressions.top();
        subExpressions.pop();

        if (myChar == '+') {
            subExpressions.push(firstValue + secondValue);
        }

        if (myChar == '.') {
            subExpressions.push(firstValue * secondValue);
        }
    }

    if (subExpressions.size() != 1) return -1;

    Union result = subExpressions.top();

    return result.maxCommonPrefix;

}
