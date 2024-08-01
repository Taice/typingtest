#include <chrono>
#include <ctime>
#include <ncurses.h>
#include <string>

double game();
std::string gen_words();

std::string wordlist[] = {
    "the",    "be",      "of",     "and",   "a",      "to",      "in",
    "he",     "have",    "it",     "that",  "for",    "they",    "with",
    "as",     "not",     "on",     "she",   "at",     "by",      "this",
    "we",     "you",     "do",     "but",   "from",   "or",      "which",
    "one",    "would",   "all",    "will",  "there",  "say",     "who",
    "make",   "when",    "can",    "more",  "if",     "no",      "man",
    "out",    "other",   "so",     "what",  "time",   "up",      "go",
    "about",  "than",    "into",   "could", "state",  "only",    "new",
    "year",   "some",    "take",   "come",  "these",  "know",    "see",
    "use",    "get",     "like",   "then",  "first",  "any",     "work",
    "now",    "may",     "such",   "give",  "over",   "think",   "most",
    "even",   "find",    "day",    "also",  "after",  "way",     "many",
    "must",   "look",    "before", "great", "back",   "through", "long",
    "where",  "much",    "should", "well",  "people", "down",    "own",
    "just",   "because", "good",   "each",  "those",  "feel",    "seem",
    "how",    "high",    "too",    "place", "little", "world",   "very",
    "still",  "nation",  "hand",   "old",   "life",   "tell",    "write",
    "become", "here",    "show",   "house"};
int wl_length = sizeof(wordlist) / sizeof(wordlist[0]);
int w_length;

int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    srand(time(0));

    clear();
    attron(COLOR_PAIR(1));
	game();
    endwin();
}

std::string gen_words()
{
    std::string words = wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length] + " " +
                        wordlist[(int)rand() % wl_length];
    w_length = words.length();
    return words;
}

double game()
{
    int index = 0;
    bool running = true;
    std::string words = gen_words();
    char written[w_length];

    for (int i = index; i < w_length; i++)
    {
        addch(words[i]);
    }
    attroff(COLOR_PAIR(1));
    char ch = getch();
    char current_char = words[index];

    if (ch == current_char)
    {
        written[index] = current_char;
        index++;
    }
    auto start = std::chrono::high_resolution_clock::now();
    while (running)
    {
        if (index == w_length)
        {
            running = false;
			break;
        }
		wmove(stdscr, 0, index);
        clear();
        attron(COLOR_PAIR(2));
        for (int i = 0; i < index; i++)
        {
            addch(written[i]);
        }
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(1));
        for (int i = index; i < w_length; i++)
        {
            addch(words[i]);
        }
        attroff(COLOR_PAIR(1));
        char ch = getch();
        char current_char = words[index];

        if (ch == current_char)
        {
            written[index] = current_char;
            index++;
        }
        else if (ch == 9)
        {
			clear();
            index = 0;
            return game();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double wpm = (w_length / 5.0) / (elapsed.count() / 60.0);
    addstr("\n");
    addstr(std::to_string(wpm).c_str());
    char chr = getch();
    if (chr == 9)
    {
		clear();
        return game();
    }
    return wpm;
}
