#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class HangMan{
private:
    string KnownWord, UnknownWord, tried_letters;
    int left_guesses, revealed_letters;
public:
    HangMan(){
        KnownWord = UnknownWord = tried_letters = "";
        left_guesses = revealed_letters = 0;
    }
    explicit HangMan(string s){
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        KnownWord = UnknownWord = s;
        left_guesses = 6;
        revealed_letters = 0;

        for (int i=0; i<KnownWord.length(); ++i)
            if (isalpha(KnownWord[i]))
                UnknownWord[i] = '_';
    }

    void printStats();
    void guess(char c);
    bool playerHasWon();
};



void HangMan::printStats(){
    cout<<"Guess: "<<UnknownWord<<endl;
    cout<<"Tried letters: "<<tried_letters<<endl;
    cout<<"You have "<<left_guesses<<" guesses left.\n\n";
}


bool HangMan::playerHasWon(){
    if (KnownWord == UnknownWord)
        return true;
    else
        return false;
}


void HangMan::guess(char c){
    if (playerHasWon())
        cout<<"You already won the game. Start a new one if you want to continue.\n\n";
    else if (left_guesses == 0)
        cout<<"You lost the game because you ran out of guesses. Start a new one if you want to continue.\n\n";
    else {
        c = char(toupper(c));
        if (tried_letters.find(c) != string::npos)
            cout<<"You already tried this letter. Choose another one!\n\n";
        else{
            tried_letters = tried_letters + c + ' ';
            if (KnownWord.find(c) != string::npos) {
                for (int i = 0; i < KnownWord.length(); ++i) {
                    if (KnownWord[i] == c) {
                        UnknownWord[i] = c;
                        ++revealed_letters;
                    }
                }
                if (UnknownWord == KnownWord)
                    cout<<"Congratulations! You've guessed the entire word ("<<KnownWord<< ") and you won the game!\n\n";
                else
                    cout<<"You hit the spot! Now you only have to guess "<<UnknownWord<<"\n\n";
            }
            else {
                --left_guesses;
                if (left_guesses != 0)
                    cout<<"Unlucky! That was not it, but you still have " << left_guesses << " guesses left.\n\n";
                else
                    cout<<"Unfortunately, you ran out of guesses and you lost the game. Better luck next time!\n\n";
            }
        }
    }
}



int  main(){
    HangMan game("Proiect La POO");
    game.printStats();

    game.guess('p');
    game.guess('r');
    game.guess('O');
    game.guess('Q');

    if (game.playerHasWon() == 1)
        cout<<"The player won the game.\n\n";
    else
        cout<<"The player didn't won the game.\n\n";

    game.guess('G');
    game.guess('G');
    game.guess('I');
    game.guess('I');
    game.guess('E');

    game.printStats();

    game.guess('u');
    game.guess('h');
    game.guess('a');
    game.guess('L');
    game.guess('c');
    game.guess('t');


    if (game.playerHasWon() == 1)
        cout<<"The player won the game.\n\n";
    else
        cout<<"The player didn't won the game.\n\n";

    game.guess('Z');

    game.printStats();

    return 0;
}
