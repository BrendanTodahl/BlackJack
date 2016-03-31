CC = g++

default:	BlackJack

BlackJack:	Card.o CardDeck.o Game.o
			$(CC) -o BlackJack Card.o CardDeck.o Game.o
			
Card.o:	Card.cpp Card.h
		$(CC) -c Card.cpp
		
CardDeck.o: CardDeck.cpp Card.h CardDeck.h
			$(CC) -c CardDeck.cpp
			
Game.o:	Game.cpp Card.h CardDeck.h
		$(CC) -c Game.cpp
		
clean:
		$(RM) BlackJack *.o *~
