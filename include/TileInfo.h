#ifndef TILEINFO_H
#define TILEINFO_H

enum TileState{
            BLOCKED = 0,
            FREE,
            ALLY,
            ENEMY
};

class TileInfo
{
    public:
        TileInfo(int tileType = -1, TileState state = BLOCKED);
        ~TileInfo();

        TileState state;
        int tileType;
    protected:
    private:
        //Point mapAdress;
        //vector<Point> neighbors[4];
};

#endif // TILEINFO_H