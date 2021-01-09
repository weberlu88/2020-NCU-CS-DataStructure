// https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
/*
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
*/
// Split string
/*
int main() {
    using namespace std;
    string sentence = "And I feel fine...";
    istringstream iss(sentence);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        ostream_iterator<string>(cout, "\n"));
}
*/

// Via cin
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
    using namespace std;
    string sentence;
    getline(cin, sentence);
    istringstream iss(sentence);
    vector<string> tokens { 
        istream_iterator<string>{iss},
        istream_iterator<string>{} 
    };

}

/*
std::vector numbers(std::istream_iterator<int>(std::cin),
                                std::istream_iterator<int>());
*/