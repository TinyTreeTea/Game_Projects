using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    static class BeginGame
    {
        static public void BeginGameCallculation()
        {
            sbyte[,] board = new sbyte[8, 8];
            Program.OrginizeBoard(board);
            Console.WriteLine("if you want to start type white");
            string whoStarts = Console.ReadLine();
            string turn;
            if (whoStarts == "white")
            {
                Program.PrintBoard(board, "white");
                Console.WriteLine("enter row and then col that u move from/n and then the row and col u move too");
                int rowFrom = int.Parse(Console.ReadLine());
                int colFrom = int.Parse(Console.ReadLine());
                int rowToo = int.Parse(Console.ReadLine());
                int colToo = int.Parse(Console.ReadLine());
                board[rowFrom, colFrom] = 0;
                board[rowToo, colToo] = -1;
                turn = "white";
                Program.PrintBoard(board, turn);
            }
            else
            {
                turn = "black";
                Program.PrintBoard(board, turn);
            }
            while (Program.GameState(board, "white") == "no winner")
            {
                Console.WriteLine(DateTime.Now);
                FirstGameTree gameTree = new FirstGameTree(board);
                FirstGameCalculation(gameTree);
                SecondGameTree moveChosen = SetFirstTreeValue(gameTree);
                Program.PrintBoard(moveChosen.board,turn);
                Console.WriteLine(DateTime.Now);
                if (Program.GameState(board, "black") == "no winner")
                {
                    sbyte row, col;
                    if (CheckerPiece.CanABlackPieceEatOnTheBoard(moveChosen.board, out row, out col))
                    {
                        Console.WriteLine("enter row and then col that you want to eat from");
                        row = sbyte.Parse(Console.ReadLine());
                        col = sbyte.Parse(Console.ReadLine());
                        List<sbyte[,]> list = new List<sbyte[,]>();
                        CheckerPiece.Eat(row, col, moveChosen.board, list);
                        int x;
                        foreach (sbyte[,] newBoard in list)
                        {
                            Console.WriteLine("1 for yes 0 for no");
                            Program.PrintBoard(newBoard, turn);
                            x = int.Parse(Console.ReadLine());
                            if (x == 1)
                            {
                                board = newBoard;
                                break;
                            }
                        }
                    }
                    else
                    {
                        Console.WriteLine("enter row and then col that u move from and then the row and col u move too");
                        int rowFrom = int.Parse(Console.ReadLine());
                        int colFrom = int.Parse(Console.ReadLine());
                        int rowToo = int.Parse(Console.ReadLine());
                        int colToo = int.Parse(Console.ReadLine());
                        sbyte temp = moveChosen.board[rowFrom, colFrom];
                        moveChosen.board[rowFrom, colFrom] = 0;
                        moveChosen.board[rowToo, colToo] = temp;
                        board = moveChosen.board;
                        Program.PrintBoard(board, turn);
                    }
                }
            }
        }
        static public void FirstGameCalculation(FirstGameTree gameTree)
        {
            sbyte row, col;
            if (CheckerPiece.CanAWhitePieceEatOnTheBoard(gameTree.board, out row, out col))
            {
                for (; row < 8; row++)
                    for (; col < 8; col++)
                        if (CheckerPiece.CanAWhitePieceEat(gameTree.board, ref row, ref col))
                        {
                            List<sbyte[,]> list = new List<sbyte[,]>();
                            CheckerPiece.Eat(row, col, gameTree.board, list);
                            foreach (sbyte[,] board in list)
                            {
                                SecondGameTree newGameTree = new SecondGameTree(board);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                        }
            }
            else
            {
                for (sbyte i = 0; i < 8; i++)
                    for (sbyte j = 0; j < 8; j++)
                    {
                        if (gameTree.board[i, j] == 1)
                        {
                            if (CheckerPiece.CanPlus1MoveUpRight(gameTree.board, i, j))
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                CheckerPiece.MovePlus1UpRight(newBoard, i, j);
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                            if (CheckerPiece.CanPlus1MoveUpLeft(gameTree.board, i, j))
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                CheckerPiece.MovePlus1UpLeft(newBoard, i, j);
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                        }
                        else if (gameTree.board[i, j] == 2)
                        {
                            int amountOfMoves1 = CheckerPiece.AmoutOfPlus2UpRightMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves1; k++)
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                newBoard[i, j] = 0;
                                newBoard[i + k + 1, j - k - 1] = 2;
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                            int amountOfMoves2 = CheckerPiece.AmoutOfPlus2UpLeftMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves2; k++)
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                newBoard[i, j] = 0;
                                newBoard[i + k + 1, j + k + 1] = 2;
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                            int amountOfMoves3 = CheckerPiece.AmoutOfPlus2DownRightMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves3; k++)
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                newBoard[i, j] = 0;
                                newBoard[i - k - 1, j + k + 1] = 2;
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                            int amountOfMoves4 = CheckerPiece.AmoutOfPlus2DownLeftMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves4; k++)
                            {
                                sbyte[,] newBoard = Program.CopyBoard(gameTree.board);
                                newBoard[i, j] = 0;
                                newBoard[i - k - 1, j - k - 1] = 2;
                                SecondGameTree newGameTree = new SecondGameTree(newBoard);
                                newGameTree.value = Program.CalculateAdvantage(gameTree.board);
                                gameTree.list.Add(newGameTree);
                                SecondGameCalculation(newGameTree);
                            }
                        }
                    }
            }
        }
        static private void SecondGameCalculation(SecondGameTree gameTree)
        {
            sbyte row, col;
            if (CheckerPiece.CanABlackPieceEatOnTheBoard(gameTree.board, out row, out col))
            {
                for (; row < 8; row++)
                    for (; col < 8; col++)
                    {
                        if (gameTree.board[row, col] == -1)
                        {
                            List<sbyte[,]> list = new List<sbyte[,]>();
                            CheckerPiece.Eat(row, col, gameTree.board, list);
                            foreach (sbyte[,] board in list)
                            {
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, board, 2);
                            }
                        }
                        else if (gameTree.board[row, col] == -2)
                        {
                            List<sbyte[,]> list = new List<sbyte[,]>();
                            CheckerPiece.Eat(row, col, gameTree.board, list);
                            foreach (sbyte[,] board in list)
                            {
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, board, 2);
                            }
                        }
                    }
            }
            else
            {
                for (sbyte i = 0; i < 8; i++)
                    for (sbyte j = 0; j < 8; j++)
                    {
                        if (gameTree.board[i, j] == -1)
                        {
                            if (CheckerPiece.CanMinus1MoveUpRight(gameTree.board, i, j))
                            {
                                CheckerPiece.MoveMinus1UpRight(gameTree.board, i, j);
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                CheckerPiece.UndoMoveMinus1UpRight(gameTree.board, i, j);
                            }
                            if (CheckerPiece.CanMinus1MoveUpLeft(gameTree.board, i, j))
                            {
                                CheckerPiece.MoveMinus1UpLeft(gameTree.board, i, j);
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                CheckerPiece.UndoMoveMinus1UpLeft(gameTree.board, i, j);
                            }
                        }
                        else if (gameTree.board[i, j] == -2)
                        {
                            int amountOfMoves1 = CheckerPiece.AmoutOfMinus2UpRightMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves1; k++)
                            {
                                gameTree.board[i, j] = 0;
                                gameTree.board[i - k - 1, j + k + 1] = -2;
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                gameTree.board[i, j] = -2;
                                gameTree.board[i - k - 1, j + k + 1] = 0;
                            }
                            int amountOfMoves2 = CheckerPiece.AmoutOfMinus2UpLeftMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves2; k++)
                            {
                                gameTree.board[i, j] = 0;
                                gameTree.board[i - k - 1, j - k - 1] = -2;
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                gameTree.board[i, j] = -2;
                                gameTree.board[i - k - 1, j - k - 1] = 0;
                            }
                            int amountOfMoves3 = CheckerPiece.AmoutOfMinus2DownRightMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves3; k++)
                            {
                                gameTree.board[i, j] = 0;
                                gameTree.board[i + k + 1, j - k - 1] = -2;
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                gameTree.board[i, j] = -2;
                                gameTree.board[i + k + 1, j - k - 1] = 0;
                            }
                            int amountOfMoves4 = CheckerPiece.AmoutOfMinus2DownLeftMoves(gameTree.board, i, j);
                            for (int k = 0; k < amountOfMoves4; k++)
                            {
                                gameTree.board[i, j] = 0;
                                gameTree.board[i + k + 1, j + k + 1] = -2;
                                GameTree newGameTree = new GameTree(Program.CalculateAdvantage(gameTree.board));
                                gameTree.list.Add(newGameTree);
                                GameCalculation(newGameTree, gameTree.board, 2);
                                gameTree.board[i, j] = -2;
                                gameTree.board[i + k + 1, j + k + 1] = 0;
                            }
                        }
                    }
            }
        }
        static private void GameCalculation(GameTree gameTree, sbyte[,] board, double turn)
        {
            if (turn < 8)
            {
                string whiteGameState = Program.GameState(board, "white");
                bool whoMoves = (turn % 2 == 0);
                if (whoMoves && whiteGameState == "no winner")
                {
                    sbyte row, col;
                    if (CheckerPiece.CanAWhitePieceEatOnTheBoard(board, out row, out col))
                    {
                        for (; row < 8; row++)
                            for (; col < 8; col++)
                                if (CheckerPiece.CanAWhitePieceEat(board, ref row, ref col))
                                {
                                    List<sbyte[,]> list = new List<sbyte[,]>();
                                    CheckerPiece.Eat(row, col, board, list);
                                    foreach (sbyte[,] newBoard in list)
                                    {
                                        GameTree newGameTree = new GameTree(Program.CalculateAdvantage(newBoard));
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, newBoard, turn + 1);
                                    }
                                }
                    }
                    else
                    {
                        for (sbyte i = 0; i < 8; i++)
                            for (sbyte j = 0; j < 8; j++)
                            {
                                if (board[i, j] == 1)
                                {
                                    if (CheckerPiece.CanPlus1MoveUpRight(board, i, j))
                                    {
                                        CheckerPiece.MovePlus1UpRight(board, i, j);
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        CheckerPiece.UndoMovePlus1UpRight(board, i, j);
                                    }
                                    if (CheckerPiece.CanPlus1MoveUpLeft(board, i, j))
                                    {
                                        CheckerPiece.MovePlus1UpLeft(board, i, j);
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        CheckerPiece.UndoMovePlus1UpLeft(board, i, j);
                                    }
                                }
                                else if (board[i, j] == 2)
                                {
                                    int amountOfMoves1 = CheckerPiece.AmoutOfPlus2UpRightMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves1; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i + k + 1, j - k - 1] = 2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = 2;
                                        board[i + k + 1, j - k - 1] = 0;
                                    }
                                    int amountOfMoves2 = CheckerPiece.AmoutOfPlus2UpLeftMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves2; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i + k + 1, j + k + 1] = 2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = 2;
                                        board[i + k + 1, j + k + 1] = 0;
                                    }
                                    int amountOfMoves3 = CheckerPiece.AmoutOfPlus2DownRightMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves3; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i - k - 1, j + k + 1] = 2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = 2;
                                        board[i - k - 1, j + k + 1] = 0;
                                    }
                                    int amountOfMoves4 = CheckerPiece.AmoutOfPlus2DownLeftMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves4; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i - k - 1, j - k - 1] = 2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = 2;
                                        board[i - k - 1, j - k - 1] = 0;
                                    }
                                }
                            }
                    }
                }
                else if (whoMoves && whiteGameState != "no winner")
                {
                    gameTree.list.Add(new GameTree(-50));
                }
                else if (Program.GameState(board, "black") == "no winner")
                {
                    sbyte row, col;
                    if (CheckerPiece.CanABlackPieceEatOnTheBoard(board, out row, out col))
                    {
                        for (; row < 8; row++)
                            for (; col < 8; col++)
                                if (CheckerPiece.CanABlackPieceEat(board, ref row, ref col))
                                {
                                    List<sbyte[,]> list = new List<sbyte[,]>();
                                    CheckerPiece.Eat(row, col, board, list);
                                    foreach (sbyte[,] newBoard in list)
                                    {
                                        GameTree newGameTree = new GameTree(Program.CalculateAdvantage(newBoard));
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, newBoard, turn + 1);
                                    }
                                }
                    }
                    else
                    {
                        for (sbyte i = 0; i < 8; i++)
                            for (sbyte j = 0; j < 8; j++)
                            {
                                if (board[i, j] == -1)
                                {
                                    if (CheckerPiece.CanMinus1MoveUpRight(board, i, j))
                                    {
                                        CheckerPiece.MoveMinus1UpRight(board, i, j);
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        CheckerPiece.UndoMoveMinus1UpRight(board, i, j);
                                    }
                                    if (CheckerPiece.CanMinus1MoveUpLeft(board, i, j))
                                    {
                                        CheckerPiece.MoveMinus1UpLeft(board, i, j);
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        CheckerPiece.UndoMoveMinus1UpLeft(board, i, j);
                                    }
                                }
                                else if (board[i, j] == -2)
                                {
                                    int amountOfMoves1 = CheckerPiece.AmoutOfMinus2UpRightMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves1; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i - k - 1, j + k + 1] = -2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = -2;
                                        board[i - k - 1, j + k + 1] = 0;
                                    }
                                    int amountOfMoves2 = CheckerPiece.AmoutOfMinus2UpLeftMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves2; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i - k - 1, j - k - 1] = -2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = -2;
                                        board[i - k - 1, j - k - 1] = 0;
                                    }
                                    int amountOfMoves3 = CheckerPiece.AmoutOfMinus2DownRightMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves3; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i + k + 1, j - k - 1] = -2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = -2;
                                        board[i + k + 1, j - k - 1] = 0;
                                    }
                                    int amountOfMoves4 = CheckerPiece.AmoutOfMinus2DownLeftMoves(board, i, j);
                                    for (int k = 0; k < amountOfMoves4; k++)
                                    {
                                        board[i, j] = 0;
                                        board[i + k + 1, j + k + 1] = -2;
                                        GameTree newGameTree = new GameTree(gameTree.value);
                                        gameTree.list.Add(newGameTree);
                                        GameCalculation(newGameTree, board, turn + 1);
                                        board[i, j] = -2;
                                        board[i + k + 1, j + k + 1] = 0;
                                    }
                                }
                            }
                    }
                }
                else
                    gameTree.list.Add(new GameTree(50));
            }
        }
        static public SecondGameTree SetFirstTreeValue(FirstGameTree gameTree)
        {
            if (gameTree.list.Count > 0)
            {
                foreach (SecondGameTree newGameTree in gameTree.list)
                {
                    SetSecondTreeValues(newGameTree);
                }
                int max = -100;
                SecondGameTree ReturnedGameTree = null;
                Random rnd = new Random();
                foreach (SecondGameTree newGameTree in gameTree.list)
                {
                    if (newGameTree.value > max)
                    {
                        max = newGameTree.value;
                        ReturnedGameTree = newGameTree;
                    }
                    else if (newGameTree.value == max)
                    {
                        if (rnd.Next(4) == 3)
                        {
                            max = newGameTree.value;
                            ReturnedGameTree = newGameTree;
                        }
                    }
                }
                return ReturnedGameTree;
            }
            return null;
        }
        static private void SetSecondTreeValues(SecondGameTree gameTree)
        {
            if (gameTree.list.Count > 0)
            {
                foreach (GameTree newGameTree in gameTree.list)
                {
                    SetRestTreeValues(newGameTree, 2);
                }
                int min = 100;
                foreach (GameTree newGameTree in gameTree.list)
                {
                    if (newGameTree.value < min)
                        min = newGameTree.value;
                }
                gameTree.value = min;
            }
        }
        static private void SetRestTreeValues(GameTree gameTree, int turn)
        {
            if (gameTree.list.Count > 0)
            {
                foreach (GameTree newGameTree in gameTree.list)
                {
                    SetRestTreeValues(newGameTree, turn + 1);
                }
                if (turn % 2 == 0)
                {
                    int max = -100;
                    foreach (GameTree newGameTree in gameTree.list)
                    {
                        if (newGameTree.value > max)
                        {
                            max = newGameTree.value;
                        }
                    }
                    gameTree.value = max;
                }
                else
                {
                    int min = 100;
                    foreach (GameTree newGameTree in gameTree.list)
                    {
                        if (newGameTree.value < min)
                        {
                            min = newGameTree.value;
                        }
                    }
                    gameTree.value = min;
                }
            }
        }
    }
}
