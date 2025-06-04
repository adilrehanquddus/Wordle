#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// STATE CHANGE INITIALIZATION
enum class WindowState
{
    startScreen,
    wordleGamePlayScreen,
    LeaderBoardScreen

};

// Constants
const int ROWS = 6;
const int COLS = 5;
const float TILESIZE = 80.0;
const sf::Color Green(0, 255, 0);
const sf::Color Yellow(200, 150, 0);
const sf::Color Gray(50, 50, 50);
const sf::Color LightGray(128, 128, 128);
const sf::Color White(255, 255, 255);

// Player type
struct Players
{
    std::string username = "";
    float score;
};
Players player;

// Random Answer Generation
std::string randomAnswerGenerator()
{
    std::string answer;
    srand(time(0));
    int randomLine = rand() % (1248 + 1);
    std::ifstream MyReadFile("answers.txt");
    if (!MyReadFile.is_open())
    {
        std::cerr << "File Not Opened" << std::endl;
        exit(1);
    }
    int i = 1;
    while (getline(MyReadFile, answer))
    {
        if (i == randomLine)
        {
            break;
        }
        i++;
    }
    MyReadFile.close();
    return answer;
}

bool validate(std::string &guess)
{
    std::ifstream MyReadFile("allwords.txt");
    std::string word;
    while (getline(MyReadFile, word))
    {
        for (int i = 0; i < guess.length(); i++)
        {
            guess[i] = toupper(guess[i]);
        }
        if (guess == word)
        {
            MyReadFile.close();
            return true;
        }
    }
    MyReadFile.close();
    return false;
}
// Storing Player data in file
void storePlayerData(Players &player)
{
    std::ofstream outFile("scores.txt", std::ios::app);
    std::string data = "";
    std::string avg = std::to_string(player.score).substr(0, 4);
    data.append(avg).append(",").append(player.username).append("\n");
    outFile << data;
}
// SHOWS GAME TITLE AND STORES USERNAME
std::string firstDisplay(sf::RenderWindow &window, sf::Font &font, WindowState &currentState)
{
    // Title initialization
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(100);
    title.setString("WORDLE");
    title.setStyle(sf::Text::Bold);
    sf::FloatRect textbounds = title.getLocalBounds();
    title.setOrigin(textbounds.left + textbounds.width / 2.0f, textbounds.top + textbounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2, 200);
    // INPUT PROMPT INITIALIZATION
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setFillColor(sf::Color::White);
    prompt.setCharacterSize(35);
    prompt.setString("ENTER YOUR USERNAME:");
    prompt.setStyle(sf::Text::Bold);
    sf::FloatRect promptbounds = prompt.getLocalBounds();
    prompt.setOrigin(promptbounds.left + promptbounds.width / 2.0f, textbounds.top + textbounds.height / 2.0f);
    prompt.setPosition(window.getSize().x / 2, 350);
    // USER INPUT
    sf::Text input_text;
    input_text.setFont(font);
    input_text.setFillColor(sf::Color::White);
    input_text.setCharacterSize(50);
    input_text.setString(" ");
    input_text.setStyle(sf::Text::Bold);
    sf::FloatRect inputbounds = input_text.getLocalBounds();
    input_text.setOrigin(inputbounds.left + inputbounds.width / 2.0f, textbounds.top + textbounds.height / 2.0f);
    input_text.setPosition(window.getSize().x / 3, 500);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b')
                    { // Backspace key
                        if (!player.username.empty())
                        {
                            player.username.pop_back(); // Remove last character
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\r')
                    {                                                             // Regulamingw32-make -r characters, excluding Enter
                        player.username += static_cast<char>(event.text.unicode); // Add character to input
                    }
                    else if (event.text.unicode == '\r')
                    { // Enter key
                        if (!player.username.empty())
                        {                                                     // Ensure username is not empty
                            currentState = WindowState::wordleGamePlayScreen; // Close the window
                            return player.username;
                        }
                    }

                    // Update the displayed text with the current username
                    input_text.setString(player.username);
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(prompt);
        window.draw(input_text);
        window.display();
    }
    return "meow";
}
// leaderBoard
void leaderBoard(sf::RenderWindow &window, sf::Font &font, WindowState &currentState)
{
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(80);
    title.setString("----------LEADER BOARD----------");
    title.setStyle(sf::Text::Bold);
    sf::FloatRect textbounds = title.getLocalBounds();
    title.setOrigin(textbounds.left + textbounds.width / 2.0f, textbounds.top + textbounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2.0f, 100);

    int count = 0;
    std::string data;

    // Count the number of lines in the file
    std::ifstream MyReadFile("scores.txt");
    while (getline(MyReadFile, data))
    {
        count++;
    }
    MyReadFile.close();

    // Store and sort the players
    Players arr[count];
    std::ifstream MyReadFile2("scores.txt");
    int i = 0;
    while (getline(MyReadFile2, data))
    {
        int comma_pos = data.find(',');                      // Find the comma separating score and username
        arr[i].score = std::stof(data.substr(0, comma_pos)); // Extract score
        arr[i].username = data.substr(comma_pos + 1);        // Extract username
        i++;
    }
    MyReadFile2.close();

    // Sort players by score in descending order
    Players temp;
    for (int j = 0; j < count - 1; j++)
    {
        for (int k = 0; k < count - j - 1; k++)
        {
            if (arr[k].score < arr[k + 1].score)
            {
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
            }
        }
    }

    // Generate the top 5 list
    sf::Text list;
    list.setFont(font);
    list.setFillColor(White);
    list.setCharacterSize(40);
    list.setStyle(sf::Text::Bold);

    std::string top5list = "";
    for (int l = 0; l < std::min(5, count); l++)
    {
        // Format score
        std::string score2dp = std::to_string(arr[l].score);
        score2dp = score2dp.substr(0, score2dp.find('.') + 3); // 2 decimal places

        top5list += std::to_string(l + 1) + "  " + arr[l].username + "  " + score2dp + "\n";
    }
    list.setString(top5list);

    // Center the list text
    sf::FloatRect listBounds = list.getLocalBounds();
    list.setOrigin(listBounds.left + listBounds.width / 2.0f, listBounds.top);
    list.setPosition(window.getSize().x / 2.0f, 200);

    // Render the window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(title);
        window.draw(list);
        window.display();
    }
}

// Gameplay function
float gameplay(sf::RenderWindow &window, sf::Font &font, int numgames, float current_score, WindowState &currentState)
{
    std::string answer;
    answer = randomAnswerGenerator();
    // std::cout << answer;
    //  Continue Playing text
    sf::Text cont;
    cont.setFont(font);
    cont.setCharacterSize(50);
    cont.setFillColor(sf::Color::White);
    cont.setPosition(window.getSize().x / 10, 900.f);
    cont.setString("Do you want to continue playing? (Y/N)");
    // Invalid word text
    sf::Text invtext;
    invtext.setFont(font);
    invtext.setCharacterSize(50);
    invtext.setFillColor(sf::Color::Red);
    invtext.setPosition(window.getSize().x / 3, 800.0f);
    invtext.setString("Invalid Word!");
    // You won Text
    sf::Text win;
    win.setFont(font);
    win.setCharacterSize(50);
    win.setFillColor(White);
    win.setPosition(window.getSize().x / 3, 800.f);
    win.setString("You Won!!");
    // You Lost Text
    sf::Text lost;
    lost.setFont(font);
    lost.setCharacterSize(50);
    lost.setFillColor(White);
    lost.setPosition(window.getSize().x / 10, 800.f);
    lost.setString("You lost......The answer was " + answer);

    sf::RectangleShape tiles[ROWS][COLS];
    sf::Text letters[ROWS][COLS];
    float gridWidth = COLS * (TILESIZE + 5) - 5;            // Total width of the grid
    float startX = (window.getSize().x - gridWidth) / 2.0f; // Center grid horizontally
    float startY = 120;                                     // Position grid below title
    // Title
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(50);
    title.setString("WORDLE");
    title.setStyle(sf::Text::Bold);
    sf::FloatRect textbounds = title.getLocalBounds();
    title.setOrigin(textbounds.left + textbounds.width / 2.0f, textbounds.top + textbounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2, 50);

    // KeyBoard
    std::string keyboard_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    sf::RectangleShape keyboardKeys[26];
    sf::Text keyboardText[26];
    sf::Color keyColors[26]; // stores corresponding color of keyboard tile

    // Initializing KEYBOARD (no event handling yet)
    for (int i = 0; i < 26; ++i)
    {
        keyboardKeys[i].setSize(sf::Vector2f(40, 40));
        keyboardKeys[i].setFillColor(LightGray);
        keyboardKeys[i].setOutlineColor(White);
        keyboardKeys[i].setOutlineThickness(2);

        int row = (i < 10) ? 0 : (i < 19 ? 1 : 2);
        int col = (i < 10) ? i : (i < 19 ? i - 10 : i - 19);

        keyboardKeys[i].setPosition(280 + col * 45, 400 + row * 50 + 250);

        keyboardText[i].setFont(font);
        keyboardText[i].setCharacterSize(24);
        keyboardText[i].setFillColor(White);
        keyboardText[i].setString(std::string(1, keyboard_characters[i]));
        keyboardText[i].setPosition(keyboardKeys[i].getPosition().x + 10,
                                    keyboardKeys[i].getPosition().y + 5);

        keyColors[i] = LightGray;
    }

    // Initialize grid and letters
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            tiles[i][j].setSize(sf::Vector2f(TILESIZE, TILESIZE));
            tiles[i][j].setFillColor(Gray);
            tiles[i][j].setOutlineColor(White);
            tiles[i][j].setOutlineThickness(5);
            tiles[i][j].setPosition(startX + j * (TILESIZE + 5), startY + i * (TILESIZE + 5));

            letters[i][j].setFont(font);
            letters[i][j].setCharacterSize(36);
            letters[i][j].setFillColor(White);
            letters[i][j].setPosition(tiles[i][j].getPosition().x + 25, tiles[i][j].getPosition().y + 20);
        }
    }

    std::string guesses[ROWS] = {"", "", "", "", "", ""};
    int rowrn = 0, colrn = 0;
    bool game_ended = false;
    bool correct;
    bool game_won = false;
    bool is_valid_word = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered && !game_ended && rowrn < ROWS)
            {
                char entered = event.text.unicode;
                entered = toupper(entered);

                if (entered >= 'A' && entered <= 'Z' && colrn < COLS)
                {
                    guesses[rowrn] += entered;
                    letters[rowrn][colrn].setString(std::string(1, entered));
                    colrn++;
                }
                else if (event.text.unicode == '\b' && colrn > 0)
                { // Handle backspace
                    colrn--;
                    guesses[rowrn].pop_back();
                    letters[rowrn][colrn].setString("");
                }
                else if (event.text.unicode == '\r' && colrn == COLS)
                { // Submit guess
                    std::string guess = guesses[rowrn];
                    if (validate(guess))
                    {
                        is_valid_word = true;
                        correct = true;
                        bool ansCheck[5] = {false, false, false, false, false};

                        // FIRST PASS FOR FNIDING GREEN
                        for (int i = 0; i < COLS; i++)
                        {
                            if (answer[i] == guess[i])
                            {
                                tiles[rowrn][i].setFillColor(Green);
                                keyColors[guess[i] - 'A'] = Green;
                                ansCheck[i] = true;
                            }
                            else
                            {
                                // keyColors[guess[i]-'A']=LightGray;
                                correct = false;
                            }
                        }

                        // SECOND PASS FOR FINDING YELLOW
                        for (int i = 0; i < COLS; i++)
                        {
                            if (tiles[rowrn][i].getFillColor() != Green)
                            {
                                for (int j = 0; j < COLS; j++)
                                {
                                    if (!ansCheck[j] && answer[j] == guess[i])
                                    {

                                        tiles[rowrn][i].setFillColor(Yellow);

                                        if (keyColors[guess[i] - 'A'] != Green)
                                        {
                                            keyColors[guess[i] - 'A'] = Yellow;
                                        }
                                        ansCheck[j] = true;
                                        break;
                                    }
                                }
                            }
                        }
                        // IF CHARACTERS FROM GUESSED WORD ARE NEITHER GREEN NOR YELLOW THEN THEY MUST BE GREY
                        for (int i = 0; i < COLS; i++)
                        {
                            if (keyColors[guess[i] - 'A'] != Green && keyColors[guess[i] - 'A'] != Yellow)
                            {
                                keyColors[guess[i] - 'A'] = Gray;
                                tiles[rowrn][i].setFillColor(Gray);
                            }
                        }

                        if (correct)
                        {
                            current_score += (6 - rowrn);
                            game_ended = true;
                            game_won = true;

                            std::cout << "You guessed the word correctly!\n";
                        }
                        else
                        {
                            rowrn++;
                            colrn = 0;
                            if (rowrn == ROWS)
                            {
                                std::cout << "You lost...... The answer was " << answer << std::endl;
                                game_ended = true;
                            }
                        }
                    }
                    else
                    {
                        is_valid_word = false;
                        std::cout << "Invalid word. Try again!\n";
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(title);
        // Draw grid
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                window.draw(tiles[i][j]);
                window.draw(letters[i][j]);
            }
        }
        // draw keyboard
        for (int i = 0; i < 26; ++i)
        {
            keyboardKeys[i].setFillColor(keyColors[i]);
            window.draw(keyboardKeys[i]);
            window.draw(keyboardText[i]);
        }

        if (game_ended)
        {
            if (game_won)
            {
                window.draw(win);
            }
            else
            {
                window.draw(lost);
            }
            window.draw(cont);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
            {
                numgames++;
                return gameplay(window, font, numgames, current_score, currentState);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
            {
                float avgscore = current_score / numgames;
                currentState = WindowState::LeaderBoardScreen;
                return avgscore;
            }
        }
        else if (is_valid_word == false)
        {
            window.draw(invtext);
            window.display();
        }
        else
        {
            window.display();
        }
    }
    return 0;
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("Roboto-Black.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Wordle");
    window.setFramerateLimit(60);

    WindowState currentState = WindowState::startScreen;

    while (window.isOpen())
    {
        switch (currentState)
        {
        case WindowState::startScreen:
            player.username = firstDisplay(window, font, currentState);
            break;

        case WindowState::wordleGamePlayScreen:
            player.score = gameplay(window, font, 1, 0, currentState);
            break;
        case WindowState::LeaderBoardScreen:
            storePlayerData(player);
            leaderBoard(window, font, currentState);
        }
    }

    return 0;
}
