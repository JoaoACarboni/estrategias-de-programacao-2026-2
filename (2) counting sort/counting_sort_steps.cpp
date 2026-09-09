#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// ---------------------------------------------------------
// Primeiro Passo
// Descobre o menor e o maior valor do array.
// ---------------------------------------------------------
struct Range { int minVal; int maxVal; int size; };

Range findRange(const vector<int>& arr) {
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    return { minVal, maxVal, maxVal - minVal + 1 };
}

// ---------------------------------------------------------
// Segundo Passo
// Conta quantas vezes cada valor aparece no array.
// ---------------------------------------------------------
vector<int> countOccurrences(const vector<int>& arr, int minVal, int rangeSize) {
    vector<int> count(rangeSize, 0);
    for (int num : arr) {
        count[num - minVal]++;
    }
    return count;
}

// ---------------------------------------------------------
// Terceiro Passo
// Transforma o array de contagem em contagem acumulada.
// ---------------------------------------------------------
vector<int> calculateCumulativeCount(vector<int> count) {
    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }
    return count;
}

// ---------------------------------------------------------
// Quarto Passo
// Usa a contagem acumulada para posicionar cada elemento.
// Percorre o array original de trás para frente para manter
// a estabilidade (preservar a ordem relativa de iguais).
// ---------------------------------------------------------
vector<int> buildSortedOutput(const vector<int>& arr, vector<int> count, int minVal) {
    vector<int> output(arr.size());
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; i--) {
        int num = arr[i];
        output[count[num - minVal] - 1] = num;
        count[num - minVal]--;
    }
    return output;
}

// ---------------------------------------------------------
// Counting Sort completo, juntando os 4 passos acima.
// ---------------------------------------------------------
vector<int> countingSort(const vector<int>& arr) {
    if (arr.empty()) return arr;

    Range r = findRange(arr);
    vector<int> count = countOccurrences(arr, r.minVal, r.size);
    vector<int> cumulative = calculateCumulativeCount(count);
    return buildSortedOutput(arr, cumulative, r.minVal);
}

// ---------------------------------------------------------
// Counting Sort para strings de mesmo comprimento,
// ordenando caractere a caractere a partir do último,
// usando o valor ASCII de cada caractere.
// ---------------------------------------------------------
vector<string> countingSortStrings(vector<string> arr) {
    size_t maxLen = 0;
    for (const string& s : arr) maxLen = max(maxLen, s.size());

    // preenche strings mais curtas com espaços à direita
    for (string& s : arr) s.resize(maxLen, ' ');

    for (int i = static_cast<int>(maxLen) - 1; i >= 0; i--) {
        vector<int> count(256, 0);
        for (const string& s : arr) count[(unsigned char)s[i]]++;

        for (int j = 1; j < 256; j++) count[j] += count[j - 1];

        vector<string> output(arr.size());
        for (int idx = static_cast<int>(arr.size()) - 1; idx >= 0; idx--) {
            unsigned char c = arr[idx][i];
            output[count[c] - 1] = arr[idx];
            count[c]--;
        }
        arr = output;
    }

    // remove o preenchimento
    for (string& s : arr) {
        size_t end = s.find_last_not_of(' ');
        s = (end == string::npos) ? "" : s.substr(0, end + 1);
    }
    return arr;
}

void printArr(const vector<int>& arr) {
    cout << "[ ";
    for (int v : arr) cout << v << " ";
    cout << "]\n";
}

int main() {
    // Exemplo básico
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    cout << "Original:  "; printArr(arr);
    cout << "Ordenado:  "; printArr(countingSort(arr));

    // Exemplo com strings (Step extra: Counting Sort for Strings)
    vector<string> words = {"pera", "uva", "kiwi", "abacaxi", "mel"};
    vector<string> sortedWords = countingSortStrings(words);

    cout << "\nPalavras originais: ";
    for (const string& w : words) cout << w << " ";
    cout << "\nPalavras ordenadas:  ";
    for (const string& w : sortedWords) cout << w << " ";
    cout << "\n";

    return 0;
}
