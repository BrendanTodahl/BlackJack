CC = g++

default:	BlackJack

BlackJack:	User.o Card.o CardDeck.o Game.o
			$(CC) -o BlackJack User.o Card.o CardDeck.o Game.o

User.o: User.cpp User.h
		$(CC) -c User.cpp			

Card.o:	Card.cpp Card.h
		$(CC) -c Card.cpp
		
CardDeck.o: CardDeck.cpp Card.h CardDeck.h
			$(CC) -c CardDeck.cpp
			
Game.o:	Game.cpp User.h Card.h CardDeck.h
		$(CC) -c Game.cpp
		
clean:
		$(RM) BlackJack *.exe *.o *~
