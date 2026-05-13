#ifndef board_h_included
#define board_h_included

using namespace std;

#include <iostream>
#include <vector>

struct Move
{
    int row;
    int col;
};

enum status
{
    EMPTY = 0,
    PLAYER_X = 1,
    PLAYER_O = 2
};

class Board
{
    private:
        char** BanCo;
        int rows;
        int cols;
        int countMoves=0;
    public:
    //Constructor tạo bàn cờ
    Board(int row=10,int col=10) : rows(row), cols(col)
    {
        BanCo = new char*[rows];
        for (int i = 0; i < rows; i++)
        {
            BanCo[i] = new char[cols]{0};
        }
    }
    //Destructor hủy bàn cờ
    ~Board()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] BanCo[i];
        }
        delete[] BanCo;
    }
    //Hàm kiểm tra giới hạn bàn cờ
    bool isValid(int row, int col) 
    {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
    //Hàm kiểm tra thắng thua với nước đi vừa rồi của player_id
    bool checkWin(int row, int col,int player_id)
    {
        //Các cặp hướng: {dr, dc}
        //{0, 1}: ngang, {1, 0}: dọc, {1, 1}: chéo chính, {1, -1}: chéo phụ
        int dr[] = {0, 1, 1, 1};
        int dc[] = {1, 0, 1, -1};
        for (int i = 0; i < 4; i++)
        {
            int count = 1;
            //1. Kiểm tra theo hướng (dr, dc)
            int nr = row + dr[i], nc = col + dc[i];
            while (isValid(nr, nc) && BanCo[nr][nc] == player_id)
            {
                count++;
                nr += dr[i];
                nc += dc[i];
            }
            //2. Kiểm tra theo hướng ngược lại (-dr, -dc)
            nr = row - dr[i]; nc = col - dc[i];
            while (isValid(nr, nc) && BanCo[nr][nc] == player_id)
            {
                count++;
                nr -= dr[i];
                nc -= dc[i];
            }
            if (count >= 5) return true;
        }
        return false;
    }
    //Hàm đánh nước đi vào bàn cờ
    bool placePiece(int row, int col, int player_id) 
    {
        if (isValid(row, col) && BanCo[row][col] == EMPTY)
        {
            BanCo[row][col] = player_id;
            countMoves++;
            return true;
        }
        return false;
    }
    //Hàm rút lại nước đi ( để tiết kiệm bộ nhớ không cần phải duplicate bàn cờ ra rồi duyệt trâu cho player )
    void undoMove(int row, int col)
    {
        if (isValid(row, col) && BanCo[row][col] != EMPTY)
        {
            BanCo[row][col] = EMPTY;
            countMoves--;
        }
    }
    //Hàm kiểm tra hòa
    bool isFull()
    {
        if (countMoves==(rows*cols)) return 1;
        else return 0;
    }
    //Hàm lấy giá trị 1 ô của bàn cờ
    int getCell(int row, int col)
    {
        return BanCo[row][col];
    }
    //Hàm tính điểm của mẫu hình
    int getRows()
    {
        return rows;
    }
    int getCols()
    {
        return cols;
    }
    int countPatterns(int player_ID)
    {
        int score = 0;
        int dr[] = {0, 1, 1, 1};
        int dc[] = {1, 0, 1, -1};
        int enemy = 3 - player_ID;
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (BanCo[r][c] == player_ID)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        //Tránh đếm trùng bằng cách chỉ đếm khi đây là quân đầu tiên của chuỗi
                        int pr = r - dr[i], pc = c - dc[i];
                        if (isValid(pr, pc) && BanCo[pr][pc] == player_ID) continue;
                        int count = 1;
                        int nr = r + dr[i], nc = c + dc[i];
                        while (isValid(nr, nc) && BanCo[nr][nc] == player_ID)
                        {
                            count++; nr += dr[i]; nc += dc[i];
                        }
                        //Kiểm tra 2 đầu của chuỗi
                        int openEnds = 0;
                        //Đầu sau (nr, nc)
                        if (isValid(nr, nc) && BanCo[nr][nc] == EMPTY) openEnds++;
                        //Đầu trước (pr, pc)
                        if (isValid(pr, pc) && BanCo[pr][pc] == EMPTY) openEnds++;
                        //Lượng giá điểm dựa trên số quân và số đầu hở
                        if (count >= 5) score += 1000000; //Win luôn
                        else if (count == 4)
                        {
                            if (openEnds == 2) score += 200000; //Open 4 -> win chắc
                            else if (openEnds == 1) score += 50000; //Blocked 4 
                        }
                        else if (count == 3)
                        {
                            if (openEnds == 2) score += 15000; //Open 3
                            else if (openEnds == 1) score += 1000; //Blocked 3
                        }
                        else if (count == 2) 
                        {
                            if (openEnds == 2) score += 500; //Open 2
                            else if (openEnds == 1) score += 100; //Blocked 2
                        }
                    }
                }
            }
        }
        return score;
    }
};

class AIPlayer
{
private:
    int playerID;
    double HSAtk;  //Hệ số tấn công
    double HSDef; //Hệ số phòng thủ
    //Hàm lượng giá để xác định thế trận
    int evaluate(Board& b)
    {
        int atkScore = b.countPatterns(playerID);
        int defScore = b.countPatterns(3 - playerID);
        return (atkScore * HSAtk) - (defScore * HSDef);
    }
    public:
    //Constructor của AIPlayer
    AIPlayer(int playerID,double HSAtk=1.0,double HSDef=1.0) : playerID(playerID),HSAtk(HSAtk),HSDef(HSDef){}
    int minimax(Board& b, int depth, bool isMaxPlayer, int alpha, int beta)
    {
        //Minimax kết hợp ALpha-Beta Prunning để chạy nhanh hơn
        //Điều kiện dừng : Bàn cờ hết chỗ trống -> Hòa, Độ sâu=0 -> Tính xong 3 nước, Hoặc X thắng luôn hoặc O thắng luôn -> Dừng
        if (depth == 0 || b.isFull()) return evaluate(b);
        if (isMaxPlayer)
        {
            int maxEval = -2e9;
            for (int r = 0; r < b.getRows(); r++) 
            {
                for (int c = 0; c < b.getCols(); c++) 
                {
                    if (b.getCell(r, c) == EMPTY) 
                    {
                        b.placePiece(r, c, playerID);
                        if (b.checkWin(r, c, playerID))
                        {
                            b.undoMove(r, c);
                            return 1000000 + depth;
                        }
                        int eval = minimax(b, depth - 1, false, alpha, beta);
                        b.undoMove(r, c);
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval); //Cập nhật alpha
                        if (beta <= alpha) break; //Cắt tỉa nhánh
                    }
                }
                if (beta <= alpha) break; //Cắt tỉa tiếp ở vòng lặp ngoài
            }
            return maxEval;
        } 
        else 
        {
            int minEval = 2e9;
            for (int r = 0; r < b.getRows(); r++) 
            {
                for (int c = 0; c < b.getCols(); c++) 
                {
                    if (b.getCell(r, c) == EMPTY)
                    {
                        b.placePiece(r, c, 3 - playerID);
                        if (b.checkWin(r, c, 3 - playerID))
                        {
                            b.undoMove(r, c);
                            return -1000000 - depth;
                        }
                        int eval = minimax(b, depth - 1, true, alpha, beta);
                        b.undoMove(r, c);
                        minEval = min(minEval, eval);
                        beta = min(beta, eval); // Cập nhật beta
                        if (beta <= alpha) break; // Cắt tỉa nhánh
                    }
                }
                if (beta <= alpha) break;
            }
            return minEval;
        }
    }
    Move calculateMove(Board& b)
    {
        vector<Move> bestMoves;
        int bestScore = -2e9;
        for (int r = 0; r < b.getRows(); r++)
        {
            for (int c = 0; c < b.getCols(); c++)
            {
                if (b.getCell(r, c) == EMPTY)
                {
                    b.placePiece(r, c, playerID);
                    if (b.checkWin(r, c, playerID))
                    { 
                        b.undoMove(r, c);
                        return {r, c};
                    }
                    int score = minimax(b, 2, false, -2e9, 2e9);
                    b.undoMove(r, c);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestMoves.clear();
                        bestMoves.push_back({r, c});
                    } else if (score == bestScore) 
                    {
                        bestMoves.push_back({r, c});
                    }
                }
            }
        }
        // Chọn ngẫu nhiên trong danh sách các nước đi tốt nhất
        return bestMoves[rand() % bestMoves.size()];
    }
};

class gameManager
{
    private:
        Board board;
        AIPlayer playerX;
        AIPlayer playerO;
        int turn = PLAYER_X;
    public:
    //Constructor gameManager
    gameManager(AIPlayer x, AIPlayer o,int row,int col) : board(row, col), playerX(x), playerO(o){}
    //Hàm chạy một trận đấu tự động
    int playMatch() 
    {
        while (true) 
        {
            Move m;
            if (turn == PLAYER_X) m = playerX.calculateMove(board);
            else m = playerO.calculateMove(board);
            board.placePiece(m.row, m.col, turn);
            if (board.checkWin(m.row, m.col, turn)) return turn; //ID người win
            if (board.isFull()) return 0;
            turn = 3 - turn;
        }
    }
};

#endif