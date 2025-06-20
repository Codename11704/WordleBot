CC = g++
FLAGS = -Wall -Werror -Wextra -pedantic -O3
LDFLAGS = -lm
WORDLE_SOURCES = wordletextview.cpp game/board.cpp game/dataloader.cpp utils/hint.cpp game/wordle.cpp
BOT_SOURCES = botmain.cpp bot/bot.cpp utils/hint.cpp

all: wordletext bot

wordletext:
	$(CC) $(FLAGS) -o wordletext $(WORDLE_SOURCES) $(LDFLAGS)

botbin:
	$(CC) $(FLAGS) -o botbin $(BOT_SOURCES) $(LDFLAGS)