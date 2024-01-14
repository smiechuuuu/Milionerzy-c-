
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;
using namespace chrono;

struct Question {
    string question;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctAnswer;
};

struct Player {
    string name;
    int score;
};

struct PlayerRanking {
    map<string, int> scores;

    void updateScore(const string& playerName, int points) {
        scores[playerName] += points;
    }

    void displayRanking() {
        cout << "Ranking graczy:" << endl;
        for (const auto& entry : scores) {
            cout << entry.first << ": " << entry.second << " punktów" << endl;
        }
    }
};

vector<Question> initializeQuestions() {
    vector<Question> questions;

    questions.push_back({"Jaka jest stolica Polski?", "Warszawa", "Kraków", "Wrocław", "Poznań", 'A'});
    questions.push_back({"Ile wynosi 2 + 2?", "3", "4", "5", "6", 'B'});
    questions.push_back({"Kto napisał \"Pan Tadeusz\"?", "Adam Mickiewicz", "Juliusz Słowacki", "Henryk Sienkiewicz", "Cyprian Kamil Norwid", 'A'});
    questions.push_back({"Która planeta jest najbliżej Słońca?", "Merkury", "Wenus", "Ziemia", "Mars", 'A'});
    questions.push_back({"Jakie jest najwyższe góry świata?", "Himalaje", "Andy", "Alpy", "Karakorum", 'A'});
    questions.push_back({"Które zwierzę jest najszybsze na świecie?", "Gepard", "Sęp", "Kangur", "Szympans", 'A'});
    questions.push_back({"Ile jest kontynentów na Ziemi?", "5", "6", "7", "8", 'C'});
    questions.push_back({"Który pierwiastek chemiczny ma symbol 'O'?", "Tlen", "Azot", "Węgiel", "Żelazo", 'A'});
    questions.push_back({"Kto jest autorem trylogii \"Władca Pierścieni\"?", "J.R.R. Tolkien", "George R.R. Martin", "J.K. Rowling", "C.S. Lewis", 'A'});
    questions.push_back({"W którym roku miała miejsce bitwa pod Grunwaldem?", "1410", "1492", "1525", "1683", 'A'});
    questions.push_back({"Które państwo nie graniczy z Polską?", "Austria", "Ukraina", "Szwecja", "Węgry", 'A'});
    questions.push_back({"Które morze jest największe?", "Morze Czarne", "Morze Śródziemne", "Morze Północne", "Morze Kaspijskie", 'D'});
    questions.push_back({"Który z podanych pierwiastków jest gazem szlachetnym?", "Hel", "Argon", "Krypton", "Neon", 'A'});
    questions.push_back({"Który kierunek wskazuje igła kompasu?", "Północ", "Południe", "Wschód", "Zachód", 'A'});
    questions.push_back({"Który z dziesięciu największych krajów świata pod względem powierzchni leży w Afryce?", "Algieria", "Rosja", "Kanada", "Indie", 'B'});
    questions.push_back({"Kto jest autorem obrazu Mona Lisa?", "Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso", "Claude Monet", 'B'});
    questions.push_back({"Ile wynosi pierwiastek kwadratowy z 144?", "10", "12", "14", "16", 'B'});
    questions.push_back({"W którym roku rozpoczęła się II wojna światowa?", "1935", "1939", "1941", "1945", 'B'});
    questions.push_back({"Które z miast jest stolicą Australii?", "Canberra", "Sydney", "Melbourne", "Brisbane", 'A'});
    questions.push_back({"Które z morz jest najmniejsze?", "Morze Czerwone", "Morze Adriatyckie", "Morze Bałtyckie", "Morze Egejskie", 'C'});
    questions.push_back({"W którym roku rozpoczęła się II wojna światowa?", "1935", "1939", "1941", "1945", 'B'});
    questions.push_back({"Które państwo posiada największy budżet wojskowy na świecie?", "USA", "Rosja", "Chiny", "Indie", 'A'});
    questions.push_back({"Ile gwiazdek znajduje się na amerykańskiej fladze?", "48", "50", "52", "55", 'B'});
    questions.push_back({"W którym roku NATO zostało założone?", "1945", "1949", "1955", "1961", 'B'});
    questions.push_back({"Który z podanych pojazdów jest czołgiem?", "F-16", "Leopard 2", "Apache", "B-52", 'B'});

    random_shuffle(questions.begin(), questions.end());

    return questions;
}

bool askQuestion(const Question& q) {
    cout << q.question << endl;
    cout << "A. " << q.optionA << endl;
    cout << "B. " << q.optionB << endl;
    cout << "C. " << q.optionC << endl;
    cout << "D. " << q.optionD << endl;

    cout << "Podaj literę poprawnej odpowiedzi: ";
    char userAnswer;
    cin >> userAnswer;

    return (toupper(userAnswer) == q.correctAnswer);
}

bool playGameWithTimer(Player& player, const vector<Question>& questions) {
    for (const auto& q : questions) {
        cout << "\nNowe pytanie:" << endl;

        cout << q.question << endl;
        cout << "A. " << q.optionA << endl;
        cout << "B. " << q.optionB << endl;
        cout << "C. " << q.optionC << endl;
        cout << "D. " << q.optionD << endl;

        auto start = steady_clock::now();

        cout << "Podaj literę poprawnej odpowiedzi: ";
        char userAnswer;
        cin >> userAnswer;

        auto end = steady_clock::now();
        auto elapsedSeconds = duration_cast<seconds>(end - start).count();

        if (toupper(userAnswer) == q.correctAnswer && elapsedSeconds <= 60) {
            cout << "Poprawna odpowiedź! Zdobywasz punkt." << endl;
            player.score++;
        } else if (elapsedSeconds > 60) {
            cout << "Niestety, czas na udzielenie odpowiedzi minął. Koniec gry." << endl;
            return false;
        } else {
            cout << "Niestety, błędna odpowiedź. Koniec gry." << endl;
            return false;
        }
    }

    cout << "Gratulacje! Odpowiedziałeś poprawnie na wszystkie pytania." << endl;
    return true;
}

void giveRewardIfWinner(const Player& player) {
    if (player.score >= 10) {
        cout << "Gratulacje, " << player.name << "! Wygrałeś/aś nagrodę zwycięzcy!" << endl;
        cout << "Dostajesz ekskluzywny tytuł: Mistrz/Mistrzyni Milionerów!" << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Player player;
    cout << "Podaj swoje imię: ";
    cin >> player.name;

    vector<Question> questions = initializeQuestions();

    if (playGameWithTimer(player, questions)) {
        PlayerRanking ranking;
        ranking.updateScore(player.name, player.score);

        ranking.displayRanking();
        giveRewardIfWinner(player);
    }

    return 0;
}


       