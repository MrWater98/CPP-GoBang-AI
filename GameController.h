#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


class GameController
{
    public:
        GameController();
        virtual ~GameController();
        //��ȡ��������
        static GameController* getInstance();
        void Start();

    protected:

    private:
        static GameController* instance;
};

#endif // GAMECONTROLLER_H
