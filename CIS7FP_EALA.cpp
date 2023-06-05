#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank rank = ACE, Suit suit = SPADES) : m_rank(rank), m_suit(suit) {}

    int getValue() const
    {
        if (m_rank >= JACK && m_rank <= KING)
        {
            return 10;
        }
        return m_rank;
    }

    void display() const
    {
        switch (m_rank)
        {
            case ACE: cout << 'A'; break;
            case JACK: cout << 'J'; break;
            case QUEEN: cout << 'Q'; break;
            case KING: cout << 'K'; break;
            default: cout << m_rank; break;
        }

        switch (m_suit)
        {
            case CLUBS: cout << 'C'; break;
            case DIAMONDS: cout << 'D'; break;
            case HEARTS: cout << 'H'; break;
            case SPADES: cout << 'S'; break;
        }
    }

private:
    Rank m_rank;
    Suit m_suit;
};

class Deck
{
public:
    Deck()
    {
        for (int suit = Card::CLUBS; suit <= Card::SPADES; ++suit)
        {
            for (int rank = Card::ACE; rank <= Card::KING; ++rank)
            {
                m_cards.push_back(Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)));
            }
        }
    }

    void shuffle()
    {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(m_cards.begin(), m_cards.end(), g);
    }

    const Card& dealCard()
    {
        const Card& card = m_cards.back();
        m_cards.pop_back();
        return card;
    }

private:
    vector<Card> m_cards;
};

class Hand
{
public:
    void addCard(const Card& card)
    {
        m_cards.push_back(card);
    }

    int getValue() const
    {
        int value = 0;
        bool hasAce = false;

        for (const auto& card : m_cards)
        {
            int cardValue = card.getValue();
            if (cardValue == Card::ACE)
            {
                hasAce = true;
            }
            value += cardValue;
        }

        if (hasAce && value + 10 <= 21)
        {
            value += 10;
        }

        return value;
    }

    void display() const
    {
        for (const auto& card : m_cards)
        {
            card.display();
            cout << ' ';
        }
    }

private:
    vector<Card> m_cards;
};

class BlackJack
{
public:
    void play()
    {
        Deck deck;
        deck.shuffle();
        
        Hand playerHand;
        Hand dealerHand;
        
        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());
        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());
        
        cout << "Dealer's Hand: ";
        dealerHand.display();
        cout << endl;
        
        cout << "Player's Hand: ";
        playerHand.display();
        cout << endl;
        
        int playerScore = playerHand.getValue();
        int dealerScore = dealerHand.getValue();
        
        cout << "\nDealer's Winning Probability: " << calculateWinningProbability(dealerScore) << "%" << endl;
        
        cout << "Player's Winning Probability: " << calculateWinningProbability(playerScore) << "%" << endl << endl;
        
        
        while (playerScore < 21)
        {
            char choice;
            cout << "Do you want to hit or stand? (h/s): ";
            cin >> choice;
            
            if (choice == 'h')
            {
                playerHand.addCard(deck.dealCard());
                playerScore = playerHand.getValue();
                
                cout << "\nPlayer's Hand: ";
                playerHand.display();
                cout << endl;
                
                cout << "Player's Winning Probability: " << calculateWinningProbability(playerScore) << "%" << endl << endl;
            } else if (choice == 's')
            {
                break;
            } else
            {
                cout << "Invalid choice. Please enter 'h' or 's'." << endl;
            }
        }
        
        while (dealerScore < 17)
        {
            dealerHand.addCard(deck.dealCard());
            dealerScore = dealerHand.getValue();
        }
        
        cout << "Dealer's Hand: ";
        dealerHand.display();
        cout << endl;
        
        cout << "Player's Hand: ";
        playerHand.display();
        cout << endl;
        
        cout << "Player's Winning Probability: " << calculateWinningProbability(playerScore) << "%" << endl;
        cout << "Dealer's Winning Probability: " << calculateWinningProbability(dealerScore) << "%" << endl;
    }
    
    double calculateWinningProbability(int score)
    {
        if (score > 21)
        {
            cout << "Bust ";
            
            return 0.0;
            
        } else if (score == 21)
            
        {
            cout << "Black Jack ";
            
            return 100.0;
            
        } else
            
        {
            
            return static_cast<double>(21 - score) / 21 * 100.0;
        }
    }
    
};
int main()
{
    cout << "*************************" << endl;
    cout << "* Welcome to black jack *" << endl;
    cout << "*************************" << endl << endl;
    
    BlackJack game;
    game.play();
    
    char choice;
    
    cout << "Would you like to play again? (y/n):";
    cin >> choice;
    cout << endl;

    if (choice == 'y')
    {
        game.play();
        
    } else if (choice == 'n')

    {
        cout << "Thank you for playing" << endl;
        return 0;
    } else

    {
        cout << "Invalid choice. Please enter 'y' or 'n': ";
        
    }
    
}
