#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


class GameController
{
    public:
        GameController();
        virtual ~GameController();
        //获取单例对象
        static GameController* getInstance();
        void Start();

    protected:

    private:
        static GameController* instance;
};

#endif // GAMECONTROLLER_H
