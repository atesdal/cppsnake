#ifndef SNAKELIST_H
#define SNAKELIST_H


class SnakeList
{
    public:
        SnakeList();
        ~SnakeList();
        void swap(EDirection direction);
        void grow(int growAmount);

    private:
        Segment *head;
};

#endif // SNAKELIST_H
