using namespace std;
class Sudoku
{
    public:
        static const int sudokuSize = 81;
        static const int sudokuNum = 9;

        Sudoku();
        void giveQuestion();
        void readIn();
        void solve();
        void transform();
        void changeNum(int a, int b);
        void changeRow(int a, int b);
        void changeCol(int a, int b);
        void rotate(int n);
        void flip(int n);

    private:
        int map[sudokuSize];
        int ans[sudokuSize];
        int blankNum[sudokuSize];
        int fillPoint;

        int nextBlank(int test);
        int pop();
        bool initial_check();
        bool check(int test);
        void change();
        void printOut(bool isAns);
};

