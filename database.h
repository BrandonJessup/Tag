#ifndef DATABASE_H
#define DATABASE_H


class Database
{
public:
    static Database* getInstance();

protected:
    Database();

private:
    static Database* instance;
};

#endif // DATABASE_H
