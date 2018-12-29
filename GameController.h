#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


class GameController
{
public:
    GameController() : speed(200), key(1), score(0) {}
    void Start();
    void SelectDifficulty(bool AIFirst);
    void StartGame(bool AIFirst,int key);
    void SelectPlayer();
    void SelectFirstPlayer();
    void DrawGame();
    int PlayGame();
    void UpdateScore(const int&);
    void RewriteScore();
    int Menu();
    void Game();
    int GameOver();
private:
    int speed;
    int key;
    int score;
};

#endif // GAMECONTROLLER_H
