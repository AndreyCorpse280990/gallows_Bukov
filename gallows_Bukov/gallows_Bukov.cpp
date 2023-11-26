#include <iostream>
#include <string>
#include <set>
#include <vector>

class HangmanVisual 
{
public:
    HangmanVisual() : incorrectGuesses(0) {}

    void displayHangman() const {
        switch (incorrectGuesses) {
        case 0:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        " << std::endl;
            std::cout << "   |        " << std::endl;
            std::cout << "   |        " << std::endl;
            break;
        case 1:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |        " << std::endl;
            std::cout << "   |        " << std::endl;
            break;
        case 2:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        " << std::endl;
            break;
        case 3:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |       /|" << std::endl;
            std::cout << "   |        " << std::endl;
            break;
        case 4:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |       /|\\" << std::endl;
            std::cout << "   |        " << std::endl;
            break;
        case 5:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |       /|\\" << std::endl;
            std::cout << "   |       / " << std::endl;
            break;
        case 6:
            std::cout << "   _________" << std::endl;
            std::cout << "   |        |" << std::endl;
            std::cout << "   |        O" << std::endl;
            std::cout << "   |       /|\\" << std::endl;
            std::cout << "   |       / \\" << std::endl;
            break;
        }
    }

    void incrementIncorrectGuesses() 
    {
        incorrectGuesses++;
    }

    int getIncorrectGuesses() const 
    {
        return incorrectGuesses;
    }
private:
    int incorrectGuesses;
};

class HangmanBase 
{
public:
    HangmanBase(const std::string& word) : secretWord(word) 
    {
        guessedWord = std::string(secretWord.length(), '_');
    }

    virtual ~HangmanBase() {}

    void displayGameStatus() const 
    {
        hangmanVisual.displayHangman();
        std::cout << "Слово: " << guessedWord << std::endl;
        std::cout << "Ошибки (" << hangmanVisual.getIncorrectGuesses() << "): ";
        for (const auto& letter : incorrectLetters) 
        {
            std::cout << letter << " ";
        }
        std::cout << std::endl;
    }

    bool isGameOver() const 
    {
        return hangmanVisual.getIncorrectGuesses() >= maxIncorrectGuesses || guessedWord == secretWord;
    }

    bool playerWins() const 
    {
        return guessedWord == secretWord;
    }

    virtual void guessLetter(char letter) = 0;

protected:
    std::string secretWord;
    std::string guessedWord;
    std::set<char> guessedLetters;
    std::vector<char> incorrectLetters;
    HangmanVisual hangmanVisual;
    const int maxIncorrectGuesses = 6;

    virtual void updateGuessedWord(char letter) 
    {
        for (size_t i = 0; i < secretWord.length(); ++i)
        {
            if (secretWord[i] == letter) {
                guessedWord[i] = letter;
            }
        }
    }
};

class HangmanGame : public HangmanBase 
{
public:
    using HangmanBase::HangmanBase;

    void guessLetter(char letter) override 
    {
        if (guessedLetters.find(letter) != guessedLetters.end()) 
        {
            std::cout << "Вы уже угадывали эту букву. Попробуйте другую." << std::endl;
            return;
        }

        guessedLetters.insert(letter);

        if (secretWord.find(letter) != std::string::npos) 
        {
            updateGuessedWord(letter);
        }
        else 
        {
            incorrectLetters.push_back(letter);
            hangmanVisual.incrementIncorrectGuesses();
        }
    }
};

int main() 
{
	setlocale(LC_ALL, "rus");
    std::string word;
    std::cout << "Игрок 1, введите слово: ";
    std::cin >> word;

    HangmanGame game(word);

    while (!game.isGameOver()) {
        system("cls"); // Очистка консоли (для Windows)
        game.displayGameStatus();

        char guess;
        std::cout << "Игрок 2, введите букву: ";
        std::cin >> guess;

        game.guessLetter(guess);
    }

    if (game.playerWins()) {
        std::cout << "Поздравляю! Игрок 2 выиграл. Загаданное слово: " << word << std::endl;
    }
    else {
        std::cout << "Игрок 2 проиграл. Загаданное слово: " << word << std::endl;
    }

    return 0;
}
