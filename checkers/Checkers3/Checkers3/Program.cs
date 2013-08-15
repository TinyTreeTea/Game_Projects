using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    class Program
    {
        static public int CalculateAdvantage(sbyte[,] board)
        {
            bool whiteWin = true, BlackWin = true;
            sbyte counter = 0;
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                {
                    if (board[i, j] != 2 && board[i, j] != -2)
                        counter += board[i, j];
                    else if (board[i, j] == -2)
                        counter += -4;
                    else
                        counter += 4;
                    if (board[i, j] > 0)
                        BlackWin = false;
                    else if (board[i, j] < 0)
                        whiteWin = false;
                }
            if (whiteWin && !BlackWin)
                return 50;
            if (!whiteWin && BlackWin)
                return -50;
           /* if (!whiteWin && !BlackWin)
            {
                sbyte row,col;
                if (!CheckerPiece.CanAWhitePieceEatOnTheBoard(board, out row, out col))
                    if (!CheckerPiece.CanAWhitePieceMoveOnTheBoard(board))
                        return -50;
                if (!CheckerPiece.CanABlackPieceEatOnTheBoard(board, out row, out col))
                    if (!CheckerPiece.CanABlackPieceMoveOnTheBoard(board))
                        return 50;
            }*/
            return counter;
        }
        static public void OrginizeBoard(sbyte[,] board)
        {
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++) 
                {
                    if ((i + j) % 2 != 0)
                    {
                        if (i < 3)
                            board[i, j] = 1;
                        else if (i > 4)
                            board[i, j] = -1;
                        else
                            board[i, j] = 0;
                    }
                    else board[i, j] = 0;
                }
        }
        static public void PrintBoard(sbyte[,] board,string turn)
        {
            if (turn == "black")
            {
                Console.WriteLine();
                Console.Write("   ");
                for (int i = 0; i < 8; i++)
                    Console.Write("  " + i + "  ");
                for (int i = 0; i < 8; i++)
                {
                    Console.WriteLine();
                    Console.WriteLine();
                    Console.Write(" " + i + " ");
                    for (int j = 0; j < 8; j++)
                    {
                        switch (board[i, j])
                        {
                            case 1:
                                Console.Write("[ w ]");
                                break;
                            case 2:
                                Console.Write("[WQ ]");
                                break;
                            case -1:
                                Console.Write("[ b ]");
                                break;
                            case -2:
                                Console.Write("[ BQ]");
                                break;
                            case 0:
                                Console.Write("[   ]");
                                break;
                        }
                    }
                }
                Console.WriteLine();
            }
            else if (turn == "white") 
            {
                Console.WriteLine();
                Console.Write("   ");
                for (int i = 0; i < 8; i++)
                    Console.Write("  " + i + "  ");
                for (int i = 0; i < 8; i++)
                {
                    Console.WriteLine();
                    Console.WriteLine();
                    Console.Write(" " + i + " ");
                    for (int j = 0; j < 8; j++)
                    {
                        switch (board[i, j])
                        {
                            case 1:
                                Console.Write("[ b ]");
                                break;
                            case 2:
                                Console.Write("[BQ ]");
                                break;
                            case -1:
                                Console.Write("[ w ]");
                                break;
                            case -2:
                                Console.Write("[ WQ]");
                                break;
                            case 0:
                                Console.Write("[   ]");
                                break;
                        }
                    }
                }
                Console.WriteLine();
            }
        }
        static public sbyte[,] CopyBoard(sbyte[,] board)
        {
            sbyte[,] copyBoard = new sbyte[8, 8];
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    copyBoard[i, j] = board[i, j];
            return copyBoard;
        }
        static public string GameState(sbyte[,] board, string turn)
        {
            sbyte row, col;
            if (turn == "white")
            {
                if (!CheckerPiece.CanAWhitePieceEatOnTheBoard(board, out row, out col))
                {
                    for (sbyte i = 0; i < 8; i++)
                        for (sbyte j = 0; j < 8; j++)
                            if (board[i, j] == 1 || board[i, j] == 2)
                                if (CheckerPiece.CanMove(board, i, j))
                                    return "no winner";
                    return "black wins";
                }
            }
            else if (turn == "black")
                if (!CheckerPiece.CanABlackPieceEatOnTheBoard(board, out row, out col))
                {
                    for (sbyte i = 0; i < 8; i++)
                        for (sbyte j = 0; j < 8; j++)
                            if (board[i, j] == -1 || board[i, j] == -2)
                                if (CheckerPiece.CanMove(board, i, j))
                                    return "no winner";
                    return "white wins";
                }
            return "no winner";
        }
        static void Main(string[] args)
        {
            /*sbyte[,] board = new sbyte[8, 8];
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    board[i, j] = 0;
            board[5, 4] = 0;
            board[4, 3] = -2;*/
            BeginGame.BeginGameCallculation();            
        }
    }
}
