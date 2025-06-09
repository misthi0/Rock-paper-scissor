#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class RockPaperScissorsGame {
private:
    vector<string> options = {"Rock", "Paper", "Scissors", "Lizard", "Spock"};
    vector<string> playerHistory;
    vector<string> computerHistory;
    int playerWins = 0;
    int computerWins = 0;
    int draws = 0;
    int round = 1;
  
    int predictPlayerChoice() {
        if (playerHistory.size() < 3) {
            return rand() % 5; 
        }
        
   
        vector<int> frequency(5, 0);
        for (int i = max(0, (int)playerHistory.size() - 3); i < playerHistory.size(); i++) {
            for (int j = 0; j < 5; j++) {
                if (playerHistory[i] == options[j]) {
                    frequency[j]++;
                    break;
                }
            }
        }
        
        int maxFreq = *max_element(frequency.begin(), frequency.end());
        for (int i = 0; i < 5; i++) {
            if (frequency[i] == maxFreq) {
                return getWinningChoice(i);
            }
        }
        
        return rand() % 5;
    }
    
    int getWinningChoice(int playerChoice) {
       
        switch(playerChoice) {
            case 0: return (rand() % 2 == 0) ? 1 : 4; 
            case 1: return (rand() % 2 == 0) ? 2 : 3; 
            case 2: return (rand() % 2 == 0) ? 0 : 4; 
            case 3: return (rand() % 2 == 0) ? 0 : 2; 
            case 4: return (rand() % 2 == 0) ? 1 : 3; 
            default: return rand() % 5;
        }
    }
    
    int determineWinner(int player, int computer) {
        if (player == computer) return 0; // Draw
        
        // Winning combinations for player
        if ((player == 0 && (computer == 2 || computer == 3)) ||  // Rock beats Scissors, Lizard
            (player == 1 && (computer == 0 || computer == 4)) ||  // Paper beats Rock, Spock
            (player == 2 && (computer == 1 || computer == 3)) ||  // Scissors beats Paper, Lizard
            (player == 3 && (computer == 1 || computer == 4)) ||  // Lizard beats Paper, Spock
            (player == 4 && (computer == 0 || computer == 2))) {  // Spock beats Rock, Scissors
            return 1; // Player wins
        }
        
        return -1; // Computer wins
    }
    
    void displayStats() {
        cout << "\n===== GAME STATISTICS =====" << endl;
        cout << "Round: " << round << endl;
        cout << "Player Wins: " << playerWins << endl;
        cout << "Computer Wins: " << computerWins << endl;
        cout << "Draws: " << draws << endl;
        
        int total = playerWins + computerWins + draws;
        if (total > 0) {
            cout << "Win Rate: " << (playerWins * 100.0 / total) << "%" << endl;
        }
        
        cout << "Player's Last 5 Moves: ";
        int start = max(0, (int)playerHistory.size() - 5);
        for (int i = start; i < playerHistory.size(); i++) {
            cout << playerHistory[i] << " ";
        }
        cout << endl;
    }
    
    void displayRules() {
        cout << "\n===== EXTENDED RULES =====" << endl;
        cout << "Rock crushes Lizard and Scissors" << endl;
        cout << "Paper covers Rock and disproves Spock" << endl;
        cout << "Scissors cuts Paper and decapitates Lizard" << endl;
        cout << "Lizard poisons Spock and eats Paper" << endl;
        cout << "Spock smashes Scissors and vaporizes Rock" << endl;
        cout << "===============================\n" << endl;
    }

public:
    void playGame() {
        srand(time(0));
        
        cout << "?? ULTIMATE ROCK PAPER SCISSORS LIZARD SPOCK! ??" << endl;
        cout << "=================================================" << endl;
        
        displayRules();
        
        while (true) {
            cout << "\n--- ROUND " << round << " ---" << endl;
            cout << "0. Rock ??" << endl;
            cout << "1. Paper ??" << endl;
            cout << "2. Scissors ?" << endl;
            cout << "3. Lizard ??" << endl;
            cout << "4. Spock ??" << endl;
            cout << "5. View Statistics" << endl;
            cout << "6. Quit Game" << endl;
            
            cout << "\nEnter your choice (0-6): ";
            int userChoice;
            cin >> userChoice;
            
            if (userChoice == 5) {
                displayStats();
                continue;
            }
            
            if (userChoice == 6) {
                cout << "\nThanks for playing! Final Stats:" << endl;
                displayStats();
                break;
            }
            
            if (userChoice < 0 || userChoice > 4) {
                cout << "? Invalid input! Please choose between 0-6." << endl;
                continue;
            }
 
            int computerChoice = predictPlayerChoice();
            
            cout << "\nYou chose: " << options[userChoice] << endl;
            cout << "Computer chose: " << options[computerChoice] << endl;
            
  
            playerHistory.push_back(options[userChoice]);
            computerHistory.push_back(options[computerChoice]);
            
            int result = determineWinner(userChoice, computerChoice);
            
            if (result == 0) {
                cout << "?? It's a draw!" << endl;
                draws++;
            } else if (result == 1) {
                cout << "?? You win this round!" << endl;
                playerWins++;
            } else {
                cout << "?? Computer wins this round!" << endl;
                computerWins++;
            }
            
            round++;
            
            // Show quick stats after each round
            cout << "Score - You: " << playerWins << " | Computer: " << computerWins << " | Draws: " << draws << endl;
            
            // Tournament mode check
            if (round > 1 && (round - 1) % 10 == 0) {
                cout << "\n?? TOURNAMENT MILESTONE REACHED! ??" << endl;
                if (playerWins > computerWins) {
                    cout << "You're leading the tournament!" << endl;
                } else if (computerWins > playerWins) {
                    cout << "Computer is leading the tournament!" << endl;
                } else {
                    cout << "Tournament is tied!" << endl;
                }
            }
        }
    }
};

int main() {
    RockPaperScissorsGame game;
    game.playGame();
    return 0;
}
