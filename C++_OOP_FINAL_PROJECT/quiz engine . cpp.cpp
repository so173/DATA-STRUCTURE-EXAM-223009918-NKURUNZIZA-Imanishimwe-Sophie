#include <iostream>
#include <cstring>

using namespace std;

// ------------------ Struct Definition ------------------
struct Question {
    char prompt[100];
    char choices[4][40];
    int correctIdx;
};

// ------------------ Base Class ------------------
class QuizUser {
public:
    virtual int takeQuiz(Question* questions, int numQuestions) = 0;
    virtual ~QuizUser() {}
};

// ------------------ Derived Class: Premium ------------------
class PremiumQuizUser : public QuizUser {
public:
    int takeQuiz(Question* questions, int numQuestions) override {
        int score = 0;
        for (int i = 0; i < numQuestions; ++i) {
            cout << "Q" << i + 1 << ": " << questions[i].prompt << "\n";
            for (int j = 0; j < 4; ++j)
                cout << j + 1 << ") " << questions[i].choices[j] << "\n";

            int ans;
            cout << "Your answer: ";
            cin >> ans;

            if (ans - 1 == questions[i].correctIdx)
                score++;
        }
        cout << "Premium user score: " << score << "/" << numQuestions << "\n";
        return score;
    }
};

// ------------------ Derived Class: Guest ------------------
class GuestQuizUser : public QuizUser {
public:
    int takeQuiz(Question* questions, int numQuestions) override {
        int score = 0;
        for (int i = 0; i < numQuestions && i < 3; ++i) {  // Guests can only attempt 3
            cout << "Q" << i + 1 << ": " << questions[i].prompt << "\n";
            for (int j = 0; j < 4; ++j)
                cout << j + 1 << ") " << questions[i].choices[j] << "\n";

            int ans;
            cout << "Your answer: ";
            cin >> ans;

            if (ans - 1 == questions[i].correctIdx)
                score++;
        }
        cout << "Guest user score: " << score << "/3 (limit)\n";
        return score;
    }
};

// ------------------ Helper Functions ------------------

void addQuestion(Question*& questions, int& size, const Question& q) {
    Question* newArr = new Question[size + 1];
    for (int i = 0; i < size; ++i)
        newArr[i] = questions[i];
    newArr[size] = q;
    delete[] questions;
    questions = newArr;
    size++;
}

void removeQuestion(Question*& questions, int& size, int index) {
    if (index < 0 || index >= size) return;
    Question* newArr = new Question[size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != index)
            newArr[j++] = questions[i];
    }
    delete[] questions;
    questions = newArr;
    size--;
}

// ------------------ Main Function ------------------
int main() {
    int numQuestions = 0;
    Question* questions = nullptr;

    // Example: Add questions
    Question q1 = {
        "What is the capital of France?",
        {"Berlin", "London", "Paris", "Rome"},
        2
    };
    Question q2 = {
        "Which number is even?",
        {"1", "3", "5", "4"},
        3
    };

    addQuestion(questions, numQuestions, q1);
    addQuestion(questions, numQuestions, q2);

    // Add participants
    int numParticipants = 2;
    QuizUser** participants = new QuizUser*[numParticipants];
    participants[0] = new PremiumQuizUser();
    participants[1] = new GuestQuizUser();

    // Each participant takes quiz
    for (int i = 0; i < numParticipants; ++i) {
        cout << "\nParticipant " << i + 1 << " taking quiz:\n";
        participants[i]->takeQuiz(questions, numQuestions);
    }

    // Cleanup
    delete[] questions;
    for (int i = 0; i < numParticipants; ++i)
        delete participants[i];
    delete[] participants;

    return 0;
}
