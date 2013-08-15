using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    static class CheckerPiece
    {
        //the region witch has the boolean functions that check if type 1 or -1 can move
        //and some other functions
        #region
        static public bool CanMoveOnTheBoard(sbyte[,] board)
        {
            for (sbyte i = 0; i < 8; i++)
                for (sbyte j = 0; j < 8; j++)
                    if (CanMove(board, i, j))
                        return true;
            return false;
        }
        static public bool CanAWhitePieceMoveOnTheBoard(sbyte[,] board)
        {
            for (sbyte i = 0; i < 8; i++)
                for (sbyte j = 0; j < 8; j++)
                {
                    if (board[i, j] == 1)
                        if (CanPlus1MoveUpRight(board, i, j) || CanPlus1MoveUpLeft(board, i, j))
                            return true;
                        else if (board[i, j] == 2)
                            if (AmoutOfPlus2UpRightMoves(board, i, j) != 0 || AmoutOfPlus2UpLeftMoves(board, i, j) != 0 || AmoutOfPlus2DownRightMoves(board, i, j) != 0 || AmoutOfPlus2DownLeftMoves(board, i, j) != 0)
                                return true;
                }
            return false;
        }
        static public bool CanABlackPieceMoveOnTheBoard(sbyte[,] board)
        {
            for (sbyte i = 0; i < 8; i++)
                for (sbyte j = 0; j < 8; j++)
                {
                    if (board[i, j] == -1)
                        if (CanMinus1MoveUpRight(board, i, j) || CanMinus1MoveUpLeft(board, i, j))
                            return true;
                        else if (board[i, j] == -2)
                            if (AmoutOfMinus2UpRightMoves(board, i, j) != 0 || AmoutOfMinus2UpLeftMoves(board, i, j) != 0 || AmoutOfMinus2DownRightMoves(board, i, j) != 0 || AmoutOfMinus2DownLeftMoves(board, i, j) != 0)
                                return true;
                }
            return false;
        }
        static public bool CanMove(sbyte[,] board, sbyte row, sbyte col)
        {
            if (board[row, col] == 1)
            {
                if (CanPlus1MoveUpRight(board, row, col))
                    return true;
                if (CanPlus1MoveUpLeft(board, row, col))
                    return true;
            }
            else if (board[row, col] == 2)
            {
                if (AmoutOfPlus2UpRightMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfPlus2UpLeftMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfPlus2DownRightMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfPlus2DownLeftMoves(board, row, col) != 0)
                    return true;
            }
            else if (board[row, col] == -1)
            {
                if (CanMinus1MoveUpRight(board, row, col))
                    return true;
                if (CanMinus1MoveUpLeft(board, row, col))
                    return true;
            }
            else if (board[row, col] == -2)
            {
                if (AmoutOfMinus2UpRightMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfMinus2UpLeftMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfMinus2DownRightMoves(board, row, col) != 0)
                    return true;
                if (AmoutOfMinus2DownLeftMoves(board, row, col) != 0)
                    return true;
            }
            return false;
        }
        /// <summary>
        /// checks if your type 1 piece can move up right
        /// </summary>
        /// <param name="board">the board witch u are currently playing on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns true if ur piece can move up right and false if it can't</returns>
        static public bool CanPlus1MoveUpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            if (col != 0)
                if (board[row + 1, col - 1] == 0)
                    return true;
            return false;
        }
        /// <summary>
        /// checks if your type 1 piece can move up left
        /// </summary>
        /// <param name="board">the board witch u are currently playing on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns true if ur piece can move up left and false if it can't</returns>
        static public bool CanPlus1MoveUpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            if (col != 7)
                if (board[row + 1, col + 1] == 0)
                    return true;
            return false;
        }
        /// <summary>
        /// checks if your type -1 piece can move up right
        /// </summary>
        /// <param name="board">the board witch u are currently playing on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns true if ur piece can move up right and false if it can't</returns>
        static public bool CanMinus1MoveUpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            if (col != 7)
                if (board[row - 1, col + 1] == 0)
                    return true;
            return false;
        }
        /// <summary>
        /// checks if your type -1 piece can move up left
        /// </summary>
        /// <param name="board">the board witch u are currently playing on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns true if ur piece can move up left and false if it can't</returns>
        static public bool CanMinus1MoveUpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            if (col != 0)
                if (board[row - 1, col - 1] == 0)
                    return true;
            return false;
        }
        #endregion
        //the region witch moves type 1 or -1,note that these functions modify ur board witch u send
        #region
        /// <summary>
        /// this function modifys your board witch u send
        /// and moves your piece up right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        static public void MovePlus1UpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 0;
            if (row == 6)
                board[row + 1, col - 1] = 2;
            else
                board[row + 1, col - 1] = 1;
        }
        /// <summary>
        /// this function modifys your board witch u send
        /// and moves your piece up left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        static public void MovePlus1UpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 0;
            if (row == 6)
                board[row + 1, col + 1] = 2;
            else
                board[row + 1, col + 1] = 1;
        }
        /// <summary>
        /// this function modifys your board witch u send
        /// and moves your piece up right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        static public void MoveMinus1UpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 0;
            if (row == 1)
                board[row - 1, col + 1] = -2;
            else
                board[row - 1, col + 1] = -1;
        }
        /// <summary>
        /// this function modifys your board witch u send
        /// and moves your piece up left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        static public void MoveMinus1UpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 0;
            if (row == 1)
                board[row - 1, col - 1] = -2;
            else
                board[row - 1, col - 1] = -1;
        }
        #endregion
        /*the region witch undo's ur previos moves,note that the row and col u send to the functions
        is the row and col that you moved from and not moved to*/
        #region
        /// <summary>
        /// modifies your board witch you send to undo your previos move
        /// in this case it undo's ur up right move
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place that your piece moved from</param>
        /// <param name="col">the col place that your piece moved from</param>
        static public void UndoMovePlus1UpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 1;
            board[row + 1, col - 1] = 0;
        }
        /// <summary>
        /// modifies your board witch you send to undo your previos move
        /// in this case it undo's ur up left move
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place that your piece moved from</param>
        /// <param name="col">the col place that your piece moved from</param>
        static public void UndoMovePlus1UpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = 1;
            board[row + 1, col + 1] = 0;
        }
        /// <summary>
        /// modifies your board witch you send to undo your previos move
        /// in this case it undo's ur up right move
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place that your piece moved from</param>
        /// <param name="col">the col place that your piece moved from</param>
        static public void UndoMoveMinus1UpRight(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = -1;
            board[row - 1, col + 1] = 0;
        }
        /// <summary>
        /// modifies your board witch you send to undo your previos move
        /// in this case it undo's ur up left move
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place that your piece moved from</param>
        /// <param name="col">the col place that your piece moved from</param>
        static public void UndoMoveMinus1UpLeft(sbyte[,] board, sbyte row, sbyte col)
        {
            board[row, col] = -1;
            board[row - 1, col - 1] = 0;
        }
        #endregion
        /*the region witch has functions that return the number of possible movements for 2 and -2
        these functions are part boolean functions because that if the function returns 0 possible movements
        then the piece can not move*/
        #region
        /// <summary>
        /// if the function returns 0 it means that your piece can not move up right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of up right moves that you can do with your piece</returns>
        static public byte AmoutOfPlus2UpRightMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 7 && col != 0)
                {
                    if (board[++row, --col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move up left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of up left moves that you can do with your piece</returns>
        static public byte AmoutOfPlus2UpLeftMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 7 && col != 7)
                {
                    if (board[++row, ++col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move down right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of down right moves that you can do with your piece</returns>
        static public byte AmoutOfPlus2DownRightMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 0 && col != 7)
                {
                    if (board[--row, ++col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move down left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of down left moves that you can do with your piece</returns>
        static public byte AmoutOfPlus2DownLeftMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 0 && col != 0)
                {
                    if (board[--row, --col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move up right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of up right moves that you can do with your piece</returns>
        static public byte AmoutOfMinus2UpRightMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 0 && col != 7)
                {
                    if (board[--row, ++col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move up left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of up left moves that you can do with your piece</returns>
        static public byte AmoutOfMinus2UpLeftMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 0 && col != 0)
                {
                    if (board[--row, --col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move down right
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of down right moves that you can do with your piece</returns>
        static public byte AmoutOfMinus2DownRightMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 7 && col != 0)
                {
                    if (board[++row, --col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        /// <summary>
        /// if the function returns 0 it means that your piece can not move down left
        /// </summary>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="row">the row of your piece</param>
        /// <param name="col">the col of your piece</param>
        /// <returns>returns the amount of down left moves that you can do with your piece</returns>
        static public byte AmoutOfMinus2DownLeftMoves(sbyte[,] board, sbyte row, sbyte col)
        {
            byte counter = 0;
            bool canMove = true;
            while (canMove)
            {
                if (row != 7 && col != 7)
                {
                    if (board[++row, ++col] == 0)
                    {
                        counter++;
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }
            }
            return counter;
        }
        #endregion
        /*this region has plenty of functions that check if u can eat, some are unspecific while
        are more specific*/
        #region
        /// <summary>
        /// A function that checks if a white piece can eat
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <returns>returns true if your piece can eat and false if it can't</returns>
        static public bool CanAWhitePieceEat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (board[row, col] == 1)
                return CanPlus1Eat(board, ref row, ref col);
            if (board[row, col] == 2)
                return CanPlus2Eat(board, ref row, ref col);
            return false;
        }
        /// <summary>
        /// A function that checks if a Black piece can eat
        /// </summary>
        /// <param name="board">the board witch you are currently working on</param>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <returns>returns true if your piece can eat and false if it can't</returns>
        static public bool CanABlackPieceEat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (board[row, col] == -1)
                return CanMinus1Eat(board, ref row, ref col);
            if (board[row, col] == -2)
                return CanMinus2Eat(board, ref row, ref col);
            return false;
        }
        static public bool CanPlus1Eat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (CanPlus1EatUpRight(board, ref row, ref col))
                return true;
            if (CanPlus1EatUpLeft(board, ref row, ref col))
                return true;
            if (CanPlus1EatDownRight(board, ref row, ref col))
                return true;
            if (CanPlus1EatDownLeft(board, ref row, ref col))
                return true;
            return false;
        }
        static public bool CanPlus1EatUpRight(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row < 6 && col > 1)
                if (board[row + 1, col - 1] == -1 || board[row + 1, col - 1] == -2)
                    if (board[row + 2, col - 2] == 0)
                        return true;
            return false;
        }
        static public bool CanPlus1EatUpLeft(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row < 6 && col < 6)
                if (board[row + 1, col + 1] == -1 || board[row + 1, col + 1] == -2)
                    if (board[row + 2, col + 2] == 0)
                        return true;
            return false;
        }
        static public bool CanPlus1EatDownRight(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row > 1 && col < 6)
                if (board[row - 1, col + 1] == -1 || board[row - 1, col + 1] == -2)
                    if (board[row - 2, col + 2] == 0)
                        return true;
            return false;
        }
        static public bool CanPlus1EatDownLeft(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row >1 && col > 1)
                if (board[row - 1, col - 1] == -1 || board[row - 1, col - 1] == -2)
                    if (board[row - 2, col - 2] == 0)
                        return true;
            return false;
        }
        static public bool CanPlus2Eat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (CanPlus2EatUpRight(board, row, col))
                return true;
            if (CanPlus2EatUpLeft(board, row, col))
                return true;
            if (CanPlus2EatDownRight(board, row, col))
                return true;
            if (CanPlus2EatDownLeft(board, row, col))
                return true;
            return false;
        }
        static public bool CanPlus2EatUpRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow < 6 && copyCol > 1)
            {
                bool playerInFront = false;
                while (copyRow != 7 && copyCol != 0)
                {
                    copyRow++;
                    copyCol--;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanPlus2EatUpLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow < 6 && copyCol < 6) 
            {
                bool playerInFront = false;
                while (copyRow != 7 && copyCol != 7)
                {
                    copyRow++;
                    copyCol++;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanPlus2EatDownRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow > 1 && copyCol < 6)
            {
                bool playerInFront = false;
                while (copyRow != 0 && copyCol != 7)
                {
                    copyRow--;
                    copyCol++;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanPlus2EatDownLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow > 1 && copyCol > 1)
            {
                bool playerInFront = false;
                while (copyRow != 0 && copyCol != 0)
                {
                    copyRow--;
                    copyCol--;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanMinus1Eat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (CanMinus1EatUpRight(board, ref row, ref col))
                return true;
            if (CanMinus1EatUpLeft(board, ref row, ref col))
                return true;
            if (CanMinus1EatDownRight(board, ref row, ref col))
                return true;
            if (CanMinus1EatDownLeft(board, ref row, ref col))
                return true;
            return false;
        }
        static public bool CanMinus1EatUpRight(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row > 1 && col < 6)
                if (board[row - 1, col + 1] == 1 || board[row - 1, col + 1] == 2)
                    if (board[row - 2, col + 2] == 0)
                        return true;
            return false;
        }
        static public bool CanMinus1EatUpLeft(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row > 1 && col > 1)
                if (board[row - 1, col - 1] == 1 || board[row - 1, col - 1] == 2)
                    if (board[row - 2, col - 2] == 0)
                        return true;
            return false;
        }
        static public bool CanMinus1EatDownRight(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row < 6 && col > 1)
                if (board[row + 1, col - 1] == 1 || board[row + 1, col - 1] == 2)
                    if (board[row + 2, col - 2] == 0)
                        return true;
            return false;
        }
        static public bool CanMinus1EatDownLeft(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (row < 6 && col < 6)
                if (board[row + 1, col + 1] == 1 || board[row + 1, col + 1] == 2)
                    if (board[row + 2, col + 2] == 0)
                        return true;
            return false;
        }
        static public bool CanMinus2Eat(sbyte[,] board, ref sbyte row, ref sbyte col)
        {
            if (CanMinus2EatUpRight(board, row, col))
                return true;
            if (CanMinus2EatUpLeft(board, row, col))
                return true;
            if (CanMinus2EatDownRight(board, row, col))
                return true;
            if (CanMinus2EatDownLeft(board, row, col))
                return true;
            return false;
        }
        static public bool CanMinus2EatUpRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow > 1 && copyCol < 6)
            {
                bool playerInFront = false;
                while (copyRow != 0 && copyCol != 7)
                {
                    copyRow--;
                    copyCol++;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanMinus2EatUpLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow > 1 && copyCol > 1)
            {
                bool playerInFront = false;
                while (copyRow != 0 && copyCol != 0)
                {
                    copyRow--;
                    copyCol--;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanMinus2EatDownRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow < 6 && copyCol > 1)
            {
                bool playerInFront = false;
                while (copyRow != 7 && copyCol != 0)
                {
                    copyRow++;
                    copyCol--;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanMinus2EatDownLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            //checks if u can eat up right
            if (copyRow < 6 && copyCol < 6)
            {
                bool playerInFront = false;
                while (copyRow != 7 && copyCol != 7)
                {
                    copyRow++;
                    copyCol++;
                    if (playerInFront)
                    {
                        if (board[copyRow, copyCol] == 0)
                            return true;
                        else
                            break;
                    }
                    if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                        playerInFront = true;
                    else if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2 || board[copyRow, copyCol] == 3)
                        break;
                }
            }
            return false;
        }
        static public bool CanAWhitePieceEatOnTheBoard(sbyte[,] board, out sbyte row, out sbyte col)
        {
            for (sbyte i = 0; i < 8; i++)
                for (sbyte j = 0; j < 8; j++)
                    if (board[i, j] == 1 || board[i, j] == 2)
                        if (Checkers3.CheckerPiece.CanAWhitePieceEat(board,ref i,ref j))
                        {
                            row = i;
                            col = j;
                            return true;
                        }
            row = 0;
            col = 0;
            return false;
        }
        static public bool CanABlackPieceEatOnTheBoard(sbyte[,] board, out sbyte row, out sbyte col)
        {
            for (sbyte i = 0; i < 8; i++)
                for (sbyte j = 0; j < 8; j++)
                    if (board[i, j] == -1 || board[i, j] == -2)
                        if (Checkers3.CheckerPiece.CanABlackPieceEat(board, ref i, ref j))
                        {
                            row = i;
                            col = j;
                            return true;
                        }
            row = 0;
            col = 0;
            return false;
        }
        #endregion
        /*this region has functions tha eat witch type 1 and -1 pieces and functions that undo
         those eating moves*/
        #region
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(-1 or -2)</returns>
        static public sbyte Plus1EatUpRight(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row + 1, col - 1];
            board[row + 1, col - 1] = 3;
            if (row + 2 == 7)
                board[row + 2, col - 2] = 2;
            else 
                board[row + 2, col - 2] = 1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoPlus1EatUpRight(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = 1;
            board[row + 1, col - 1] = enemy;
            board[row + 2, col - 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(-1 or -2)</returns>
        static public sbyte Plus1EatUpLeft(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row + 1, col + 1];
            board[row + 1, col + 1] = 3;
            if (row + 2 == 7)
                board[row + 2, col + 2] = 2;
            else
                board[row + 2, col + 2] = 1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoPlus1EatUpLeft(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = 1;
            board[row + 1, col + 1] = enemy;
            board[row + 2, col + 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(-1 or -2)</returns>
        static public sbyte Plus1EatDownRight(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row - 1, col + 1];
            board[row - 1, col + 1] = 3;
            board[row - 2, col + 2] = 1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoPlus1EatDownRight(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = 1;
            board[row - 1, col + 1] = enemy;
            board[row - 2, col + 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(-1 or -2)</returns>
        static public sbyte Plus1EatDownLeft(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row - 1, col - 1];
            board[row - 1, col - 1] = 3;
            board[row - 2, col - 2] = 1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoPlus1EatDownLeft(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = 1;
            board[row - 1, col - 1] = enemy;
            board[row - 2, col - 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(1 or 2)</returns>
        static public sbyte Minus1EatUpRight(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row - 1, col + 1];
            board[row - 1, col + 1] = 3;
            if (row - 2 == 0)
                board[row - 2, col + 2] = -2;
            else
                board[row - 2, col + 2] = -1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoMinus1EatUpRight(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = -1;
            board[row - 1, col + 1] = enemy;
            board[row - 2, col + 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(1 or 2)</returns>
        static public sbyte Minus1EatUpLeft(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row - 1, col - 1];
            board[row - 1, col - 1] = 3;
            if (row - 2 == 0)
                board[row - 2, col - 2] = -2;
            else
                board[row - 2, col - 2] = -1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoMinus1EatUpLeft(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = -1;
            board[row - 1, col - 1] = enemy;
            board[row - 2, col - 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(1 or 2)</returns>
        static public sbyte Minus1EatDownRight(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row + 1, col - 1];
            board[row + 1, col - 1] = 3;
            board[row + 2, col - 2] = -1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoMinus1EatDownRight(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = -1;
            board[row + 1, col - 1] = enemy;
            board[row + 2, col - 2] = 0;
        }
        /// <summary>
        /// this function modifies your board
        /// </summary>
        /// <param name="row">the row place of your piece</param>
        /// <param name="col">the col place of your piece</param>
        /// <param name="board">the current board your working on</param>
        /// <returns>returns the number type of enemy u ate(1 or 2)</returns>
        static public sbyte Minus1EatDownLeft(sbyte row, sbyte col, sbyte[,] board)
        {
            board[row, col] = 0;
            sbyte enemy = board[row + 1, col + 1];
            board[row + 1, col + 1] = 3;
            board[row + 2, col + 2] = -1;
            return enemy;
        }
        /// <summary>
        /// undos your previos eating move
        /// </summary>
        /// <param name="row">the row place that your piece ate from</param>
        /// <param name="col">the col place that your piece ate from</param>
        /// <param name="board">the current board your working on</param>
        /// <param name="enemy">recieves the enemy piece type witch
        /// u ate with ur previos eating function</param>
        static public void UndoMinus1EatDownLeft(sbyte row, sbyte col, sbyte[,] board, sbyte enemy)
        {
            board[row, col] = -1;
            board[row + 1, col + 1] = enemy;
            board[row + 2, col + 2] = 0;
        }
        #endregion
        //this region has a lot of queen eating move funtions
        #region
        /// <summary>
        /// make sure that you used the CanPlus1EatUpRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Plus2EatUpRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 7 && copyCol != 0)
            {
                copyRow++;
                copyCol--;
                if (playerInFront)
                {
                    while (copyRow != 8 && copyCol != -1 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = 2;
                        if (CanAWhitePieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow++;
                        copyCol--;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanPlus1EatDownRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Plus2EatUpLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 7 && copyCol != 7)
            {
                copyRow++;
                copyCol++;
                if (playerInFront)
                {
                    while (copyRow != 8 && copyCol != 8 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = 2;
                        if (CanAWhitePieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow++;
                        copyCol++;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanPlus1EatDownRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Plus2EatDownRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 0 && copyCol != 7)
            {
                copyRow--;
                copyCol++;
                if (playerInFront)
                {
                    while (copyRow != -1 && copyCol != 8 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = 2;
                        if (CanAWhitePieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow--;
                        copyCol++;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanPlus1EatDownLeft() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Plus2EatDownLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 0 && copyCol != 0)
            {
                copyRow--;
                copyCol--;
                if (playerInFront)
                {
                    while (copyRow != -1 && copyCol != -1 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = 2;
                        if (CanAWhitePieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow--;
                        copyCol--;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == -1 || board[copyRow, copyCol] == -2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanMinus1EatUpRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Minus2EatUpRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 0 && copyCol != 7)
            {
                copyRow--;
                copyCol++;
                if (playerInFront)
                {
                    while (copyRow != -1 && copyCol != 8 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = -2;
                        if (CanABlackPieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow--;
                        copyCol++;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanMinus1EatDownRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Minus2EatUpLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 0 && copyCol != 0)
            {
                copyRow--;
                copyCol--;
                if (playerInFront)
                {
                    while (copyRow != -1 && copyCol != -1 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = -2;
                        if (CanABlackPieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow--;
                        copyCol--;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanMinus1EatDownRight() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Minus2EatDownRight(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 7 && copyCol != 0)
            {
                copyRow++;
                copyCol--;
                if (playerInFront)
                {
                    while (copyRow != 8 && copyCol != -1 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = -2;
                        if (CanABlackPieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow++;
                        copyCol--;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        /// <summary>
        /// make sure that you used the CanMinus1EatDownLeft() function before you call this function
        /// </summary>
        /// <param name="board">current board your working on</param>
        /// <param name="copyRow">the row place of ur piece u want to eat with</param>
        /// <param name="copyCol">the col place of ur piece u want to eat with</param>        
        /// <returns>returns a list of eating options in one eat move boards with ur
        /// current piece and the queen u ate with is now a 4 on the boards</returns>
        static public List<sbyte[,]> Minus2EatDownLeft(sbyte[,] board, sbyte copyRow, sbyte copyCol)
        {
            List<sbyte[,]> list = new List<sbyte[,]>();
            List<sbyte[,]> accurateList = new List<sbyte[,]>();
            bool playerInFront = false;
            sbyte originalCopyRow = copyRow;
            sbyte originalCopyCol = copyCol;
            sbyte enemyRow = 0, enemyCol = 0;
            while (copyRow != 7 && copyCol != 7)
            {
                copyRow++;
                copyCol++;
                if (playerInFront)
                {
                    while (copyRow != 8 && copyCol != 8 && board[copyRow, copyCol] == 0)
                    {
                        sbyte[,] copyBoard = Program.CopyBoard(board);
                        copyBoard[originalCopyRow, originalCopyCol] = 0;
                        copyBoard[enemyRow, enemyCol] = 3;
                        copyBoard[copyRow, copyCol] = -2;
                        if (CanABlackPieceEat(copyBoard, ref copyRow, ref copyCol))
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            accurateList.Add(copyBoard);
                        }
                        else
                        {
                            copyBoard[copyRow, copyCol] = 4;
                            list.Add(copyBoard);
                        }
                        copyRow++;
                        copyCol++;
                    }
                    if (accurateList.Count == 0)
                        return list;
                    return accurateList;
                }
                if (board[copyRow, copyCol] == 1 || board[copyRow, copyCol] == 2)
                {
                    enemyRow = copyRow;
                    enemyCol = copyCol;
                    playerInFront = true;
                }
            }
            //if u got here it probablly means that you didn't use the CanType1EatUpRight() function before you called this function
            return null;
        }
        #endregion
        //a complicated eating function
        /// <summary>
        /// modifies your list to have boards of eating options
        /// </summary>
        /// <param name="row">the row place of your eating piece</param>
        /// <param name="col">the col place of your eating piece</param>
        /// <param name="board">the board you are currently working on</param>
        /// <param name="boards">the list witch will contain boards of eating options</param>
        static public void Eat(sbyte row, sbyte col,sbyte[,] board, List<sbyte[,]> boards)
        {
            if (board[row, col] == 1)
            {
                if (CanPlus1EatUpRight(board, ref row, ref col))
                {
                    sbyte enemy = Plus1EatUpRight(row, col, board);
                    Eat2((sbyte)(row + 2),(sbyte) (col -2), board, boards);
                    UndoPlus1EatUpRight(row, col, board, enemy);
                }
                if (CanPlus1EatUpLeft(board, ref row, ref col))
                {
                    sbyte enemy = Plus1EatUpLeft(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col + 2), board, boards);
                    UndoPlus1EatUpLeft(row, col, board, enemy);
                }
                if (CanPlus1EatDownRight(board, ref row, ref col))
                {
                    sbyte enemy = Plus1EatDownRight(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col + 2), board, boards);
                    UndoPlus1EatDownRight(row, col, board, enemy);
                }
                if (CanPlus1EatDownLeft(board, ref row, ref col))
                {
                    sbyte enemy = Plus1EatDownLeft(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col - 2), board, boards);
                    UndoPlus1EatDownLeft(row, col, board, enemy);
                }
            }
            else if (board[row, col] == 2)
            {
                if (CanPlus2EatUpRight(board, row, col))
                {
                    List<sbyte[,]> boardList = Plus2EatUpRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol--;
                        }
                    }
                }
                if (CanPlus2EatUpLeft(board, row, col))
                {
                    List<sbyte[,]> boardList = Plus2EatUpLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol++;
                        }
                    }
                }
                if (CanPlus2EatDownRight(board, row, col))
                {
                    List<sbyte[,]> boardList = Plus2EatDownRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol++;
                        }
                    }
                }
                if (CanPlus2EatDownLeft(board, row, col))
                {
                    List<sbyte[,]> boardList = Plus2EatDownLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol--;
                        }
                    }
                }
            }
            else if (board[row, col] == -1)
            {
                if (CanMinus1EatUpRight(board, ref row, ref col))
                {
                    sbyte enemy = Minus1EatUpRight(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col + 2), board, boards);
                    UndoMinus1EatUpRight(row, col, board, enemy);
                }
                if (CanMinus1EatUpLeft(board, ref row, ref col))
                {
                    sbyte enemy = Minus1EatUpLeft(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col - 2), board, boards);
                    UndoMinus1EatUpLeft(row, col, board, enemy);
                }
                if (CanMinus1EatDownRight(board, ref row, ref col))
                {
                    sbyte enemy = Minus1EatDownRight(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col - 2), board, boards);
                    UndoMinus1EatDownRight(row, col, board, enemy);
                }
                if (CanMinus1EatDownLeft(board, ref row, ref col))
                {
                    sbyte enemy = Minus1EatDownLeft(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col + 2), board, boards);
                    UndoMinus1EatDownLeft(row, col, board, enemy);
                }
            }
            else if (board[row, col] == -2)
            {
                if (CanMinus2EatUpRight(board, row, col))
                {
                    List<sbyte[,]> boardList = Minus2EatUpRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol++;
                        }
                    }
                }
                if (CanMinus2EatUpLeft(board, row, col))
                {
                    List<sbyte[,]> boardList = Minus2EatUpLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol--;
                        }
                    }
                }
                if (CanMinus2EatDownRight(board, row, col))
                {
                    List<sbyte[,]> boardList = Minus2EatDownRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol--;
                        }
                    }
                }
                if (CanMinus2EatDownLeft(board, row, col))
                {
                    List<sbyte[,]> boardList = Minus2EatDownLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol++;
                        }
                    }
                }
            }
        }
        static public void Eat2(sbyte row, sbyte col, sbyte[,] board, List<sbyte[,]> boards)
        {
            bool check = true;
            if (board[row, col] == 1)
            {
                if (CanPlus1EatUpRight(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Plus1EatUpRight(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col - 2), board, boards);
                    UndoPlus1EatUpRight(row, col, board, enemy);
                }
                if (CanPlus1EatUpLeft(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Plus1EatUpLeft(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col + 2), board, boards);
                    UndoPlus1EatUpLeft(row, col, board, enemy);
                }
                if (CanPlus1EatDownRight(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Plus1EatDownRight(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col + 2), board, boards);
                    UndoPlus1EatDownRight(row, col, board, enemy);
                }
                if (CanPlus1EatDownLeft(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Plus1EatDownLeft(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col - 2), board, boards);
                    UndoPlus1EatDownLeft(row, col, board, enemy);
                }
                if (check)
                {
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            if (board[i, j] == 3)
                                board[i, j] = 0;
                    boards.Add(Program.CopyBoard(board));
                }
            }
            else if (board[row, col] == 2)
            {
                if (CanPlus2EatUpRight(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Plus2EatUpRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol--;
                        }
                    }
                }
                if (CanPlus2EatUpLeft(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Plus2EatUpLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol++;
                        }
                    }
                }
                if (CanPlus2EatDownRight(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Plus2EatDownRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol++;
                        }
                    }
                }
                if (CanPlus2EatDownLeft(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Plus2EatDownLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = 2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol--;
                        }
                    }
                }
                if (check)
                {
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            if (board[i, j] == 3)
                                board[i, j] = 0;
                    boards.Add(Program.CopyBoard(board));
                }
            }
            else if (board[row, col] == -1)
            {
                if (CanMinus1EatUpRight(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Minus1EatUpRight(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col + 2), board, boards);
                    UndoMinus1EatUpRight(row, col, board, enemy);
                }
                if (CanMinus1EatUpLeft(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Minus1EatUpLeft(row, col, board);
                    Eat2((sbyte)(row - 2), (sbyte)(col - 2), board, boards);
                    UndoMinus1EatUpLeft(row, col, board, enemy);
                }
                if (CanMinus1EatDownRight(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Minus1EatDownRight(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col - 2), board, boards);
                    UndoMinus1EatDownRight(row, col, board, enemy);
                }
                if (CanMinus1EatDownLeft(board, ref row, ref col))
                {
                    check = false;
                    sbyte enemy = Minus1EatDownLeft(row, col, board);
                    Eat2((sbyte)(row + 2), (sbyte)(col + 2), board, boards);
                    UndoMinus1EatDownLeft(row, col, board, enemy);
                }
                if (check)
                {
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            if (board[i, j] == 3)
                                board[i, j] = 0;
                    boards.Add(Program.CopyBoard(board));
                }
            }
            else if (board[row, col] == -2)
            {
                if (CanMinus2EatUpRight(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Minus2EatUpRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol++;
                        }
                    }
                }
                if (CanMinus2EatUpLeft(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Minus2EatUpLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row - 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow--;
                            copyCol--;
                        }
                    }
                }
                if (CanMinus2EatDownRight(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Minus2EatDownRight(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col - 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol--;
                        }
                    }
                }
                if (CanMinus2EatDownLeft(board, row, col))
                {
                    check = false;
                    List<sbyte[,]> boardList = Minus2EatDownLeft(board, row, col);
                    foreach (sbyte[,] newBoard in boardList)
                    {
                        bool spotFound = false;
                        sbyte copyRow = (sbyte)(row + 2), copyCol = (sbyte)(col + 2);
                        while (!spotFound)
                        {
                            if (newBoard[copyRow, copyCol] == 4)
                            {
                                newBoard[copyRow, copyCol] = -2;
                                Eat2(copyRow, copyCol, newBoard, boards);
                                break;
                            }
                            copyRow++;
                            copyCol++;
                        }
                    }
                }
                if (check)
                {
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            if (board[i, j] == 3)
                                board[i, j] = 0;
                    boards.Add(Program.CopyBoard(board));
                }
            }
        }
    }
}
